#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H





typedef struct
{
	INT8U head1;
	INT8U head2;
	INT8U len;
	INT8U addr;
	INT8U LEDLight;
	INT8U beep;
	INT8U sum;
}
DISP;




void Uart_SendDisplay(INT8U *buf,INT8U len);

void SetBeep(INT8U times,INT8U flag);
void DisplayBoardTask(void);

void Display_Send(void);


void Uart_KeyHandle(INT8U*buf,INT8U len);

#endif

