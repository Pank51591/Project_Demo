#include"config.h"
#include"system.h"

#ifndef SYS_TIMER_NUM
//#define SYS_TASK_NUM	1
#endif




 SYSTIMER TaskTimer[SYS_TIMER_NUM];//����ʱ�� 

 MSGQUEUE	MsgQueue;//��Ϣ����

 SYSTEMTIME sSystemTime;

//**************************************************************************************
//	��������	: SYSInit	
//	����		: yzy	
//	ģ�鹦��	: ϵͳ��ʼ��
//	����ֵ      : ��	
//  ��������    : 
//  ���ļ�¼	:
//**************************************************************************************
void SYSInit(void)
{
	//MSG *msg;
	INT8U i;

	//�����ʼ��
	//
	//
	//��ʱ����ʼ��

	memset(TaskTimer,0,sizeof(TaskTimer));
	for(i=0;i<SYS_TIMER_NUM;i++)
	{
		TaskTimer[i].IDEvent = SYS_TIMER_FREEID;
	}

	//��Ϣ���г�ʼ��
	/*
	msg = (MSG*)(&MsgQueue.HGPriority);
	msg->hwnd = 0;
	msg->message = 0;
	msg->wParam = 0;

	msg = (MSG*)(MsgQueue.msg);
	MsgQueue.len = 0;

	for(i=0;i<SYS_QUEUE_NUM;i++)
	{
		msg->hwnd = 0;
		msg->message = 0;
		msg->wParam = 0;

		msg++;
		//printf("%d,%d,%d\n",MsgQueue.msg[i].hwnd,MsgQueue.msg[i].message,MsgQueue.msg[i].wParam);
	}*/
	memset(&MsgQueue,0,sizeof(MSGQUEUE));
	MsgQueue.pGet = MsgQueue.msg;
	MsgQueue.pSend = MsgQueue.msg;

	//memset(&sSystemTime,0,sizeof(SYSTEMTIME));
#if DATE_ENABLE	
	sSystemTime.Year = 2021;
	sSystemTime.Month = 9;
	sSystemTime.Day = 20;
#endif
	sSystemTime.Hour = 12;
	sSystemTime.Minute = 0;
	sSystemTime.Second = 0;
	sSystemTime.Milliseconds = 0;

	//���ڳ�ʼ��
	WinInit();
	
	SendMessage(0,WM_CREATE,0x00);//ϵͳ��ʼ����

}
#if 0
//**************************************************************************************
//	��������	: SetTimer	
//	����		: yzy	
//	ģ�鹦��	: ��ʱ�� 
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : hwnd ��ʱ���ھ����nIDEvent��ʱ��ID��nElapse��ʱʱ�䵥λms
//  ���ļ�¼	:
//**************************************************************************************
BOOL SetTimer(HWND hwnd,INT8U nIDEvent,INT32U nElapse,TIMERPROC TimerProc)//TIMERPROC
{
	if(TaskTimer[nIDEvent].IDEvent != SYS_TIMER_FREEID)
	{
		return FALSE;	
	}
	TaskTimer[nIDEvent].hwnd = hwnd;
	TaskTimer[nIDEvent].IDEvent = nIDEvent;
	TaskTimer[nIDEvent].nElapse = nElapse;
	TaskTimer[nIDEvent].nElapseBuff= nElapse;
	TaskTimer[nIDEvent].Flag = FALSE;
	TaskTimer[nIDEvent].State = ENABLE;
	TaskTimer[nIDEvent].Mode = TIME_PERIODIC;//TIME_ONESHOT
	TaskTimer[nIDEvent].MonitorFlag = FALSE;
	TaskTimer[nIDEvent].TimerFunc = TimerProc;

	return TRUE;
}
#endif
//**************************************************************************************
//	��������	: TimeSetEvent	
//	����		: yzy	
//	ģ�鹦��	: ��ʱ�� 
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : nIDEventID��uDelay��ʱʱ��(��λms)�lpTimeProc�ص�������fuEventΪ��ʱ�����¼�����
//  ���ļ�¼	:
//**************************************************************************************
BOOL TimeSetEvent(INT8U nIDEvent,INT32U nElapse,TIMERPROC lpTimeProc,BOOL fuEvent)
{
	if(TaskTimer[nIDEvent].IDEvent != SYS_TIMER_FREEID)
	{
		return FALSE;	
	}//UartSendString("TimeSetEvent start����\r\nr");UartSendNumber((INT16U)lpTimeProc);
	TaskTimer[nIDEvent].hwnd = 0;
	TaskTimer[nIDEvent].IDEvent = nIDEvent;
	TaskTimer[nIDEvent].nElapse = nElapse;
	TaskTimer[nIDEvent].nElapseBuff= nElapse;
	TaskTimer[nIDEvent].Flag = FALSE;
	TaskTimer[nIDEvent].State = ENABLE;
	TaskTimer[nIDEvent].Mode = fuEvent;
	TaskTimer[nIDEvent].MonitorFlag = FALSE;
	TaskTimer[nIDEvent].TimerFunc = lpTimeProc;
	//UartSendString("TimeSetEvent 0k����");
	return TRUE; 
}
#if 0
//**************************************************************************************
//	��������	: SetDelayTimer	
//	����		: yzy	
//	ģ�鹦��	: ��ʱ�� 
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : nIDEvent��ʱ��ID��nElapse��ʱʱ�䵥λms
//  ���ļ�¼	:
//**************************************************************************************
BOOL SetDelayTimer(INT8U nIDEvent,INT32U nElapse)
{//UartSendString("SetDelayTimer  1");
	if(TaskTimer[nIDEvent].IDEvent != SYS_TIMER_FREEID)
	{
		return FALSE;	
	}//UartSendString("SetDelayTimer  2");
	TaskTimer[nIDEvent].hwnd = 0;
	TaskTimer[nIDEvent].IDEvent = nIDEvent;
	TaskTimer[nIDEvent].nElapse = nElapse;
	TaskTimer[nIDEvent].nElapseBuff= nElapse;
	TaskTimer[nIDEvent].Flag = FALSE;
	TaskTimer[nIDEvent].State = ENABLE;
	TaskTimer[nIDEvent].Mode = TIME_DELAY;
	TaskTimer[nIDEvent].MonitorFlag = FALSE;
	TaskTimer[nIDEvent].TimerFunc = NULL;

	return TRUE;
}
#endif

