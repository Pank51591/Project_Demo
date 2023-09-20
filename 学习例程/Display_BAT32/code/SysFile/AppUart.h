#ifndef UART_H
#define UART_H
#include"config.h"
#include"typedef.h"




typedef struct 
{
	INT8U buf[100];
	INT16U len;
	INT16U isend;//发送字节计数
	INT8U busy;//发送忙线中
}
SENDBUF;


extern INT8U uarttimeout;
extern INT8U uart1timeout;
extern INT8U uart2timeout;
extern INT8U uart5timeout;




BOOL UartSendDisplayData(INT8U *buff,INT8U len);
BOOL UartSendFaucetData(INT8U *buff,INT8U len);
BOOL UartSendWifiData(INT8U *buff,INT8U len);


INT16U GetDisplayData(INT8U *buff);
INT16U GetFaucetData(INT8U *buff);
INT16U GetLORAData(INT8U *buff);
INT16U GetWifiData(INT8U *buff);


#if 1//UART_DEBUG
BOOL UartSendString(CONST INT8S *buff);
void Uartprintf(const char* pBuf,INT16U num);
void UartDisInfo(const char* pBuf,INT32S num);
int MCUprintf(const char *fmt,...);
int uart_printf1(const char *fmt,...);

#endif

#endif
