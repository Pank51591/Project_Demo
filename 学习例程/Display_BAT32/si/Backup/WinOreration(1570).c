#include"config.h"
#include"winFilterSet.h"


WINHAND gWinFilterSet;



enum FILTERSET_FOCUS
{
	FOCUS_NULL,
	FOCUS_1,
	FOCUS_2,
	FOCUS_MAX=FOCUS_2
};





WINHAND* GetFilterSetWin(void)
{
	return 	&gWinFilterSet;
}



void RestFilter(INT8U focus)
{
	if(focus==FOCUS_1)
	{
		FilterReset_PCB();
	}
	else if(focus==FOCUS_2)
	{
		FilterReset_RO();
	}
}


static BOOL LongKeyHand(INT8U key)
{
	switch(key)
	{
	case VK_FLUSH:

		break;
	case VK_REST://³¤°´¸´Î»ÂËÐ¾
	{
		SetBeep(1,1);
		RestFilter(gWinFilterSet.focus);
		EQUI_UpdataState(WIFI_CMD_06);
		//SaveSysSeting();
		SendMessage(0, WM_PAGESWITCH, HWND_DESKTOP);
	}break;
	case VK_REST_FLUSH://
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
	case VK_SELECT:
		break;
	case VK_REST:
		break;
	case VK_REST_FLUSH:
		break;
	default:
		break;
	}

	return TRUE;
}


static void Update(void)
{
	INT8U focus=gWinFilterSet.focus;

	memset((INT8U*)&gDisplayReg,0x00,sizeof(DISPLAY_REG));


	if(focus==FOCUS_1)
	{
		if(systemseting.FilterLife_PCB==PCB_level_3){gDisplayReg.pcb_w_en = 1;gDisplayReg.pcb_w_flash = 1;}//PCB
		else if(systemseting.FilterLife_PCB==PCB_level_2){gDisplayReg.pcb_r_en = 1;gDisplayReg.pcb_r_flash = 1;}
		else {gDisplayReg.pcb_r_en = 1;gDisplayReg.pcb_r_flash = 1;}
	}
	else if(focus==FOCUS_2)
	{
		if(systemseting.FilterLife_RO==PCB_level_3){gDisplayReg.ro_w_en = 1;gDisplayReg.ro_w_flash = 1;}//RO
		else if(systemseting.FilterLife_RO==PCB_level_2){gDisplayReg.ro_r_en = 1;gDisplayReg.ro_r_flash = 1;}
		else {gDisplayReg.ro_r_en = 1;gDisplayReg.ro_r_flash = 1;}
	}	


	Uart_SendDisplay((INT8U*)&gDisplayReg,2);
}



static BOOL KeyDownHand(INT8U key)
{
	INT8U focus=gWinFilterSet.focus;

	switch(key)
	{
	case VK_FLUSH:
		{

		}
		break;
	case VK_REST:
		{
			focus++;
			if(focus>FOCUS_MAX)
			{
				focus = FOCUS_1;	
			}
			SetBeep(1,1);
		}
		break;
	case VK_REST_FLUSH:
		break;
	default:
		break;
	}

	gWinFilterSet.focus = focus;
	
	return TRUE;
}

static BOOL WinProc(MSG *msg)
{
	switch(msg->message)
	{
	case WM_DISPLAY:
		Update();
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		KeyDownHand(msg->wParam);
		break;
	case WM_KEYLONG:
		LongKeyHand(msg->wParam);
		break;
	case WM_KEYCONTINUE:
		KeyContinueHand(msg->wParam);
		break;
	default:
		DefWindowProc(msg);
		break;
	}
	return TRUE;
}

static void WinPageInit(void)
{
	systemseting.WinTimerCount=0;
	gWinFilterSet.focus = FOCUS_1;
}

void WinFilterSetInit(void)
{
	gWinFilterSet.id = HWND_FILTERSET;
	gWinFilterSet.item = 0;
	gWinFilterSet.focus = FOCUS_1;
	gWinFilterSet.Init = WinPageInit;
	gWinFilterSet.WinProc = WinProc;
	
	CreatePage(&gWinFilterSet);
}

