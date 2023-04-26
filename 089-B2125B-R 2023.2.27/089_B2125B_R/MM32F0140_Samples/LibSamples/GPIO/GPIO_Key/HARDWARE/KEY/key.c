////////////////////////////////////////////////////////////////////////////////
/// @file    key.c
/// @author  AE TEAM
/// @brief   key intput.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _KEY_C_

// Files includes
#include "key.h"
#include "delay.h"
#include "led.h"
#include "089_B19110A.h"
#include "LED_RF.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY_Exported_Functions
/// @{

uint8_t gcKeyState;
uint8_t gcKeyCount;
uint8_t gcKey4LongEn = 0;
uint16_t giKeyValue;

uint16_t KeyComcount;
uint8_t TimeAdd_sta;   
uint16_t giKeyAddDelay_Count;

volatile unsigned int KEYSW4Count;
volatile unsigned int KEYSW11Count;
volatile unsigned int KEYSW12Count;
volatile unsigned int KEYSW2Count;
volatile unsigned int KEYSW10Count;

extern volatile unsigned int giTempKeyVal;
extern volatile unsigned int  giLED_status;
extern volatile unsigned int  giLED_Tempstatus;
extern volatile unsigned char gcMainSubPair_Flag;
extern  void DELAY_xUs(u32 count);

void Set_All_OutPut(void)
{
		GPIO_InitTypeDef  GPIO_InitStruct;
	
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	  /* �õ����ŵ�ƽ */
		Clr_PA5;    
		Clr_PA7;
		Clr_PB0;
		Clr_PB1;
}

