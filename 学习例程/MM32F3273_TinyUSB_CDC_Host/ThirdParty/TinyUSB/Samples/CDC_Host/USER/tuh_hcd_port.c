/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "mm32_device.h"
#include "hal_conf.h"
#include "hal_common.h"

#include "hal_usb.h"
//#include "reg_usb_otg_fs.h"
#include "hal_usb_bdt.h"
#include "host/hcd.h"
#include "tusb.h"
#include "stdlib.h"

extern u32 SystemCoreClock ;
/* USB. */
#define BOARD_USB_PORT               USB_OTG_FS
#define BOARD_USB_IRQn               USB_FS_IRQn
#define BOARD_USB_IRQHandler         OTG_FS_IRQHandler    
#define BOARD_USB_SOFTHRESHOLD       255u

/*
 * Common.
 */

/* the marco of conversion between dev_addr, ep_addr & dev_ep_addr. */
#define TUH_HCD_PORT_GET_DEV_ADDR(dev_ep_addr)         (dev_ep_addr >> 8u) /* dev_ep_addr -> dev_addr. */
#define TUH_HCD_PORT_GET_EP_ADDR(dev_ep_addr)          (dev_ep_addr & 0xFF) /* dev_ep_addr -> ep_addr. */
#define TUH_HCD_PORT_GET_DEV_EP_ADDR(dev_addr,ep_addr) ((dev_addr << 8u) | ep_addr) /* dev_addr + ep_addr -> dev_ep_addr. */
/* the marco of xfer task deque size. */
#define TUH_HCD_PORT_XFER_TASK_DEQUE_SIZE               (CFG_TUH_ENDPOINT_MAX * 2u)
/* the max number of support endpoint. */
#define TUH_HCD_PORT_MAX_EP_NUM                         (CFG_TUH_ENDPOINT_MAX * 2u)
/* the timeout value that xfer data. */
#define TUH_HCD_PORT_XFER_TIMEOUT                       1000000u
/* the buf size of xfer data. */
#define TUH_HCD_PORT_XFER_BUF_SIZE                      64u
/* xfer data need to wait 100ms after bus reset. */
#define TUH_HCD_PORT_FIRST_XFER_DATA_CNT_DOWN           100u


/* xfer task deque node. */
typedef struct
{
    uint32_t  dev_ep_addr; /* record the dev_addr & ep_addr. */
    uint32_t  max_packet_size; /* record the endpoint max max packet size. */
    uint8_t * buf; /* the xfer data addr. */
    uint32_t  len; /* data size. */
    uint32_t  remaining; /* remaining data size. */
    USB_TokenPid_Type token; /* xfer token. */
    uint32_t  data_toggle; /* data0 or data1 that xfer tag. */
} xfer_task_node_t;

/* endpoint status. */
typedef struct
{
    uint32_t dev_ep_addr; /* the index of endpoint, record dev_addr & ep_addr. */
    uint32_t max_packet_size; /* record the max packet size that the endpoint supported. */
    uint32_t data_toggle; /* data toggle, the value is 0 or 1. */
} ep_status_t;

/* xfer task deque support. */
static xfer_task_node_t xfer_task_deque[TUH_HCD_PORT_XFER_TASK_DEQUE_SIZE] = {0u}; /* xfer task deque buf. */
static uint32_t xfer_task_head = 0u; /* record deque head. */
static uint32_t xfer_task_tail = 0u; /* record deque tail. */
static uint32_t xfer_task_cnt  = 0u; /* record xfer task num. */

/* endpoint status table. */
static ep_status_t ep_tbl[TUH_HCD_PORT_MAX_EP_NUM]; /* the table that record the ep_status. */
static uint32_t ep_count = 0u; /* record the how many endpoint status in ep_tbl[]. */

/* usb buf descriptor table. */
__ALIGNED(512) static USB_BufDespTable_Type usb_bdt = {0u};

/* speed status. */
volatile static tusb_speed_t device_speed = TUSB_SPEED_FULL;

/* xfer_buf. */
__ALIGNED(4) static uint8_t usb_xfer_buf[TUH_HCD_PORT_XFER_BUF_SIZE] = {0u};

