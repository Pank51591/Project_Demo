//***********************************************************************************
//  文件名称    : KeyScan.c
//  作者        : yangzhengyun	
//  模块功能    : 按键判断  
//  创作日期    : 2013-4-25
//  最后更正日期: 2013-4-25	
//  版本        :	
//  更改记录    :  
//************************************************************************************
#include"config.h"
#include"KeyScan.h"
  
#define DNOP	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();

//************************************************************************************
//----------按键状态定义（内部使用）-------------------------------------------------- 

#define C_KEY_STATE_INIT      0   //有按键按下
#define C_KEY_STATE_WOBBLE    1   //消抖
#define C_KEY_STATE_PRESS     2   //短按
#define C_KEY_STATE_LONG      3   //长按
#define C_KEY_STATE_WAITCONT  4   //进入连按延时阶段
#define C_KEY_STATE_CONTINUE  5   //连按
#define C_KEY_STATE_RELEASE   6   //按键释放

//*************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////
//*************************************************************************************
//  函数名称	: KeyScanInit()	
//  作者        : yangzhengyun
//  模块功能	: 按键初始化  
//  创建日期    ：2013-4-25晚 	
//  最后更正日期: 2013-4-25晚 
//  更改记录	:
//  备注        ：此函数跟硬件有关，具体场合具体用
//*************************************************************************************


#define KEYSCANINIT() SET_IO_INTPUT;   //设置按键端口为输入	

#define KEY1	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define KEY2	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)


#if 0
//*************************************************************************************
//  函数名称	: KeyFind	
//  作者        : 杨政云
//  模块功能	: 软件延时  
//  创建日期    ：2013-4-25晚 	
//  最后更正日期: 2013-4-25晚 
//  更改记录	:
//  备注        ：此函数跟硬件有关，具体场合具体用
//*************************************************************************************
TYKEYFIND CODE KeyFind[VK_NUM]=
{
	{0X01,VK_DOWN},
	{0X02,VK_UP},
	{0X03,VK_LEFT},
	{0X04,VK_RIGHT},

	{0X05,VK_MENU},
	{0X06,VK_OK},
	{0X07,VK_EXIT},/*
	{0X08,VK_DOWN},
	{0X09,VK_DOWN},
	{0X10,VK_DOWN},
	{0X11,VK_DOWN},
	{0X12,VK_DOWN},
	{0X13,VK_DOWN},
	{0X14,VK_DOWN},
	{0X15,VK_DOWN},
	{0X16,VK_DOWN}*/
};
#endif
#if 1	
//*************************************************************************************
//  函数名称	: INT8U Getkey	
//  作者        : yangzhengyun
//  模块功能	: 软件延时  
//  创建日期    ：2013-4-25晚 	
//  最后更正日期: 2013-4-25晚 
//  更改记录	:
//  备注        ：此函数跟硬件有关，具体场合具体用
//*************************************************************************************
INT8U uartkeyval;
INT8U Getkey(void)
{
	INT8U key;
	
	key = uartkeyval;

	if(key==0x03)
	{
		return 0x81;
	}
	else if(key==0x01)//复位
	{
		return 1;
	}
	else if(key==0x02)//冲洗
	{
		return 2;
	}	

	return 0;
}
#endif