void Set_PA5_OutPut(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5;	
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;    //�������
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	Clr_PA5;

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;   //��������
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

void Set_PA7_OutPut(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7;	
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	Clr_PA7;

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}


void Set_PB0_OutPut(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;	
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	Clr_PB0;

	
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}


void Set_PB1_OutPut(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1;	
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	Clr_PB1;         // PB1��0

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}


/*��ȡ������ֵ*/
void Get_KeyValue(void)
{
	
		Set_PA5_OutPut();		         // PA5 = 0 ,����Ϊ�������״̬����ȡ����ֵ
		DELAY_xUs(20);
	
		if (ReadKEY_PA10 == 0 | ReadKEY_PA6 == 0 | ReadKEY_PA8 == 0)      // SW1,SW2,SW3 ��һ��������
		{
			Set_Key2Down_Flag;      
			giKeyValue |= KEYSW2;      //����
			Clr_KeyReturn_Flag;        //�����ذ�����ֵ
			
		}
		
		else
		{
			Clr_Key2Down_Flag;
		}
		
		Set_PA7_OutPut();	     	// PA7 = 0 ,����Ϊ�������״̬����ȡ����ֵ
		DELAY_xUs(20);
		if (ReadKEY_PA6 == 0)
		{
			giKeyValue |= KEYSW6;         //ȡů
		}
		
		if (ReadKEY_PA8 == 0)
		{
			if(Ptcol_RunMode != standby)    //����ģʽ�£�����ʱ��Ч
			{
				Set_Key4Down_Flag;
				giKeyValue |= KEYSW4;       //��ʱ
				Clr_KeyReturn_Flag;					
			}
		}
		else
		{
			Clr_Key4Down_Flag;
		}
		
		if (ReadKEY_PA10 == 0)
		{
			Set_Key5Down_Flag;    
			giKeyValue |= KEYSW5;         //����
			if(gcKeyState != 1)
			{
				Clr_KeyReturn_Flag;
			}	
		}	
		else
		{
			Clr_Key5Down_Flag;  
		}
		Set_PB0_OutPut();		                 // PB0 = 0 ,����Ϊ�������״̬����ȡ����ֵ
		DELAY_xUs(20);		
		if (ReadKEY_PA6 == 0)
		{
			Set_Key12Down_Flag;
			if((Ptcol_RunMode != standby)&&(Ptcol_RunMode != changeair))
				{
					giKeyValue |= KEYSW12;       //����-��ɢ     	
				}
			else
				{
					giKeyValue |= 0;
				}
				
			if(gcKeyState != 1)               //�������û�а���
			{
				Clr_KeyReturn_Flag;
			}
		}
		else
		{
			Clr_Key12Down_Flag;
		}
		
		if (ReadKEY_PA8 == 0)
		{
			Set_Key10Down_Flag;
			if((Ptcol_RunMode != standby)&&(Ptcol_RunMode != changeair))
			{
				giKeyValue |= KEYSW10;       //����-����   	
			}
	    else
			{
				giKeyValue |= 0;
			}
			if(gcKeyState != 1)               //�������û�а���
			{
				Clr_KeyReturn_Flag;
			}
		}
		else
		{
			Clr_Key10Down_Flag;
		}
		
//		if (ReadKEY_PA10 == 0)
//		{
//			Set_Key11Down_Flag;
//			giKeyValue |= KEYSW11;             //wifi  (δ�õ�)
//			
//			if(gcKeyState != 1)
//			{
//				Clr_KeyReturn_Flag;
//			}
//		}
//		else
//		{
//			Clr_Key11Down_Flag;
//		}
		
		Set_PB1_OutPut();		              // PB1 = 0 ,����Ϊ�������״̬����ȡ����ֵ
		DELAY_xUs(20);          //////4.24 20us
		if (ReadKEY_PA6 == 0)    
		{
				giKeyValue |= KEYSW9;         //�ȸ���
		}
		
		if (ReadKEY_PA10 == 0)
		{
			giKeyValue |= KEYSW8;          //������
		}
		
		if (ReadKEY_PA8 == 0)
		{
			if((Ptcol_RunMode != standby)&&(Ptcol_RunMode != changeair))
			{
				giKeyValue |= KEYSW7;         //����	
			}
		}
		
	
}

/*************************************************************************
//					void TimeAdd_func(void)
//					��ʱ+��������ʱ���������
//					
*************************************************************************/
void TimeAdd_func(void)
{		
	
	switch(Ptcol_TimeSet)      //��ʼֵ���ϵ�������Ҳ�����Ǵ�����3s��ָ�����ʼֵ
	{
		case timer15min:
		{
			Ptcol_TimeSet = timer30min;			
		}	
		break;
		
		case timer30min:
		{
			Ptcol_TimeSet = timer1hour;	
		}	
		break;
		
		case timer1hour:
		{
			Ptcol_TimeSet = timer3hour;				
		}	
		break;		
		
		case timer3hour:
		{
			if(Ptcol_RunMode == warmhouse)
			{
				if(TimeAdd_sta == 0)
				{
					Ptcol_TimeSet = timer15min;
				}
				else
				{
					Clr_KeyAddDelay_flag;     /* ��ʹһֱ�����̶�������ֵ */	
				}	
			}
			else
			{
				Ptcol_TimeSet = timer6hour;	
			}			
		
		}	
		break;				
		
		case timer6hour:
		{
			if((Ptcol_RunMode == hot_dry)||(Ptcol_RunMode == warmhouse))
			{
				if(TimeAdd_sta == 0)
				{
					Ptcol_TimeSet = timer15min;		
					
				}
				else
				{
					Clr_KeyAddDelay_flag;	     /* ��ʹһֱ�����̶�������ֵ */
					
				}
			}
			else
			{
				Ptcol_TimeSet = timerconti;	
			}	
		}	
		break;
		
		case timerconti:
		{
			if(TimeAdd_sta == 0)
			{
				Ptcol_TimeSet = timer15min;						
			}
			else
			{
				Clr_KeyAddDelay_flag;	    /* ��ʹһֱ�����̶�������ֵ */
			}			
		}
		break;	
		default:
		break;		
	}
		
}

/*************************************************************************
//					void TimeSave_func(void)
//					���涨ʱʱ��					
*************************************************************************/
void TimeSave_func(void)
{
	//���涨ʱʱ��
	if(Ptcol_RunMode == warmhouse)            
		{
			stWarm_Stro.gcTimeSet = Ptcol_TimeSet;
		}
	else if(Ptcol_RunMode == changeair)
		{	
			stChAir_Stro.gcTimeSet = Ptcol_TimeSet;
		}
	else if(Ptcol_RunMode == cold_dry)
		{
			stCold_dry.gcTimeSet = Ptcol_TimeSet;	
		}
	else if(Ptcol_RunMode == hot_dry)
		{
			stHot_dry.gcTimeSet = Ptcol_TimeSet;	
		}
	else if(Ptcol_RunMode == degerming)
		{
			stDegerming.gcTimeSet = Ptcol_TimeSet;	
		}	
	
}
/*************************************************************************
//					void TimeAddHandle_func(void)
//					��ʱ+�������´�����
//					
*************************************************************************/
void TimeAddHandle_func(void)
{
	switch (TimeAdd_sta)	
	{
		case 0:
		{
			Set_KeyAddDelay_flag;
			
			TimeAdd_func();
			TimeSave_func();
			Time_convert();	      //��ʱ����20211123
			gi1sCount = 0;			
			
			TimeAdd_sta = 1;		
		}
		break;
		
		case 1:                //ʵ�������Ĺ���
		{
			
		}
		break;		
	
		case 2:
		{
			TimeAdd_func();
			TimeSave_func();
			Time_convert();	     //��ʱ����20211123
			gi1sCount = 0;			
			
			TimeAdd_sta = 1;				
		}
		break;
				
		default:
		break;					
	}
}

/*************************************************************************
//					uint16_t KeyCheck(void)
//					����ɨ�躯�������ذ���ֵ
//					
*************************************************************************/
unsigned int KeyCheck(void)
{
		switch(gcKeyState)
		{
			case 0:
			{
				Set_All_OutPut();          //���������
				DELAY_xUs(10);
				
				if( (ReadKEY_PA6 == 0) || (ReadKEY_PA8 == 0) || (ReadKEY_PA10 == 0) )   //�а�������
				{
					gcKeyCount++;
					if(gcKeyCount >= 5)      //����
					{
						gcKeyCount = 0;
						gcKeyState = 1;
						Clr_WdtWakeUp_Flag;      //������Ź����ѵı�־
					}
				}
				else
				{
					gcKeyCount = 0;
				}				
			}
			break;
			case 1:
			{
				giSleepTime = 0;
				Set_KeyReturn_Flag;
				Get_KeyValue();         // ��ȡ������ֵ
				
				if(giKeyValue == KEYcom1)   // ��ϰ���  ��ȡů�뻻����
				{
					Clr_KeyReturn_Flag;       // �尴�����صı�־
					giKeyValue = 0;  	         
				}
				if(giKeyValue == KEYSW4)
				{					
					gcKey4LongEn = 1;
				}
				gcKeyState = 2;
			}
			break;
			case 2:
			{
				Set_All_OutPut();
				
				Clr_PA5;
				Clr_PA7;
				Clr_PB0;
				Clr_PB1;
				DELAY_xUs(10);
				if( (ReadKEY_PA6) && (ReadKEY_PA8) && (ReadKEY_PA10) )   //���ⰴ������
				{
				gcKeyCount++;
				if (gcKeyCount >= 3)
				{
					gcKeyCount = 0;
					gcKeyState = 0;						
					if(Key4Down_Flag)       //��ʱ����
					{
						Clr_KeyAddDelay_flag;
						TimeAdd_sta = 0;
						giKeyAddDelay_Count = 0;
						giKeyValue = KEYSW4;
						Set_KeyReturn_Flag;	
						Clr_Key4Down_Flag;	
            						
					}	
					

					if(KEYSW2Count < 300)   
					{
						if(Key2Down_Flag)     //���������̰�
						{
							giKeyValue = KEYSW2;
							Set_KeyReturn_Flag;	
							Clr_Key2Down_Flag;							
						}				
					}
					else
					{
						giKeyValue &= 0xfffe;	       //0x1110
					}					
					KEYSW2Count = 0;

//					if((Ptcol_RunMode != standby)&&(Ptcol_RunMode != changeair))    
//					{                                                        //������ģʽ���ֵ�����Ч
//						if((KEYSW10Count < 310))       //����10�̰�
//						{
//							if(Key10Down_Flag)
//							{
//								giKeyValue = KEYSW10;
//								Set_KeyReturn_Flag;	
//								Clr_Key10Down_Flag;									
//							}	
//							
//						}
//						else
//						{
//							giKeyValue &= 0xfdff;		    //�����㣨ȫ1Ϊ1��					
//						}
//					}
//					else
//					{
//						Clr_Key10Down_Flag;
//						giKeyValue &= 0xfdff;
//					}
//					KEYSW10Count = 0;
														
					if(KeyComcount == 310)       //��ϼ�3s ����֤��������ͬʱ���£�
					{	
						
						Clr_Key6Down_Flag;
						Clr_Key5Down_Flag;						
					}
					KeyComcount = 0;

					if(Key6Down_Flag)
					{
						Set_RfSendEnable_Flag;
						Set_MainFun_flag;	   				
//						giKeyValue = KEYSW6;
//						Set_KeyReturn_Flag;
						Clr_Key6Down_Flag;
					}
					else if(Key5Down_Flag)
					{
						Set_RfSendEnable_Flag;
						Set_MainFun_flag;   
//						giKeyValue = KEYSW5;
//						Set_KeyReturn_Flag;
						Clr_Key5Down_Flag;
					}					
				}
			}
				
			 else    //���������Ĵ���
				{
					giSleepTime = 0;			//����������ʱ�򣬲�����˯��
					
					Get_KeyValue();
					
					if (giKeyValue  == KEYcom1)     //ͬʱ����ȡů�ͻ��� 3s  ���
					{
						if (KeyComcount <300)      // ����������ʱ��
							KeyComcount++;
						if (KeyComcount == 300)
						{
							KeyComcount = 310;
							Set_KeyReturn_Flag;
							giKeyValue = KEYcom1;

						}
					}
					if((giKeyValue  == KEYSW4)&&(gcKey4LongEn == 1))     //��ʱ���� (�������)
					{
						TimeAddHandle_func();
						Set_LEDon_Flag;
            giLED_status = giLED_Tempstatus;						
					}
					else
					{
						gcKey4LongEn = 0;
						Clr_KeyAddDelay_flag;
						TimeAdd_sta = 0;       //�Ӷ�ʱ
						giKeyAddDelay_Count = 0;	
					}
					
////					if(giKeyValue == KEYSW10)   //���ֳ���3s  ����  �������������ԣ�
////					{
////						if(KEYSW10Count < 300)
////						{
////							KEYSW10Count++;	
////						}
////						
////						if(KEYSW10Count == 300)
////						{
////							KEYSW10Count = 310;
////							Set_KeyReturn_Flag;
////							giKeyValue = KEYSW10_3s;
////						}
////						
////					}				
				
					if(giKeyValue == KEYSW2)    //������������3s
					{
						if(KEYSW2Count < 300)
						{
							KEYSW2Count++;	
						}
						
						if(KEYSW2Count == 300)
						{
							KEYSW2Count = 310;
							Set_KeyReturn_Flag;
							giKeyValue = KEYSW2_3s;
						}	
					}				

				}				
			
			break;
		}
  }
	
	if (KeyReturnFlag)
	{
		Clr_KeyReturn_Flag;
		return giKeyValue;
	}
	else
	{
		return 0x0000;	
	}	
		
}


/*************************************************************************
//					void Key_Process(void)
//					����ֵ������
//					
*************************************************************************/

void Key_Process(void)
{
	switch (giTempKeyVal)        //��������ʱֵ����
	{
		case KEYSW2:               //����
		{
			Set_RfSendEnable_Flag;
			Set_MainFun_flag;
	
			StandBy_func();	
					
		}
		break;
		
		case KEYSW6:               //ȡů
		{
			Set_RfSendEnable_Flag;
			Set_MainFun_flag;

			if(Ptcol_RunMode != warmhouse)
			{ 
	
				Ptcol_RunMode = warmhouse;	
				
				Ptcol_AirVol = strong;
				Ptcol_AirDir = stWarm_Stro.gcAirDir;
				Ptcol_Airkind = stWarm_Stro.gcAirkind;
				Ptcol_TimeSet = stWarm_Stro.gcTimeSet;
				
				Time_convert();
			  gi1sCount = 0;	
			}              			
				
//////			Time_convert();      //���趨ʱ��ת��Ϊʣ��ʱ��
//////			gi1sCount = 0;		
						
			Set_LEDon_Flag;
      giLED_status = LED_WarmHouse;
      giLED_Tempstatus = giLED_status;			
						
		}
		break;
		
		case KEYSW4:                //��ʱ  
		{
			Set_RfSendEnable_Flag;
			Set_MainFun_flag;
			
			Set_Rfwait500ms_Flag;
			giRf500msCount = 0;			

			
		}
		break;
		
		case KEYSW5:                 //����
		{
//			Set_RfSendEnable_Flag;
//			Set_MainFun_flag;

			if(Ptcol_RunMode != changeair)
			{
				Ptcol_RunMode = changeair;
				Ptcol_AirVol = strong;
				Ptcol_AirDir = stChAir_Stro.gcAirDir;
				Ptcol_Airkind = stChAir_Stro.gcAirkind;
				Ptcol_TimeSet = stChAir_Stro.gcTimeSet;
				
				Time_convert();	
			  gi1sCount = 0;
			}					
////			Time_convert();	      //
////			gi1sCount = 0;				
			
//			if(Ptcol_AirVol == weak)
//			{
//				giLED_status = (LED_AirChange|LED_AirWeak);		
//			}
//			else
//			{
//				giLED_status = (LED_AirChange|LED_AirStrong);	
//			}
			
			Set_LEDon_Flag;
      giLED_status = LED_AirChange;			
			giLED_Tempstatus = giLED_status;
		}
		break;
		
		
		case KEYSW7:                  //����   
		{  
			Set_RfSendEnable_Flag;	
			gcMainSubPair_Flag = 3;
			
			if(Ptcol_AirDir != automat)
			{
				Ptcol_AirDir = automat;
			}
			else
			{
				Ptcol_AirDir = fixed;
			}

			if(Ptcol_RunMode == changeair)                 //�����·������趨
			{
				Ptcol_AirDir = noneset;							
			}
			else if(Ptcol_RunMode == warmhouse)            //�������
			{
				stWarm_Stro.gcAirDir = Ptcol_AirDir;
			}
			else if(Ptcol_RunMode == cold_dry)
			{
				stCold_dry.gcAirDir = Ptcol_AirDir;	
			}
			else if(Ptcol_RunMode == hot_dry)
			{
				stHot_dry.gcAirDir = Ptcol_AirDir;	
			}
			
		}
		break;
		
		case KEYSW9:                  //�ȸ���
		{
			Set_RfSendEnable_Flag;
			Set_MainFun_flag;
			
			if(Ptcol_RunMode != hot_dry)
			{
				Ptcol_RunMode = hot_dry;
				Ptcol_AirVol = stHot_dry.gcAirVol;
				Ptcol_AirDir = stHot_dry.gcAirDir;
				Ptcol_Airkind = stHot_dry.gcAirkind;
				Ptcol_TimeSet = stHot_dry.gcTimeSet;
				Time_convert();	
				gi1sCount = 0;						
			}			
			
			Set_LEDon_Flag;	
			giLED_status = LED_HotDry;	
      giLED_Tempstatus = giLED_status;			
		}
		break;	
		
		case KEYSW10:                 //����-����
		{
			Set_RfSendEnable_Flag;
			gcMainSubPair_Flag = 3;
			
			if(Ptcol_Airkind != focus)
			{
				Ptcol_Airkind = focus;
			}
					
			if(Ptcol_RunMode == changeair)           //�����·������趨
			{
				Ptcol_Airkind = noneset;							
			}
			else if(Ptcol_RunMode == warmhouse)      //�������
			{

				stWarm_Stro.gcAirkind = Ptcol_Airkind;
			}
			else if(Ptcol_RunMode == cold_dry)
			{
				stCold_dry.gcAirkind = Ptcol_Airkind;	
			}
			else if(Ptcol_RunMode == hot_dry)
			{
				stHot_dry.gcAirkind = Ptcol_Airkind;	
			}
						
			Set_Rfwait500ms_Flag;
			giRf500msCount = 0;			
		}
		break;
		
		case KEYSW12:                   //����-��ɢ
		{
			Set_RfSendEnable_Flag;
			gcMainSubPair_Flag = 3;
			
			if(Ptcol_Airkind != spread)
			{
				Ptcol_Airkind = spread;          //��ɢ
			}
			if(Ptcol_RunMode == changeair)     //�����·������趨
			{
				Ptcol_Airkind = noneset;							
			}
			else if(Ptcol_RunMode == warmhouse)
			{
				stWarm_Stro.gcAirkind = Ptcol_Airkind;
			}
			else if(Ptcol_RunMode == cold_dry)
			{
				stCold_dry.gcAirkind = Ptcol_Airkind;	
			}
			else if(Ptcol_RunMode == hot_dry)
			{
				stHot_dry.gcAirkind = Ptcol_Airkind;	
			}				
			Set_Rfwait500ms_Flag;
			giRf500msCount = 0;			
		}
		break;
		
		
		case KEYSW8:                   //������
		{
			Set_RfSendEnable_Flag;
			Set_MainFun_flag;
			
			if(Ptcol_RunMode != cold_dry)
			{
				Ptcol_RunMode = cold_dry;
				Ptcol_AirVol = stCold_dry.gcAirVol;
				Ptcol_AirDir = stCold_dry.gcAirDir;
				Ptcol_Airkind = stCold_dry.gcAirkind;
				Ptcol_TimeSet = stCold_dry.gcTimeSet;			
				Time_convert();	
				gi1sCount = 0;						
			}
			
			Set_LEDon_Flag;	
			giLED_status = LED_ColdDry;
      giLED_Tempstatus = giLED_status;			
		}
		break;
		
		
		case KEYcom1:              //���
		{
			Set_RfSendEnable_Flag;
			Set_PairFun_flag;				
		}
		break;
		
//		case KEYSW10_3s:         //����   �������������ԣ�
//		{
//			Set_RfSendEnable_Flag;
//			Set_SubFun_flag;
//			
//			if(Ptcol_voice != voice_off) 
//			{
//				Ptcol_voice = voice_off;	
//			}
//			else
//			{
//				Ptcol_voice = voice_on;		
//			}
//			
//			TxPtcol_voice = Ptcol_voice;		
//		}
//		break;

			
		case KEYSW2_3s:
		{
			StandBy_init();	
		}
		break;		
			
		default:
		break;									
	}
	giKeyValue = 0;
	giTempKeyVal = 0;
}