#if 1
//**************************************************************************************
//	��������	: KillTimer	
//	����		: yzy	
//	ģ�鹦��	: ��ʱ������ 
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : hwnd ��ʱ����ţ�nIDEvent��ʱ��ID
//  ���ļ�¼	:
//**************************************************************************************
BOOL KillTimer(HWND hwnd,INT8U IDEvent)
{
	hwnd = hwnd;

	TaskTimer[IDEvent].nElapse = 0;
	TaskTimer[IDEvent].Flag = FALSE;
	TaskTimer[IDEvent].State = DISABLE;
	TaskTimer[IDEvent].MonitorFlag = FALSE;
	TaskTimer[IDEvent].IDEvent = SYS_TIMER_FREEID;
	TaskTimer[IDEvent].TimerFunc = 0;

	return TRUE;
}
#endif
#if 0
//**************************************************************************************
//	��������	: TimerPause	
//	����		: yzy	
//	ģ�鹦��	: ��ʱ����ͣ 
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : hwnd ��ʱ����ţ�nIDEvent��ʱ��ID
//  ���ļ�¼	:
//**************************************************************************************
BOOL TimerPause(HWND hwnd,INT8U IDEvent)
{
	hwnd = hwnd;
	
	if(TaskTimer[IDEvent].IDEvent == SYS_TIMER_FREEID)
	{
		return FALSE;
	}

	TaskTimer[IDEvent].State = DISABLE;
	
	return TRUE;
}
#endif
#if 1
//**************************************************************************************
//	��������	: TimerStart	
//	����		: yzy	
//	ģ�鹦��	: ��ʱ����ʼ��ʱ
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : hwnd ��ʱ����ţ�nIDEvent��ʱ��ID
//  ���ļ�¼	:
//**************************************************************************************
BOOL TimerStart(HWND hwnd,INT8U IDEvent)
{
	hwnd = hwnd;

	if(TaskTimer[IDEvent].IDEvent == SYS_TIMER_FREEID)
	{
		return FALSE;
	}

	TaskTimer[IDEvent].State = ENABLE;
	TaskTimer[IDEvent].nElapse = TaskTimer[IDEvent].nElapseBuff;
	
	return TRUE;
}
#endif

