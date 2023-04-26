#include "SC_System.h"


extern void Buzzer_Process(void);

void IR_StartSend_36KHZ(void);
void IR_StopSend_36KHZ(void);

extern uint8_t gcOneMsCount;
extern uint8_t  gcIRSendStatus;
extern uint8_t IRSendDataBitCount; // 24bit
extern uint32_t gllIRSendData;    // IR Send Data
extern uint32_t gllIRSendDataBak; // IR Send Data
extern uint16_t gcIRSendDelayTime; // 1S
extern uint8_t gcIRSendCount;      // 3
extern uint8_t gcSpeedLevel;
extern volatile uint8_t gcADCDelayTime;
extern uint8_t gcIRSendLightOnCount;
extern uint8_t gcIRSendLightOnTime ;
extern uint8_t gcIRSendLightOffCount ;				//灯开发送计数
extern uint8_t gcIRSendLightOffTime ;
extern uint8_t gcIRSendSpeedOffCount;				 
extern uint8_t gcIRSendSpeedOffTime;
extern uint8_t gcIRSendSpeedCommandCount ;	 
extern uint8_t gcIRSendSpeedCommandTime ;
extern uint8_t gcT250MsCount;

extern bit  BTM_WakeUpFlag ;	//BTM唤醒标志位
extern uint8_t gcBurnerStatus;
extern uint8_t gcBurnerOpenCount;

extern uint8_t gcIRSendTestACount;
extern uint8_t gcIRSendTestBCount;
extern uint8_t gcIRSendTestCCount;
extern uint8_t gcTestSendIRStatus;

extern uint8_t gcIRSendTestATime;
extern uint8_t gcIRSendTestBTime;
extern uint8_t gcIRSendTestCTime;

extern uint8_t gcWaitKeyTime;

//uint8_t gc250msCount = 0;

void TC1_Timer16bitPeriodSet(uint16_t Count)
{
	TIM0_Mode1SetReloadCounter(Count);
}

void INT0Interrupt()		interrupt 0				
{
    TCON &= 0XFD;
//	BTM_WakeUpFlag = 1;
}
void INT1Interrupt()		interrupt 2		
{
    TCON &= 0XF7;    //Clear interrupt flag bit				
//	BTM_WakeUpFlag = 1;
}


void INT2Interrupt()		interrupt 10
{	
	
//	BTM_WakeUpFlag = 1;
}

