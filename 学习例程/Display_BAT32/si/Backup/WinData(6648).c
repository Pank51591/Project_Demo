#include"config.h"
#include"WinData.h"


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
	INT8U item,focus;
	char buf[20];

	item = gWinData.item;
	focus = gWinData.focus;

	//size = gUISet.Type[0].Size;
	
	if(item==ITEM_1)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"-> Total On Time    ");
			LcdWriteStrimg(1,0,"Total Dispense Time ");
			LcdWriteStrimg(2,0,"Dispense Counts     ");
			LcdWriteStrimg(3,0,"Last Clean          ");			
		}
		else if(focus==FOCUS_1)
		{ 
			LcdWriteStrimg(0,0,"Total On Time:      ");
			snprintf(buf, 20, "%d year              ", gUISet.Data.TotalOnTime.year);
			LcdWriteStrimg(1,0,buf);
			snprintf(buf, 20, "%d months            ", gUISet.Data.TotalOnTime.months);
			LcdWriteStrimg(2,0,buf);
			snprintf(buf, 20, "%d days              ", gUISet.Data.TotalOnTime.days);
			LcdWriteStrimg(3,0,buf);		
		}		
	}
	else if(item==ITEM_2)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Total On Time       ");
			LcdWriteStrimg(1,0,"->Total Disp. Time  ");
			LcdWriteStrimg(2,0,"Dispense Counts     ");
			LcdWriteStrimg(3,0,"Last Clean          ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Total Disp. Time    ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "%d hours             ", gUISet.Data.TotalDispTime);
			LcdWriteStrimg(3,0,buf);		
		}
	}
	else if(item==ITEM_3)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Total On Time       ");
			LcdWriteStrimg(1,0,"Total Dispense Time ");
			LcdWriteStrimg(2,0,"-> Dispense Counts  ");
			LcdWriteStrimg(3,0,"Last Clean          "); 
		}
	}
	else if(item==ITEM_4)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Total On Time       ");
			LcdWriteStrimg(1,0,"Total Dispense Time ");
			LcdWriteStrimg(2,0,"Dispense Counts     ");
			LcdWriteStrimg(3,0,"-> Last Clean       ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Time Since Last:    ");
			LcdWriteStrimg(1,0,"                    ");
			snprintf(buf, 20, "%d months	            ", gUISet.Data.LastClean.months);
			LcdWriteStrimg(2,0,buf);
			snprintf(buf, 20, "%d days              ", gUISet.Data.LastClean.days);
			LcdWriteStrimg(3,0,buf);
		}		
	}	

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
			SendMessage(0, WM_PAGESWITCH, HWND_DESKTOP);
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

