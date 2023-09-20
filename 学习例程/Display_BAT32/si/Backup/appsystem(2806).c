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

INT16U GetModbusCRC(INT8U *pSendBuf, INT8U num)//获得校验码 
{ 
	  INT8U i,j;
	  INT16U c,wCrc = 0xFFFF;

       for(i=0; i<num; i++)
       {
       	  c=pSendBuf[i];
          wCrc ^= c;
          for(j=0; j<8; j++)
          {
             if(wCrc & 1)
             {
                wCrc >>= 1; 
                wCrc ^= 0xA001; 
             }
             else
			 {
                wCrc >>= 1; 
             }
          }
       }
	   
       return wCrc;
}



void SendDisplayData(void)
{
	INT8U pbuff[100]={0};
	INT8U i,k,num; 
	INT8U *p;
	INT16U crc;

	p = (INT8U*)&gUISet;

	num = sizeof(UIset_t);

	if(num<1)
	{
		return;
	}
	
	pbuff[0]=0XFA;
	pbuff[1]=0X03;
	pbuff[2]=num;
	
	for(i=0;i<num;i++)
	{
		pbuff[3+i]=p[i];
	}
	
	crc=GetModbusCRC(pbuff,i+3);
	pbuff[3+i]=crc&0x00ff;
	pbuff[4+i]=((crc>>8)&0x00ff);

	UartSendDisplayData(pbuff,4+i+1);
}

//解析读取
void ParsingDisplayData(INT8U *pbuff,INT16U len)
{
	INT16S temp;
	INT16U addr;//寄存器起始地址
	INT16U regnum;
	INT8U cmd;

	//数据校验
	if(GetModbusCRC(pbuff,len)!=0)
	{
		return;
	}

	systemseting.uartdisplayTimeOutCnt=0;
	systemseting.uartdisplayError=0;
	
	SendDisplayData();

	return;	
}

//10ms
void MonitorState(void)
{
	if(systemseting.uartdisplayTimeOutCnt<300)systemseting.uartdisplayTimeOutCnt++;
	else 
	{
		systemseting.uartdisplayError=1;	
	}
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

