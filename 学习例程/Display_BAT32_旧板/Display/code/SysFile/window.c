#include"config.h"
#include"window.h"



/*static*/ WINHAND *spWinBuff[HWND_MAX];
/*static*/ WINHAND *spWinHand=&gWinDesktop;
/*static*/ WINHAND *spWinFatherHand=&gWinDesktop;//����




#if 1
HWND CreatePage(WINHAND *win)
{
	INT8U id;
	id = win->id;
	spWinBuff[id] = win;

	return id;
}
#endif


//��ȡ��ǰ���ھ��
HWND GetActiveWindow(void)
{
	return spWinHand->id;
}

//��ȡ����(֮ǰһ��)���ھ��
HWND GetParent(void)
{
	return spWinFatherHand->id;
}


BOOL SetCursorPos(INT8U item,INT8U focus)
{
	spWinHand->item = item;
	spWinHand->focus = focus;

	return TRUE;
}


BOOL GetCursorPos(LPPOINT point)
{
	point->item = spWinHand->item;
	point->focus = spWinHand->focus;

	return TRUE;
}


void WinInit(void)
{
	INT8U i;

	for(i=0;i<HWND_MAX;i++)
	{
		spWinBuff[i] = &gWinDesktop;
	}
	
	WinDesktopInit();//����
	
	WinOrerationInit();
	WinServiceInit();
	WinDataInit();
	WinLEDLevelInit();
	WinTypeSizeInit();
	WinDispenseCntInit();
}


BOOL WinPageSwitch(HWND hwnd)
{
	INT8U i;
	
	for(i=0;i<HWND_MAX;i++)
	{
		if(spWinBuff[i]->id == hwnd)
		{
			spWinFatherHand = spWinHand;
			//KillTimer(0, SYS_TIMER_WINTIMEOUT);
			spWinHand = spWinBuff[i];
			spWinHand->Init();

			return TRUE;
		}
	}	
	
	return FALSE;
}


 BOOL DISWinProc(MSG *msg);

void WndProc(MSG *msg)
{	
	if(msg->message==WM_KEYDOWN)
	{	
		systemseting.WinTimerCount=0;
		systemseting.WinTimerOutFlag=0;
		StandbyRestart();
		TimeSetEvent(SYS_TIMER_WINTIMEOUT,sec(1), WinTimerOut, TIME_PERIODIC);
	}	
	//else
	{
		if(systemseting.WinTimerOutFlag)//���泬ʱ�˻�����
		{
			if(spWinHand->id!=HWND_DESKTOP&&spWinHand->id!=HWND_FCT)
			{
				SendMessage(0,WM_PAGESWITCH, HWND_DESKTOP); 
			}
		}
		else if(msg->message==WM_KEYCONTINUE)
		{
			systemseting.BackTimerCount=0;
		}   
		
		if(spWinHand->id<HWND_INVALID)
		{
			spWinHand->WinProc(msg);			
		}
		else
		{
			DefWindowProc(msg);
		}		
	}	
}



void DefWindowProc(MSG *msg)
{
	
	switch(msg->message)
	{
	case WM_NONE:
		break;
	case WM_POWERLOW:
		break;
	case WM_TIMERAPP:
	
		break;
	case WM_ALARM:
		break;
	case WM_SERIALRXD:
		break;
	case WM_USERSTARTPROC:
		break;
	case WM_PAGESWITCH://ҳ���л�
		WinPageSwitch(msg->wParam);
		break;
	case WM_TIMER:
		break;
	case WM_CREATE:
		OS_START();
		SendMessage(0,WM_LOGO,0);//��ʾlogo
		SendMessage(0,WM_USERINTT,0x00);//��ʼ���û�����
		break;
	case WM_LOGO:
	{

	}break;
	case WM_USERINTT:
	{
		WinPageSwitch(HWND_DESKTOP);
	}
	break;		
	default:
		//DefOSProc(msg);
	break; 
	}
}




