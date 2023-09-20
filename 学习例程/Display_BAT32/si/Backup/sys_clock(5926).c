#include"config.h"


//extern INT16U SYSClockCountMS;//系统时间定时
//extern INT8U UartReciveTimeMS;//串口接收时间计数
//extern INT8U Uart2ReciveTimeMS;//串口接收时间计数

extern SYSTIMER TaskTimer[SYS_TIMER_NUM];//任务定时器 

extern SYSTEMTIME sSystemTime;

extern TASK_COMPONENTS Comps[TASKS_MAX];
//extern INT16U fcttimeTic;
#if 1

//**************************************************************************************
//	函数名称	:	
//	作者		:	
//	模块功能	:   
//	局部函数列表: 	
//  最后更正日期:
//  更改记录	:
//**************************************************************************************
void SYSClockInit(void)
{
	uint32_t msCnt; 	// count value of 1ms

	SystemCoreClockUpdate();
	
	msCnt = SystemCoreClock / 1000; //1ms
	SysTick_Config(msCnt); 	
}




#if 1
//**************************************************************************************
//	函数名称	: Timer0	
//	作者		: yzy	
//	模块功能	: 定时器销毁 
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : hwnd 定时任务号，nIDEvent定时器ID
//  更改记录	:
//**************************************************************************************
 //void Timer0(void)  ///1ms中断一次
void SysTick_Handler(void)
{
	//static INT16U count=0;
	INT8U i;

	
	if(sSystemTime.Milliseconds < 65535)
	{
		sSystemTime.Milliseconds++;

		SyStemTimeTask();
	}

	if(uarttimeout<250)uarttimeout++;
	//if(uart1timeout<250)uart1timeout++;
	//if(uart2timeout<250)uart2timeout++;
	//if(uart5timeout<250)uart5timeout++;

	//if(gATtimeOut>0)gATtimeOut--;

	//if(fcttimeTic)fcttimeTic--;

	//SysTick1ms++;
	//SysTick1msC++;
	
	//if(SysTick1msD < 500)
	//	SysTick1msD++;	
	
#if 1
	for (i=0; i < SYS_TIMER_NUM; i++) 
	{
		if (TaskTimer[i].State) 
		{
			if(TaskTimer[i].nElapse == 0)
			{
				TaskTimer[i].Flag = TRUE; 
				TaskTimer[i].State = DISABLE;
				TaskTimer[i].MonitorFlag = TRUE;		
			}
			else
			{
				TaskTimer[i].nElapse--;	
			}
		}	  
	}
#endif
#if 1 
	for(i=0; i<TASKS_MAX; i++)          // 逐个任务时间处理
	{
		if(TaskComps[i].Timer)          // 时间不为0
		{
			TaskComps[i].Timer--;         // 减去一个节拍
		}
		else
		{
			TaskComps[i].Timer = TaskComps[i].ItvTime;       // 恢复计时器值，从新下一次
			TaskComps[i].Run = 1;           // 任务可以运行
		}
	}
#endif
}

#endif












#endif
