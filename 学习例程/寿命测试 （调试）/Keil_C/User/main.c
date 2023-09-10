//Set:�밴�ո����ý���OPTION��������ܳ���
//WDT:Enable                EXternal 32K: Enable
//Systerm clock:Fosc/1      P5.2 Normal
//LVR 1.9V                  Vref: Internal 2.048V
//IAP Range��EEPROM Only    DISJTG:Normal
//Start from:APROM          LDROM Size:0K

//2022-5-25  �޸��ڿ��ضϿ���LED����������Ϊ��˸ ��˸ʱ����define FLASHTIME �ж���
//2022-5-30  �޸��ڲ����ⲿIR�жϷ�������Ϊ��ذ汾û���ⲿ���⣬�������¶����ж�ֵ 300~2100֮����Ϊ���ⲿIR������ֵ��Ϊ���ڲ�IR��

#include "SC_System.h"
#include "Key_Process.h"
#include "Burner_Process.h"
#include "Buzzer_Process.h"
#include "ADC_Process.h"
#include "Time_Process.h"
#include "Output_Process.h"
#include "Sleep_Process.h"
#include "Lifetest.h"
#include "SR_EEPROM.h"
#include "IapOperation.h"

struct Flag_Struct MyFlag;

uint8_t gcBurner1OpenCount;          
uint8_t gcBurner1CloseCount;        

uint8_t gcBurner2OpenCount;         
uint8_t gcBurner2CloseCount;       

uint8_t gcBurner3OpenCount;         
uint8_t gcBurner3CloseCount;        

uint8_t gcBurner4OpenCount;        
uint8_t gcBurner4CloseCount;         

uint8_t gcBurner5OpenCount;         
uint8_t gcBurner5CloseCount;         

uint8_t gcBurner6OpenCount;          
uint8_t gcBurner6CloseCount;        

uint8_t gcBurnerStatus;             
uint8_t gcBurnerOpenCount;        
uint8_t gcMCBuzzerstatus;
uint8_t gcAHCloseBuzzerStatus;

uint8_t gcKeyStatus;                
uint8_t gcKeyCount;                 
uint8_t gcOneMsCount;                
uint32_t gcButton1State;            
uint8_t gcKeyValue;                 
uint16_t giKeySW6LongDownTime;      
uint8_t  IRSendCommand[4]={0,0,0,0};
uint32_t gllIRSendData;                //IR Send Data
uint32_t gllIRSendDataBak;                //IR Send Data


uint8_t  IRSendDataBitCount;          // 24bit
uint8_t  gcIRSendStatus;
uint16_t  gcIRSendDelayTime;            // 1S
uint8_t gcIRSendCount = 0;              // 3
uint8_t gcIRSendLightOnCount = 0;				//�ƿ����ͼ���
uint8_t gcIRSendLightOnTime = 0;

uint8_t gcIRSendLightOffCount = 0;				//�ƹط��ͼ���
uint8_t gcIRSendLightOffTime = 0;

uint8_t gcIRSendSpeedOffCount = 0;		 
uint8_t gcIRSendSpeedOffTime = 0;

uint8_t gcIRSendSpeedCommandCount = 0;	 
uint8_t gcIRSendSpeedCommandTime = 0;

uint8_t gcBuzzerTime = 0;         

uint32_t gllIRAdcSumValue = 0;
uint16_t giIRADCValue = 0;
uint8_t  gcIRADCCount = 0;
uint16_t giPowerUpTime = 0;
uint8_t  gcPowerUpTime = 0;
uint16_t giLEDPwmValue = 0;
uint16_t giLEDFlashTime = 0;
uint8_t gcLEDFlashCount = 0;
uint8_t gcSpeedLevel = 0;
uint8_t gcT250MsCount = 0;
uint8_t gi500msCount = 0;
uint16_t  giTimesCount;

uint8_t gchightbit; 
uint8_t gcmediumbit;
uint8_t gclowbit;
uint8_t gcfallowbit;

uint8_t mday;
uint8_t giLEDTime;
uint8_t gcLedCount = 0;
uint8_t gcKey;
uint8_t TestLowPower;
extern uint8_t gcKey_Count;
uint8_t L1x,L2x,L3x,L4x;

extern unsigned char Readbuff[12]; 
extern uint8_t RadioFREQ[10];

volatile uint16_t giSpeedDelayOffTime;  // 5minute
volatile uint16_t giLightDelayOffTime;  // 5minute
volatile uint8_t gcADCDelayTime;

void Display_Day (uint8_t Days);

extern void IAP_Read_NByte(unsigned long Sadd,unsigned long Eadd,unsigned char Iapade);

