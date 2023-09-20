#include"config.h"
#include"WinTypeSize.h"


WINHAND gWinTypeSize;

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

static const char typetemp[3][25]=
{
	"Type: Shaken        ",
	"Type: Blended       ",
	"Type: Cold Foam     "
};

static void Update(void)
{
	INT8U item,focus;
	char buf[20];

	item = gWinTypeSize.item;
	focus = gWinTypeSize.focus;

	//size = gUISet.Type[0].Size;
	
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
			LcdWriteStrimg(0,0,typetemp[type]);
			LcdWriteStrimg(1,0,"Size: Tall          ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "%d          ", gUISet.Type[type].Size_Gram[0]);
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
			LcdWriteStrimg(0,0,typetemp[type]);
			LcdWriteStrimg(1,0,"Size: Grande        ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "%d          ", gUISet.Type[type].Size_Gram[1]);
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
			LcdWriteStrimg(0,0,typetemp[type]);
			LcdWriteStrimg(1,0,"Size: Venti         ");
			LcdWriteStrimg(2,0,"                    ");
			snprintf(buf, 20, "%d          ", gUISet.Type[type].Size_Gram[2]);
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
				LcdWriteStrimg(0,0,typetemp[type]);
				LcdWriteStrimg(1,0,"Size: Trenta        ");
				LcdWriteStrimg(2,0,"                    ");
				snprintf(buf, 20, "%d          ", gUISet.Type[type].Size_Gram[3]);
				LcdWriteStrimg(3,0,buf);				
			}
		}		
	}	
}



static BOOL KeyDownHand(INT8U key)
{
	INT8U item=gWinTypeSize.item;
	INT8U focus=gWinTypeSize.focus;
	INT16U temp;
	
	switch(key)
	{
	case VK_UP://
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
				temp=gUISet.Type[type].Size_Gram[0];
				
				if(temp<1000)
				{
					temp++;
				}
				else 
				{
					temp=1000;
				}
				gUISet.Type[type].Size_Gram[0]=temp;
			}
			else if(item==ITEM_2)
			{
				temp=gUISet.Type[type].Size_Gram[1];
				
				if(temp<1000)
				{
					temp++;
				}
				else 
				{
					temp=1000;
				}	
				gUISet.Type[type].Size_Gram[1]=temp;
			}
			else if(item==ITEM_3)
			{
				temp=gUISet.Type[type].Size_Gram[2];
				
				if(temp<1000)
				{
					temp++;
				}
				else 
				{
					temp=1000;
				}
				gUISet.Type[type].Size_Gram[2]=temp;
			}
			else if(item==ITEM_4)
			{
				temp=gUISet.Type[type].Size_Gram[3];
				
				if(temp<1000)
				{
					temp++;
				}
				else 
				{
					temp=1000;
				}
				gUISet.Type[type].Size_Gram[3]=temp;
			}
			
			systemseting.StateChangeFlag=1;
		}
		break;
	case VK_DOWN:	
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
				temp=gUISet.Type[type].Size_Gram[0];
				
				if(temp>2)
				{
					temp--;
				}
				else 
				{
					temp=1;
				}
				gUISet.Type[type].Size_Gram[0]=temp;
			}
			else if(item==ITEM_2)
			{
				temp=gUISet.Type[type].Size_Gram[1];
				
				if(temp>2)
				{
					temp--;
				}
				else 
				{
					temp=1;
				}	
				gUISet.Type[type].Size_Gram[1]=temp;
			}
			else if(item==ITEM_3)
			{
				temp=gUISet.Type[type].Size_Gram[2];
				
				if(temp>2)
				{
					temp--;
				}
				else 
				{
					temp=1;
				}
				gUISet.Type[type].Size_Gram[2]=temp;
			}
			else if(item==ITEM_4)
			{
				temp=gUISet.Type[type].Size_Gram[3];
				
				if(temp>2)
				{
					temp--;
				}
				else 
				{
					temp=1;
				}
				gUISet.Type[type].Size_Gram[3]=temp;
			}

			systemseting.StateChangeFlag=1;			
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
				systemseting.StateChangeSaveflag=1;
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
	gWinTypeSize.item = ITEM_1;
	Parent = GetParent();

	if(spWinFatherHand->id==HWND_Oreration&&spWinFatherHand->item==ITEM_1)
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

void WinTypeSizeInit(void)
{
	gWinTypeSize.id = HWND_TypeSize;
	gWinTypeSize.item = ITEM_1;
	gWinTypeSize.focus = FOCUS_1;
	gWinTypeSize.Init = WinPageInit;
	gWinTypeSize.WinProc = WinProc;
	
	CreatePage(&gWinTypeSize);
}