/* usb first xfer delay. */
volatile uint32_t usb_first_xfer_cnt = 0u;

/* atached. */
volatile bool usb_attached = false;

/*
 * deque func.
 */

/* get deque head node & delete the node in deque. */
bool xfer_task_pop_head(xfer_task_node_t * task)
{
    if (0u == xfer_task_cnt)
    {
        return false; /* no xfer_task. */
    }

    /* pop head: read head, head--, cnt--. */
    memcpy(task, &xfer_task_deque[xfer_task_head], sizeof(xfer_task_node_t)); /* read head. */
    if (xfer_task_head == 0u) /* head--. */
    {
        xfer_task_head = TUH_HCD_PORT_XFER_TASK_DEQUE_SIZE - 1u;
    }
    else
    {
        xfer_task_head--;
    }
    xfer_task_cnt--; /* cnt--. */

    return true;
}

/* put node in deque head. */
bool xfer_task_push_head(xfer_task_node_t * task)
{
    if (TUH_HCD_PORT_XFER_TASK_DEQUE_SIZE == xfer_task_cnt)
    {
        return false; /* queue full. */
    }

    /* push head: head++, write head, cnt++ */

    if (xfer_task_head == TUH_HCD_PORT_XFER_TASK_DEQUE_SIZE - 1u) /* head++. */
    {
        xfer_task_head = 0u;
    }
    else
    {
        xfer_task_head++;
    }
    memcpy(&xfer_task_deque[xfer_task_head], task, sizeof(xfer_task_node_t)); /* write tail. */
    xfer_task_cnt++;/* cnt++. */

    return true;
}

/* put node in deque tail. */
bool xfer_task_push_tail(xfer_task_node_t * task)
{
    if (TUH_HCD_PORT_XFER_TASK_DEQUE_SIZE == xfer_task_cnt)
    {
        return false; /* queue full. */
    }

    /* push tail: write tail, tail--, cnt++ */

    memcpy(&xfer_task_deque[xfer_task_tail], task, sizeof(xfer_task_node_t)); /* write tail. */
    if (xfer_task_tail == 0u) /* head++. */
    {
        xfer_task_tail = TUH_HCD_PORT_XFER_TASK_DEQUE_SIZE - 1u;
    }
    else
    {
        xfer_task_tail--;
    }
    xfer_task_cnt++;/* cnt++. */

    return true;
}

/* reset the deque, delete all node. */
void xfer_task_reset(void)
{
    xfer_task_head = 0u;
    xfer_task_tail = 0u;
    xfer_task_cnt  = 0u;
}

/*
 * endpoint database.
 */

/* get endpoint status. */
ep_status_t * ep_get_status(uint32_t dev_ep_addr)
{
    ep_status_t * ep_status = NULL;
    for(uint32_t i = 0u; i < ep_count; i++)
    {
        if(dev_ep_addr == ep_tbl[i].dev_ep_addr)
        {
            ep_status = &ep_tbl[i];
            break;
        }
    }
    return ep_status;
}

/* add new or modify endpoint status. */
bool ep_set_status(ep_status_t * status)
{
    ep_status_t * ep_status = ep_get_status(status->dev_ep_addr);
    if (NULL == ep_status)
    {
        if (ep_count == TUH_HCD_PORT_MAX_EP_NUM)
        {
            return false;
        }
        ep_status = &ep_tbl[ep_count];
        ep_count++;
    }
    memcpy(ep_status, status, sizeof(ep_status_t));
    return true;
}

/* clear all endpoint status. */
void ep_reset(void)
{
    ep_count = 0u;
}

/*
 * process.
 */

