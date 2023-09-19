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

extern uint8_t gcIRSendLightOffCount ;				//灯开发送计数
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
	 /*（用于一键关闭的功能）当发送完关灯的信号后，间隔250ms再发送关风扇的信号*/
	 if(LightOffDelay250ms_Flag)            //开始计时250ms
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
			 gcIRSendSpeedOffTime = 100;           //立即发送关风扇的信号
			 Set_SysWakeUpSleepFlag;		 
		 }
	 }
	 
	 /*250ms后发送开风扇命令*/
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
			 Clr_ToBurnerOpen_Flag;            //清有炉头闭合的标志
			 
			 /*判断风速*/
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
			 /*开风扇*/
			 Clr_IRSendEnFlag;                                
			 Clr_INTENSIVEONModeFlag;          //清除密集模式 																																
			 Set_SendSpeedCommandFlag;
			 Set_SysWakeUpSleepFlag;          //退出低功耗模式
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
	  if (gcT10MsCount >= 4  * 2 )    //按照define设定时间进行闪烁
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
							   
							   Set_KeySureBuzzerFlag;         //五分钟结束后，蜂鸣器响一声
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
							 
                 /*这里直接共用一键关闭的功能里的代码*/							 
//                 Set_SendSpeedOffCommandFlag;               
//								 gcIRSendSpeedOffTime = SPEEDOFFTIME;
//								 Set_SysWakeUpSleepFlag;
             }
         }
         else
         {
             giSpeedDelayOffTime = 0;
         }
				 
				 if(IntoTestFlag)           //计时2分钟
				 {
					 
					 if(giTestTime < 60*2)
					 {
						 giTestTime++;
							
					 }
					 if(giTestTime >= 60*2)       //超过2分钟，退出自检
					 {
						 giTestTime = 0;
						 Clr_IntoTestFlag;
						 Clr_TestONFlag;
						 Delay1ms();          
						 GPIO_Init(GPIO3, GPIO_PIN_2, GPIO_MODE_OUT_PP);    //将P32设置成推挽输出，以达到省电
						 Delay1ms();
						 P32 = 0; 
					 }
					 
					 /*延时5s，等待按键按下*/
////					 if(Wait5sFlag)     //计满就停止
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
