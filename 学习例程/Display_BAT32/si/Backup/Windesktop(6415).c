#include"config.h"
#include"windesktop.h"


WINHAND gWinDesktop;

INT8U equistate=0;
INT8U longkeycount=0;

enum LIST_focus
{
	FOCUS_NULL,
	FOCUS_1,
	FOCUS_MAX=FOCUS_1
};

enum LIST_item
{
	ITEM_1,
	ITEM_2,
	ITEM_3,
	ITEM_MAX=ITEM_3
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
void DesktopUpdate(void)
{
	INT8U item;

	if(systemseting.pc_en)
	{
		LcdWriteStrimg(0,0,"                    ");
		LcdWriteStrimg(1,0,"      PC mode       ");
		LcdWriteStrimg(2,0,"                    ");
		LcdWriteStrimg(3,0,"                    ");
		return;
	}
	else if(systemseting.uartdisplayError)//通讯错误
	{
		LcdWriteStrimg(0,0,"                    ");
		LcdWriteStrimg(1,0,"Communication error ");
		LcdWriteStrimg(2,0,"   please check     ");
		LcdWriteStrimg(3,0,"                    ");		
		return;
	}	

	item = gWinDesktop.item;
	
	if(item==ITEM_1)
	{
		LcdWriteStrimg(0,0,"->Oreration Menu    ");
		LcdWriteStrimg(1,0,"Service Menu        ");
		LcdWriteStrimg(2,0,"Data Menu           ");
		LcdWriteStrimg(3,0,"                    ");
	}
	else if(item==ITEM_2)
	{
		LcdWriteStrimg(0,0,"Oreration Menu      ");
		LcdWriteStrimg(1,0,"->Service Menu      ");
		LcdWriteStrimg(2,0,"Data Menu           ");
		LcdWriteStrimg(3,0,"                    ");
	}
	else if(item==ITEM_3)
	{
		LcdWriteStrimg(0,0,"Oreration Menu      ");
		LcdWriteStrimg(1,0,"Service Menu        ");
		LcdWriteStrimg(2,0,"->Data Menu         ");
		LcdWriteStrimg(3,0,"                    ");		
	}	
}


static BOOL KeyDownHand(INT8U key)
{
	INT8U item=gWinDesktop.item;

	if(systemseting.uartdisplayError)
	{
		return 0;
	}
	
	switch(key)
	{
	case VK_UP://
		{	
			if(item>ITEM_1)
			{
				item--;
			}
			else 
			{
				item=ITEM_MAX;
			}
		}	
		break;
	case VK_DOWN:	
		{
			if(item<ITEM_3)
			{
				item++;
			}
			else 
			{
				item=ITEM_1;
			}
		}
		break;
	case VK_SELECT:	
		{
			if(item==ITEM_1)
			{
				SendMessage(0, WM_PAGESWITCH, HWND_Oreration);
			}
			else if(item==ITEM_2)
			{
				SendMessage(0, WM_PAGESWITCH, HWND_Service);
			}
			else if(item==ITEM_3)
			{
				SendMessage(0, WM_PAGESWITCH, HWND_Data);
			}			
		}
		break;
	case VK_RETUN:	
		{

		}
		break;		
	default:
		break;
	}

	gWinDesktop.item=item;

	return TRUE;
}


static BOOL LongKeyUpHand(INT8U key)
{
	switch(key)
	{
	case VK_UP://
	{
		
	}break;
	case VK_DOWN://进入滤芯复位模式
	{
	
	}break;
	case VK_SELECT://长按3秒进入电解模式
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
	case VK_UP://长按选择键：进入配网模式
	{
		
		


	}break;
	case VK_DOWN://进入滤芯复位模式
	{
		
	}break;
	case VK_SELECT://长按3秒进入电解模式
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
	case VK_UP:
	{	
		longkeycount++;
		if(longkeycount<=1)//长按5秒进入配网模式     ，      长按3秒，1秒进入continue，1秒continue
		{
			longkeycount=1;
			
		}
	}break;
	case VK_DOWN:
		break;
	case VK_SELECT:
		break;
	default:
		break;
	}

	return TRUE;
}


static BOOL WinProc(MSG *msg)
{
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
	gWinDesktop.item = ITEM_1;
	gWinDesktop.focus = FOCUS_1;
	gWinDesktop.Init = WinPageInit;
	gWinDesktop.WinProc = WinProc;

	CreatePage(&gWinDesktop);
}

