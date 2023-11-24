#include "bsp_can.h"


/* CAN 初始化函数 */
void CAN_Init(void)
{
    fsp_err_t err = R_CAN_Open(&g_can0_ctrl, &g_can0_cfg);
    assert(FSP_SUCCESS == err);
}



/* CAN 帧 */
can_frame_t can_tx_frame; //CAN transmit frame
can_frame_t can_rx_frame;


/* 要在回调函数中设置的标志 */
volatile bool can_tx_complete_flag = false;
volatile bool can_rx_complete_flag = false;
volatile bool can_err_status_flag = false;
volatile can_error_t can_err_status = (can_error_t) 0;


/* CAN 中断回调函数 */
void can_callback(can_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        case CAN_EVENT_RX_COMPLETE: //接收完成中断
        {
            can_rx_complete_flag = true;    //can接收到数据

            /* 读取接收帧 */
            memcpy(&can_rx_frame, &(p_args->frame), sizeof(can_frame_t));

            break;
        }
        case CAN_EVENT_TX_COMPLETE: //传输完成中断
        {
            can_tx_complete_flag = true;    //can数据发送完成
            break;
        }
        case CAN_EVENT_ERR_BUS_OFF:          /* Bus error event. (bus off) */
        case CAN_EVENT_ERR_PASSIVE:          /* Bus error event. (error passive) */
        case CAN_EVENT_ERR_WARNING:          /* Bus error event. (error warning) */
        case CAN_EVENT_BUS_RECOVERY:         /* Bus error event. (bus recovery) */
        case CAN_EVENT_MAILBOX_MESSAGE_LOST: /* Overwrite/overrun error */
        {
            can_err_status_flag = true;     //设置标志位

            /* 获取错误状态 */
            can_err_status = (can_error_t) p_args->error;

            break;
        }
        default:
        {
            break;
        }
    }
}


/* 发送和应答消息定义 */
uint8_t can_tx_msg[CAN_FRAME_TRANSMIT_DATA_BYTES] = "TXD_MESG"; //data to be load in tx_frame while transmitting
uint8_t can_rx_msg[CAN_FRAME_TRANSMIT_DATA_BYTES] = "RXD_MESG"; //data to be load in rx_frame while acknowledging

/* CAN 操作函数 */
void CAN_Operation(void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t time_out = WAIT_TIME;

    /* Clear the data part of receive frame */
    memset(can_rx_frame.data, 0, CAN_FRAME_TRANSMIT_DATA_BYTES);


    /* 更新传输帧的参数 */
    /* CAN Destination Device ID, in this case it is the same device with another mailbox */
    can_tx_frame.id               = CAN_DESTINATION_MAILBOX_3;
    can_tx_frame.type             = CAN_FRAME_TYPE_DATA;
    can_tx_frame.data_length_code = CAN_FRAME_TRANSMIT_DATA_BYTES;

    /* 填充将要传输的帧数据 */
    /* copy the tx data frame with TXD_MESG */
    memcpy((uint8_t*)&can_tx_frame.data[0], (uint8_t*)&can_tx_msg[0], CAN_FRAME_TRANSMIT_DATA_BYTES);


    CAN_MSG_PRINTF("CAN 正在传输数据");
    CAN_MSG_PRINTF("Transmitting the data");
    /* transmit the data from mail box #0 with tx_frame */
    err = R_CAN_Write(&g_can0_ctrl, CAN_MAILBOX_NUMBER_0, &can_tx_frame);
    /* Error trap */
    if (FSP_SUCCESS != err)
    {
        CAN_MSG_PRINTF("CAN Write API FAILED");
        while(1);
    }

    /* 等待传输完成 */
    while ((true != can_tx_complete_flag) && (--time_out));
    can_tx_complete_flag = false;
    if (0 == time_out)
    {
        CAN_MSG_PRINTF("传输超时！！传输失败！！");
        return;
    }
    CAN_MSG_PRINTF("传输完成\r\n");
    
    
    /* 等待对方（另一个 CAN）回复应答消息 */
    CAN_MSG_PRINTF("等待 CAN 接收完成中断（等待对方回复）");
    while (false == can_rx_complete_flag);
    can_rx_complete_flag = false;

    CAN_MSG_PRINTF("开始验证对方回复的应答消息数据");
    for( uint16_t j = 0; j < CAN_FRAME_TRANSMIT_DATA_BYTES; j++)
    {
        if (can_rx_msg[j] != can_rx_frame.data[j])
        {
            CAN_MSG_PRINTF("对方 CAN 回复的应答消息数据不正确");
        }
    }
    CAN_MSG_PRINTF("CAN 互相传输测试完成\r\n");
}

