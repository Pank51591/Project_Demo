#include"config.h"
#include"WinDispenseCnt.h"


WINHAND gWinDispenseCnt;

static INT8U type;
static HWND Parent=HWND_DESKTOP;

enum FILTERSET_FOCUS
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
	ITEM_4,
	ITEM_MAX=ITEM_4
};



WINHAND* GetDispenseCntWin(void)
{
	return 	&gWinDispenseCnt;
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

/*static const char typetemp[3][25]=
{
	"Type: Shaken        ",
	"Type: Blended       ",
	"Type: Cold Foam     "
};*/

static const char typeval[12][21]=
{
	"Shaken : Tall       ",
	"Shaken : Grande     ",
	"Shaken : Venti      ",
	"Shaken : Trenta     ",
	
	"Blended : Tall      ",
	"Blended : Grande    ",
	"Blended : Venti     ",
	"Blended : Trenta    ",

	"Cold Foam : Tall    ",
	"Cold Foam : Grande  ",
	"Cold Foam : Venti   ",
	"Cold Foam : Trenta  ",
};


static void Update(void)
{
	INT8U item,focus;
	char buf[20];

	item = gWinDispenseCnt.item;
	focus = gWinDispenseCnt.focus;

	
	if(item==ITEM_1)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"-> Tall             ");
			LcdWriteStrimg(1,0,"Grande              ");
			LcdWriteStrimg(2,0,"Venti               ");
			LcdWriteStrimg(3,0,"Trenta              ");			
		}
		else if(focus==FOCUS_1)
		{ 
			LcdWriteStrimg(0,0,"Dispense Count:     ");
			LcdWriteStrimg(1,0,typeval[type*4+0]);
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "%d dispenses         ", gUISet.Type[type].Size_DispenseCnt[0]);
			LcdWriteStrimg(3,0,buf);		
		}		
	}
	else if(item==ITEM_2)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Tall                ");
			LcdWriteStrimg(1,0,"-> Grande           ");
			LcdWriteStrimg(2,0,"Venti               ");
			LcdWriteStrimg(3,0,"Trenta              ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Dispense Count:     ");
			LcdWriteStrimg(1,0,typeval[type*4+1]);
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "%d dispenses         ", gUISet.Type[type].Size_DispenseCnt[1]);
			LcdWriteStrimg(3,0,buf);		
		}
	}
	else if(item==ITEM_3)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Tall                ");
			LcdWriteStrimg(1,0,"Grande              ");
			LcdWriteStrimg(2,0,"-> Venti            ");
			LcdWriteStrimg(3,0,"Trenta              ");
		}
		else if(focus==FOCUS_1)
		{
			LcdWriteStrimg(0,0,"Dispense Count:     ");
			LcdWriteStrimg(1,0,typeval[type*4+2]);
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "%d dispenses         ", gUISet.Type[type].Size_DispenseCnt[2]);
			LcdWriteStrimg(3,0,buf);
		}		
	}
	else if(item==ITEM_4)
	{
		if(focus==FOCUS_NULL)
		{
			LcdWriteStrimg(0,0,"Tall                	");
			LcdWriteStrimg(1,0,"Grande              ");
			LcdWriteStrimg(2,0,"Venti               ");
			LcdWriteStrimg(3,0,"-> Trenta           ");
		}
		else if(focus==FOCUS_1)
		{
			if(type==1)//Blended
			{
				LcdWriteStrimg(0,0,"                    ");
				LcdWriteStrimg(1,0,"   Not Implemented  ");
				LcdWriteStrimg(2,0,"                    ");
				LcdWriteStrimg(3,0,"                    ");
			}
			else 
			{
				LcdWriteStrimg(0,0,"Dispense Count:     ");
				LcdWriteStrimg(1,0,typeval[type*4+3]);
				LcdWriteStrimg(2,0,"                    ");
				snprintf(buf, 20, "%d dispenses         ", gUISet.Type[type].Size_DispenseCnt[3]);
				LcdWriteStrimg(3,0,buf);				
			}
		}		
	}	
}



static BOOL KeyDownHand(INT8U key)
{
	INT8U item=gWinDispenseCnt.item;
	INT8U focus=gWinDispenseCnt.focus;
	
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
					focus=FOCUS_1;
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
				if(focus<FOCUS_1)
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
			if(focus==FOCUS_NULL)
			{
				focus=FOCUS_1;
			}
			else 
			{
				focus=FOCUS_NULL;
			}
		}
		break;
	case VK_RETUN:	
		{
			if(focus==FOCUS_NULL)
			{
				SendMessage(0, WM_PAGESWITCH, Parent);
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

	gWinDispenseCnt.item=item;
	gWinDispenseCnt.focus=focus;

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
	gWinDispenseCnt.focus = FOCUS_NULL;
	gWinDispenseCnt.item = ITEM_1;
	Parent = GetParent();

	if(spWinFatherHand->id==HWND_Data&&spWinFatherHand->item==ITEM_3)
	{
		if(spWinFatherHand->focus==1)type=0;
		else if(spWinFatherHand->focus==2)type=1;
		else if(spWinFatherHand->focus==3)type=2;
		else 
		{	
			type=0;
			SendMessage(0, WM_PAGESWITCH, Parent);
		}
	}
	else 
	{
		type=0;
		SendMessage(0, WM_PAGESWITCH, Parent);
	}
}

void WinDispenseCntInit(void)
{
	gWinDispenseCnt.id = HWND_DISPCNT;
	gWinDispenseCnt.item = ITEM_1;
	gWinDispenseCnt.focus = FOCUS_NULL;
	gWinDispenseCnt.Init = WinPageInit;
	gWinDispenseCnt.WinProc = WinProc;
	
	CreatePage(&gWinDispenseCnt);
}

