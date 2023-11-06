#include"config.h"
#include"system.h"

#ifndef SYS_TIMER_NUM
//#define SYS_TASK_NUM	1
#endif




 SYSTIMER TaskTimer[SYS_TIMER_NUM];//任务定时器 

 MSGQUEUE	MsgQueue;//消息队列

 SYSTEMTIME sSystemTime;

//**************************************************************************************
//	函数名称	: SYSInit	
//	作者		: yzy	
//	模块功能	: 系统初始化
//	返回值      : 无	
//  参数介绍    : 
//  更改记录	:
//**************************************************************************************
void SYSInit(void)
{
	//MSG *msg;
	INT8U i;

	//任务初始化
	//
	//
	//定时器初始化

	memset(TaskTimer,0,sizeof(TaskTimer));
	for(i=0;i<SYS_TIMER_NUM;i++)
	{
		TaskTimer[i].IDEvent = SYS_TIMER_FREEID;
	}

	//消息队列初始化
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

	//窗口初始化
	WinInit();
	
	SendMessage(0,WM_CREATE,0x00);//系统开始运行

}
#if 0
//**************************************************************************************
//	函数名称	: SetTimer	
//	作者		: yzy	
//	模块功能	: 定时器 
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : hwnd 定时窗口句柄，nIDEvent定时器ID，nElapse定时时间单位ms
//  更改记录	:
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
//	函数名称	: TimeSetEvent	
//	作者		: yzy	
//	模块功能	: 定时器 
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : nIDEventID，uDelay延时时间(单位ms)pTimeProc回调函数，fuEvent为定时器的事件类型
//  更改记录	:
//**************************************************************************************
BOOL TimeSetEvent(INT8U nIDEvent,INT32U nElapse,TIMERPROC lpTimeProc,BOOL fuEvent)
{
	if(TaskTimer[nIDEvent].IDEvent != SYS_TIMER_FREEID)
	{
		return FALSE;	
	}//UartSendString("TimeSetEvent start……\r\nr");UartSendNumber((INT16U)lpTimeProc);
	TaskTimer[nIDEvent].hwnd = 0;
	TaskTimer[nIDEvent].IDEvent = nIDEvent;
	TaskTimer[nIDEvent].nElapse = nElapse;
	TaskTimer[nIDEvent].nElapseBuff= nElapse;
	TaskTimer[nIDEvent].Flag = FALSE;
	TaskTimer[nIDEvent].State = ENABLE;
	TaskTimer[nIDEvent].Mode = fuEvent;
	TaskTimer[nIDEvent].MonitorFlag = FALSE;
	TaskTimer[nIDEvent].TimerFunc = lpTimeProc;
	//UartSendString("TimeSetEvent 0k……");
	return TRUE; 
}
#if 0
//**************************************************************************************
//	函数名称	: SetDelayTimer	
//	作者		: yzy	
//	模块功能	: 定时器 
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : nIDEvent定时器ID，nElapse定时时间单位ms
//  更改记录	:
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
//	函数名称	: KillTimer	
//	作者		: yzy	
//	模块功能	: 定时器销毁 
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : hwnd 定时任务号，nIDEvent定时器ID
//  更改记录	:
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
//	函数名称	: TimerPause	
//	作者		: yzy	
//	模块功能	: 定时器暂停 
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : hwnd 定时任务号，nIDEvent定时器ID
//  更改记录	:
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
//	函数名称	: TimerStart	
//	作者		: yzy	
//	模块功能	: 定时器开始计时
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : hwnd 定时任务号，nIDEvent定时器ID
//  更改记录	:
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
//	函数名称	: GetTimerFlag	
//	作者		: yzy	
//	模块功能	: 获取定时器定时标志
//	返回值      : 定时时间到返回1，定时时间没到返回0	
//  参数介绍    : nIDEvent定时器ID号
//  更改记录	:
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
//	函数名称	: MonitorTimer	
//	作者		: yzy	
//	模块功能	: 监控定时情况，并处理相应功能
//	返回值      : 无	
//  参数介绍    : 
//  更改记录	:
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
			
			if(TaskTimer[id].Mode==TIME_PERIODIC)//如果是多次循环使用，那么不清除
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
			else//如果没有回调函数则发送 定时消息
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
//	函数名称	: SendMessage()	
//	作者		: yzy	
//	模块功能	: 发送最高优先级消息，
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : msg 消息结构，hwnd 窗口句柄
//  更改记录	: 这条消息作为系统的下一条要处理的消息，优先级最高
//**************************************************************************************
BOOL SendHGPriotityMessage(HWND hWnd,INT8U Msg, WPARAM wParam)
{
	MSG *msgbuff;

	msgbuff = (MSG*)(&MsgQueue.HGPriority);
	
	//消息队列已经满
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
//	函数名称	: SendMessage()	
//	作者		: yzy	
//	模块功能	: 发送消息到消息队列
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : msg 消息结构，hwnd 窗口句柄
//  更改记录	:
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
  
	//消息队列已经满
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
//	函数名称	: GetMessage	
//	作者		: yzy	
//	模块功能	: 获取消息队列的消息 
//	返回值      : 成功返回1，失败返回0	
//  参数介绍    : msg 消息结构，hwnd 窗口句柄
//  更改记录	:
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
		//这里默认获取它的第一个消息
		msg->hwnd = msgbuff->hwnd;
		msg->message = msgbuff->message;
		msg->wParam = msgbuff->wParam;


		msgbuff->message = 0;

		MsgQueue.iGet++;//取消息加一个
		MsgQueue.pGet++;//消息队列向前移动一个
		
		if(MsgQueue.iGet > SYS_QUEUE_NUM-1)
		{
			MsgQueue.iGet = 0;//取消息加一个
			MsgQueue.pGet = MsgQueue.msg;//消息队列向前移动
		}
		return TRUE;
	}
}

