#include"config.h"
#include"DisplayBoard.h"



#define ADDR	8//800G»úÐÍ


INT8U BeepTimes=0,BeepFlag=0;
INT8U LightFlag,LightFlash;
DISPLAY_REG LightReg,LightOut;

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

//500ms
void LightTask(void)
{
	static INT8U flash=0;


	LightOut.run_r_en=LightReg.run_r_en;
	LightOut.pcb_r_en=LightReg.pcb_r_en;
	LightOut.ro_r_en=LightReg.ro_r_en;
	LightOut.wifi_r_en=LightReg.wifi_r_en;

	if(flash)
	{
		flash=0;
		if(LightReg.run_r_flash&&LightReg.run_r_en){LightOut.run_r_en=1;}
		if(LightReg.pcb_r_flash&&LightReg.pcb_r_en){LightOut.pcb_r_en=1;}
		if(LightReg.ro_r_flash&&LightReg.ro_r_en){LightOut.ro_r_en=1;}
		if(LightReg.wifi_r_flash&&LightReg.wifi_r_en){LightOut.wifi_r_en=1;}
		
		if(LightReg.run_w_flash&&LightReg.run_w_en){LightOut.run_w_en=1;}
		if(LightReg.pcb_w_flash&&LightReg.pcb_w_en){LightOut.pcb_w_en=1;}
		if(LightReg.ro_w_flash&&LightReg.ro_w_en){LightOut.ro_w_en=1;}
		if(LightReg.wifi_w_flash&&LightReg.wifi_w_en){LightOut.wifi_w_en=1;}

	}
	else 
	{
		flash=1;
		if(LightReg.run_r_flash){LightOut.run_r_en=0;}
		if(LightReg.pcb_r_flash){LightOut.pcb_r_en=0;}
		if(LightReg.ro_r_flash){LightOut.ro_r_en=0;}
		if(LightReg.wifi_r_flash){LightOut.wifi_r_en=0;}
		
		if(LightReg.run_w_flash){LightOut.run_w_en=0;}
		if(LightReg.pcb_w_flash){LightOut.pcb_w_en=0;}
		if(LightReg.ro_w_flash){LightOut.ro_w_en=0;}
		if(LightReg.wifi_w_flash){LightOut.wifi_w_en=0;}
	}
}


void Uart_SendDisplay(INT8U *buf,INT8U len)
{
	LightFlag=buf[0];
	LightFlash=buf[1];

	memcpy((INT8U*)&LightReg,buf,len);
}


INT8U LightHandle(void)
{
	
	
	
	return 1;
}


void Display_Send(void)
{
	DISP buf;
	INT8U *plight=(INT8U*)&LightOut;

	buf.head1=0xFF;
	buf.head2=0xFF;
	buf.len = 7;
	buf.addr= ADDR;
	buf.LEDLight=plight[0];
	buf.beep=BeepFlag;
	buf.sum=1;

	UartSendDisplayData((INT8U*)&buf,sizeof(DISP));
}
























