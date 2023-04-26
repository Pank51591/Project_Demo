#include "SC_System.h"
#include "Burner_Process.h"
#include "Output_Process.h"

extern void SC_PWM3_Init_2Khz(void);

extern void SC_PWM3_Init_41Khz(void);

extern void SC_PWM3_Init(void);
extern void SC_PWM3_Init_33Khz(void);

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
extern uint16_t giPowerUpTime;
extern uint8_t  gcPowerUpTime;
extern uint16_t giLEDPwmValue;
extern uint16_t giLEDFlashTime;
extern uint8_t gcLEDFlashCount;
extern uint8_t gcSpeedLevel;
extern uint32_t gllIRSendData;                //IR Send Data
extern uint32_t gllIRSendDataBak;                //IR Send Data
extern uint8_t  IRSendDataBitCount;          // 24bit
extern uint8_t  gcIRSendStatus;
extern uint16_t  gcIRSendDelayTime;             // 1S
extern uint8_t gcIRSendCount;                  // 3
extern uint8_t gcIRSendLightOnCount;
extern uint8_t gcIRSendLightOnTime;

extern uint8_t gcIRSendLightOffCount ;				//灯开发送计数
extern uint8_t gcIRSendLightOffTime ;

extern uint8_t gcIRSendSpeedOffCount;				 
extern uint8_t gcIRSendSpeedOffTime;

extern uint8_t gcIRSendSpeedCommandCount ;	 
extern uint8_t gcIRSendSpeedCommandTime ;

extern uint8_t gcVar;
extern uint8_t gcTemp;

uint32_t gllTestIRSendData = 0;
uint32_t gllTestIRSendData1 = 0;
uint32_t gllTestIRSendData2 = 0;
uint32_t gllTestIRSendData3 = 0;

uint8_t gcTestSendIRStatus = 0;

uint8_t gcBatHigh4bit;
uint8_t gcBatLow8bit;

uint8_t gcIRSendTestATime;
uint8_t gcIRSendTestBTime;
uint8_t gcIRSendTestCTime;

extern 	unsigned 	int		xdata 	RawData[];			 				
extern 	unsigned 	int		data	  BaseLine[];	
extern uint32_t gllIRSendDataBak;                //IR Send Data
extern uint8_t gcIRSendCount;
extern uint16_t gcIRSendDelayTime;
extern uint8_t gcIRSendTestACount;
extern uint8_t gcIRSendTestBCount;
extern uint8_t gcIRSendTestCCount;
extern uint8_t IRSendDataBitCount;   // 24bit
extern uint16_t giBatValue;          //检测到的电压值
extern uint16_t giADCValue;

uint8_t gcTestDataACount = 0;
uint8_t gcTestDataBCount = 0;
uint8_t gcTestDataCCount = 0;

uint8_t gcPWMCly = 0;
uint8_t gcPWMWaitTime = 0;
uint16_t gcPWMCount = 0;
uint8_t PWMUpDown_Flag;
uint8_t gcPWMDelayTime = 0;

uint8_t gcSleedFlashTime = 0;
extern unsigned char gcSleepDelayTime;
void LED_Process(void);

#define PWMMaxTime         31999
uint8_t gcSleepTime;
void Set_PWMDuty(uint16_t PWM)
{
   // TC2_Compare16bitMatch1Set(PWM);
	PWM_IndependentModeConfigEX(PWM20, PWM, PWM_OUTPUTSTATE_ENABLE);
}