#if 0
//**************************************************************************************
//	��������	: GetTimerFlag	
//	����		: yzy	
//	ģ�鹦��	: ��ȡ��ʱ����ʱ��־
//	����ֵ      : ��ʱʱ�䵽����1����ʱʱ��û������0	
//  ��������    : nIDEvent��ʱ��ID��
//  ���ļ�¼	:
//**************************************************************************************
BOOL GetTimerFlag(INT8U IDEvent)
{
	BOOL flag;

	flag = (BOOL)TaskTimer[IDEvent].Flag;

	if(flag)
	{
		TaskTimer[IDEvent].Flag = FALSE;
		if(TaskTimer[IDEvent].Mode == TIME_DELAY)
		{
			TaskTimer[IDEvent].IDEvent = SYS_TIMER_FREEID;
		}
	}

	return flag;
}
#endif
//**************************************************************************************
//	��������	: MonitorTimer	
//	����		: yzy	
//	ģ�鹦��	: ��ض�ʱ�������������Ӧ����
//	����ֵ      : ��	
//  ��������    : 
//  ���ļ�¼	:
//**************************************************************************************
void MonitorTimer(void)
{
	RTDATA INT8U id;
	//MSG *msg;

	for(id=0;id<SYS_TIMER_NUM;id++)
	{
		if(TaskTimer[id].MonitorFlag)
		{
			TaskTimer[id].MonitorFlag = FALSE;
			
			if(TaskTimer[id].Mode==TIME_PERIODIC)//����Ƕ��ѭ��ʹ�ã���ô�����
			{
				TaskTimer[id].nElapse = TaskTimer[id].nElapseBuff;
				TaskTimer[id].State = ENABLE;
			}
			else if(TaskTimer[id].Mode==TIME_ONESHOT)
			{
				TaskTimer[id].IDEvent = SYS_TIMER_FREEID;
			}

			if(TaskTimer[id].TimerFunc != NULL)
			{
				TaskTimer[id].Flag = FALSE;
				TaskTimer[id].TimerFunc();
			}
			else//���û�лص��������� ��ʱ��Ϣ
			{
				TaskTimer[id].Flag = FALSE;
				SendMessage(TaskTimer[id].hwnd,WM_TIMER, TaskTimer[id].IDEvent);
			}
			//printf("len=%d ,%d,%d,%d\n",MsgQueue.len,MsgQueue.msg[MsgQueue.len-1].hwnd,MsgQueue.msg[MsgQueue.len-1].message,MsgQueue.msg[MsgQueue.len-1].wParam);
		}
	}
}
#if 1
//**************************************************************************************
//	��������	: SendMessage()	
//	����		: yzy	
//	ģ�鹦��	: ����������ȼ���Ϣ��
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : msg ��Ϣ�ṹ��hwnd ���ھ��
//  ���ļ�¼	: ������Ϣ��Ϊϵͳ����һ��Ҫ�������Ϣ�����ȼ����
//**************************************************************************************
BOOL SendHGPriotityMessage(HWND hWnd,INT8U Msg, WPARAM wParam)
{
	MSG *msgbuff;

	msgbuff = (MSG*)(&MsgQueue.HGPriority);
	
	//��Ϣ�����Ѿ���
	if(msgbuff->message!=0)
	{
		return SendMessage(hWnd,Msg,wParam);
	}

	msgbuff->hwnd = hWnd;
	msgbuff->message = Msg;
	msgbuff->wParam = wParam;

	return TRUE;
}
#endif
//**************************************************************************************
//	��������	: SendMessage()	
//	����		: yzy	
//	ģ�鹦��	: ������Ϣ����Ϣ����
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : msg ��Ϣ�ṹ��hwnd ���ھ��
//  ���ļ�¼	:
//**************************************************************************************
BOOL SendMessage(HWND hWnd,INT8U Msg, WPARAM wParam)
{
	MSG *msgbuff;
	int i;

	msgbuff = MsgQueue.pSend;


	msgbuff->hwnd = hWnd;
	msgbuff->message = Msg;
	msgbuff->wParam = wParam;

	MsgQueue.iSend++;
	MsgQueue.pSend++;
  
	//��Ϣ�����Ѿ���
	if(MsgQueue.iSend>SYS_QUEUE_NUM-1)
	{
		MsgQueue.iSend = 0;
		MsgQueue.pSend = MsgQueue.msg;	
	}

	for(i=0;i<5;i++)
	{
		//printf("len=%d,%d   ",MsgQueue.len,MsgQueue.msg[i].message);
	}
	//printf("\n");
	return TRUE;
}
//**************************************************************************************
//	��������	: GetMessage	
//	����		: yzy	
//	ģ�鹦��	: ��ȡ��Ϣ���е���Ϣ 
//	����ֵ      : �ɹ�����1��ʧ�ܷ���0	
//  ��������    : msg ��Ϣ�ṹ��hwnd ���ھ��
//  ���ļ�¼	:
//**************************************************************************************
BOOL GetMessage(MSG *msg,HWND hwnd)
{
	MSG *msgbuff; 
#if 0	
	INT8U i;

	printf("iget=%d  ",MsgQueue.iGet);
	for(i=0;i<SYS_QUEUE_NUM;i++)
	{
		printf("%d ",MsgQueue.msg[i].message);
	}
	printf("\n");
#endif
	hwnd = hwnd;

	msgbuff = &MsgQueue.HGPriority;

	if(msgbuff->message!=0)
	{
		msg->hwnd = msgbuff->hwnd;
		msg->message = msgbuff->message;
		msg->wParam = msgbuff->wParam;

		msgbuff->message = 0;

		return TRUE;
	}
	else 
	{
		msgbuff = MsgQueue.pGet;

		if(msgbuff->message==0)
		{
			msgbuff->message = msgbuff->message;
			return FALSE;
		}
		//����Ĭ�ϻ�ȡ���ĵ�һ����Ϣ
		msg->hwnd = msgbuff->hwnd;
		msg->message = msgbuff->message;
		msg->wParam = msgbuff->wParam;


		msgbuff->message = 0;

		MsgQueue.iGet++;//ȡ��Ϣ��һ��
		MsgQueue.pGet++;//��Ϣ������ǰ�ƶ�һ��
		
		if(MsgQueue.iGet > SYS_QUEUE_NUM-1)
		{
			MsgQueue.iGet = 0;//ȡ��Ϣ��һ��
			MsgQueue.pGet = MsgQueue.msg;//��Ϣ������ǰ�ƶ�
		}
		return TRUE;
	}
}