void main(void)
{	
						
	
//	         giTimesCount = 125;
//			
//						RadioFREQ[0] =  giTimesCount / 1000;          
//						RadioFREQ[1] =  (giTimesCount - (giTimesCount / 1000) *1000)/100 ;
//						RadioFREQ[2] =  (giTimesCount - (giTimesCount / 1000) *1000 - ((giTimesCount - (giTimesCount / 1000) *1000)/100 ) *100) / 10; 
//						RadioFREQ[3] = (giTimesCount - (giTimesCount / 1000) *1000 - ((giTimesCount - (giTimesCount / 1000) *1000)/100 ) *100) % 10;
//						RadioFREQ[4] = 0x01;
//						Write_EEPROM();
		
//						Delay1ms(); 
//						Delay1ms(); 
//						Delay1ms(); 
	
//	          IAP_Read_NByte(0,10,EEPROM);
//					 
//					  L1x =  Readbuff[1];
//					  L2x =  Readbuff[2];
//					  L3x =  Readbuff[3];
//					  L4x =  Readbuff[4];							
//					  TestLowPower = Readbuff[5];
//	
//    IAP_Read_NByte(0,5,EEPROM);	
//	
//	  gchightbit  =  Readbuff[1];
//	  gcmediumbit =  Readbuff[2];
//		TestLowPowerFlag = Readbuff[3];
	
//		
//		RadioFREQ[2] = 1;

//	  giTimesCount =  Readbuff[2] * 256 + Readbuff[1];
//					 
//		 gchightbit = giTimesCount / 1000;
//		 gcmediumbit = (giTimesCount - gchightbit *1000)/100;
//		 gclowbit = (giTimesCount - gchightbit *1000 - gcmediumbit *100)/10;	
//		 gcfallowbit = (giTimesCount - gchightbit *1000 - gcmediumbit *100) % 10;


//    IAP_Read_NByte(0,5,EEPROM);
//					 
//		Lx =  Readbuff[1];
//		Hx =  Readbuff[2];
//		TestLowPowerFlag = Readbuff[3];
//	 
//	 giTimesCount =  Hx * 256 + Lx;
//	 
//	 gchightbit = giTimesCount / 1000;
//	 gcmediumbit = (giTimesCount - gchightbit *1000)/100;
//	 gclowbit = (giTimesCount - gchightbit *1000 - gcmediumbit *100)/10;	
//	 gcfallowbit = (giTimesCount - gchightbit *1000 - gcmediumbit *100) % 10;
	
	  gcPowerUpTime = 0;
    giPowerUpTime = 0;
    Clr_ExtIRFlag;
    Set_PowerUpFlag;
    SC_Init();
    Set_Cfg();    /* ѡ������Ⱥ��� */
    TouchKeyInit();
    Clr_IO();
    ADC_ExtIR_Check();
    Set_AutoModeFlag;
    TIM0_Cmd(ENABLE);
    TIM1_Cmd(ENABLE);
    EA = 1;
	 
		Set_ActivateModeFlag;
		Set_AutoModeFlag;     
		Set_FirstPowerUpFlag;
	
		Set_BatLowWarrnEnFlag;
	  Clr_BatLowWarrnFlag;        //���õ͵�ѹ����
		GPIO_Init(GPIO3, GPIO_PIN_1, GPIO_MODE_OUT_PP); /* ���ѡ���� */
		
		SR_EEPROM_Init();
		
		Clr_HalfSecondFlag;
		Clr_DisPlayModeFlag;
	
    while(1)
    {
//			  P31=~P31;				//��BTM���ѣ��û�������Ҫ�������������
				WDTCON |= 0X10;
        if(GetLowPowerScanFlag())
        {
            LowPower_Touchkey_Scan();  
        }
        else
        {   			 		
				//	Key_Scan();
					  if (gcOneMsCount >= 10) /* 10ms */
            {			
							 gcOneMsCount = 0;								
							 Key_Process();
							 Burner_Process();
							
							ADC_Process();     //��Դ��ѹһֱ�ټ��
							
							if(gcT250MsCount >= 125)        //��ʱ��Ϊ125ms 7.11
							{
								gcT250MsCount = 0;
								Time_Process();
							}
							Output_Process();
						  Sleep_Process();	
//							GPIO_Init(GPIO3, GPIO_PIN_1, GPIO_MODE_OUT_PP); //* ���ѡ���� 			 ����ʱ���ӣ����⻽�Ѻ�ö˿ڱ� ��ʼ��������ˡ�	
							if(DisPlayModeFlag == 1)    //��ʾģʽ��  �������͵�ѹ������
							{								
                Clr_BatLowWarrnFlag;           //ֹͣ�͵�ѹ����
								if (TestLowPower == 0x01)        //���������λΪ1,�������ʾ
								{
										gi500msCount++;
										if(gi500msCount > 50)      //��ʱ500ms
										{
//											P31=~P31;				//��BTM���ѣ��û�������Ҫ�������������
											gi500msCount = 0;	
											
											switch (gcKey)
											{
												case 1:
												{	
													Display_Day(L1x);
												}
												break;
												case 2:
												{
												
													Display_Day(L2x);
												}
												break;
												case 3:
												{
													
													Display_Day(L3x);
												}
												break;
												case 4:
												{
													
													Display_Day(L4x);													
												}
												break;									
												default:
													break;
											}
												
										}
								}										
										
            }
					
        }
    }
}

}

void Display_Day (uint8_t Days)
{		  
	  gcLedCount++;//�����Ĵ���
		if(gcLedCount <= 2 * Days)
		{
			P23=~P23;
			
		}
	 else
	 {
		  gcKey = 0;
			P23=1;      //���
	 }

}