void xfer_start(xfer_task_node_t * task)
{
    USB_BufDesp_Type * bd = NULL;

    /* set endpoint status & select bd. */
    switch(task->token)
    {
        case USB_TokenPid_IN:
            USB_EnableEndPoint(BOARD_USB_PORT, 0u, USB_EndPointMode_Bulk, true);
            bd = &usb_bdt.Table[0u][0u][0u];
            break;
        case USB_TokenPid_OUT:
            USB_EnableEndPoint(BOARD_USB_PORT, 0u, USB_EndPointMode_Bulk, true);
            bd = &usb_bdt.Table[0u][1u][0u];
            break;
        case USB_TokenPid_SETUP:
            USB_EnableEndPoint(BOARD_USB_PORT, 0u, USB_EndPointMode_Control, true);
            bd = &usb_bdt.Table[0u][1u][0u];
            break;
        default:
            break;
    }

    /* calc xfer size. */
    uint32_t xfer_size = task->remaining;
    if (xfer_size > task->max_packet_size)
    {
        xfer_size = task->max_packet_size;
    }

    /* calc xfer buf start. */
    uint8_t * xfer_buf = task->buf + (task->len - task->remaining);
    uint32_t  ep_addr = TUH_HCD_PORT_GET_EP_ADDR(task->dev_ep_addr);

    /* xfer data  */
    if (task->token == USB_TokenPid_OUT || task->token == USB_TokenPid_SETUP)
    {
        memcpy(usb_xfer_buf, xfer_buf, xfer_size);
    }

    /* ready to xfer. */
    USB_SetDeviceAddr(BOARD_USB_PORT, TUH_HCD_PORT_GET_DEV_ADDR(task->dev_ep_addr));
    USB_BufDesp_Reset(bd);
    USB_BufDesp_Xfer(bd, task->data_toggle, usb_xfer_buf, xfer_size);
    for(uint32_t i = 0u; i < TUH_HCD_PORT_XFER_TIMEOUT; i++)
    {
        if (USB_SetToken(BOARD_USB_PORT, tu_edpt_number(ep_addr), task->token))
        {
            break;
        }
    }
}

void process_softok(void)
{
    xfer_task_node_t task;
    if (xfer_task_pop_head(&task)) /* have xfer task. */
    {
        if (usb_first_xfer_cnt > 0) /* xfer first paxket need to wait a moment. */
        {
            usb_first_xfer_cnt--;
            xfer_task_push_head(&task);
            return;
        }
        xfer_start(&task);
        xfer_task_push_head(&task);
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_SOFTOK, false);
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_TOKENDONE, true);
    }
}

/* process when token xfer done. */
void process_token_done(void)
{
    xfer_task_node_t task;
    if (!xfer_task_pop_head(&task)) /* get xfer task. */
    {
        return; /* error. */
    }

    USB_BufDesp_Type * bd = USB_GetBufDesp(BOARD_USB_PORT); /* get xfer bd. */

    if (USB_BufDesp_GetTokenPid(bd) == USB_TokenPid_NAK) /* nak, do next xfer task. */
    {
        xfer_task_push_tail(&task);
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_TOKENDONE, false);
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_SOFTOK, true);
        USB_ClearInterruptStatus(BOARD_USB_PORT, USB_INT_SOFTOK);
        return;
    }

    if (false == usb_attached) /* attached test. */
    {
        if (task.token == USB_TokenPid_SETUP) /* test SETUP packet. */
        {
            task.data_toggle = 1u;
            task.dev_ep_addr = 0x80;
            task.token = USB_TokenPid_IN;
            xfer_task_push_tail(&task);
        }
        else if (task.token == USB_TokenPid_IN) /* test IN packet. */
        {
            task.data_toggle = 1u;
            task.len = 0u;
            task.remaining = 0u;
            task.dev_ep_addr = 0x00;
            task.token = USB_TokenPid_OUT;
            xfer_task_push_tail(&task);
        }
        else if (task.token == USB_TokenPid_OUT) /* test OUT packet. */
        {
            hcd_event_device_attach(BOARD_TUH_RHPORT, true);
            usb_attached = true;
        }
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_TOKENDONE, false);
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_SOFTOK, true);
        USB_ClearInterruptStatus(BOARD_USB_PORT, USB_INT_SOFTOK);
        return;
    }

    /* move xfer context. */
    if (task.token == USB_TokenPid_IN)
    {
        /* calc xfer size. */
        uint32_t xfer_size = task.remaining;
        if (xfer_size > task.max_packet_size)
        {
            xfer_size = task.max_packet_size;
        }

        /* calc xfer buf start. */
        uint8_t * xfer_buf = task.buf + (task.len - task.remaining);
        memcpy(xfer_buf, usb_xfer_buf, xfer_size);
    }

    if (task.remaining > task.max_packet_size) /* have remain, xfer next packet. */
    {
        task.remaining -= task.max_packet_size;
        task.data_toggle ^= 1u;
        xfer_start(&task);
        xfer_task_push_head(&task);
    }
    else /* xfer done. */
    {
        ep_status_t * ep = ep_get_status(task.dev_ep_addr);
        ep->data_toggle = task.data_toggle ^= 1u;
        ep_set_status(ep); /* save ep status. */
        /* send xfer done event. */
        hcd_event_xfer_complete(TUH_HCD_PORT_GET_DEV_ADDR(task.dev_ep_addr),
                    TUH_HCD_PORT_GET_EP_ADDR(task.dev_ep_addr),
                    task.len,
                    XFER_RESULT_SUCCESS, true);
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_TOKENDONE, false);
        USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_SOFTOK, true);
        USB_ClearInterruptStatus(BOARD_USB_PORT, USB_INT_SOFTOK);
    }
}

