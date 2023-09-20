#include"config.h"
#include"WinTypeSize.h"


WINHAND gWinTypeSize;



enum FILTERSET_FOCUS
{
	FOCUS_NULL,
	FOCUS_1,
	FOCUS_2,
	FOCUS_3,
	FOCUS_4,
	FOCUS_5,
	FOCUS_MAX=FOCUS_5
};


enum LIST_item
{
	ITEM_1,
	ITEM_2,
	ITEM_3,
	ITEM_MAX=ITEM_3
};



WINHAND* GetTypeSizeWin(void)
{
	return 	&gWinTypeSize;
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
	INT8U item,focus,size;
	char buf[20];

	item = gWinTypeSize.item;
	focus = gWinTypeSize.focus;

	//size = gUISet.Type[0].Size;
	
	if(item==ITEM_1)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"-> Shaken           ");
			LcdWriteStrimg(1,0,"Blended             ");
			LcdWriteStrimg(2,0,"Cold Flam           ");
			LcdWriteStrimg(3,0,"                    ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"-> Tall             ");
			LcdWriteStrimg(1,0,"Grande              ");
			LcdWriteStrimg(2,0,"Venti               ");
			LcdWriteStrimg(3,0,"Trenta              ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Type: Shaken        ");
			LcdWriteStrimg(1,0,"Size: Tall          ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[0].Size[0]);
			LcdWriteStrimg(3,0,buf);		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Type: Shaken        ");
			LcdWriteStrimg(1,0,"Size: Grande        ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[0].Size[1]);
			LcdWriteStrimg(3,0,buf);		
		}
		else if(focus==FOCUS_4)
		{
			LcdWriteStrimg(0,0,"Type: Shaken        ");
			LcdWriteStrimg(1,0,"Size: Venti         ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[0].Size[2]);
			LcdWriteStrimg(3,0,buf);		
		}	
		else if(focus==FOCUS_5)
		{
			LcdWriteStrimg(0,0,"Type: Shaken        ");
			LcdWriteStrimg(1,0,"Size: Trenta        ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[0].Size[3]);
			LcdWriteStrimg(3,0,buf);		
		}		
	}
	else if(item==ITEM_2)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Shaken              ");
			LcdWriteStrimg(1,0,"-> Blended          ");
			LcdWriteStrimg(2,0,"Cold Flam           ");
			LcdWriteStrimg(3,0,"                    ");	
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Tall                ");
			LcdWriteStrimg(1,0,"-> Grande           ");
			LcdWriteStrimg(2,0,"Venti               ");
			LcdWriteStrimg(3,0,"Trenta              ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Type: Blended       ");
			LcdWriteStrimg(1,0,"Size: Tall          ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[1].Size[0]);
			LcdWriteStrimg(3,0,buf);		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Type: Blended       ");
			LcdWriteStrimg(1,0,"Size: Grande        ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[1].Size[1]);
			LcdWriteStrimg(3,0,buf);		
		}
		else if(focus==FOCUS_4)
		{
			LcdWriteStrimg(0,0,"Type: Blended       ");
			LcdWriteStrimg(1,0,"Size: Venti         ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[1].Size[2]);
			LcdWriteStrimg(3,0,buf);		
		}	
		else if(focus==FOCUS_5)
		{
			LcdWriteStrimg(0,0,"Type: Blended       ");
			LcdWriteStrimg(1,0,"Size: Trenta        ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[1].Size[3]);
			LcdWriteStrimg(3,0,buf);		
		}

	}
	else if(item==ITEM_3)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Shaken              ");
			LcdWriteStrimg(1,0,"Blended             ");
			LcdWriteStrimg(2,0,"-> Cold Flam        ");
			LcdWriteStrimg(3,0,"                    ");	
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"-> Tall             ");
			LcdWriteStrimg(1,0,"Grande              ");
			LcdWriteStrimg(2,0,"Venti               ");
			LcdWriteStrimg(3,0,"Trenta              ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Type: Cold Flam     ");
			LcdWriteStrimg(1,0,"Size: Tall          ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[2].Size[0]);
			LcdWriteStrimg(3,0,buf);		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Type: Cold Flam     ");
			LcdWriteStrimg(1,0,"Size: Grande        ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[2].Size[1]);
			LcdWriteStrimg(3,0,buf);		
		}
		else if(focus==FOCUS_4)
		{
			LcdWriteStrimg(0,0,"Type: Cold Flam     ");
			LcdWriteStrimg(1,0,"Size: Venti         ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[2].Size[2]);
			LcdWriteStrimg(3,0,buf);		
		}	
		else if(focus==FOCUS_5)
		{
			LcdWriteStrimg(0,0,"Type: Cold Flam     ");
			LcdWriteStrimg(1,0,"Size: Trenta        ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "->Shaken  %d", gUISet.Type[2].Size[3]);
			LcdWriteStrimg(3,0,buf);		
		}		
	}
}



static BOOL KeyDownHand(INT8U key)
{
	INT8U item=gWinTypeSize.item;
	INT8U focus=gWinTypeSize.focus;
	
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
					focus=FOCUS_MAX;
				}			
			}
			else if(item==ITEM_2)
			{
				if(focus>FOCUS_1)
				{
					focus--;
				}
				else 
				{
					focus=FOCUS_MAX;
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
					focus=FOCUS_3;
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
				if(focus<FOCUS_MAX)
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
				if(focus<FOCUS_MAX)
				{
					focus++;
				}
				else 
				{
					focus=FOCUS_1;
				}				
			}
			else if(item==ITEM_3)
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
		}
		break;
	case VK_SELECT:	
		{
			if(item==ITEM_1)
			{

			}
			else if(item==ITEM_2)
			{


			}
			else if(item==ITEM_3)
			{


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
				focus=FOCUS_NULL;
			}
		}
		break;		
	default:
		break;
	}

	gWinTypeSize.item=item;
	gWinTypeSize.focus=focus;

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

extern WINHAND *spWinFatherHand;
static void WinPageInit(void)
{
	systemseting.WinTimerCount=0;
	gWinTypeSize.focus = FOCUS_NULL;

	/*if(spWinFatherHand->id==HWND_Oreration)
	{
		if(spWinFatherHand->focus)gWinTypeSize.item=spWinFatherHand->focus-1;
		else SendMessage(0, WM_PAGESWITCH, GetParent());
	}
	else 
	{
		SendMessage(0, WM_PAGESWITCH, GetParent());
	}*/
}

void WinTypeSizeInit(void)
{
	gWinTypeSize.id = HWND_TypeSize;
	gWinTypeSize.item = ITEM_1;
	gWinTypeSize.focus = FOCUS_1;
	gWinTypeSize.Init = WinPageInit;
	gWinTypeSize.WinProc = WinProc;
	
	CreatePage(&gWinTypeSize);
}

