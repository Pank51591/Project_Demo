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


static INT8U doubleFlag=0;


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
	memset((INT8U*)&gDisplayReg,0x00,sizeof(DISPLAY_REG));
	I2C_SendDisplay((INT8U*)&gDisplayReg,2);		
}


static BOOL KeyDownHand(INT8U key)
{
//	INT8U page;
	
	switch(key)
	{
	case VK_FLUSH://短按回到桌面
		{	
			if(gReg.WorkState==WORKSTATE_PowerOnFlush
			||gReg.WorkState==WORKSTATE_autoflush
			||gReg.WorkState==WORKSTATE_manualflush)
			{
				ExitManualFlush();
			}
			else 
			{
				systemseting.ManualFlushFlag=1;
			}
		}	
		break;
	case VK_REST:	
		{
			/*if(gReg.WorkState==WORKSTATE_PowerOnFlush
			||gReg.WorkState==WORKSTATE_autoflush
			||gReg.WorkState==WORKSTATE_manualflush)
			{
				ExitManualFlush();
			}*/
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


void AllLedFlashTimes(INT8U times,INT8U led)
{
	INT8U i;

	gDisplayReg.run_w_en = 0;gDisplayReg.run_w_flash = 0;
	gDisplayReg.pcb_w_en = 0;gDisplayReg.pcb_w_flash = 0;
	gDisplayReg.ro_w_en = 0;gDisplayReg.ro_w_flash = 0;
	gDisplayReg.wifi_w_en = 0;gDisplayReg.wifi_w_flash = 0;	

	gDisplayReg.run_r_en = 0;gDisplayReg.run_r_flash = 0;
	gDisplayReg.pcb_r_en = 0;gDisplayReg.pcb_r_flash = 0;
	gDisplayReg.ro_r_en = 0;gDisplayReg.ro_r_flash = 0;
	gDisplayReg.wifi_r_en = 0;gDisplayReg.wifi_r_flash = 0;	
	delayms(500);

	if(led==1)//红色
	{
		for(i=0;i<times;i++)
		{
			gDisplayReg.run_r_en = 1;gDisplayReg.run_r_flash = 0;
			gDisplayReg.pcb_r_en = 1;gDisplayReg.pcb_r_flash = 0;
			gDisplayReg.ro_r_en = 1;gDisplayReg.ro_r_flash = 0;
			gDisplayReg.wifi_r_en = 1;gDisplayReg.wifi_r_flash = 0;
			I2C_SendDisplay((INT8U*)&gDisplayReg,2);
			delayms(500);
			
			gDisplayReg.run_r_en = 0;gDisplayReg.run_r_flash = 0;
			gDisplayReg.pcb_r_en = 0;gDisplayReg.pcb_r_flash = 0;
			gDisplayReg.ro_r_en = 0;gDisplayReg.ro_r_flash = 0;
			gDisplayReg.wifi_r_en = 0;gDisplayReg.wifi_r_flash = 0;
			I2C_SendDisplay((INT8U*)&gDisplayReg,2);
			delayms(500);
		}		
	}
	else 
	{
		for(i=0;i<times;i++)
		{
			gDisplayReg.run_w_en = 1;gDisplayReg.run_w_flash = 0;
			gDisplayReg.pcb_w_en = 1;gDisplayReg.pcb_w_flash = 0;
			gDisplayReg.ro_w_en = 1;gDisplayReg.ro_w_flash = 0;
			gDisplayReg.wifi_w_en = 1;gDisplayReg.wifi_w_flash = 0;
			I2C_SendDisplay((INT8U*)&gDisplayReg,2);
			delayms(500);
			
			gDisplayReg.run_w_en = 0;gDisplayReg.run_w_flash = 0;
			gDisplayReg.pcb_w_en = 0;gDisplayReg.pcb_w_flash = 0;
			gDisplayReg.ro_w_en = 0;gDisplayReg.ro_w_flash = 0;
			gDisplayReg.wifi_w_en = 0;gDisplayReg.wifi_w_flash = 0;
			I2C_SendDisplay((INT8U*)&gDisplayReg,2);
			delayms(500);
		}		
	}

}

static BOOL LongKeyHand(INT8U key)
{
	switch(key)
	{
	case VK_FLUSH://长按选择键：进入配网模式
	{
		EQUI_EnterWifiNetwork();
	}break;
	case VK_REST://进入滤芯复位模式
	{
		SendMessage(0, WM_PAGESWITCH, HWND_FILTERSET);
	}break;
	case VK_REST_FLUSH://长按3秒进入电解模式
	{
		if(systemseting.PowerOnTimerCount<120)//上电一分钟前
		{
			if(gReg.fruits)//电解模
			{
				gReg.fruits=0;
				AllLedFlashTimes(2,1);//退出闪2次
			}
			else 
			{
				gReg.fruits=1;
				AllLedFlashTimes(3,1);//进入闪3次
			}
			gReg.error.BitFlag.sparklingWaterStatus = gReg.fruits;
		}
		else 
		{
			if(gReg.BackFlow)
			{
				gReg.BackFlow=0;
				AllLedFlashTimes(2,0);//退出闪2次
			}
			else 
			{
				gReg.BackFlow=1;
				AllLedFlashTimes(3,0);//进入闪3次
			}			
		}
		
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



//滤芯快检
void FilterFastInspection(MSG *msg)
{
	static INT8U dd=0;
	if(systemseting.PowerOnTimerCount>20)
	{
		doubleFlag = 0;
		return;
	}
	dd=msg->message;
	
	switch(dd)
	{
	case WM_KEYUP:
	{
		if(doubleFlag==1)
		{
			if(msg->wParam==VK_SELECT)
			{
				doubleFlag = 2;
			}
			else 
			{
				doubleFlag = 0;
			}			
		}	
		else if(doubleFlag==2)//上电10秒内，三击两键后，再短按“选择”，最后短按“复位”，进滤芯快检。途中必须满足这个顺序，不然就不再进入
		{
			if(msg->wParam==VK_REST)
			{
				FilterDetection();
			}
			doubleFlag = 0;			
		}
	}break;
	case WM_KEYCLICK_6:
	case WM_KEYCLICK_3:
	case WM_KEYLONG:
	case WM_KEYCONTINUE:
		doubleFlag = 0;
		break;	
	default:
		break;
	}
}

static BOOL WinProc(MSG *msg)
{
	if(gReg.WorkState==WORKSTATE_FCT)
	{
		SendMessage(0, WM_PAGESWITCH, HWND_FCT);
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