void process_attach(void)
{
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_ATTACH, false);
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_SOFTOK | USB_INT_RESET, true);
    USB_ClearInterruptStatus(USB_OTG_FS, USB_INT_TOKENDONE | USB_INT_SOFTOK | USB_INT_RESET | USB_INT_ATTACH);

    xfer_task_reset();
    ep_reset();

    /* get speed. */
    if (USB_BusSignalStatus_J == USB_GetBusSignalStatus(BOARD_USB_PORT) ) /* full speed. */
    {
        USB_EnableLowSpeed(BOARD_USB_PORT, false);
        device_speed = TUSB_SPEED_FULL;
    }
    else /* low speed. */
    {
        USB_EnableLowSpeed(BOARD_USB_PORT, true);
        device_speed = TUSB_SPEED_LOW;
    }

    /* attach tast. */
    usb_first_xfer_cnt = TUH_HCD_PORT_FIRST_XFER_DATA_CNT_DOWN;
    usb_attached = false;
    /* bus reset signal. */
    USB_Enable(BOARD_USB_PORT, false);
    USB_EnableBusReset(BOARD_USB_PORT, true);
    for (uint32_t i = 0u; i < SystemCoreClock / 100u; i++)
    {
        __NOP();
    }
    USB_EnableBusReset(BOARD_USB_PORT, false);
    USB_Enable(BOARD_USB_PORT, true);

    /* build SETUP packet. */
    memset(usb_xfer_buf, 0u, 8u);
    usb_xfer_buf[0] = 0x80;
    usb_xfer_buf[1] = 0x06;
    usb_xfer_buf[3] = 0x01;
    usb_xfer_buf[6] = 0x08;

    /* build xfer task. */
    xfer_task_node_t task;
    task.buf = usb_xfer_buf;
    task.data_toggle = 0;
    task.dev_ep_addr = 0x00;
    task.len = 8u;
    task.max_packet_size = 8u;
    task.remaining = 8u;
    task.token = USB_TokenPid_SETUP;
    xfer_task_push_tail(&task);

    /* prepare to send packet. */
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_SOFTOK, true);
    USB_ClearInterruptStatus(BOARD_USB_PORT, USB_INT_SOFTOK);
}

void process_detach(void)
{
    usb_attached = false;
    xfer_task_reset();
    ep_reset();
    device_speed = TUSB_SPEED_FULL;
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_TOKENDONE | USB_INT_SOFTOK | USB_INT_RESET, false);
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_ATTACH, true); /* wait device attached. */
    USB_ClearInterruptStatus(USB_OTG_FS, USB_INT_TOKENDONE | USB_INT_SOFTOK | USB_INT_RESET | USB_INT_ATTACH);

    USB_Enable(BOARD_USB_PORT, false); /* stop send SOF token. */
    USB_SetDeviceAddr(BOARD_USB_PORT, 0x00); /* set usb addr is 0x00, to xfer data when device attached. */
    USB_EnableEndPoint(BOARD_USB_PORT, 0, USB_EndPointMode_NULL, false); /* disable ep0. */
    USB_EnableLowSpeed(BOARD_USB_PORT, false); /* disable low speed mode. */
    memset(&usb_bdt, 0, sizeof(usb_bdt));
    hcd_event_device_remove(BOARD_TUH_RHPORT, true);
}

