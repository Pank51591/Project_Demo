#include"config.h"
#include"WinService.h"


WINHAND gWinService;



enum FILTERSET_FOCUS
{
	FOCUS_NULL,
	FOCUS_1,
	FOCUS_2,
	FOCUS_3,
	FOCUS_4,
	FOCUS_MAX=FOCUS_4
};


enum LIST_item
{
	ITEM_1,
	ITEM_2,
	ITEM_MAX=ITEM_2
};



WINHAND* GetServiceWin(void)
{
	return 	&gWinService;
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

static const char keyval[16][21]=
{
	"Shaken : null       ",
	"Blended : null      ",
	"Cold Flam : null    ",

	"Shaken : Tall       ",
	"Shaken : Grande     ",
	"Shaken : Venti      ",
	"Shaken : Trenta     ",
	
	"Blended : Tall      ",
	"Blended : Grande    ",
	"Blended : Venti     ",
	"Blended : Trenta    ",

	"Cold Flam : Tall    ",
	"Cold Flam : Grande  ",
	"Cold Flam : Venti   ",
	"Cold Flam : Trenta  ",

	"FLOW                ",
};



static void Update(void)
{
	INT8U item,focus;
	char buf[30];
	
	item = gWinService.item;
	focus = gWinService.focus;

	if(gUISet.Service.MainButtonTestFlag)
	{
		systemseting.WinTimerCount=0;
	}
	
	if(item==ITEM_1)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"-> Button Test      ");
			LcdWriteStrimg(1,0,"Sensor Readouts     ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");			
		}
		else if(focus==FOCUS_1)
		{
			if(gUISet.Service.MainButtonTestVal>=0&&gUISet.Service.MainButtonTestVal<=15)
			{
				LcdWriteStrimg(0,0,keyval[gUISet.Service.MainButtonTestVal]);
			}
			else 
			{
				LcdWriteStrimg(0,0,"                    ");
			}
			
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");			
		}		
	}
	else if(item==ITEM_2)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Button Test         ");
			LcdWriteStrimg(1,0,"-> Sensor Readouts  ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"-> Low Level        ");
			LcdWriteStrimg(1,0,"Drip Tray           ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");	
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Low Level           ");
			LcdWriteStrimg(1,0,"-> Drip Tray        ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");	
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Low Level Test      ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "Status: %s        ", gUISet.Service.LowLevel?"HIGH":"LOW ");
			LcdWriteStrimg(3,0,buf);		
		}
		else if(focus==FOCUS_4)
		{
			LcdWriteStrimg(0,0,"Drig Tray Test      ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "Status: %s        ", gUISet.Service.DripTray?"HIGH":"LOW ");
			LcdWriteStrimg(3,0,buf);		
		}		
	}
}



static BOOL KeyDownHand(INT8U key)
{
	INT8U item,focus;
	
	item = gWinService.item;
	focus = gWinService.focus;

	
	switch(key)
	{
	case VK_UP://
		{	
			if(focus==FOCUS_NULL)
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
			else 
			{
				if(item==ITEM_2)
				{
					if(focus==FOCUS_1)
					{
						focus=FOCUS_2;
					}
					else 
					{
						focus=FOCUS_1;
					}
				}				
			}
		}	
		break;
	case VK_DOWN:	
		{
			if(focus==FOCUS_NULL)
			{
				if(item<ITEM_MAX)
				{
					item++;
				}
				else 
				{
					item=ITEM_1;
				}
			}
			else 
			{
				if(item==ITEM_2)
				{
					if(focus==FOCUS_1)
					{
						focus=FOCUS_2;
					}
					else 
					{
						focus=FOCUS_1;
					}
				}
			}
		}
		break;
	case VK_SELECT:	
		{
			if(item==ITEM_1)
			{
				if(focus==FOCUS_NULL)
				{
					focus=FOCUS_1;
					gUISet.Service.MainButtonTestFlag=1;
					systemseting.StateChangeFlag=1;
				}
				else 
				{
					focus=FOCUS_NULL;
					gUISet.Service.MainButtonTestFlag=0;
					systemseting.StateChangeFlag=1;
				}
			}
			else if(item==ITEM_2)
			{
				if(focus==FOCUS_NULL)
				{
					focus=FOCUS_1;
				}
				else if(focus==FOCUS_1)
				{
					focus=FOCUS_3;
				}
				else if(focus==FOCUS_2)
				{
					focus=FOCUS_4;
				}
				else if(focus==FOCUS_3)
				{
					focus=FOCUS_1;
				}
				else if(focus==FOCUS_4)
				{
					focus=FOCUS_2;
				}
				else 
				{
					focus=FOCUS_NULL;
				}
			}			
		}
		break;
	case VK_RETUN:
		if(focus==FOCUS_NULL)
		{
			gUISet.Service.MainButtonTestFlag=0;systemseting.StateChangeFlag=1;
			SendMessage(0, WM_PAGESWITCH, HWND_DESKTOP);
			break;
		}
		else 
		{
			if(item==ITEM_1)
			{
				focus=FOCUS_NULL;
				gUISet.Service.MainButtonTestFlag=0;systemseting.StateChangeFlag=1;
			}
			else if(item==ITEM_2)
			{
				if(focus==FOCUS_3)
				{
					focus=FOCUS_1;
				}
				else if(focus==FOCUS_4)
				{
					focus=FOCUS_2;
				}
				else 
				{
					focus=FOCUS_NULL;
				}
			}			
		}
		break;		
	default:
		break;
	}

	gWinService.item=item;
	gWinService.focus=focus;
	
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
	gWinService.focus = FOCUS_NULL;
	gWinService.item = ITEM_1;
}

void WinServiceInit(void)
{
	gWinService.id = HWND_Service;
	gWinService.item = ITEM_1;
	gWinService.focus = FOCUS_NULL;
	gWinService.Init = WinPageInit;
	gWinService.WinProc = WinProc;
	
	CreatePage(&gWinService);
}

