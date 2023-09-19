#include "SC_System.h"
#include "Burner_Process.h"
#include "Output_Process.h"

extern uint8_t gcBurner1OpenCount;       
extern uint8_t gcBurner1CloseCount;       

extern uint8_t gcBurner2OpenCount;        
extern uint8_t gcBurner2CloseCount;       

extern uint8_t gcBurner3OpenCount;        
extern uint8_t gcBurner3CloseCount;      

extern uint8_t gcBurner4OpenCount;         
extern uint8_t gcBurner4CloseCount;        

extern uint8_t gcBurner5OpenCount;        
extern uint8_t gcBurner5CloseCount;        

extern uint8_t gcBurner6OpenCount;         
extern uint8_t gcBurner6CloseCount;        

extern uint8_t gcBurnerStatus;            
extern uint8_t gcBurnerOpenCount;   

extern uint8_t gcKeyStatus;                
extern uint8_t gcKeyCount;                
extern uint8_t gcOneMsCount;               
extern uint32_t gcButton1State;             
extern uint8_t gcKeyValue;                
extern uint16_t giKeySW6LongDownTime;      
extern uint8_t gcBuzzerTime; 
extern uint8_t  gcPowerUpTime;
extern uint16_t giLEDPwmValue;
extern volatile uint16_t giLightDelayOffTime;  // 5minute
extern volatile uint16_t giSpeedDelayOffTime;  // 5minute
extern uint8_t gcIRSendLightOnCount;
extern uint8_t gcIRSendLightOnTime;

extern uint8_t gcIRSendLightOffCount ;				//�ƿ����ͼ���
extern uint8_t gcIRSendLightOffTime ;

extern uint8_t gcIRSendSpeedOffCount;				 
extern uint8_t gcIRSendSpeedOffTime;

extern uint8_t gcIRSendSpeedCommandCount ;	 
extern uint8_t gcIRSendSpeedCommandTime ;

extern uint8_t gcSpeedLevel;

uint8_t gc250msCount = 0;
uint8_t gc250msCount2 = 0;

uint8_t gcTenMsCount = 0;
uint8_t gcT10MsCount = 0;

uint8_t gcT500MsCount = 0;
uint16_t giTestTime = 0;
uint8_t gcWaitKeyTime = 0;