void WakeAutoSleep(void)
{

	if(SysWakeUpSleepFlag)
			{
				Clr_SysWakeUpSleepFlag;
				TouchKey_QuitLowPowerMode();
			}
			
}
void SleepLED_Process(void)
{
	
	if (PowerUpFlag)
	{
		
	}
	else
	{
		LED_Process();
	}
}
void LED_Process(void)
{
	  if(TestONFlag)
		{
				if(LEDONFlag)
				{
					Set_LED;
				}
				else
				{
					Clr_LED;
				}
		}
		else if (BatLowWarrnFlag)			//低电压报警时，优先显示LED状态
			{
				 if(gcBurnerStatus != 0)     //有炉头开启
				 {
					if (LowFlashLedFlag)
					{
						Set_LED;
					}
					else
					{
						Clr_LED;
					}
					gcSleepTime = 0;
				}
			}
		else if ((LightOffDelayStartFlag)||(SpeedDelayOffStartFlag))
				{
//					P31=~P31;
					if (HalfSecondFlag)
					{
						Set_LED;
					}
					else
					{
						Clr_LED;
					}
				}
		else if (ActivateModeFlag)
				 {
						 if (gcBurnerStatus != 0)
						 {
									Set_LED;
									gcPWMCount = 0;
							  
						 }
						 else
						 {
						  	 
								 Clr_LED;
						 }
							 
				 }
		else
		 {
				Clr_LED;
		 }

}
//=======================================================================================
//                  void Output_Process(void)
//                  Run once in 10ms         
//                  Return value::No
//=======================================================================================
 void Output_Process(void)
 {
     if (PowerUpFlag)     //刚上电
     {
         if (giPowerUpTime == 0)
         {
             Set_LEDOnFlag;
             Set_LED;
          //   Set_KeyBuzzerFlag;
					   gcPWMCount = 0;
         }
         
         giPowerUpTime++;
         if (giPowerUpTime >= 80)    //上电亮0.8ms
         {
             Clr_LED;
             giLEDPwmValue = 0;
             PWMUpDown_Flag = 1;
             Clr_PowerUpFlag;
             giPowerUpTime = 0; 
					 
					   gcPWMCount = 31999;
         }
				gcSleepTime = 0;
     }
     else
     {
				
			LED_Process(); 
			if(TestONFlag)     //测试模式下
			 {
		   switch(gcTestSendIRStatus)
				{
					case 0 :     //发送第一个信号
					{
//						if(gcTestDataACount < 1)
//						{
//							gcTestDataACount = 1;
							if(TestKeyDownFlag)      //如果有按键按下    (也要保证这一段只跑一次)
							{
									gllTestIRSendData1 = 0x0a;
									gllTestIRSendData1 = (gllTestIRSendData1 << 4) | 0x05;
									gllTestIRSendData2 = gcVar;
									gllTestIRSendData3 = ((gllTestIRSendData1 + gllTestIRSendData2 + 1) & 0xff) ;      //检验和
									gllTestIRSendData  = (gllTestIRSendData1 << 16) | (gllTestIRSendData2 << 8) | gllTestIRSendData3;     //要发送的数据
								
							}
							else
							{
									gllTestIRSendData1 = 0x0a;
									gllTestIRSendData1 = (gllTestIRSendData1 << 4) | 0x0a;
									gllTestIRSendData2 = gcVar;
									gllTestIRSendData3 = ((gllTestIRSendData1 + gllTestIRSendData2 + 1) & 0xff) ;      //检验和
									gllTestIRSendData  = (gllTestIRSendData1 << 16) | (gllTestIRSendData2 << 8) | gllTestIRSendData3;     //要发送的数据
								
							}
//						}
						
							if(SendTestAFlag)
								{								
									if((SendTestAEnFlag)&&(IRSendEnFlag==0))
									{
										
										gllIRSendData = gllTestIRSendData;
										gllIRSendDataBak = 	gllIRSendData;
										Set_IRSendEnFlag;               //使能信号发送										
										gcIRSendStatus = 0;								
										IRSendDataBitCount = 0;
										gcIRSendCount = 0;      //gcIRSendTestACount;          //数据发送的次数
										
									}
									else
									{
										gcIRSendTestATime++;
										if (gcIRSendTestATime >=50)
										{
											gcIRSendTestATime = 0;
											Set_SendTestAEnFlag;
										}
									}
						    }

						}				
					break;					
					case 1:     //发送第二个信号 
					{
//						if(gcTestDataBCount < 1)
//						{
//							gcTestDataBCount = 1;
							if(LEDONFlag)     //LED灯亮
							 {	
								 if(JP1Flag)    //接了跳帽
								 {
									 gcTemp = gcBurnerStatus | (1<<6) | (1<<7);        //LED使bit7  跳帽是bit6
								 }
								 else
								 {
									 gcTemp = gcBurnerStatus | (0<<6) | (1<<7);
								 }
							 }
							 else
							 {
								 if(JP1Flag)    //接了跳帽
								 {
									 gcTemp = gcBurnerStatus | (1<<6) | (0<<7);
								 }
								 else
								 {
									 gcTemp = gcBurnerStatus | (0<<6) | (0<<7);
								 }
							 }
		
							if(ExtIRFlag)
							{
								gllTestIRSendData1 = 0x0b;
								gllTestIRSendData1 = (gllTestIRSendData1 << 4) | 0x05;
							}
							else
							{
								gllTestIRSendData1 = 0x0b;
								gllTestIRSendData1 = (gllTestIRSendData1 << 4) | 0x0a;
							}
						
							gllTestIRSendData2 = gcTemp;          //第二个信号的第二个字节
							gllTestIRSendData3 = ((gllTestIRSendData1 + gllTestIRSendData2 + 1) & 0xff);      //检验和
							gllTestIRSendData  = (gllTestIRSendData1 << 16) | (gllTestIRSendData2 << 8) | gllTestIRSendData3;     //要发送的数据
							
							 if(SendTestBFlag)		
								{
									if((SendTestBEnFlag)&&(IRSendEnFlag==0))
									{										
										gllIRSendData = gllTestIRSendData;
										gllIRSendDataBak = 	gllIRSendData;										
										gcIRSendStatus = 0;
										gcIRSendDelayTime = 0;
										IRSendDataBitCount = 0;
										gcIRSendCount = 0;        //gcIRSendTestBCount;          //数据发送的次数
										Set_IRSendEnFlag;          //使能信号发送							
									}
									else
									{
										gcIRSendTestBTime++;
										if (gcIRSendTestBTime >=50)
										{
											gcIRSendTestBTime = 0;
											Set_SendTestBEnFlag;
										}
									}
								}					
						}
					break;
					case 2:     //发送第三个信号（ADC采样值） 
					{
						ADC_Process();
//						if(gcTestDataCCount < 1)
//						{
							gcTestDataCCount = 1;
							gcBatHigh4bit = ((giBatValue >> 8) & 0xf);     //取高4位
							gcBatLow8bit = (giBatValue & 0xff);    //取低8位
							gllTestIRSendData1 = (0x0c << 4) | gcBatHigh4bit;
							gllTestIRSendData2 = gcBatLow8bit;           //第二个信号的第二个字节
							gllTestIRSendData3 = ((gllTestIRSendData1 + gllTestIRSendData2 + 1) & 0xff);       //检验和
							gllTestIRSendData  = (gllTestIRSendData1 << 16) | (gllTestIRSendData2 << 8) | gllTestIRSendData3;     //要发送的数		
//						}
						if(SendTestCFlag)		
						{
							if((SendTestCEnFlag)&&(IRSendEnFlag==0))
							{						
								gllIRSendData = gllTestIRSendData;
								gllIRSendDataBak = 	gllIRSendData;										
								gcIRSendStatus = 0;
								gcIRSendDelayTime = 0;
								IRSendDataBitCount = 0;
								gcIRSendCount = 0;       //gcIRSendTestCCount;          //数据发送的次数
								Set_IRSendEnFlag;          //使能信号发送										
							}
							else
							{
								gcIRSendTestCTime++;
								if (gcIRSendTestCTime >=50)
								{
									gcIRSendTestCTime = 0;
									Set_SendTestCEnFlag;								
								}
							}
					}					         
			}
					break;
					default:
						break;				
				}	
			}
			else	             //用户模式下
			{
        if(SendSpeedOffCommandFlag)
        {
					if((SendSpeedOffEnFlag)&&(IRSendEnFlag==0))
					{
						Set_FirstSendSpeedOffCommandFlag;
						gllIRSendData = 0x5B9B1B; //  
						gllIRSendDataBak = gllIRSendData;

						gcIRSendStatus = 0;
						gcIRSendDelayTime = 0;
						IRSendDataBitCount = 0;
						gcIRSendCount = gcIRSendSpeedOffCount;
						Set_IRSendEnFlag;
					}
					else 
					{
						gcIRSendSpeedOffTime++;
						if (gcIRSendSpeedOffTime >= 100)
						{
							gcIRSendSpeedOffTime = 0;
							Set_SendSpeedOffEnFlag;
						}
						
					}
        }
				else
				{
					gcIRSendSpeedOffTime = SPEEDOFFTIME;
					gcIRSendSpeedOffCount = 0;
				}
				
        if(SendLightOnCommandFlag)
        {
						if ((SendLightOnEnFlag)&&(IRSendEnFlag==0)) 
							{ 
								Set_FirSendLightOnCommandFlag;
								gllIRSendData =0x2BCB4B;   // 0x2D2C2B; // 210-211-212
								gllIRSendDataBak = gllIRSendData;

								gcIRSendStatus = 0;
								gcIRSendDelayTime = 0;
								IRSendDataBitCount = 0;
								gcIRSendCount = gcIRSendLightOnCount;
								Set_IRSendEnFlag;
  
							}
					else
						{
							gcIRSendLightOnTime++;
							if (gcIRSendLightOnTime >=100)
							{
								gcIRSendLightOnTime = 0;
								Set_SendLightOnEnFlag;
							}
						}
        }
				else
				{
					gcIRSendLightOnTime = LIGHTONTIME;			   //为了使其首次进入时立即发送.	
					gcIRSendLightOnCount = 0;
				}
				
        if(SendLightOffCommandFlag)
        {
            if((SendLightOffEnFlag)&&(IRSendEnFlag==0)) 
            {
                Set_FirSendLightOffCommandFlag;
                gllIRSendData = 0xEB6BAB; // 
                gllIRSendDataBak = gllIRSendData;

                gcIRSendStatus = 0;
                gcIRSendDelayTime = 0;
                IRSendDataBitCount = 0;
                gcIRSendCount = gcIRSendLightOffCount; 
                Set_IRSendEnFlag;
            }
						else
						{
							gcIRSendLightOffTime++;
							if (gcIRSendLightOffTime >= 100)
							{
								gcIRSendLightOffTime = 0;
								Set_SendLightOffEnFlag;
							}
						}
        }
				else
				{
					gcIRSendLightOffTime = LIGHTOFFTIME;
					gcIRSendLightOffCount = 0;
				}
				
       if (SendSpeedCommandFlag)
        {
					if ((SendSpeedCommandEnFlag)&&(IRSendEnFlag==0))
					{
                Set_FirstSendSpeedCommandFlag;
                switch(gcSpeedLevel)
                {
                    case 1:
                    {
                         gllIRSendData = 0x76B636; //  
                    }
                    break;
                    case 2:
                    {
                         gllIRSendData = 0x8E0EF6; //  
                    }
                    break;
                    case 3:
                    {
                         gllIRSendData = 0xC74787; //  
                    }
                    break;
                    case 4:
                    {
                         gllIRSendData = 0x2ECE4E; //
                    }
                    break;
                    default:
                        break;
                }
               
                gllIRSendDataBak = gllIRSendData;

                gcIRSendStatus = 0;
                gcIRSendDelayTime = 0;
                IRSendDataBitCount = 0;
                gcIRSendCount = gcIRSendSpeedCommandCount;     
                Set_IRSendEnFlag;
					}
					else
					{
							gcIRSendSpeedCommandTime++;
							if (gcIRSendSpeedCommandTime >= 100)
							{
								gcIRSendSpeedCommandTime = 0;
								Set_SendSpeedCommandEnFlag;
							}
					}
        }
				else
				{
					gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;
					gcIRSendSpeedCommandCount = 0;					
				}
			}
				if (gcSleepDelayTime < 100)
				{
					gcSleepDelayTime++;
					
				}
		 
				if ((SendLightOnCommandFlag == 0) &&(SendLightOffCommandFlag == 0) &&(SendSpeedOffCommandFlag == 0) &&(SendSpeedCommandFlag == 0)&&(gcSleepDelayTime == 100)&&(BatLowWarrnFlag == 0)&&(AllHodCloseFlag == 0)&&(TestONFlag == 0))
				{			
					gcSleepDelayTime = 101;
					Set_AllDataSendEndFlag;       //所有命令发送完成之后，允许睡眠
					Set_SleepEnFlag;
				}  
				
     }// end else

 }
