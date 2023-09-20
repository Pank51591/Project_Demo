#include"config.h"
#include"winOreration.h"


WINHAND gWinOreration;



enum FILTERSET_FOCUS
{
	FOCUS_NULL,
	FOCUS_1,
	FOCUS_2,
	FOCUS_3,
	FOCUS_MAX=FOCUS_3
};


enum LIST_item
{
	ITEM_1,
	ITEM_2,
	ITEM_3,
	ITEM_MAX=ITEM_3
};



WINHAND* GetOrerationWin(void)
{
	return 	&gWinOreration;
}



static void Update(void)
{
	INT8U item,focus;

	item = gWinOreration.item;
	focus = gWinOreration.focus;
	
	if(item==ITEM_1)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"-> Calibration      ");
			LcdWriteStrimg(1,0,"UI LED Brightness   ");
			LcdWriteStrimg(2,0,"Activate Clean      ");
			LcdWriteStrimg(3,0,"                    ");
		}
		/*else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"-> Shaken           ");
			LcdWriteStrimg(1,0,"Blended             ");
			LcdWriteStrimg(2,0,"Cold Flam           ");
			LcdWriteStrimg(3,0,"                    ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Shaken              ");
			LcdWriteStrimg(1,0,"-> Blended          ");
			LcdWriteStrimg(2,0,"Cold Flam           ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Shaken              ");
			LcdWriteStrimg(1,0,"Blended             ");
			LcdWriteStrimg(2,0,"-> Cold Flam        ");
			LcdWriteStrimg(3,0,"                    ");		
		}*/		
	}
	else if(item==ITEM_2)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Calibration         ");
			LcdWriteStrimg(1,0,"-> UI LED Brightness");
			LcdWriteStrimg(2,0,"Activate Clean      ");
			LcdWriteStrimg(3,0,"                    ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Brightness Level:   ");
			LcdWriteStrimg(1,0,"                    ");
			if(gUISet.Oreration.LEDLevel==LEDLevel_LOW)			LcdWriteStrimg(2,0,"Low                 ");
			if(gUISet.Oreration.LEDLevel==LEDLevel_LOW_Medium)	LcdWriteStrimg(2,0,"Low-Medium          ");
			if(gUISet.Oreration.LEDLevel==LEDLevel_Medium)		LcdWriteStrimg(2,0,"Medium              ");
			if(gUISet.Oreration.LEDLevel==LEDLevel_Medium_High)	LcdWriteStrimg(2,0,"Medium-High         ");
			if(gUISet.Oreration.LEDLevel==LEDLevel_High)		LcdWriteStrimg(2,0,"High                ");
			LcdWriteStrimg(3,0,"                    ");		
		}		
	}
	else if(item==ITEM_3)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Calibration         ");
			LcdWriteStrimg(1,0,"UI LED Brightness   ");
			LcdWriteStrimg(2,0,"-> Activate Clean   ");
			LcdWriteStrimg(3,0,"                    ");	
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"                    ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"Cleaning...         ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"                    ");
			LcdWriteStrimg(1,0,"        Done!       ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}		
	}	
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

static BOOL KeyDownHand(INT8U key)
{
	INT8U item=gWinOreration.item;
	INT8U focus=gWinOreration.focus;
	
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
			else if(item==ITEM_1)
			{
				if(focus>FOCUS_1)
				{
					focus--;
				}
				else 
				{
					focus=FOCUS_3;
				}			
			}
			else if(item==ITEM_2)
			{
				if(focus==FOCUS_NULL)
				{
					focus=FOCUS_1;
				}
				else 
				{
					if(gUISet.Oreration.LEDLevel<LEDLevel_High)gUISet.Oreration.LEDLevel++;
				}
			}
			else if(item==ITEM_3)
			{
				if(focus>FOCUS_1)
				{
					focus--;
				}
				else 
				{
					focus=FOCUS_2;
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
			else if(item==ITEM_1)
			{
				if(focus<FOCUS_3)
				{
					focus++;
				}
				else 
				{
					focus=FOCUS_1;
				}				
			}
			else if(item==ITEM_2)
			{
				if(focus==FOCUS_NULL)
				{
					focus=FOCUS_1;
				}
				else 
				{
					if(gUISet.Oreration.LEDLevel>LEDLevel_LOW)gUISet.Oreration.LEDLevel--;
				}				
			}
			else if(item==ITEM_3)
			{
				if(focus<FOCUS_2)
				{
					focus++;
				}
				else 
				{
					focus=FOCUS_1;
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
					//focus=FOCUS_1;
					SendMessage(0, WM_PAGESWITCH, HWND_TypeSize);
				}
				/*else if(focus==FOCUS_1)
				{
					SendMessage(0, WM_PAGESWITCH, HWND_TypeSize);
				}
				else if(focus==FOCUS_2)
				{
					SendMessage(0, WM_PAGESWITCH, HWND_TypeSize);
				}
				else if(focus==FOCUS_3)
				{
					SendMessage(0, WM_PAGESWITCH, HWND_TypeSize);
				}	
				else 
				{
					focus=FOCUS_1;
					
				}*/
			}
			else if(item==ITEM_2)
			{
				if(focus==FOCUS_NULL)
				{
					focus=FOCUS_1;
				}	
				else 
				{
					focus=FOCUS_NULL;
					SaveSysSeting();
				}
			}
			else if(item==ITEM_3)
			{
				if(focus==FOCUS_NULL)
				{
					focus=FOCUS_1;
				}
				else if(focus==FOCUS_1)
				{
					
				}
				else if(focus==FOCUS_2)
				{
					
				}
				else if(focus==FOCUS_3)
				{
					
				}	
				else 
				{
					focus=FOCUS_1;
				}
			}
		}
		break;
	case VK_RETUN:	
		{
			if(item==ITEM_1)
			{
				if(focus==FOCUS_NULL)
				{
					SendMessage(0, WM_PAGESWITCH, HWND_DESKTOP);
				}
			}
			else if(item==ITEM_2)
			{
				if(focus==FOCUS_1)
				{
					focus=FOCUS_NULL;
					SaveSysSeting();	
				}
			}
			else if(item==ITEM_3)
			{
				if(focus==FOCUS_NULL)
				{
					SendMessage(0, WM_PAGESWITCH, HWND_DESKTOP);
				}
				else 
				{
					focus=FOCUS_NULL;
				}
			}
			else 
			{
				item=ITEM_1;
				focus=FOCUS_NULL;
			}
		}
		break;		
	default:
		break;
	}

	gWinOreration.item=item;
	gWinOreration.focus=focus;
	
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
	gWinOreration.item = ITEM_1;
	gWinOreration.focus = FOCUS_NULL;

	if(gUISet.Oreration.LEDLevel>LEDLevel_High)
	{
		gUISet.Oreration.LEDLevel=LEDLevel_High;
	}
}

void WinOrerationInit(void)
{
	gWinOreration.id = HWND_Oreration;
	gWinOreration.item = ITEM_1;
	gWinOreration.focus = FOCUS_NULL;
	gWinOreration.Init = WinPageInit;
	gWinOreration.WinProc = WinProc;
	
	CreatePage(&gWinOreration);
}