#if 0
//**************************************************************************************
//	��������	: GetMessageNum	
//	����		: yzy	
//	ģ�鹦��	: ��ȡ��Ϣ������Ϣ�� 
//	����ֵ      : ��	
//  ��������    : 
//  ���ļ�¼	:
//**************************************************************************************
INT8U GetMessageNum(void)
{
	return MsgQueue.iSend;
}
#endif
#if 0
//**************************************************************************************
//	��������	: MonitorMessage	
//	����		: yzy	
//	ģ�鹦��	: ��Ϣ���м�� 
//	����ֵ      : ��	
//  ��������    : 
//  ���ļ�¼	:
//**************************************************************************************
void MonitorMessage(void)
{

}
#endif
#if 0
//**************************************************************************************
//	��������	: DefOSProc	
//	����		: yzy	
//	ģ�鹦��	: �����������Ϣ 
//	����ֵ      : ��	
//  ��������    : 
//  ���ļ�¼	:
//**************************************************************************************
 void DefOSProc(MSG *msg)
{
	switch(msg->message)
	{
		case WM_PREVPAGE://���ص���һ��ҳ��
			WinPreviousPage();
			break;
		case WM_NEXTPAGE://������һ��ҳ��
			WinSwichToNextPage();
			break;
		case WM_PAGESWITCH://ҳ���л�
			WinPageSwitch(msg->wParam);
			break;
		case WM_TIMER:
			TaskTimer[msg->wParam].Flag = FALSE;
			break;
		case WM_CREATE:
			OS_START();
			SendMessage(0,WM_LOGO,0);//��ʾlogo
			SendMessage(0,WM_USERINTT,0x00);//��ʼ���û�����
			
			break;
		default:
			break;
	}
	//return TRUE;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////
//----------------------ϵͳʱ��---------------------------------------------------------
#if 1
//***************************************************************************************
//  ��������	: GetSystemTime()	
//  ����        : yangzyun
//  ģ�鹦��	: ��ȡϵͳʱ��  
//  ��������    ��2015-9-1�� 	
//  ����������: 2015-9-1�� 
//  ���ļ�¼	:
//  ��ע        ��
//***************************************************************************************
void GetSystemTime(SYSTEMTIME *time)
{
	memcpy(time,&sSystemTime,sizeof(SYSTEMTIME));
}
//***************************************************************************************
//  ��������	: SetSystemTime()	
//  ����        : yangzyun
//  ģ�鹦��	: ����ϵͳʱ��  
//  ��������    ��2015-9-1�� 	
//  ����������: 2015-9-1�� 
//  ���ļ�¼	:
//  ��ע        ��
//***************************************************************************************
void SetSystemTime(SYSTEMTIME *time)
{
	memcpy(&sSystemTime,time,sizeof(SYSTEMTIME));
}
#endif
//***************************************************************************************
//  ��������	: SyStemTimeTask()	
//  ����        : yangzyun
//  ģ�鹦��	: ϵͳʱ������  
//  ��������    ��2015-9-1�� 	
//  ����������: 2015-9-1�� 
//  ���ļ�¼	:
//  ��ע        ��
//***************************************************************************************
void SyStemTimeTask(void)
{
#if DATE_ENABLE	
	INT8U leap=0;
#endif
	if(sSystemTime.Milliseconds >= 1000)
	{
		sSystemTime.Milliseconds -=1000;
		sSystemTime.Second ++;
		
		if(sSystemTime.Second > 59)
		{
			sSystemTime.Second -= 60;
			sSystemTime.Minute ++;

			if(sSystemTime.Minute > 59)
			{
				sSystemTime.Minute -= 60;
				sSystemTime.Hour ++;

			#if (!DATE_ENABLE)
				if(sSystemTime.Hour > 23)
				{
					sSystemTime.Hour = 0;
				}
			#endif
			}
		}
	}
#if DATE_ENABLE	
	if(sSystemTime.Hour > 23)
	{
		sSystemTime.Hour = 0;
		sSystemTime.Day ++;
		
		switch(sSystemTime.Month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(sSystemTime.Day > 31)
			{
				sSystemTime.Day = 1;
				sSystemTime.Month++;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if(sSystemTime.Day > 30)
			{
				sSystemTime.Day = 1;
				sSystemTime.Month++;
			}
			break;
		case 2:
			if(sSystemTime.Year%4 != 0) //���ܱ�4������,��������
			{
				leap=FALSE;
			}
			else
			{
				if (sSystemTime.Year%100==0)//�ܱ�100 ������
				{
					if (sSystemTime.Year%400==0) //���ܱ�400������,������
					{
						leap=TRUE;
					}
					else //�ܱ�100����,�����ܱ�400������,��������
					{
						leap=FALSE;
					}
				}
				else //�ܱ�4����,�����ܱ�100������Ϊ����
				{
					leap=TRUE;
				}
			}
			
			if(leap==FALSE)//��������
			{
				if(sSystemTime.Day > 28)
				{
					sSystemTime.Day = 1;
					sSystemTime.Month++;
				}
			}
			else
			{
				if(sSystemTime.Day > 29)
				{
					sSystemTime.Day = 1;
					sSystemTime.Month++;
				}
			}
			break;
		default:
			break;

		}

		if(sSystemTime.Month > 12)
		{
			sSystemTime.Month = 1;
			sSystemTime.Year ++;
		}
	}

#endif	
}


////////////////////////////////////////////////////////////////////////////////////////
//***************************************************************************************
//  ��������	: GetSoftVersion()	
//  ����        : yangzyun
//  ģ�鹦��	: ��ȡ�汾�� 
//  ��������    ��2015-9-1�� 	
//  ����������: 2015-9-1�� 
//  ���ļ�¼	:
//  ��ע        ��
//***************************************************************************************
void GetSoftVersion(char *ver)
{
	memcpy(ver,SOFT_VERSION,sizeof(SOFT_VERSION));
}


////////////////////////////////////////////////////////////////////////////////////////
//***************************************************************************************
//  ��������	: GetMCUInfor()	
//  ����        : yangzyun
//  ģ�鹦��	: ��ȡ�汾�� 
//  ��������    ��2020-5-129�� 	
//  ����������: 2020-5-129�� 
//  ���ļ�¼	:
//  ��ע        ��
//***************************************************************************************		
#define soft_add		"-"
#define soft_mcuinfo	"\",\"mcutype\":\"MM32F0131\",\"module\":\"WIFI\",\"flash\":64000,\"packsize\":1024,\"ver\":\""
#define soft_end		"\"}"
#define SOFT			soft_mcuinfo SOFT_VERSION soft_add SOFT_NUM soft_add SOFT_DATE soft_end
void GetMCUInfor(char *ver)
{
	char buff[200]="{\"cmd\":\"MCUInfor\",\"IMEI\":\"";

	strcat(buff,"888888888888888");
	strcat(buff,SOFT);
	
	memcpy(ver,buff,strlen(buff)+1);
}





