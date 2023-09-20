#include"config.h"
#include"DisplayBoard.h"



#define ADDR	6//600G机型


INT8U BeepTimes=0,BeepFlag=0;
INT8U LightFlag,LightFlash;
DISPLAY_REG LightReg,LightOut;

static INT16S keytimeoutcount=0,waittime=200;//10秒
static INT8U keytimecount=0;
extern INT8U uartkeyval;


void BeepTimer(void)
{
	BeepTimes--;
	
	if(BeepTimes<=1)
	{
		BeepFlag=0;
		KillTimer(0, SYS_TIMER_Beep);		
	}
	else if(BeepTimes%2==0)
	{
		BeepFlag=1;
	}
	else 
	{
		BeepFlag=0;
	}
}


void SetBeep(INT8U times,INT8U flag)
{
	if(flag)
	{
		BeepTimes=times*2;
		BeepFlag=flag;
		TimeSetEvent(SYS_TIMER_Beep, 450, BeepTimer, TIME_PERIODIC);
	}
	else 
	{
		KillTimer(0, SYS_TIMER_Beep);
		BeepFlag=0;		
	}
}


//450ms
void DisplayBoardTask(void)
{
	static INT8U flash=0;

	LightOut.run_r_en=LightReg.run_r_en;
	LightOut.pcb_r_en=LightReg.pcb_r_en;
	LightOut.ro_r_en=LightReg.ro_r_en;
	LightOut.wifi_r_en=LightReg.wifi_r_en;

	LightOut.run_w_en=LightReg.run_w_en;
	LightOut.pcb_w_en=LightReg.pcb_w_en;
	LightOut.ro_w_en=LightReg.ro_w_en;
	LightOut.wifi_w_en=LightReg.wifi_w_en;	

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
	INT8U *p=(INT8U*)&LightReg;
	
	LightFlag=buf[0];
	LightFlash=buf[1];
	p[0]=buf[0];
	p[1]=buf[1];
}


void Uart_KeyHandle(INT8U*buf,INT8U len)
{
	len=len;
	uartkeyval = buf[4];

	keytimecount=0;
	keytimeoutcount=0;
	systemseting.uartdisplayError=0;//显示通讯正常
	waittime=2400;//120秒
}


void Display_SetData(DISPLAY_REG *dis,INT8U beep)
{
	BeepFlag=beep;
	memcpy((INT8U*)&LightOut,(INT8U*)dis,2);
	Display_Send();
}

//50ms
void Display_Send(void)
{
	INT8U buf[15];
	INT8U *p=buf,*pbuf=buf,len=4;
	INT8U *plight=(INT8U*)&LightOut;

	if(gReg.WorkState==WORKSTATE_FCT)
	{
		return;
	}
	if(systemseting.displaydelaysend)
	{
		systemseting.displaydelaysend--;
		return;
	}	

	if(++keytimeoutcount>waittime)
	{
		keytimeoutcount=0;
		systemseting.uartdisplayError=1;//显示通讯错误
	}

	if(++keytimecount>5)
	{
		uartkeyval=0;
	}
	
	*pbuf++ = 0xFF;
	*pbuf++ = 0xFF;

	*pbuf++ = len;//帧长
	
	*pbuf++ = ADDR;//地址

	if(plight[0]!=0xFF){*pbuf++ =plight[0];}//灯
	else{*pbuf++ =plight[0];*pbuf++ =0x55;len++;}
	
	*pbuf++ = BeepFlag;

	
	*pbuf++ = GetSum(p+2,len);//累加和

	if(*pbuf==0xFF){pbuf++;*pbuf = 0x55;len++;}


	UartSendDisplayData(p,len+3);
}


