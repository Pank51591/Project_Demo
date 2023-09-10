#include "SC_System.h"
#include "Burner_Process.h"
#include "Output_Process.h"
#include "Lifetest.h"

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

extern uint8_t gcIRSendLightOffCount ;				//灯开发送计数
extern uint8_t gcIRSendLightOffTime ;

extern uint8_t gcIRSendSpeedOffCount;				 
extern uint8_t gcIRSendSpeedOffTime;

extern uint8_t gcIRSendSpeedCommandCount ;	 
extern uint8_t gcIRSendSpeedCommandTime ;

extern uint8_t gclifeteststatus;

uint8_t gcTenMsCount = 0;
uint8_t gcT10MsCount = 0;

uint8_t gcT500MsCount = 0;

//=======================================================================================
//                  void Time_Process(void)
//                  Run once in 125ms         
//                  Return value::No
//=======================================================================================
 void Time_Process(void)
 {
	 
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
	  if (gcT10MsCount >= 4  * 2 )   //按照define设定时间进行闪烁
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

         if (LightOffDelayStartFlag)      // 计时5分钟
         {
					 
             if (giLightDelayOffTime <= 60*5)
             giLightDelayOffTime++;
             if (giLightDelayOffTime == 60*5)
             {
							   Set_KeySureBuzzerFlag;      //五分钟结束后，蜂鸣器响一声
                 giLightDelayOffTime = 0;
                 Clr_LightOffDelayStartFlag;
                 Set_SendLightOffCommandFlag; 
                 Clr_FirSendLightOnCommandFlag;
							 
							   gcIRSendLightOffTime = LIGHTOFFTIME;
								// Set_SendLightOffCommandFlag; 
							 Set_SysWakeUpSleepFlag;
							 
							 gclifeteststatus = 0;	
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
                 Set_SendSpeedOffCommandFlag; 
                 Clr_FirstSendSpeedOffCommandFlag;
							    gcIRSendSpeedOffTime = SPEEDOFFTIME;
									Set_SysWakeUpSleepFlag;
             }
         }
         else
         {
             giSpeedDelayOffTime = 0;
         }
     }
  
 }
