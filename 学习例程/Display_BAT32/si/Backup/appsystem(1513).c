#include"config.h"
#include"appsystem.h"
#include"stdio.h"
#include <stdlib.h>



INT8U RecBuff[SERIAL_BUFF_NUM];

SYSTEMSETING systemseting;
UARTPROC UartDispProc=ParsingDisplayData;//ModbusProc;
//UARTPROC UartFaucetProc=Faucet_proc;
//UARTPROC UartWifiProc=WifiMsgProc;

UIset_t gUISet;



void AppSystemInit(void)
{

	
}

//恢复出厂设置：恢复出厂设置，滤芯寿命、净水量、记忆的TDS、WIFI配网等数据清零。
void RestoreFactory(void)
{

}








BOOL SendDisplayMsg(INT8U *pdat,INT8U len)
{
	//INT8U buf[10],*pbuf;



	
	//UartSendDisplayData(buf,len);
	
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
	INT8U i,num,cmd=0x03; 
	INT8U *p;
	INT16U crc;

	p = (INT8U*)&gUISet;

	num = sizeof(UIset_t);

	if(num<1)
	{
		return;
	}

	if(systemseting.StateChangeSaveflag)
	{
		cmd=0x04;
	}
	else 
	{
		cmd=0x03;
	}
	
	pbuff[0]=0XFA;
	pbuff[1]=cmd;
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

void SetDisplayData(INT8U *pbuff,INT16U len)
{
	INT8U i,*p=(INT8U*)&gUISet;
	
	for(i=0;i<sizeof(UIset_t);i++)
	{
		p[i]=pbuff[i+3];
	}
}

//解析读取
void ParsingDisplayData(INT8U *pbuff,INT16U len)
{
	//INT16S temp;
	//INT16U regnum;
	//INT8U cmd;

	//数据校验
	if(GetModbusCRC(pbuff,len)!=0)
	{
		return;
	}

	systemseting.uartdisplayTimeOutCnt=0;
	systemseting.uartdisplayError=0;

	if(pbuff[1]==0x03)
	{
		systemseting.pc_en=0;
		systemseting.StateChangeFlag=0;
		//SendDisplayData();
	}
	else if(pbuff[1]==0x04)
	{
		systemseting.StateChangeSaveflag=0;
	}
	else if(pbuff[1]==0x10)
	{
		//systemseting.pc_en=1;
		if(systemseting.StateChangeFlag==0&&systemseting.StateChangeSaveflag==0)
		{
			SetDisplayData(pbuff,len);
		}
	}

	return;	
}

//100ms
void MonitorState(void)
{
	HWND hwnd;
	
	if(systemseting.uartdisplayTimeOutCnt<100)//10s
	{
		systemseting.uartdisplayTimeOutCnt++;
	}
	else 
	{
		systemseting.uartdisplayError=1;	
	}

	if(gUISet.WorkMode)
	{	
		UI_Power(0);

		hwnd=GetActiveWindow();
		
		if(hwnd!=HWND_DESKTOP&&hwnd!=HWND_FCT)//待机的时候要回到主界面
		{
			SendMessage(0,WM_PAGESWITCH, HWND_DESKTOP); 
		}
	}
	else 
	{
		UI_Power(1);
	}
	

	if(systemseting.StateChangeFlag||systemseting.StateChangeSaveflag)
	{
		SendDisplayData();
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
	if(++systemseting.WinTimerCount<60)return;

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

