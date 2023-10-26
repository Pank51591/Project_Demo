/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_usb.h"

/* this func be used for register buf_desp mem addr. */
static void USB_SetBufDespTableAddr(USB_OTG_FS_TypeDef * USBx, uint32_t addr)
{
    USBx->BDT_PAGE_01 = USB_FSBDTPAGE1_BDTBA(addr >> 9u);
    USBx->BDT_PAGE_02 = USB_FSBDTPAGE2_BDTBA(addr >> 16u);
    USBx->BDT_PAGE_03 = USB_FSBDTPAGE3_BDTBA(addr >> 24u);
}

/* make USB module work on device mode. */
void USB_InitDevice(USB_OTG_FS_TypeDef * USBx, USB_Device_Init_Type * init)
{
    if ( NULL == init
        &&(uint32_t)(init->BufDespTable_Addr) % 512u != 0u)
    {
        return;
    }

    USB_SetBufDespTableAddr(USBx, init->BufDespTable_Addr); /* set bdt addr. */
    USBx->CTL &= OTG_FS_CTL_HOST_MODE_EN; /* disable host mode. */

    /* disable D+ & D- pulldown resistors. */
    USBx->OTG_CTRL &= ~OTG_FS_OTG_CTRL_OTG_EN;
}

/* make USB module work on host mode. */
void USB_InitHost(USB_OTG_FS_TypeDef * USBx, USB_Host_Init_Type * init)
{
    if ( NULL == init
        &&(uint32_t)(init->BufDespTable_Addr) % 512u != 0u)
    {
        return;
    }

    USB_SetBufDespTableAddr(USBx, init->BufDespTable_Addr); /* set bdt addr. */
    USBx->CTL |= OTG_FS_CTL_HOST_MODE_EN; /* enable host mode. */
    USBx->SOF_THLD = init->SofThreshold; /* set SOF threshold. */

    if (init->NakRetry)
    {
        USBx->EP_CTL[0] &= ~OTG_FS_EP_CTL_RETRY_DIS;
    }
    else
    {
        USBx->EP_CTL[0] |=  OTG_FS_EP_CTL_RETRY_DIS;
    }

    /* enable D+ & D- pulldown resistors. */
    USBx->OTG_CTRL |= OTG_FS_OTG_CTRL_DM_LOW | OTG_FS_OTG_CTRL_DP_LOW | OTG_FS_OTG_CTRL_OTG_EN;
}

void USB_EnableInterrupts(USB_OTG_FS_TypeDef * USBx, uint32_t interrupts, bool enable)
{
    if(enable)
    {
        USBx->INT_ENB |=  interrupts;
    }
    else
    {
        USBx->INT_ENB &= ~interrupts;
    }
}

uint32_t USB_GetEnabledInterrupts(USB_OTG_FS_TypeDef * USBx)
{
    return USBx->INT_ENB;
}

uint32_t USB_GetInterruptStatus(USB_OTG_FS_TypeDef * USBx)
{
    return USBx->INT_STAT;
}

void USB_ClearInterruptStatus(USB_OTG_FS_TypeDef * USBx, uint32_t interrupts)
{
    USBx->INT_STAT = interrupts;
}

void USB_EnableErrInterrupts(USB_OTG_FS_TypeDef * USBx, uint32_t interrupts, bool enable)
{
    if(enable)
    {
        USBx->ERR_ENB |=  interrupts;
    }
    else
    {
        USBx->ERR_ENB &= ~interrupts;
    }
}


uint32_t USB_GetEnabledErrInterrupts(USB_OTG_FS_TypeDef * USBx)
{
    return USBx->ERR_ENB;
}

uint32_t USB_GetErrInterruptStatus(USB_OTG_FS_TypeDef * USBx)
{
    return USBx->ERR_STAT;
}

void USB_ClearErrInterruptStatus(USB_OTG_FS_TypeDef * USBx, uint32_t interrupts)
{
    USBx->ERR_STAT = interrupts;
}

uint32_t USB_GetBufDespIndex(USB_OTG_FS_TypeDef * USBx)
{
    return (USBx->STAT)>>2;
}

/* enable usb, but in host mode, this func be use for ctrl send softok. */
void USB_Enable(USB_OTG_FS_TypeDef * USBx, bool enable)
{
    if(enable)
    {
        USBx->CTL |=  OTG_FS_CTL_USB_EN_SOF_EN;
    }
    else
    {
        USBx->CTL &= ~OTG_FS_CTL_USB_EN_SOF_EN;
    }
}

void USB_EnableOddEvenReset(USB_OTG_FS_TypeDef * USBx, bool enable)
{
    if(enable)
    {
        USBx->CTL |=  OTG_FS_CTL_ODD_RST;
    }
    else
    {
        USBx->CTL &= ~OTG_FS_CTL_ODD_RST;
    }
}

