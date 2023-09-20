//***********************************************************************************
//  �ļ�����    : KeyScan.c
//  ����        : yangzhengyun	
//  ģ�鹦��    : �����ж�  
//  ��������    : 2013-4-25
//  ����������: 2013-4-25	
//  �汾        :	
//  ���ļ�¼    :  
//************************************************************************************
#include"config.h"
#include"KeyScan.h"
  
#define DNOP	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();

//************************************************************************************
//----------����״̬���壨�ڲ�ʹ�ã�-------------------------------------------------- 

#define C_KEY_STATE_INIT      0   //�а�������
#define C_KEY_STATE_WOBBLE    1   //����
#define C_KEY_STATE_PRESS     2   //�̰�
#define C_KEY_STATE_LONG      3   //����
#define C_KEY_STATE_WAITCONT  4   //����������ʱ�׶�
#define C_KEY_STATE_CONTINUE  5   //����
#define C_KEY_STATE_RELEASE   6   //�����ͷ�

//*************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////
//*************************************************************************************
//  ��������	: KeyScanInit()	
//  ����        : yangzhengyun
//  ģ�鹦��	: ������ʼ��  
//  ��������    ��2013-4-25�� 	
//  ����������: 2013-4-25�� 
//  ���ļ�¼	:
//  ��ע        ���˺�����Ӳ���йأ����峡�Ͼ�����
//*************************************************************************************


#define KEYSCANINIT() SET_IO_INTPUT;   //���ð����˿�Ϊ����	

#define KEY1	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define KEY2	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)


#if 0
//*************************************************************************************
//  ��������	: KeyFind	
//  ����        : ������
//  ģ�鹦��	: �����ʱ  
//  ��������    ��2013-4-25�� 	
//  ����������: 2013-4-25�� 
//  ���ļ�¼	:
//  ��ע        ���˺�����Ӳ���йأ����峡�Ͼ�����
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
//  ��������	: INT8U Getkey	
//  ����        : yangzhengyun
//  ģ�鹦��	: �����ʱ  
//  ��������    ��2013-4-25�� 	
//  ����������: 2013-4-25�� 
//  ���ļ�¼	:
//  ��ע        ���˺�����Ӳ���йأ����峡�Ͼ�����
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
	else if(key==0x01)//��λ
	{
		return 1;
	}
	else if(key==0x02)//��ϴ
	{
		return 2;
	}	

	return 0;
}
#endif