//*************************************************************************************
//  函数名称	: void GetKeyState
//  作者        : yangzhengyun
//  模块功能	: 获取按键状态及按键值
//  创建日期    ：2013-4-25晚 	
//  最后更正日期: 2015-6-19 
//  参数介绍    ：pkeyvalue按键
//  返回值介绍  ：无 
//  更改记录	: 把16进制的参数用结构体代替
//  用法        ：当一次有效按下后先回送(0x80|按键值)，当继续按为长按的时候回送
//              : (0x40|按键值)，当按键超过长按时间后会送（0x20|按键值）如果继续按则
//              ： 连按，这时每500ms回送（0x20|按键值，当释放按键后回送（0x10|按键值）
//*************************************************************************************
void GetKeyState(TYKEY *pkeyvalue) 
{
	static INT8U u8keystep = C_KEY_STATE_INIT;   //按键步骤
	static INT16U u8keytimecount = 0;             //按键时间加 
	static INT8U u8lastkey = C_KEY_NULL;         //保存按键释放时候的键值
	static INT8U u8keystate = 0;                  //按键状态
	INT8U statetemp = C_KEY_NULL;
	INT8U keytemp = C_KEY_NULL;
	
	keytemp = Getkey();//获取键值
	
	switch(u8keystep) 
	{ 
		case C_KEY_STATE_INIT: //|-0-|有按键按下
			{ 
				if(C_KEY_NULL != keytemp)//
				{ 
					u8keytimecount = 0;
					u8lastkey = keytemp; //保存键值,以便在释放按键状态返回键值
					//u8keystep = C_KEY_STATE_WOBBLE;
					u8keystep = C_KEY_STATE_PRESS;
				} 
			} 
			break ; 
	
	 	case C_KEY_STATE_WOBBLE: // |-1-| 消抖 
			{ 
				if(++u8keytimecount > C_KEY_DIS_SHAKE) 
				{ 
						u8keytimecount = 0; 
						u8keystep = C_KEY_STATE_PRESS;
				} 
				else if(u8lastkey != keytemp )
				{
						u8keystep = C_KEY_STATE_INIT;
				}
			}
			break ;
	 
		case C_KEY_STATE_PRESS: //|-2-|按键按下
			{ 
				if( u8lastkey == keytemp )  
				{ 
					statetemp = C_KEY_DOWN; //按键按下 
					u8keystate = C_KEY_DOWN;//保存状态
					u8lastkey = keytemp; //保存键值,以便在释放按键状态返回键值
					u8keystep = C_KEY_STATE_LONG; 	
				} 
				else 
				{
					u8keystep = C_KEY_STATE_INIT;
				} 
			} 
			
			break; 
	
	 	case C_KEY_STATE_LONG : //|-3-|长按
			{
				if(u8lastkey == keytemp) 
				{ 
					if(++u8keytimecount > (C_KEY_LONG_PERIOD)) 
					{ 
						u8keytimecount = 0; 
						statetemp = C_KEY_LONG; //长按键事件发生 
						u8keystate = C_KEY_LONG;//保存状态
						u8keystep = C_KEY_STATE_WAITCONT; 
					}
				} 
				else 
				{
					u8keystep = C_KEY_STATE_RELEASE; 
				} 
			} 
			break; 
			
		case C_KEY_STATE_WAITCONT://等待连击
			{
				if(++u8keytimecount > C_KEY_WAIT_PERIOD) 
				{ 
						u8keytimecount = 0; 
						u8keystep = C_KEY_STATE_CONTINUE;
				} 
				else if(u8lastkey != keytemp )
				{
						u8keystep = C_KEY_STATE_RELEASE;
				}
			}
			break;
	
	 	case C_KEY_STATE_CONTINUE: //|-4-|连按
			{
				if(u8lastkey == keytemp) 
				{  
					if(++u8keytimecount > C_KEY_CONTINUE_PERIOD)
					{ 
						u8keytimecount = 0; 
						statetemp = C_KEY_CONTINUE; //继续连击
						u8keystate = C_KEY_CONTINUE;//保存状态
					}
				} 
				else  
				{ 
					u8keystep = C_KEY_STATE_RELEASE;  
				} 
			} 
			break;
	 
	 	case C_KEY_STATE_RELEASE: //|-5-|释放
			{
				u8keystep = C_KEY_STATE_INIT;
				
				if(((u8lastkey&0x80)==0)&&(keytemp&0x80))
				{
					pkeyvalue->KeyState = C_KEY_NULL; 
					return;
				}
				
				statetemp = (u8keystate|C_KEY_UP);
				keytemp = u8lastkey; 			
			} 
			break;
	 
		default: 
			break; 

	}
	//UartSendNumber(u8keystep);//(P_PIN&0x30
	pkeyvalue->KeyState = statetemp; //返回键值
	pkeyvalue->KeyValue = keytemp;
}

