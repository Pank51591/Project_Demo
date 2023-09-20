//#include"main.h"
#include"config.h"
//#include<string.h>
//#include <stdio.h>



void SYS_Init()	
{
	WDT_Restart();
	delayms(200);
	WDT_Restart();
	delayms(200);
	WDT_Restart();
	delayms(200);
	WDT_Restart();
	delayms(200);
	WDT_Restart();

	//NVIC_SetVectorTable(NVIC_VECTTABLE_FLASH, 0x1000); /* Set base location of the Vector Table at 0x1000 */

    return;
}

void StartWDT(u8 ucTcnt, u8 ucWcnt)
{
	#if 0
    // WWDG configuration
    // Enable WWDG clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

    //WWDG_Prescaler_x,x?1,2,4,8,WWDG counter clock = (PCLK1/4096)/x
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(ucWcnt);

    // Enable WWDG and set counter value from 0x40  to 0x7F
    // Enable WWDG and set counter value to 127, WWDG timeout = ~683 us * 64 = 43.7 ms
    //In this case the refresh window is: ~683 * (127-80)= 32.1ms < refresh window < ~683 * 64 = 43.7ms
    WWDG_Enable(ucTcnt);
#endif	
}

void FeedWDT(void)
{
//	WWDG->CR = 0x7e & WWDG_CFGR_WINDOW;
}


void ADCInit(void)
{
	ADC_Init();
}


extern WINHAND *spWinHand;
int main(void)
{
	RTDATA HWND hwnd=0;
	RTDATA MSG msg;
	INT16U len;
	
	//上层系统时钟初始化
	SYSClockInit();

	IOInit();

	ExternalInterruptInit();
	
	UART0_Init(SystemCoreClock, 9600);//
	UART1_Init(SystemCoreClock, 9600);//
	UART2_Init(SystemCoreClock, 9600);

	delayms(1000);
	
	SYS_Init();
	
	fifo_init();

	ADCInit();
	AppADCInit();
	
	SYSInit();//系统初始化

	AppSystemInit();
	GetSysSeting();
	
	PowerOnDisplay(); 
	StandbyRestart();
	
	while(1) 
	{
		WDT_Restart();	
	
		while(GetMessage(&msg,hwnd))
		{	
			WndProc(&msg);
		}
		
		MonitorTimer();//定时器监控
		
		TaskProcess();//任务过程	

		len = GetDisplayData(RecBuff);
		if(len)
		{
			UartDispProc(RecBuff,len);
		}		
		len = GetFaucetData(RecBuff);
		if(len)
		{
			UartFaucetProc(RecBuff,len);
		}
		len = GetWifiData(RecBuff);
		if(len)
		{
			UartWifiProc(RecBuff,len);//UartSendFaucetData(RecBuff,len);
		}
	}
}


