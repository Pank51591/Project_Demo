#include"config.h"
#include"windesktop.h"


WINHAND gWinDesktop;

INT8U equistate=0;
INT8U longkeycount=0;

enum desktop_FOCUS
{
	FOCUS_NULL,
	FOCUS_1,
	FOCUS_2,
	FOCUS_3,
	FOCUS_4,
	FOCUS_MAX=FOCUS_4
};


WINHAND* GetDesktopWin(void)
{
	return 	&gWinDesktop;
}

void PowerDwon(void)
{
	//LCDClearScreen(0);
	
}


static void UpdateStandby(void)
{
		
}


static BOOL KeyDownHand(INT8U key)
{
//	INT8U page;
	
	switch(key)
	{
	case VK_FLUSH://短按回到桌面
		{	

		}	
		break;
	case VK_REST:	
		{

		}
		break;
	case VK_REST_FLUSH:
		break;
	default:
		break;
	}

	return TRUE;
}


static BOOL LongKeyUpHand(INT8U key)
{
	switch(key)
	{
	case VK_FLUSH://
	{
		
	}break;
	case VK_REST://进入滤芯复位模式
	{
	
	}break;
	case VK_REST_FLUSH://长按3秒进入电解模式
	{

	}break;
	default:
		break;
	}
	return TRUE;
}



static BOOL LongKeyHand(INT8U key)
{
	switch(key)
	{
	case VK_FLUSH://长按选择键：进入配网模式
	{
		
		


	}break;
	case VK_REST://进入滤芯复位模式
	{
		
	}break;
	case VK_REST_FLUSH://长按3秒进入电解模式
	{

	}break;
	default:
		break;
	}
	return TRUE;
}



static BOOL KeyContinueHand(INT8U key)
{
	switch(key)
	{
	case VK_REST_FLUSH:
	{	
		longkeycount++;
		if(longkeycount<=1)//长按5秒进入配网模式     ，      长按3秒，1秒进入continue，1秒continue
		{
			longkeycount=1;
			
		}
	}break;
	case VK_REST:
		break;
	case VK_FLUSH:
		break;
	default:
		break;
	}

	return TRUE;
}


static BOOL WinProc(MSG *msg)
{
	if(gReg.WorkState==WORKSTATE_FCT)
	{
		//SendMessage(0, WM_PAGESWITCH, HWND_FCT);
	}

	switch(msg->message)
	{
	case WM_DISPLAY:
		if(gReg.WorkState==WORKSTATE_standby)
		{
			UpdateStandby();
		}
		else
		{
			DesktopUpdate();
		}break;
	case WM_KEYDOWN:
		longkeycount=0;
		if(systemseting.uartWifiError)//按任意键退出异常
		{
			systemseting.uartWifiError=0;
		}
		break;
	case WM_KEYUP:
		longkeycount=0;
		KeyDownHand(msg->wParam);
		break;
	case WM_KEYLONGUP:
		LongKeyUpHand(msg->wParam);
		break;
	case WM_KEYLONG:
		LongKeyHand(msg->wParam);
		break;
	case WM_KEYCONTINUE:
		KeyContinueHand(msg->wParam);
		break;
	case WM_KEYCLICK_3:
		//KeyCLICK_3(msg->wParam);
		break;	
	case WM_KEYCLICK_6:
		//KeyCLICK_6(msg->wParam);
		break;	
	default:
		DefWindowProc(msg);
		break;
	}
	return TRUE;
}

static void WinPageInit(void)
{

	//显示桌面界面
	DesktopUpdate();	
}

void WinDesktopInit(void)
{
	gWinDesktop.id = HWND_DESKTOP;
	gWinDesktop.focus = 0;
	gWinDesktop.focus = FOCUS_NULL;
	gWinDesktop.Init = WinPageInit;
	gWinDesktop.WinProc = WinProc;

	CreatePage(&gWinDesktop);
}

