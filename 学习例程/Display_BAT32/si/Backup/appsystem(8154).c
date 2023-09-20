#include"config.h"
#include"appsystem.h"
#include"stdio.h"
#include <stdlib.h>



INT8U RecBuff[SERIAL_BUFF_NUM];
CODE INT8U Digitaltube[11]={0x3F,0x03,0x5D,0x4F,0x63,0x6E,0x7E,0x0B,0x7F,0x6F,0x7C};//0123456789E



SYSTEMSETING systemseting;
UARTPROC UartDispProc=ParsingDisplayData;//ModbusProc;
//UARTPROC UartFaucetProc=Faucet_proc;
//UARTPROC UartWifiProc=WifiMsgProc;
DISPLAY_REG gDisplayReg;
REG gReg;


UIset_t gUISet;



void AppSystemInit(void)
{

	gReg.WorkState=WORKSTATE_working;
}

//恢复出厂设置：恢复出厂设置，滤芯寿命、净水量、记忆的TDS、WIFI配网等数据清零。
void RestoreFactory(void)
{

}








BOOL SendDisplayMsg(INT8U *pdat,INT8U len)
{
	INT8U buf[10],*pbuf;



	
	UartSendDisplayData(buf,len);
	
	return TRUE;
}

//解析读取
void ParsingDisplayData(INT8U *pbuff,INT16U len)
{
	INT8U i,page,col,reverse;

	page=pbuff[0];
	col=pbuff[1];
	reverse=pbuff[2];

	len -= 5;
	
	for(i=0;i<len;i++)
	{
		//gdisReg.LCD[i]=pbuff[i+3];
	}
	//gdisReg.LCD[i]='\0';

	

	



	return;	
}




void DisplayUpdate(void)
{

	SendMessage(0, WM_DISPLAY, 1);
}



void Standby(void)
{	

}

void StandbyRestart(void)
{

}

void WinTimerOut(void)
{
	if(++systemseting.WinTimerCount<30)return;

	systemseting.WinTimerCount=0;
	systemseting.WinTimerOutFlag=1;

	KillTimer(0, SYS_TIMER_WINTIMEOUT);
}




void Beepring(void)
{
	  

}

void PowerOnDisplay(void)
{

}

