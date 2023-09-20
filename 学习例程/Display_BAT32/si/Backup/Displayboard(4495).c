#include"config.h"
#include"DisplayBoard.h"



#define ADDR	6//600G机型


//INT8U BeepTimes=0,BeepFlag=0;
//INT8U LightFlag,LightFlash;
//DISPLAY_REG LightReg,LightOut;

//static INT16S keytimeoutcount=0,waittime=200;//10秒
//static INT8U keytimecount=0;
extern INT8U uartkeyval;





//450ms
/*void DisplayBoardTask(void)
{
	
	//UartSendDisplayData("DisplayBoardTask\r\n",18);
}


void Uart_SendDisplay(INT8U *buf,INT8U len)
{

}


void Uart_KeyHandle(INT8U*buf,INT8U len)
{
	len=len;
	uartkeyval = buf[4];

	keytimecount=0;
	keytimeoutcount=0;
	systemseting.uartdisplayError=0;//显示通讯正常
	waittime=2400;//120秒
}*/


/*void Display_SetData(DISPLAY_REG *dis,INT8U beep)
{

	Display_Send();
}*/

//50ms
/*void Display_Send(void)
{
	INT8U buf[15];
	INT8U *p=buf,*pbuf=buf,len=4;
	//INT8U *plight=(INT8U*)&LightOut;



	UartSendDisplayData(p,len+3);
}*/


