#include "bsp_wifi_esp8266.h"
#include "bsp_debug_uart.h"


/*Wifi (SCI2 UART) 初始化*/
void ESP8266_UART2_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    
    R_SCI_UART_Open(g_uart2_esp8266.p_ctrl, g_uart2_esp8266.p_cfg);
    assert(FSP_SUCCESS == err);
}


/*Wifi串口回调函数*/
void esp8266_uart2_callback(uart_callback_args_t * p_args)
{
       switch(p_args->event)
       {
           case UART_EVENT_RX_CHAR:  //收到AT的指令后打印回显信息
               R_SCI_UART_Write(&g_uart1_ctrl, (uint8_t *)&(p_args->data), 1);
               break;
           default:
               break;
       }
}