//*************************************************************************************
//  ��������	: void GetKeyState
//  ����        : yangzhengyun
//  ģ�鹦��	: ��ȡ����״̬������ֵ
//  ��������    ��2013-4-25�� 	
//  ����������: 2015-6-19 
//  ��������    ��pkeyvalue����
//  ����ֵ����  ���� 
//  ���ļ�¼	: ��16���ƵĲ����ýṹ�����
//  �÷�        ����һ����Ч���º��Ȼ���(0x80|����ֵ)����������Ϊ������ʱ�����
//              : (0x40|����ֵ)����������������ʱ�����ͣ�0x20|����ֵ�������������
//              �� ��������ʱÿ500ms���ͣ�0x20|����ֵ�����ͷŰ�������ͣ�0x10|����ֵ��
//*************************************************************************************
void GetKeyState(TYKEY *pkeyvalue) 
{
	static INT8U u8keystep = C_KEY_STATE_INIT;   //��������
	static INT16U u8keytimecount = 0;             //����ʱ��� 
	static INT8U u8lastkey = C_KEY_NULL;         //���水���ͷ�ʱ��ļ�ֵ
	static INT8U u8keystate = 0;                  //����״̬
	INT8U statetemp = C_KEY_NULL;
	INT8U keytemp = C_KEY_NULL;
	
	keytemp = Getkey();//��ȡ��ֵ
	
	switch(u8keystep) 
	{ 
		case C_KEY_STATE_INIT: //|-0-|�а�������
			{ 
				if(C_KEY_NULL != keytemp)//
				{ 
					u8keytimecount = 0;
					u8lastkey = keytemp; //�����ֵ,�Ա����ͷŰ���״̬���ؼ�ֵ
					//u8keystep = C_KEY_STATE_WOBBLE;
					u8keystep = C_KEY_STATE_PRESS;
				} 
			} 
			break ; 
	
	 	case C_KEY_STATE_WOBBLE: // |-1-| ���� 
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
	 
		case C_KEY_STATE_PRESS: //|-2-|��������
			{ 
				if( u8lastkey == keytemp )  
				{ 
					statetemp = C_KEY_DOWN; //�������� 
					u8keystate = C_KEY_DOWN;//����״̬
					u8lastkey = keytemp; //�����ֵ,�Ա����ͷŰ���״̬���ؼ�ֵ
					u8keystep = C_KEY_STATE_LONG; 	
				} 
				else 
				{
					u8keystep = C_KEY_STATE_INIT;
				} 
			} 
			
			break; 
	
	 	case C_KEY_STATE_LONG : //|-3-|����
			{
				if(u8lastkey == keytemp) 
				{ 
					if(++u8keytimecount > (C_KEY_LONG_PERIOD)) 
					{ 
						u8keytimecount = 0; 
						statetemp = C_KEY_LONG; //�������¼����� 
						u8keystate = C_KEY_LONG;//����״̬
						u8keystep = C_KEY_STATE_WAITCONT; 
					}
				} 
				else 
				{
					u8keystep = C_KEY_STATE_RELEASE; 
				} 
			} 
			break; 
			
		case C_KEY_STATE_WAITCONT://�ȴ�����
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
	
	 	case C_KEY_STATE_CONTINUE: //|-4-|����
			{
				if(u8lastkey == keytemp) 
				{  
					if(++u8keytimecount > C_KEY_CONTINUE_PERIOD)
					{ 
						u8keytimecount = 0; 
						statetemp = C_KEY_CONTINUE; //��������
						u8keystate = C_KEY_CONTINUE;//����״̬
					}
				} 
				else  
				{ 
					u8keystep = C_KEY_STATE_RELEASE;  
				} 
			} 
			break;
	 
	 	case C_KEY_STATE_RELEASE: //|-5-|�ͷ�
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
	pkeyvalue->KeyState = statetemp; //���ؼ�ֵ
	pkeyvalue->KeyValue = keytemp;
}

//**************************************************************************************
//	��������	: HkeytoVkey	
//	����		: yzy	
//	ģ�鹦��	: ������ֵת������Ӳ������ֵת����ϵͳ���ֵ
//	����ֵ      : ϵͳ��ֵ	
//  ��������    : HkeyΪҪת����Ӳ����ֵ
//  ���ļ�¼	:
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
//	��������	: TaskKeySan	
//	����		: yzy	
//	ģ�鹦��	: ����ɨ������
//	����ֵ      : ��	
//  ��������    : 
//  ���ļ�¼	:
//**************************************************************************************
void TaskKeySan(void)
{
	TYKEY key;
	HWND hwnd=0;


	if(gReg.error.BitFlag.WaterLeakErrorFlag)//©ˮ������Ч
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
		case C_KEY_DOWN://�а�������
			{
				SendMessage(hwnd,WM_KEYDOWN,key.KeyValue);
			}break;
		case C_KEY_DOWN|C_KEY_UP://�̰�
			SendMessage(hwnd,WM_KEYUP,key.KeyValue);
			//SendKeyInfo(WM_KEYUP,key.KeyValue);
			break;
		case C_KEY_LONG:
			SendMessage(hwnd,WM_KEYLONG,key.KeyValue);
			break;
		case C_KEY_LONG|C_KEY_UP://����
			SendMessage(hwnd,WM_KEYLONGUP,key.KeyValue);
			break;
		case C_KEY_CONTINUE://����
			SendMessage(hwnd,WM_KEYCONTINUE,key.KeyValue);
			//SendKeyInfo(WM_KEYCONTINUE,key.KeyValue);
			break;
		//case C_KEY_CLICK_3://3��
		//	SendMessage(hwnd,WM_KEYCLICK_3,key.KeyValue);
		//	break;
		//case C_KEY_CLICK_6://6��
		//	SendMessage(hwnd,WM_KEYCLICK_6,key.KeyValue);
		//	break;
		//default:
		//	break;
		}
	}
}