/*定时器0中断*/
void Timer0Interrupt()		interrupt 1		    //中断号：1	   
{
	  // P31 = ~P31;	
    if (IRSendEnFlag)
    {
        switch (gcIRSendStatus)
        {
            case 0:     // Start Conditon 1088us
            {
                IR_StartSend_36KHZ();
                if (gcIRSendCount !=1 )
                {
                     TC1_Timer16bitPeriodSet(Time_705us);    // 1 and 3   Faber 
                }
                else
                {
                     TC1_Timer16bitPeriodSet(Time_738us);  //2 Elica
                }
                gcIRSendStatus = 1;
                IRSendDataBitCount = 0;
            }
            break;
            case 1:         // Send Data 
            {
                if (gllIRSendData&0x0001)      //1
                {
                    IR_StopSend_36KHZ();
                    if (gcIRSendCount !=1 )
                    {
                        TC1_Timer16bitPeriodSet(Time_705us);  // 1 and 3  Faber 
                    }
                    else
                    {
                        TC1_Timer16bitPeriodSet(Time_738us);
                    }
                    
                }
                else                        // 0
                {
                   IR_StartSend_36KHZ();
                   if (gcIRSendCount !=1 )
                   {
                       TC1_Timer16bitPeriodSet(Time_738us); 
                   }
                   else
                   {
                       TC1_Timer16bitPeriodSet(Time_705us); 
                   }
                   
                }
                gllIRSendData = (gllIRSendData>>1);
                IRSendDataBitCount++;
                if (IRSendDataBitCount > 24)
                {
                    IRSendDataBitCount = 0;
                    gllIRSendData = gllIRSendDataBak;
                    gcIRSendStatus = 0;
                    IR_StopSend_36KHZ();             // stop PWM 36KHZ
                    TC1_Timer16bitPeriodSet(Time_5ms);  // 50ms
                    gcIRSendDelayTime = 0;
                    Clr_IRSendEnFlag;    // Send End
									 
									  if (SendLightOnEnFlag)
										{
											gcIRSendLightOnTime = 0;
											Clr_SendLightOnEnFlag;
											gcIRSendLightOnCount++;
											if (gcIRSendLightOnCount >= 3)
											{
												gcIRSendLightOnCount = 0;
												Clr_SendLightOnCommandFlag;
												if(ToBurnerOpen_Flag)
												{
													Set_LightOnDelay250ms_Flag;     //开始计时250ms
										    }
											}
										}
									   
									  if (SendLightOffEnFlag)
										{
											gcIRSendLightOffTime = 0;
											Clr_SendLightOffEnFlag;
											gcIRSendLightOffCount++;
											if (gcIRSendLightOffCount >= 3)
											{
												gcIRSendLightOffCount = 0;									
												Clr_SendLightOffCommandFlag;
												Set_LightOffDelay250ms_Flag;        //开始计时250ms
												
											}
										}			

										/**/
									  if (SendSpeedOffEnFlag)
										{
											gcIRSendSpeedOffTime = 0;
											Clr_SendSpeedOffEnFlag;
											gcIRSendSpeedOffCount++;
											if (gcIRSendSpeedOffCount >= 3)       //发送关风扇的指令3次
											{
												gcIRSendSpeedOffCount = 0;
												Clr_SendSpeedOffCommandFlag;
												
												/**/
												if(AutoFanFlag)       //AutoFan
												{
													  Clr_AutoFanFlag;
														Clr_IRSendEnFlag;                                
//													Clr_INTENSIVEONModeFlag;        //清除密集模式                               
														Set_SendSpeedCommandFlag;
//                          Clr_FirstSendSpeedCommandFlag;
														gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;      //
													
														Clr_FirstSendSpeedOffCommandFlag; 

														Clr_LightOffDelayStartFlag;
														Clr_SpeedDelayOffStartFlag;
														
														if ((gcBurnerStatus&0x01) ||(gcBurnerStatus&0x02) )   // work burner 
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
													 
												}
												
												if(INTENSIVEONModeFlag)
												{
															Clr_INTENSIVEONModeFlag;
															Set_SendSpeedCommandFlag;
															Clr_FirstSendSpeedCommandFlag;
															gcSpeedLevel = 1;   
															gcIRSendSpeedCommandTime = 100;
															if (FirstLightOffFlag == 0)
															{
																	Set_FirstLightOffFlag;
																	Set_LightOffDelayStartFlag;
															}
														 if (FirstSpeedOffFlag == 0)
														 {
																 Set_FirstSpeedOffFlag;
																 Set_SpeedDelayOffStartFlag;
														 }
												}												
											}
										}	
										
									  if (SendSpeedCommandEnFlag)
										{
											gcIRSendSpeedCommandTime = 0;
											Clr_SendSpeedCommandEnFlag;
											gcIRSendSpeedCommandCount++;
											if (gcIRSendSpeedCommandCount >= 3)
											{
												gcIRSendSpeedCommandCount = 0;
												Clr_SendSpeedCommandFlag;
											}
										}	
										
                   if(SendTestAEnFlag)         //测试自检A
										{
											gcIRSendTestATime = 0; 
											Clr_SendTestAEnFlag;						
											Clr_IRSendEnFlag;          //
////											gcIRSendTestACount++;
////											if(gcIRSendTestACount >= 3)      //发送3次，发完就不用再发了
////											{
////												gcIRSendTestACount = 0;
												Clr_SendTestAFlag;        //清按键按下标志
//												Clr_TestKeyDownFlag;          //发送完3次，清测试按键按下的标志
                        Clr_IRSendEnFlag; 												
												gcTestSendIRStatus = 1; 
												
////											}										
										}
										
										if(SendTestBEnFlag)         //测试自检B
										{
											gcIRSendTestBTime = 0;
											Clr_SendTestBEnFlag;
											Clr_IRSendEnFlag;
////											gcIRSendTestBCount++;
////											if(gcIRSendTestBCount >= 3)      //发送3次，发完就不用再发了
////											{
												gcIRSendTestBCount = 0;
												Clr_SendTestBFlag;
												Clr_IRSendEnFlag; 
												gcTestSendIRStatus = 2; 
////											}
											
										}
										
										if(SendTestCEnFlag)         //测试自检C
										{
											gcIRSendTestCTime = 0;
											Clr_SendTestCEnFlag;
											Clr_IRSendEnFlag;
////											gcIRSendTestCCount++;
////											if(gcIRSendTestCCount >= 3)        //发送3次，发完就不用再发了
////											{
////												gcIRSendTestCCount = 0;
//												gcWaitKeyTime = 0;
												Clr_IRSendEnFlag;
												Clr_SendTestCFlag;
//												Clr_WaitKeyTimeFlag;
//												Set_TestIROverFlag;
												gcTestSendIRStatus = 0;
												
												Set_SendTestAFlag;
												Set_SendTestBFlag;
												Set_SendTestCFlag;
												Clr_IRSendEnFlag;
//												Clr_TestONFlag;              //退出自检模式,此时可以准备测试睡眠电流
////											}										
										}								
                										
                }
            }
            break;
            case 2:         // 3???  这里是进不来的
            {
							 TC1_Timer16bitPeriodSet(Time_5ms);  // 50ms
                gcIRSendDelayTime++;
                if (gcIRSendDelayTime >= 199 ) // (199+1)*5ms = 1S
                {
                    gcIRSendStatus = 0;         //reSendIR
                                    
                }
            }
            break;
        }
    }
    else
    {
        IR_StopSend_36KHZ();             // stop PWM 36KHZ
        gcIRSendStatus = 0;
        gcIRSendDelayTime = 0;
        IRSendDataBitCount = 0;      
    }
}


/* 定时器中断 1ms一次 */
void Timer1Interrupt()		interrupt 3		
{
		
    TIM1_Mode1SetReloadCounter(Time_1ms);    //重载值
    gcOneMsCount++;
		gcT250MsCount++;
		Buzzer_Process();
	
							
}

void IR_StartSend_36KHZ(void)
{
    if (ExtIRFlag == 0)
    {

        Set_InsideIR_Send;
    }
    else
    {
        Set_ExternalIR_Send;
    }
}

void IR_StopSend_36KHZ(void)
{
    if (ExtIRFlag == 0)
    {
        Clr_InsideIR_Send;
    }
    else
    {
        Clr_ExternalIR_Send;
    }
}

 
