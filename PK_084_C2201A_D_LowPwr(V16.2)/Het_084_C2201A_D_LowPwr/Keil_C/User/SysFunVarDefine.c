#include "SC_System.h"
 extern void Time_Process(void);
 extern  void Sleep_Clr();//�رպĵ�����
	 
unsigned long exKeyValueFlag = 0;
unsigned int TK_NoKeyCount = 0;
extern unsigned char gcSleepDelayTime;
// ���Ѻ��ִ�иú���
 void Customer_BTM_Dispose()
{
	gcSleepDelayTime = 0;
	Clr_SleepEnFlag;
}
//����͹���ǰ����
 void Customer_IntoLowPowerMode_Init()
{
	gcSleepDelayTime = 0;
	Clr_SleepEnFlag;
	
	Sleep_Clr();
	
	
}

//�˳��͹��Ĵ���
 void Customer_QuitLowPowerMode_Init()
{
	gcSleepDelayTime = 0;
	Clr_SleepEnFlag;
	
	 SC_Init();
	 SC_GPIO_LowOutput();
}

bit enable_keyfree=0;
void Key_Scan()
{
   if(SOCAPI_TouchKeyStatus & 0x80)
			{
					SOCAPI_TouchKeyStatus &= 0x7f;
					exKeyValueFlag = TouchKeyScan();  
//					 if(enable_keyfree)
//					 {
//					 enable_keyfree=0;
//					 }
					if(exKeyValueFlag == 0 )
					{
							TK_NoKeyCount ++;
//						if(TK_NoKeyCount>=65530)
//						{
//							TK_NoKeyCount=0;
//						}
							if (SleepEnFlag)
							{
									TK_NoKeyCount  = 0;
									TouchKey_IntoLowPowerMode();
							}
					}
					else
					{
							TK_NoKeyCount = 0;
					}
				
					TouchKeyRestart();      
			}  

}

void Delay1ms()   //@33.000MHz
{
    unsigned char i, j;
    i = 33;
    j = 22;
    do
    {
        while (--j)
            ;
    } while (--i);
}
/*************************************.Generated by EasyCodeCube.************************************/