/*
 * Controller API.
 */

/* Initialize controller to host mode. */
bool hcd_init(uint8_t rhport)
{
    (void)rhport;

    /* init usb host module. */
    USB_Host_Init_Type usb_init;
    usb_init.BufDespTable_Addr = (uint32_t)(&usb_bdt);
    usb_init.SofThreshold      = BOARD_USB_SOFTHRESHOLD;
    usb_init.NakRetry          = false;
    USB_InitHost(BOARD_USB_PORT, &usb_init);

    USB_EnableOddEvenReset(BOARD_USB_PORT, true); /* only use even buf desp, this example will not usb odd buf desp xfer data. */
    USB_SetDeviceAddr(BOARD_USB_PORT, 0x00); /* set usb addr is 0x00, to xfer data when device attached. */

    /* enable interrupt, but not use NVIC_EnableIRQ(). */
    NVIC_ClearPendingIRQ(BOARD_USB_IRQn);
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_ATTACH | USB_INT_ERROR, true);
    USB_EnableErrInterrupts(BOARD_USB_PORT, 0xFF, true);
    return true;
}

/* Enable USB interrupt. */
void hcd_int_enable (uint8_t rhport)
{
    (void)rhport;

    NVIC_EnableIRQ(BOARD_USB_IRQn);
}

/* Disable USB interrupt. */
void hcd_int_disable(uint8_t rhport)
{
    (void)rhport;

    NVIC_DisableIRQ(BOARD_USB_IRQn);
}

/* Get frame number (1ms). */
uint32_t hcd_frame_number(uint8_t rhport)
{
    (void)rhport;

    return USB_GetFrameNumber(BOARD_USB_PORT);
}

/*
 * Port API.
 */