void USB_EnableResumeSignal(USB_OTG_FS_TypeDef * USBx, bool enable)
{
    if(enable)
    {
        USBx->CTL |=  OTG_FS_CTL_RESUME;
    }
    else
    {
        USBx->CTL &= ~OTG_FS_CTL_RESUME;
    }
}

void USB_EnableSuspend(USB_OTG_FS_TypeDef * USBx, bool enable)
{
    if(true == enable)
    {
        USBx->CTL |=  OTG_FS_CTL_TXDSUSPEND_TOKENBUSY;
    }
    else
    {
        USBx->CTL &= ~OTG_FS_CTL_TXDSUSPEND_TOKENBUSY;
    }

}

void USB_SetDeviceAddr(USB_OTG_FS_TypeDef * USBx, uint8_t addr)
{
    USBx->ADDR = ( (USBx->ADDR & ~OTG_FS_ADDR_ADDR)
                               | (addr & OTG_FS_ADDR_ADDR) )
                               ;
}

uint8_t USB_GetDeviceAddr(USB_OTG_FS_TypeDef * USBx)
{
    return USBx->ADDR & OTG_FS_ADDR_ADDR;
}

uint32_t USB_GetBufDespTableAddr(USB_OTG_FS_TypeDef * USBx)
{
    return (uint32_t)
        ( ( (USBx->BDT_PAGE_01 >> OTG_FS_BDT_PAGE_01_BDT_BA_15_9_Pos) << 9u )
        | ( (USBx->BDT_PAGE_02 >> OTG_FS_BDT_PAGE_02_BDT_BA_23_16_Pos) << 16u)
        | ( (USBx->BDT_PAGE_03 >> OTG_FS_BDT_PAGE_03_BDT_BA_31_24_Pos) << 24u)
        );
}

uint32_t USB_GetFrameNumber(USB_OTG_FS_TypeDef * USBx)
{
    return (USBx->FRM_NUML) | (USBx->FRM_NUML << 8u);
}

USB_BufDesp_Type * USB_GetBufDesp(USB_OTG_FS_TypeDef * USBx)
{
    USB_BufDespTable_Type * bdt = (USB_BufDespTable_Type *)USB_GetBufDespTableAddr(USBx);
    return &bdt->Index[USBx->STAT >> 2];
}

USB_TokenPid_Type USB_BufDesp_GetTokenPid(USB_BufDesp_Type * bd)
{
    return (USB_TokenPid_Type)bd->TOK_PID;
}

uint32_t USB_BufDesp_GetPacketAddr(USB_BufDesp_Type * bd)
{
    return bd->ADDR;
}

uint32_t USB_BufDesp_GetPacketSize(USB_BufDesp_Type * bd)
{
    return bd->BC;
}

void USB_BufDesp_Reset(USB_BufDesp_Type * bd)
{
    bd->HEAD = 0u;
}

