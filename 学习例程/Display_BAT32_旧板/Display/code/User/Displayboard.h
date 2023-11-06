#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H


#include"typedef.h"



typedef struct
{
	INT8U Head;//
	INT8U cmd;
	INT8U len;
	INT8U page;//
	INT8U Col;//ÆðÊ¼ÁÐ
	INT8U reverse;
	INT8U Data[22];//
	INT16U crc;
}LCDString_t;





void Uart_SendDisplay(INT8U *buf,INT8U len);

void SetBeep(INT8U times,INT8U flag);
void DisplayBoardTask(void);

void Display_Send(void);


void Uart_KeyHandle(INT8U*buf,INT8U len);

#endif

