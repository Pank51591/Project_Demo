#include"config.h"
#include"DisplayBoard.h"



#define ADDR	8


INT8U BeepTimes=0,BeepFlag=0;
DISPLAY_REG disreg;

void SetBeep(INT8U times,INT8U flag)
{
	BeepTimes=times;
	BeepFlag=flag;
}

//500ms
void BeepTask(void)
{
	if(BeepTimes)
	{
		BeepTimes--;
	}
	else 
	{
		BeepFlag=0;
	}
}


void Uart_SendDisplay(INT8U *buf,INT8U len)
{
	memcpy((INT8U*)&disreg,buf,len);
}


INT8U LightHandle(void)
{
	

	
	return 1;
}


void Display_Send(void)
{
	DISP buf;

	buf.head1=0xFF;
	buf.head2=0xFF;
	buf.len = 7;
	buf.addr= ADDR;
	buf.LEDLight=LightHandle();
	buf.beep=BeepFlag;
	buf.sum=

	UartSendDisplayData((INT8U*)&buf,sizeof(DISP));
}
