#if 0
//**************************************************************************************
//	函数名称	: GetMessageNum	
//	作者		: yzy	
//	模块功能	: 获取消息队列消息量 
//	返回值      : 无	
//  参数介绍    : 
//  更改记录	:
//**************************************************************************************
INT8U GetMessageNum(void)
{
	return MsgQueue.iSend;
}
#endif
#if 0
//**************************************************************************************
//	函数名称	: MonitorMessage	
//	作者		: yzy	
//	模块功能	: 消息队列监控 
//	返回值      : 无	
//  参数介绍    : 
//  更改记录	:
//**************************************************************************************
void MonitorMessage(void)
{

}
#endif
#if 0
//**************************************************************************************
//	函数名称	: DefOSProc	
//	作者		: yzy	
//	模块功能	: 处理其余的消息 
//	返回值      : 无	
//  参数介绍    : 
//  更改记录	:
//**************************************************************************************
 void DefOSProc(MSG *msg)
{
	switch(msg->message)
	{
		case WM_PREVPAGE://返回到上一个页面
			WinPreviousPage();
			break;
		case WM_NEXTPAGE://进入下一个页面
			WinSwichToNextPage();
			break;
		case WM_PAGESWITCH://页面切换
			WinPageSwitch(msg->wParam);
			break;
		case WM_TIMER:
			TaskTimer[msg->wParam].Flag = FALSE;
			break;
		case WM_CREATE:
			OS_START();
			SendMessage(0,WM_LOGO,0);//显示logo
			SendMessage(0,WM_USERINTT,0x00);//初始化用户数据
			
			break;
		default:
			break;
	}
	//return TRUE;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////
//----------------------系统时间---------------------------------------------------------
#if 1
//***************************************************************************************
//  函数名称	: GetSystemTime()	
//  作者        : yangzyun
//  模块功能	: 获取系统时间  
//  创建日期    ：2015-9-1晚 	
//  最后更正日期: 2015-9-1晚 
//  更改记录	:
//  备注        ：
//***************************************************************************************
void GetSystemTime(SYSTEMTIME *time)
{
	memcpy(time,&sSystemTime,sizeof(SYSTEMTIME));
}
//***************************************************************************************
//  函数名称	: SetSystemTime()	
//  作者        : yangzyun
//  模块功能	: 设置系统时间  
//  创建日期    ：2015-9-1晚 	
//  最后更正日期: 2015-9-1晚 
//  更改记录	:
//  备注        ：
//***************************************************************************************
void SetSystemTime(SYSTEMTIME *time)
{
	memcpy(&sSystemTime,time,sizeof(SYSTEMTIME));
}
#endif
//***************************************************************************************
//  函数名称	: SyStemTimeTask()	
//  作者        : yangzyun
//  模块功能	: 系统时间任务  
//  创建日期    ：2015-9-1晚 	
//  最后更正日期: 2015-9-1晚 
//  更改记录	:
//  备注        ：
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
			if(sSystemTime.Year%4 != 0) //不能被4整除的,不是闰年
			{
				leap=FALSE;
			}
			else
			{
				if (sSystemTime.Year%100==0)//能被100 整除的
				{
					if (sSystemTime.Year%400==0) //且能被400整除的,是闰年
					{
						leap=TRUE;
					}
					else //能被100整除,但不能被400整除的,不是闰年
					{
						leap=FALSE;
					}
				}
				else //能被4整除,但不能被100整除的为闰年
				{
					leap=TRUE;
				}
			}
			
			if(leap==FALSE)//不是闰年
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
//  函数名称	: GetSoftVersion()	
//  作者        : yangzyun
//  模块功能	: 获取版本号 
//  创建日期    ：2015-9-1晚 	
//  最后更正日期: 2015-9-1晚 
//  更改记录	:
//  备注        ：
//***************************************************************************************
void GetSoftVersion(char *ver)
{
	memcpy(ver,SOFT_VERSION,sizeof(SOFT_VERSION));
}


////////////////////////////////////////////////////////////////////////////////////////
//***************************************************************************************
//  函数名称	: GetMCUInfor()	
//  作者        : yangzyun
//  模块功能	: 获取版本号 
//  创建日期    ：2020-5-129晚 	
//  最后更正日期: 2020-5-129晚 
//  更改记录	:
//  备注        ：
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