/* Get the current connect status of roothub port. */
bool hcd_port_connect_status(uint8_t rhport)
{
    (void)rhport;

    uint32_t flag = USB_GetInterruptStatus(BOARD_USB_PORT);
    if (0 != (flag & USB_INT_ATTACH) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Reset USB bus on the port. */
void hcd_port_reset(uint8_t rhport)
{
    (void)rhport;

    ep_reset();
    xfer_task_reset();
    usb_first_xfer_cnt = TUH_HCD_PORT_FIRST_XFER_DATA_CNT_DOWN;
    USB_Enable(BOARD_USB_PORT, false);
    USB_EnableBusReset(BOARD_USB_PORT, true);

    for (uint32_t i = 0u; i < SystemCoreClock / 100u; i++)
    {
        __NOP();
    }

    USB_EnableBusReset(BOARD_USB_PORT, false);
    USB_Enable(BOARD_USB_PORT, true);
}

/* TODO implement later. */
void hcd_port_reset_end(uint8_t rhport)
{
    (void)rhport;
}

/* Get port link speed. */
tusb_speed_t hcd_port_speed_get(uint8_t rhport)
{
    (void)rhport;

    return device_speed;
}

/* HCD closes all opened endpoints belong to this device. */
void hcd_device_close(uint8_t rhport, uint8_t dev_addr)
{
    xfer_task_reset();
    ep_reset();
}

/*
 * Endpoints API.
 */

/* Open an endpoint. */
bool hcd_edpt_open(uint8_t rhport, uint8_t dev_addr, tusb_desc_endpoint_t const * ep_desc)
{
    (void)rhport;

    NVIC_DisableIRQ(BOARD_USB_IRQn);
    ep_status_t ep     = {0u};
    ep.max_packet_size = ep_desc->wMaxPacketSize;
    ep.dev_ep_addr     = TUH_HCD_PORT_GET_DEV_EP_ADDR(dev_addr, ep_desc->bEndpointAddress);

    if (tu_edpt_dir(ep_desc->bEndpointAddress) == TUSB_DIR_IN)
    {
        ep.data_toggle = 1u;
    }
    else
    {
        ep.data_toggle = 0u;
    }

    if (0u == ep_desc->bEndpointAddress)
    {
        ep.dev_ep_addr = TUH_HCD_PORT_GET_DEV_EP_ADDR(dev_addr, 0x00);
        ep_set_status(&ep);
        ep.dev_ep_addr = TUH_HCD_PORT_GET_DEV_EP_ADDR(dev_addr, 0x80);
        ep_set_status(&ep);
        return true;
    }
    else if (ep_set_status(&ep))
    {
        return true;
    }
    else
    {
        return false;
    }
    NVIC_EnableIRQ(BOARD_USB_IRQn);
}

/* Submit a transfer, when complete hcd_event_xfer_complete() must be invoked. */
bool hcd_edpt_xfer(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr, uint8_t * buffer, uint16_t buflen)
{
    (void)rhport;

    NVIC_DisableIRQ(BOARD_USB_IRQn);
    xfer_task_node_t task;
    task.dev_ep_addr = TUH_HCD_PORT_GET_DEV_EP_ADDR(dev_addr, ep_addr);
    task.buf      = (uint8_t *)buffer;
    if (tu_edpt_dir(ep_addr) == TUSB_DIR_IN)
    {
        task.token = USB_TokenPid_IN;
    }
    else
    {
        task.token = USB_TokenPid_OUT;
    }
    ep_status_t * ep = ep_get_status(task.dev_ep_addr);
    task.max_packet_size = ep->max_packet_size;
    task.data_toggle     = ep->data_toggle;
    task.len       = buflen;
    task.remaining = buflen;

    bool ret = false;
    if (xfer_task_push_tail(&task) )
    {
        ret = true;
    }
    NVIC_EnableIRQ(BOARD_USB_IRQn);
    return ret;
}
bool hcd_edpt_abort_xfer(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr) {
  (void) rhport;
  (void) dev_addr;
  (void) ep_addr;
  // TODO not implemented yet
  return false;
}
/* Submit a special transfer to send 8-byte Setup Packet, when complete hcd_event_xfer_complete() must be invoked. */
bool hcd_setup_send(uint8_t rhport, uint8_t dev_addr, uint8_t const setup_packet[8])
{
    (void)rhport;

    NVIC_DisableIRQ(BOARD_USB_IRQn);
    xfer_task_node_t task;
    task.dev_ep_addr = TUH_HCD_PORT_GET_DEV_EP_ADDR(dev_addr, 0u);
    task.max_packet_size = 8u;
    task.buf      = (uint8_t *)setup_packet;
    task.token    = USB_TokenPid_SETUP;
    task.data_toggle   = 0u;
    task.len      = 8u;
    task.remaining = 8u;

    bool ret = false;
    if (xfer_task_push_tail(&task) )
    {
        ret = true;
    }
    NVIC_EnableIRQ(BOARD_USB_IRQn);
    return ret;
}

/*
 * USB interrupt handler.
 */
void BOARD_USB_IRQHandler(void)
{
    uint32_t flag = USB_GetInterruptStatus(BOARD_USB_PORT);
    flag &= USB_GetEnabledInterrupts(BOARD_USB_PORT);

    /* device attached. */
    if (0u != (flag & USB_INT_ATTACH))
    {
        process_attach();
    }

    /* sof token, prepare to xfer packet. */
    if (0u != (flag & USB_INT_SOFTOK))
    {
        process_softok();
    }

    /* xfer a token done. */
    if (0u != (flag & USB_INT_TOKENDONE))
    {
        process_token_done();
    }

    /* device detached. */
    if (0u != (flag & USB_INT_RESET))
    {
        tuh_task(); /* clear all event. */
        process_detach(); /* do detache process. */
    }

    if (0u != (flag & USB_INT_ERROR))
    {
        tuh_task(); /* clear all event. */
        process_detach(); /* do detache process. */
        uint32_t err = USB_GetErrInterruptStatus(BOARD_USB_PORT);
        USB_ClearErrInterruptStatus(BOARD_USB_PORT, err); /* clear err interrut. */
    }

    USB_ClearInterruptStatus(BOARD_USB_PORT, flag);
}

/* EOF. */
