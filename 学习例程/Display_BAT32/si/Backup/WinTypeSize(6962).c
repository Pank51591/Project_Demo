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

const char sizetemp[4][10]=  
{
	"Tall",
	"Grande",
	"Venti",
	"Trenta"
};

static void Update(void)
{
	INT8U item,focus,size;
	char buf[20];

	item = gWinTypeSize.item;
	focus = gWinTypeSize.focus;

	size = gUISet.TypeSize.Size;
	
	if(item==ITEM_1)
	{
		if(focus==FOCUS_NULL)
		{
			//snprintf(buf, 20, "->Shaken  %s", sizetemp[size]);
			
			LcdWriteStrimg(0,0,"->Shaken            ");
			LcdWriteStrimg(1,0,"Blended             ");
			LcdWriteStrimg(2,0,"Cold Foam           ");
			LcdWriteStrimg(3,0,"Flow                ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Shaken: Tall        ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Shaken: Grande      ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Shaken: Venti       ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_4)
		{
			LcdWriteStrimg(0,0,"Shaken: Trenta      ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}		
	}
	else if(item==ITEM_2)
	{
		if(focus==FOCUS_NULL)
		{
			//snprintf(buf, 20, "->Blended  %s", sizetemp[size]);
			
			LcdWriteStrimg(0,0,"Shaken              ");
			LcdWriteStrimg(1,0,"->Blended           ");
			LcdWriteStrimg(2,0,"Cold Foam           ");
			LcdWriteStrimg(3,0,"Flow                ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Blended: Tall       ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Blended: Grande     ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Blended: Venti      ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
	}
	else if(item==ITEM_3)
	{
		if(focus==FOCUS_NULL)
		{
			//snprintf(buf, 20, "->Cold Foam  %s", sizetemp[size]);
			
			LcdWriteStrimg(0,0,"Shaken              ");
			LcdWriteStrimg(1,0,"Blended             ");
			LcdWriteStrimg(2,0,"->Cold Foam         ");
			LcdWriteStrimg(3,0,"Flow                ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Cold Foam: Tall     ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Cold Foam: Grande   ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_3)
		{
			LcdWriteStrimg(0,0,"Cold Foam: Venti    ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}
		else if(focus==FOCUS_4)
		{
			LcdWriteStrimg(0,0,"Cold Foam: Trenta   ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
		}		
	}
	else if(item==ITEM_4)
	{
		if(focus==FOCUS_NULL)
		{
			if(gUISet.TypeSize.Flow)
			{
				snprintf(buf, 20, "->Flow    %s", "ON");
			}
			else 
			{
				snprintf(buf, 20, "->Flow    %s", "OFF");
			}
			
			LcdWriteStrimg(0,0,"Shaken              ");
			LcdWriteStrimg(1,0,"Blended             ");
			LcdWriteStrimg(2,0,"Cold Foam           ");
			LcdWriteStrimg(3,0,buf);
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Flow: OFF           ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");			
		}
		else if(focus==FOCUS_2)
		{
			LcdWriteStrimg(0,0,"Flow: ON            ");
			LcdWriteStrimg(1,0,"                    ");
			LcdWriteStrimg(2,0,"                    ");
			LcdWriteStrimg(3,0,"                    ");		
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
			else if(item==ITEM_4)
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
			else if(item==ITEM_4)
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
				gUISet.TypeSize.Flow=0;
				gUISet.TypeSize.Type=type_Shaken;
			
				if(focus==FOCUS_1)
				{
					gUISet.TypeSize.Size=size_Tall;
				}
				else if(focus==FOCUS_2)
				{
					gUISet.TypeSize.Size=size_Grande;
				}
				else if(focus==FOCUS_3)
				{
					gUISet.TypeSize.Size=size_Venti;
				}
				else if(focus==FOCUS_4)
				{
					gUISet.TypeSize.Size=size_Trenta;
				}				
				else 
				{
					if(gUISet.TypeSize.Size!=size_NULL)
					{
						focus=gUISet.TypeSize.Size;
					}
					else 
					{
						focus=FOCUS_1;
					}
				}
			}
			else if(item==ITEM_2)
			{
				gUISet.TypeSize.Flow=0;
				gUISet.TypeSize.Type=type_Blended;
								
				if(focus==FOCUS_1)
				{
					gUISet.TypeSize.Size=size_Tall;
				}
				else if(focus==FOCUS_2)
				{
					gUISet.TypeSize.Size=size_Grande;
				}
				else if(focus==FOCUS_3)
				{
					gUISet.TypeSize.Size=size_Venti;
				}				
				else 
				{
					if(gUISet.TypeSize.Size!=size_NULL)
					{
						focus=gUISet.TypeSize.Size;
					}
					else 
					{
						focus=FOCUS_1;
					}
				}

			}
			else if(item==ITEM_3)
			{
				gUISet.TypeSize.Flow=0;
				gUISet.TypeSize.Type=type_ColdFoam;
								
				if(focus==FOCUS_1)
				{
					gUISet.TypeSize.Size=size_Tall;
				}
				else if(focus==FOCUS_2)
				{
					gUISet.TypeSize.Size=size_Grande;
				}
				else if(focus==FOCUS_3)
				{
					gUISet.TypeSize.Size=size_Venti;
				}
				else if(focus==FOCUS_4)
				{
					gUISet.TypeSize.Size=size_Trenta;
				}				
				else 
				{
					if(gUISet.TypeSize.Size!=size_NULL)
					{
						focus=gUISet.TypeSize.Size;
					}
					else 
					{
						focus=FOCUS_1;
					}
				}

			}
			else if(item==ITEM_4)
			{
				if(focus==FOCUS_1)
				{
					gUISet.TypeSize.Flow=0;
				}
				else if(focus==FOCUS_2)
				{
					gUISet.TypeSize.Flow=1;
				}
				else 
				{
					if(gUISet.TypeSize.Flow==0)
					{
						focus=FOCUS_1;
					}
					else 
					{
						focus=FOCUS_2;
					}
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

	if(spWinFatherHand->id==HWND_Oreration)
	{
		if(spWinFatherHand->focus)gWinTypeSize.item=spWinFatherHand->focus-1;
		else SendMessage(0, WM_PAGESWITCH, GetParent());
	}
	else 
	{
		SendMessage(0, WM_PAGESWITCH, GetParent());
	}
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

