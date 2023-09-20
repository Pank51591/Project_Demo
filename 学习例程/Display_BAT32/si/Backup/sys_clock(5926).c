#include"config.h"


//extern INT16U SYSClockCountMS;//ϵͳʱ�䶨ʱ
//extern INT8U UartReciveTimeMS;//���ڽ���ʱ�����
//extern INT8U Uart2ReciveTimeMS;//���ڽ���ʱ�����

extern SYSTIMER TaskTimer[SYS_TIMER_NUM];//����ʱ�� 

extern SYSTEMTIME sSystemTime;

extern TASK_COMPONENTS Comps[TASKS_MAX];
//extern INT16U fcttimeTic;
#if 1

//**************************************************************************************
//	��������	:	
//	����		:	
//	ģ�鹦��	:   
//	�ֲ������б�: 	
//  ����������:
//  ���ļ�¼	:
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
//	��������	: Timer0	
//	����		: yzy	
//	ģ�鹦��	: ��ʱ������ 
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : hwnd ��ʱ����ţ�nIDEvent��ʱ��ID
//  ���ļ�¼	:
//**************************************************************************************
 //void Timer0(void)  ///1ms�ж�һ��
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
	for(i=0; i<TASKS_MAX; i++)          // �������ʱ�䴦��
	{
		if(TaskComps[i].Timer)          // ʱ�䲻Ϊ0
		{
			TaskComps[i].Timer--;         // ��ȥһ������
		}
		else
		{
			TaskComps[i].Timer = TaskComps[i].ItvTime;       // �ָ���ʱ��ֵ��������һ��
			TaskComps[i].Run = 1;           // �����������
		}
	}
#endif
}

#endif












#endif