//**************************************************************************************
//	函数名称	: HkeytoVkey	
//	作者		: yzy	
//	模块功能	: 按键键值转换，从硬件按键值转换成系统软件值
//	返回值      : 系统键值	
//  参数介绍    : Hkey为要转换的硬件键值
//  更改记录	:
//**************************************************************************************
INT8U HkeytoVkey(INT8U Hkey)
{
	//INT8U Vkey;

	switch(Hkey)
	{	
	case 0x01: return VK_REST;
	case 0x02: return VK_FLUSH;
	case 0x81: return VK_REST_FLUSH;
	
	case 0x04: return VK_NULL;
	
	case 0x05: return VK_NULL;
	case 0x06: return VK_NULL;
	case 0x07: return VK_NULL;
	case 0x08: return VK_NULL;	
	case 0x09: return VK_NULL;	
	default:
		break;	 
	}
	return FALSE;
} 

void keydownhandle(TYKEY *key)
{
	static INT16U keydowncount=0,timercount=0;
	static INT8U oldkey=0; 

	timercount++;

	if(key->KeyState==(C_KEY_DOWN|C_KEY_UP))
	{
		timercount=0;
		if(oldkey!=key->KeyValue){oldkey=key->KeyValue;keydowncount=0;}
		
		keydowncount++;
		key->KeyState = 0;
	}
	else if(key->KeyState&(C_KEY_LONG|C_KEY_CONTINUE))
	{
		keydowncount=0;
		timercount=0;
		oldkey=0;
	}

	if(timercount>35)//100
	{
		if(keydowncount==6)
		{
			key->KeyState = C_KEY_CLICK_6;
			key->KeyValue = oldkey;
		}
		else if(keydowncount==3)
		{
			key->KeyState = C_KEY_CLICK_3;
			key->KeyValue = oldkey;
		}	
		else if(keydowncount==1)
		{
			key->KeyState = (C_KEY_DOWN|C_KEY_UP);
			key->KeyValue = oldkey;
		}
		keydowncount=0;
		timercount=0;
		oldkey=0;
	}

}


//**************************************************************************************
//	函数名称	: TaskKeySan	
//	作者		: yzy	
//	模块功能	: 按键扫描任务
//	返回值      : 无	
//  参数介绍    : 
//  更改记录	:
//**************************************************************************************
void TaskKeySan(void)
{
	TYKEY key;
	HWND hwnd=0;


	if(gReg.error.BitFlag.WaterLeakErrorFlag)//漏水按键无效
	{
		//return;
	}
	
	GetKeyState(&key);

	key.KeyValue = HkeytoVkey(key.KeyValue);

	//if(GetActiveWindow()==HWND_DESKTOP)keydownhandle(&key);

	if(key.KeyState != C_KEY_NULL)
	{
		//uart_printf1("keystate=%d,key=%d",key.KeyState,key.KeyValue);
	
		switch(key.KeyState)
		{
		case C_KEY_DOWN://有按键按下
			{
				SendMessage(hwnd,WM_KEYDOWN,key.KeyValue);
			}break;
		case C_KEY_DOWN|C_KEY_UP://短按
			SendMessage(hwnd,WM_KEYUP,key.KeyValue);
			//SendKeyInfo(WM_KEYUP,key.KeyValue);
			break;
		case C_KEY_LONG:
			SendMessage(hwnd,WM_KEYLONG,key.KeyValue);
			break;
		case C_KEY_LONG|C_KEY_UP://长按
			SendMessage(hwnd,WM_KEYLONGUP,key.KeyValue);
			break;
		case C_KEY_CONTINUE://连按
			SendMessage(hwnd,WM_KEYCONTINUE,key.KeyValue);
			//SendKeyInfo(WM_KEYCONTINUE,key.KeyValue);
			break;
		//case C_KEY_CLICK_3://3击
		//	SendMessage(hwnd,WM_KEYCLICK_3,key.KeyValue);
		//	break;
		//case C_KEY_CLICK_6://6击
		//	SendMessage(hwnd,WM_KEYCLICK_6,key.KeyValue);
		//	break;
		//default:
		//	break;
		}
	}
}

