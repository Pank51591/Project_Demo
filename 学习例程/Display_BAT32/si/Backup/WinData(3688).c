#include"config.h"
#include"winData.h"


WINHAND gWinData;



enum FILTERSET_FOCUS
{
	FOCUS_NULL,
	FOCUS_1,
	FOCUS_2,
	FOCUS_MAX=FOCUS_2
};


enum LIST_item
{
	ITEM_1,
	ITEM_2,
	ITEM_3,
	ITEM_4,
	ITEM_MAX=ITEM_4
};



WINHAND* GetDataWin(void)
{
	return 	&gWinData;
}






static BOOL LongKeyHand(INT8U key)
{
	switch(key)
	{
	case VK_UP:

		break;
	case VK_DOWN://
	{
	
	}break;
	case VK_SELECT://
	{

		
	}break;
	case VK_RETUN://
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
		break;
	case VK_DOWN:
		break;
	case VK_SELECT:
		break;
	case VK_RETUN:
		break;		
	default:
		break;
	}

	return TRUE;
}


static void Update(void)
{

}



static BOOL KeyDownHand(INT8U key)
{
	INT8U item=gWinData.item;
	
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
	gWinData.focus = FOCUS_1;
}

void WinDataInit(void)
{
	gWinData.id = HWND_Data;
	gWinData.item = ITEM_1;
	gWinData.focus = FOCUS_1;
	gWinData.Init = WinPageInit;
	gWinData.WinProc = WinProc;
	
	CreatePage(&gWinData);
}