bool USB_BufDesp_IsBusy(USB_BufDesp_Type * bd)
{
    if (1u == bd->OWN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool USB_BufDesp_Xfer(USB_BufDesp_Type * bd, uint32_t data_n, uint8_t * buffer, uint32_t len)
{
    if (1u == bd->OWN)
    {
        return false;
    }
    bd->ADDR = (uint32_t)buffer;
    bd->DATA = data_n;
    bd->BC   = len;
    bd->OWN  = 1u;
    return true;
}

uint32_t USB_GetEndPointIndex(USB_OTG_FS_TypeDef * USBx)
{
    return (USBx->STAT & OTG_FS_OTG_STAT_ENDP) >> OTG_FS_OTG_STAT_ENDP_Pos;
}

USB_Direction_Type USB_GetXferDirection(USB_OTG_FS_TypeDef * USBx)
{
    return (USB_Direction_Type)( (USBx->STAT & OTG_FS_STAT_TX) >> OTG_FS_STAT_TX_Pos);
}

USB_BufDesp_OddEven_Type USB_GetBufDespOddEven(USB_OTG_FS_TypeDef * USBx)
{
    return (USB_BufDesp_OddEven_Type)( (USBx->STAT & OTG_FS_STAT_ODD) >> OTG_FS_STAT_ODD_Pos );
}

void USB_EnableEndPoint(USB_OTG_FS_TypeDef * USBx, uint32_t index, USB_EndPointMode_Type mode, bool enable)
{
    if (false == enable)
    {
        USBx->EP_CTL[index] = (USBx->EP_CTL[index] & ~OTG_FS_EP_CTL_EP_TX_EN & ~OTG_FS_EP_CTL_EP_HSHK);
        USB_BufDespTable_Type * bdt = (USB_BufDespTable_Type * )USB_GetBufDespTableAddr(USBx);
        bdt->Table[index][0u][0u].HEAD = 0u;
        bdt->Table[index][0u][1u].HEAD = 0u;
        bdt->Table[index][1u][0u].HEAD = 0u;
        bdt->Table[index][1u][1u].HEAD = 0u;
        return;
    }
    if (USB_EndPointMode_Control == mode)
    {
        USBx->EP_CTL[index] = (USBx->EP_CTL[index] & ~OTG_FS_EP_CTL_EP_TX_EN & ~OTG_FS_EP_CTL_EP_HSHK)
                             |  USB_FSEPCTL_EPCTLDISEPRXENEPTXEN(3) | OTG_FS_EP_CTL_EP_HSHK;
    }
    else if (USB_EndPointMode_Bulk == mode)
    {
         USBx->EP_CTL[index] = (USBx->EP_CTL[index] & ~OTG_FS_EP_CTL_EP_TX_EN & ~OTG_FS_EP_CTL_EP_HSHK)
                             |  USB_FSEPCTL_EPCTLDISEPRXENEPTXEN(7u) | OTG_FS_EP_CTL_EP_HSHK;
    }
    else if (USB_EndPointMode_Interrupt == mode)
    {
         USBx->EP_CTL[index] = (USBx->EP_CTL[index] & ~OTG_FS_EP_CTL_EP_TX_EN & ~OTG_FS_EP_CTL_EP_HSHK)
                             |  USB_FSEPCTL_EPCTLDISEPRXENEPTXEN(7u) | OTG_FS_EP_CTL_EP_HSHK;
    }
    else if (USB_EndPointMode_Isochronous == mode)
    {
         USBx->EP_CTL[index] = (USBx->EP_CTL[index] & ~OTG_FS_EP_CTL_EP_TX_EN & ~OTG_FS_EP_CTL_EP_HSHK)
                             |  USB_FSEPCTL_EPCTLDISEPRXENEPTXEN(7u);
    }
}

void USB_EnableEndPointStall(USB_OTG_FS_TypeDef * USBx, uint32_t index, bool enable)
{
    USB_BufDespTable_Type * bdt = (USB_BufDespTable_Type * )USB_GetBufDespTableAddr(USBx);
    for (uint32_t i = 0; i < USB_BDT_EP_NUM; i++)
    {
        if (true == enable)
        {
            USBx->EP_CTL[i] |= OTG_FS_EP_CTL_EP_STALL;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_IN ].BDT_STALL = 1u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_OUT].BDT_STALL = 1u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_IN ].BDT_STALL = 1u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_OUT].BDT_STALL = 1u;
        }
        else
        {
            USBx->EP_CTL[i] &= ~OTG_FS_EP_CTL_EP_STALL;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_IN ].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_IN ].OWN       = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_OUT].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Odd ][USB_Direction_OUT].OWN       = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_IN ].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_IN ].OWN       = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_OUT].BDT_STALL = 0u;
            bdt->Table[i][USB_BufDesp_OddEven_Even][USB_Direction_OUT].OWN       = 0u;
        }
    }
}

uint32_t USB_GetEnabledEndPointStall(USB_OTG_FS_TypeDef * USBx)
{
    uint32_t status = 0u;
    for(uint32_t i = 0u; i < USB_BDT_EP_NUM; i++)
    {
        if (0 != (USBx->EP_CTL[i] & OTG_FS_EP_CTL_EP_STALL) )
        {
            status |= 1u << i;
        }
    }
    return status;
}

void USB_EnableLowSpeed(USB_OTG_FS_TypeDef * USBx, bool enable)
{
    if (enable)
    {
        USBx->ADDR |= OTG_FS_ADDR_LS_EN;
        USBx->EP_CTL[0] |= OTG_FS_EP_CTL_HOST_WO_HUB;
    }
    else
    {
        USBx->ADDR &= ~OTG_FS_ADDR_LS_EN;
        USBx->EP_CTL[0] &= ~OTG_FS_EP_CTL_HOST_WO_HUB;
    }
}

bool USB_SetToken(USB_OTG_FS_TypeDef * USBx, uint32_t ep_num, USB_TokenPid_Type token_pid)
{
    if (0 != (USBx->CTL & OTG_FS_CTL_TXDSUSPEND_TOKENBUSY) )
    {
        return false;
    }
    USBx->TOKEN = USB_TOKEN_TOKENENDPT(ep_num) | USB_TOKEN_TOKENPID(token_pid);
    return true;
}

void USB_EnableBusReset(USB_OTG_FS_TypeDef * USBx, bool enable)
{
    if (enable)
    {
        USBx->CTL |= OTG_FS_CTL_RESET;
    }
    else
    {
        USBx->CTL &= ~OTG_FS_CTL_RESET;
    }
}

USB_BusSignalStatus_Type USB_GetBusSignalStatus(USB_OTG_FS_TypeDef * USBx)
{
    if ( 0 == (USBx->CTL & OTG_FS_CTL_JSTATE) && 0 != (USBx->CTL & OTG_FS_CTL_SE0) )
    {
        return USB_BusSignalStatus_SE0;
    }
    else if ( 0 != (USBx->CTL & OTG_FS_CTL_JSTATE) && 0 == (USBx->CTL & OTG_FS_CTL_SE0) )
    {
        return USB_BusSignalStatus_J;
    }
    else
    {
        return USB_BusSignalStatus_Other;
    }
}

/* EOF. */
