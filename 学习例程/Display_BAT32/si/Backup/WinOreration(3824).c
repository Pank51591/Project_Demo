#include"config.h"
#include"winOreration.h"


WINHAND gWinOreration;



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
	ITEM_3,
	ITEM_4,
	ITEM_MAX=ITEM_4
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
			LcdWriteStrimg(0,0,"->Language Select   ");
			LcdWriteStrimg(1,0,"Calibration         ");
			LcdWriteStrimg(2,0,"Activate Clean      ");
			LcdWriteStrimg(3,0,"LED Level Set       ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"->English           ");
			LcdWriteStrimg(1,0,"French              ");
			LcdWriteStrimg(2,0,"Spanish             ");
			LcdWriteStrimg(3,0,"                    ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"English             ");
			LcdWriteStrimg(1,0,"->French            ");
			LcdWriteStrimg(2,0,"Spanish             ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"English             ");
			LcdWriteStrimg(1,0,"French              ");
			LcdWriteStrimg(2,0,"->Spanish           ");
			LcdWriteStrimg(3,0,"                    ");		
		}		
	}
	else if(item==ITEM_2)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Language Select     ");
			LcdWriteStrimg(1,0,"->Calibration       ");
			LcdWriteStrimg(2,0,"Activate Clean      ");
			LcdWriteStrimg(3,0,"LED Level Set       ");
		}
		else if(focus==FOCUS_1)
		{
		
		}
	}
	else if(item==ITEM_3)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Language Select     ");
			LcdWriteStrimg(1,0,"Calibration         ");
			LcdWriteStrimg(2,0,"->Activate Clean    ");
			LcdWriteStrimg(3,0,"LED Level Set       ");	
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Confirm...          ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Clean Initiated...  ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}		
	}	
	else if(item==ITEM_4)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Language Select     ");
			LcdWriteStrimg(1,0,"Calibration         ");
			LcdWriteStrimg(2,0,"Activate Clean      ");
			LcdWriteStrimg(3,0,"->LED Level Set     ");	
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Level: Low          ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Level: Medium       ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Level: High         ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_4)
		{
			LcdWriteStrimg(0,0,"Level: max          ");
			LcdWriteStrimg(1,0,"                    ");
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
				
			}
			else if(item==ITEM_3)
			{
				
			}
			else if(item==ITEM_4)
			{
				if(focus>FOCUS_1)
				{
					focus--;
				}
				else 
				{
					focus=FOCUS_4;
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
				
			}
			else if(item==ITEM_3)
			{
				
			}
			else if(item==ITEM_4)
			{
				if(focus<FOCUS_4)
				{
					focus++;
				}
				else 
				{
					focus=FOCUS_1;
				}
				
				if(focus==FOCUS_1)
				{
					gUISet.Oreration.LEDLevel=LEDLevel_LOW;
				}
				else if(focus==FOCUS_2)
				{
					gUISet.Oreration.LEDLevel=LEDLevel_Medium;
				}
				else if(focus==FOCUS_3)
				{
					gUISet.Oreration.LEDLevel=LEDLevel_High;
				}
				else if(focus==FOCUS_4)
				{
					gUISet.Oreration.LEDLevel=LEDLevel_max;
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
					focus=gUISet.Oreration.Language+FOCUS_1;
				}
				else if(focus==FOCUS_1)
				{
					focus=FOCUS_NULL;
					gUISet.Oreration.Language=Language_English;
				}
				else if(focus==FOCUS_2)
				{
					focus=FOCUS_NULL;
					gUISet.Oreration.Language=Language_French;
				}
				else if(focus==FOCUS_3)
				{
					focus=FOCUS_NULL;
					gUISet.Oreration.Language=Language_Spanish;
				}	
				else 
				{
					focus=FOCUS_1;
				}
			}
			else if(item==ITEM_2)
			{
				gUISet.Oreration.CalibrationFlag=1;
			}
			else if(item==ITEM_3)
			{
				if(focus==FOCUS_NULL)
				{
					focus=FOCUS_1;
				}
				else  if(focus==FOCUS_1)
				{
					focus=FOCUS_2;
				}
				else 
				{
					gUISet.Oreration.ActivateCleanFlag=1;
				}
			}
			else if(item==ITEM_4)
			{
				if(focus==FOCUS_NULL)
				{
					focus=gUISet.Oreration.LEDLevel+FOCUS_1;
				}
				else if(focus==FOCUS_1)
				{
					focus=FOCUS_NULL;
					gUISet.Oreration.LEDLevel=LEDLevel_LOW;
				}
				else if(focus==FOCUS_2)
				{
					focus=FOCUS_NULL;
					gUISet.Oreration.LEDLevel=LEDLevel_Medium;
				}
				else if(focus==FOCUS_3)
				{
					focus=FOCUS_NULL;
					gUISet.Oreration.LEDLevel=LEDLevel_High;
				}
				else if(focus==FOCUS_4)
				{
					focus=FOCUS_NULL;
					gUISet.Oreration.LEDLevel=LEDLevel_max;
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
			if(focus==FOCUS_NULL)
			{
				SendMessage(0, WM_PAGESWITCH, HWND_DESKTOP);
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