//=======================================================================================
//                  void Time_Process(void)
//                  Run once in 125ms         
//                  Return value::No
//=======================================================================================
 void Time_Process(void)
 {	 
	 /*������һ���رյĹ��ܣ���������صƵ��źź󣬼��250ms�ٷ��͹ط��ȵ��ź�*/
	 if(LightOffDelay250ms_Flag)            //��ʼ��ʱ250ms
	 {
		 if(gc250msCount < 2)
		 {
				gc250msCount++;	
		 }			 
		 if(gc250msCount >= 2)
		 {
			 gc250msCount = 0;
			 Clr_LightOffDelay250ms_Flag;
			 
			 Set_SendSpeedOffCommandFlag; 							 
			 gcIRSendSpeedOffTime = 100;           //�������͹ط��ȵ��ź�
			 Set_SysWakeUpSleepFlag;		 
		 }
	 }
	 
	 /*250ms���Ϳ���������*/
	 if(LightOnDelay250ms_Flag)
	 {
		 if(gc250msCount2 < 2)
		 {
			 gc250msCount2++;
		 }
		 if(gc250msCount2 >= 2)
		 {
			 gc250msCount2 = 0;
			 Clr_LightOnDelay250ms_Flag;		 
			 Clr_ToBurnerOpen_Flag;            //����¯ͷ�պϵı�־
			 
			 /*�жϷ���*/
			if ((gcBurnerStatus&0x01) ||(gcBurnerStatus&0x02) )     // work burner 
			{
				 gcSpeedLevel = 2;
			}
			else if (gcBurnerOpenCount > 1)
			{
				 gcSpeedLevel = 2;
			}
			else
			{																			
				 gcSpeedLevel = 1; 																					
			}			
			 /*������*/
			 Clr_IRSendEnFlag;                                
			 Clr_INTENSIVEONModeFlag;          //����ܼ�ģʽ 																																
			 Set_SendSpeedCommandFlag;
			 Set_SysWakeUpSleepFlag;          //�˳��͹���ģʽ
			 gcIRSendSpeedCommandTime =  100;         //SPEEDCOMMANDTIME;      //75																  															

		 }	 
			 
	 }
	 
	 
	 
	 gcT500MsCount++;
	 if (gcT500MsCount >= 2 * 2)
	 {
		 gcT500MsCount = 0;
		 if (LowFlashLedFlag)
			 Clr_LowFlashLedFlag;
		 else
			 Set_LowFlashLedFlag;
	 }
	 
		gcT10MsCount++;
	  if (gcT10MsCount >= 4  * 2 )    //����define�趨ʱ�������˸
		{
		 	gcT10MsCount = 0;
			 
			 if (HalfSecondFlag)
			 {
					 Clr_HalfSecondFlag;
			 }
			 else
			 {
					 Set_HalfSecondFlag;
				 
			 }
		}
     gcTenMsCount++;
     if (gcTenMsCount >= 4  * 2)   // 1s
     {
         gcTenMsCount = 0;

         if (LightOffDelayStartFlag)      // ��ʱ5����
         {					 
             if (giLightDelayOffTime <= 60*5)
								giLightDelayOffTime++;
             if (giLightDelayOffTime == 60*5)
             {
							   
							   Set_KeySureBuzzerFlag;         //����ӽ����󣬷�������һ��
                 giLightDelayOffTime = 0;
                 Clr_LightOffDelayStartFlag;
                 Set_SendLightOffCommandFlag; 
                 Clr_FirSendLightOnCommandFlag;
							 
							   gcIRSendLightOffTime = LIGHTOFFTIME;
								 Set_SysWakeUpSleepFlag;
             }
         }
         else
         {
             giLightDelayOffTime = 0;
         }
         
         if (SpeedDelayOffStartFlag)
         {
             if (giSpeedDelayOffTime <= 60*5)  
									giSpeedDelayOffTime++;
             if (giSpeedDelayOffTime == 60*5)
             {
                 giSpeedDelayOffTime = 0;
                 Clr_SpeedDelayOffStartFlag;
 						     Clr_FirstSendSpeedOffCommandFlag;
							 
                 /*����ֱ�ӹ���һ���رյĹ�����Ĵ���*/							 
//                 Set_SendSpeedOffCommandFlag;               
//								 gcIRSendSpeedOffTime = SPEEDOFFTIME;
//								 Set_SysWakeUpSleepFlag;
             }
         }
         else
         {
             giSpeedDelayOffTime = 0;
         }
				 
				 if(IntoTestFlag)           //��ʱ2����
				 {
					 
					 if(giTestTime < 60*2)
					 {
						 giTestTime++;
							
					 }
					 if(giTestTime >= 60*2)       //����2���ӣ��˳��Լ�
					 {
						 giTestTime = 0;
						 Clr_IntoTestFlag;
						 Clr_TestONFlag;
						 Delay1ms();          
						 GPIO_Init(GPIO3, GPIO_PIN_2, GPIO_MODE_OUT_PP);    //��P32���ó�����������Դﵽʡ��
						 Delay1ms();
						 P32 = 0; 
					 }
					 
					 /*��ʱ5s���ȴ���������*/
////					 if(Wait5sFlag)     //������ֹͣ
////					 {
////						 if(gcWaitKeyTime < 10)
////						 {
////							 gcWaitKeyTime++;
////						 }
////						 if(gcWaitKeyTime >= 10)
////						 {
////							 Clr_Wait5sFlag;
////							 gcWaitKeyTime = 0;
////							 Set_WaitKeyTimeFlag;
////						 }
////					 }
					 
				 }
     }
  
 }
