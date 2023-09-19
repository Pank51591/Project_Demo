//Set:�밴�ո����ý���OPTION��������ܳ���
//WDT:Enable                EXternal 32K: Enable
//Systerm clock:Fosc/1      P5.2 Normal
//LVR 1.9V                  Vref: Internal 2.048V      //����Ӧ����2.4v
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


struct Flag_Struct MyFlag;

uint8_t gcBurner1OpenCount = 0;          
uint8_t gcBurner1CloseCount = 0;        

uint8_t gcBurner2OpenCount = 0;         
uint8_t gcBurner2CloseCount = 0;       

uint8_t gcBurner3OpenCount = 0;         
uint8_t gcBurner3CloseCount = 0;        

uint8_t gcBurner4OpenCount = 0;        
uint8_t gcBurner4CloseCount = 0;         

uint8_t gcBurner5OpenCount = 0;         
uint8_t gcBurner5CloseCount = 0;         

uint8_t gcBurner6OpenCount = 0;          
uint8_t gcBurner6CloseCount = 0;        

uint8_t gcBurnerStatus = 0;             
uint8_t gcBurnerOpenCount = 0;  

//uint8_t gcMCBuzzerstatus;
//uint8_t gcAHCloseBuzzerStatus;

uint8_t gcKeyStatus = 0;                
uint8_t gcKeyCount = 0;                 
uint8_t gcOneMsCount = 0;                
uint32_t gcButton1State = 0;            
uint8_t gcKeyValue = 0;                 
uint16_t giKeySW6LongDownTime = 0;      
uint8_t  IRSendCommand[4]={0,0,0,0};
uint32_t gllIRSendData = 0;                //IR Send Data
uint32_t gllIRSendDataBak = 0;                //IR Send Data


uint8_t  IRSendDataBitCount = 0;          // 24bit
uint8_t  gcIRSendStatus = 0;
uint16_t  gcIRSendDelayTime = 0;            // 1S
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
uint16_t giT500msCount = 0;
uint8_t gc50msCount = 0;
uint8_t gcIRSendTestACount =0;
uint8_t gcIRSendTestBCount =0;
uint8_t gcIRSendTestCCount =0;

uint8_t gcVar;
uint16_t gcVar2;
uint8_t gcTemp;

unsigned char gcSleepDelayTime = 0;

volatile uint16_t giSpeedDelayOffTime;  // 5minute
volatile uint16_t giLightDelayOffTime;  // 5minute
volatile uint8_t gcADCDelayTime;

extern uint8_t gcBurnerCheckStatus;
extern uint8_t gcTestSendIRStatus;
void IS_IntoTest (void);


void main(void)
{  
	  Clr_AllFlag();
	  gcPowerUpTime = 0;
    giPowerUpTime = 0;
    Clr_ExtIRFlag;
    Set_PowerUpFlag;
    SC_Init();
	  SC_JP1();
    Set_Cfg();      /* ѡ������Ⱥ��� */
    //		SOCAPI_DeBugTouchKey_Init();      //����ʱ�������Ҫ���ε�
    IS_IntoTest();
	  TouchKeyInit();
    Clr_IO();
    ADC_ExtIR_Check();
    Set_AutoModeFlag;
    TIM0_Cmd(ENABLE);
    TIM1_Cmd(ENABLE);
    EA = 1;
	 
	  gcBurnerCheckStatus = 0;
		
		Set_ActivateModeFlag;
		Set_AutoModeFlag;     
		Set_FirstPowerUpFlag;	
		Set_BatLowWarrnEnFlag;
	  Clr_BatLowWarrnFlag;        //���õ͵�ѹ����
		Clr_ToBurnerOpen_Flag;
		GPIO_Init(GPIO3, GPIO_PIN_1, GPIO_MODE_OUT_PP);   /* ���ѡ���� */
		
	
    while(1)
    {
			  // GPIO_Init(GPIO3, GPIO_PIN_1, GPIO_MODE_OUT_PP); //* ���ѡ���� 			 ����ʱ���ӣ����⻽�Ѻ�ö˿ڱ� ��ʼ���������
				WDTCON |= 0X10;
        if(GetLowPowerScanFlag())
        {
            LowPower_Touchkey_Scan();  
        }
        else
        {  
         //  P31=~P31; 					//��BTM���ѣ��û�������Ҫ�������������
				 //	 Key_Scan();
					if (gcOneMsCount >= 10) /* 10ms */
					{
						 gcOneMsCount = 0;
						 Key_Process();
						 Burner_Process();
						
						 if(TestONFlag)
							{		
								TestKey_Process();         //�����԰���								
							}
						
							gc50msCount++;
							if(gc50msCount >= 5)      //50
							{
								gc50msCount = 0;
								if(TestONFlag)
								{
									SC_Init();									
									SC_JP1();
									Clr_ExtIRFlag;
									ADC_ExtIR_Check();
								}
							}
							
						 ADC_Process();																					
						 Output_Process();
						 Sleep_Process();
										
						//GPIO_Init(GPIO3, GPIO_PIN_1, GPIO_MODE_OUT_PP);         //* ���ѡ���� 			 ����ʱ���ӣ����⻽�Ѻ�ö˿ڱ� ��ʼ��������ˡ�	
					}
					
					if(gcT250MsCount >= 125)      //��ʱ��Ϊ125ms   7.11      (����ʱ��7.28���Ž��ж�����)
						{
							gcT250MsCount = 0;
							Time_Process();
						}
					
        }
    }
}

void IS_IntoTest (void)
{	
	
	if(P32 == 0)      //һ�ϵ��ʼ�������ó����룬����P3.2�ǵ͵�ƽ�������Լ�
	{
		Set_Wait5sFlag;
		Set_TestONFlag;
    Set_IntoTestFlag;
    gcSleepDelayTime = 0;     //������˯��
    Set_SendTestAFlag;
	  Set_SendTestBFlag;
	  Set_SendTestCFlag;
    Clr_IRSendEnFlag;		
	}
	else   
	{
		Clr_IntoTestFlag;	 		
	}
}

