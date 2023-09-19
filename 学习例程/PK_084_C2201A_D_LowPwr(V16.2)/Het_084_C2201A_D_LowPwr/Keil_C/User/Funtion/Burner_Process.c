#include "SC_System.h"
#include "Burner_Process.h"

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
extern uint8_t gcSpeedLevel;
extern uint8_t gcBuzzerTime; 
extern uint8_t gcIRSendLightOnCount;
extern uint8_t gcIRSendLightOnTime;

extern uint8_t gcIRSendLightOffCount ;				//灯开发送计数
extern uint8_t gcIRSendLightOffTime ;

extern uint8_t gcIRSendSpeedOffCount;				 
extern uint8_t gcIRSendSpeedOffTime;

extern uint8_t gcIRSendSpeedCommandCount ;	 
extern uint8_t gcIRSendSpeedCommandTime ;

extern uint8_t gcSleepDelayTime;
extern uint16_t giT500msCount;

uint8_t gcBurnerCheckStatus = 0;
uint8_t gcBurnerCheckCount = 0;
uint8_t gcBurnerStatusBak = 0;

void BurnerOpenNumber_Check(void)
{
    uint8_t i = 0;
    uint8_t lcBurnerStatus = 0;
    
    lcBurnerStatus = gcBurnerStatus;
    gcBurnerOpenCount = 0;
    
    for (i=0;i<6;i++)
    {
       if (lcBurnerStatus & 0x01) 
       {
          gcBurnerOpenCount++;  
       }
       lcBurnerStatus = (lcBurnerStatus >> 1);
    }
          
}
//=======================================================================================
//                  void Burner_Process(void)
//                  Run once in 10ms         
//                  Return value::No
//=======================================================================================
 void Burner_Process(void)
 {	  
     if (SW1_Get() == BURNER_STATUS_ON)        //Burnur 1
     {
			   Clr_FirstBurner1CloseFlag;
			   if(FirstBurner1OpenFlag  == 0)
				 {
					 Set_FirstBurner1OpenFlag;
					 gcSleepDelayTime = 0;
				 }	
				 
         gcBurner1CloseCount = 0;
         if (gcBurner1OpenCount < BURNER_TIME)
         {
              gcBurner1OpenCount++;
         }
         if (gcBurner1OpenCount == BURNER_TIME )
         {
             gcBurner1OpenCount = BURNER_TIME +1;
             gcBurnerStatus |= BURNER_1_STATUS;
					   
         }
     }
     else
     {
			   Clr_FirstBurner1OpenFlag;
			   if(FirstBurner1CloseFlag == 0)
			   {
					 Set_FirstBurner1CloseFlag;
					 gcSleepDelayTime = 0;
				 }
			 
         gcBurner1OpenCount = 0;
         if (gcBurner1CloseCount < BURNER_TIME)
         {
              gcBurner1CloseCount++;
         }
         if (gcBurner1CloseCount == BURNER_TIME )
         {
             gcBurner1CloseCount = BURNER_TIME +1;
             gcBurnerStatus &= (0xff - BURNER_1_STATUS);
					   
         }
     }
     
  if (SW2_Get() == BURNER_STATUS_ON)        //Burnur 2
     {
			   Clr_FirstBurner2CloseFlag;
			   if(FirstBurner2OpenFlag == 0)
				 {
					 Set_FirstBurner2OpenFlag;
					 gcSleepDelayTime = 0;
				 }	
				 
         gcBurner2CloseCount = 0;
         if (gcBurner2OpenCount < BURNER_TIME)
         {
              gcBurner2OpenCount++;
         }
         if (gcBurner2OpenCount == BURNER_TIME )
         {
             gcBurner2OpenCount = BURNER_TIME +1;
             gcBurnerStatus |= BURNER_2_STATUS;
					   
         }
     }
     else
     {
			   Clr_FirstBurner2OpenFlag;
			   if(FirstBurner2CloseFlag == 0)
			   {
					 Set_FirstBurner2CloseFlag;
					 gcSleepDelayTime = 0;
				 }
				 
         gcBurner2OpenCount = 0;
         if (gcBurner2CloseCount < BURNER_TIME)
         {
              gcBurner2CloseCount++;
         }
         if (gcBurner2CloseCount == BURNER_TIME )
         {
             gcBurner2CloseCount = BURNER_TIME +1;
             gcBurnerStatus &= (0xff - BURNER_2_STATUS);
					   
         }
     }
     
  if (SW3_Get() == BURNER_STATUS_ON)        //Burnur 3
     {
			   Clr_FirstBurner3CloseFlag;
			   if(FirstBurner3OpenFlag == 0)
				 {
					 Set_FirstBurner3OpenFlag;
					 gcSleepDelayTime = 0;
				 }	
				 
         gcBurner3CloseCount = 0;
         if (gcBurner3OpenCount < BURNER_TIME)
         {
              gcBurner3OpenCount++;
         }
         if (gcBurner3OpenCount == BURNER_TIME )
         {
             gcBurner3OpenCount = BURNER_TIME +1;
             gcBurnerStatus |= BURNER_3_STATUS;
					   
         }
     }
     else
     {
			   Clr_FirstBurner3OpenFlag;
			   if(FirstBurner3CloseFlag == 0)
			   {
					 Set_FirstBurner3CloseFlag;
					 gcSleepDelayTime = 0;
				 }
				 
         gcBurner3OpenCount = 0;
         if (gcBurner3CloseCount < BURNER_TIME)
         {
              gcBurner3CloseCount++;
         }
         if (gcBurner3CloseCount == BURNER_TIME )
         {
             gcBurner3CloseCount = BURNER_TIME +1;
             gcBurnerStatus &= (0xff - BURNER_3_STATUS);
					   
         }
     }
     
  if (SW4_Get() == BURNER_STATUS_ON)        //Burnur 4
     {
			   Clr_FirstBurner4CloseFlag;
			   if(FirstBurner4OpenFlag == 0)
				 {
					 Set_FirstBurner4OpenFlag;
					 gcSleepDelayTime = 0;
				 }
				 
         gcBurner4CloseCount = 0;
         if (gcBurner4OpenCount < BURNER_TIME)
         {
              gcBurner4OpenCount++;
         }
         if (gcBurner4OpenCount == BURNER_TIME )
         {
             gcBurner4OpenCount = BURNER_TIME +1;
             gcBurnerStatus |= BURNER_4_STATUS;
					   
         }
     }
     else
     {
			   Clr_FirstBurner4OpenFlag;
			   if(FirstBurner4CloseFlag == 0)
			   {
					 Set_FirstBurner4CloseFlag;
					 gcSleepDelayTime = 0;
				 }
         gcBurner4OpenCount = 0;
         if (gcBurner4CloseCount < BURNER_TIME)
         {
              gcBurner4CloseCount++;
         }
         if (gcBurner4CloseCount == BURNER_TIME )
         {
             gcBurner4CloseCount = BURNER_TIME +1;
             gcBurnerStatus &= (0xff - BURNER_4_STATUS);
					   
         }
     } 
   
  if (SW5_Get() == BURNER_STATUS_ON)        //Burnur 5
     {
			   Clr_FirstBurner5CloseFlag;
			   if(FirstBurner5OpenFlag  == 0)
				 {
					 Set_FirstBurner5OpenFlag;
					 gcSleepDelayTime = 0;
				 }	
				 
         gcBurner5CloseCount = 0;
         if (gcBurner5OpenCount < BURNER_TIME)
         {
              gcBurner5OpenCount++;
         }
         if (gcBurner5OpenCount == BURNER_TIME )
         {
             gcBurner5OpenCount = BURNER_TIME +1;
             gcBurnerStatus |= BURNER_5_STATUS;
					   
         }
     }
     else
     {
			   Clr_FirstBurner5OpenFlag;
			   if(FirstBurner5CloseFlag == 0)
			   {
					 Set_FirstBurner5CloseFlag;
					 gcSleepDelayTime = 0;
				 }
         gcBurner5OpenCount = 0;
         if (gcBurner5CloseCount < BURNER_TIME)
         {
              gcBurner5CloseCount++;
         }
         if (gcBurner5CloseCount == BURNER_TIME )
         {
             gcBurner5CloseCount = BURNER_TIME +1;
             gcBurnerStatus &= (0xff - BURNER_5_STATUS);
					   
         }
     } 
     
  if (SW6_Get() == BURNER_STATUS_ON)        //Burnur 6
     {
			   Clr_FirstBurner6CloseFlag;
			   if(FirstBurner6OpenFlag == 0)
				 {
					 Set_FirstBurner6OpenFlag;
					 gcSleepDelayTime = 0;
				 }	
				 
         gcBurner6CloseCount = 0;
         if (gcBurner6OpenCount < BURNER_TIME)
         {
              gcBurner6OpenCount++;
         }
         if (gcBurner6OpenCount == BURNER_TIME )
         {
             gcBurner6OpenCount = BURNER_TIME +1;
             gcBurnerStatus |= BURNER_6_STATUS;
					   
         }
     }
     else
     {
			   Clr_FirstBurner6OpenFlag;
			   if(FirstBurner6CloseFlag == 0)
			   {
					 Set_FirstBurner6CloseFlag;
					 gcSleepDelayTime = 0;
				 }
				 
         gcBurner6OpenCount = 0;
         if (gcBurner6CloseCount < BURNER_TIME)
         {
              gcBurner6CloseCount++;
         }
         if (gcBurner6CloseCount == BURNER_TIME )
         {
             gcBurner6CloseCount = BURNER_TIME +1;
             gcBurnerStatus &= (0xff - BURNER_6_STATUS);
					   
         }
     }  
     
     BurnerOpenNumber_Check();        // Burners open number detection
 
		/**/
	if(TestONFlag == 0)
	{
     switch(gcBurnerCheckStatus)
     {
         case 0:     
         {
             if (gcBurnerStatus != 0)          //有炉头开启
             {
                 gcBurnerCheckCount++;
							 if (gcBurnerCheckCount >= 12)
                 {
                     gcBurnerCheckCount = 0;
									 
                     if (gcBurnerStatus != gcBurnerStatusBak)    
                     {											 
                        gcBurnerStatusBak = gcBurnerStatus;
											 
											 
                        /* 在炉头开启之后，这3个状态就被清掉了，后续再发送一些信号时，用来判断炉头是否由开启转为了关闭的变化状态 */                 
												Clr_FirstLightOffFlag; 
                        Clr_FirstSpeedOffFlag;
                        Clr_FirstPowerUpFlag;
  
                        if (ActivateModeFlag)       
                        {		
													  /*炉头开启时，发送风速信号*/													
                            if (AutoModeFlag)
                            {
																if(gcSpeedLevel == 4)
																{
																	Clr_IRSendEnFlag;
																	Set_SendSpeedOffCommandFlag;
																	gcSpeedLevel = 0;   
																	gcIRSendSpeedOffTime = 100;     //立即发送
																	Set_SendSpeedOffEnFlag;																			
//																	gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;
																	Set_AutoFanFlag;
																}
																else
																{	
																	/*这里的目的是，防止刚闭合炉头时交错发送风扇的信号*/
                                  if((ToBurnerOpen_Flag == 0)&&(FirstLightOnFlag))
																	{																		
																		Clr_IRSendEnFlag;                                
																		Clr_INTENSIVEONModeFlag;          //清除密集模式 																																
																		Set_SendSpeedCommandFlag;
																		//Clr_FirstSendSpeedCommandFlag;
																		gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;      //75																  															
																		Clr_FirstSendSpeedOffCommandFlag; 
																	}
																	Clr_LightOffDelayStartFlag;
																	Clr_SpeedDelayOffStartFlag;														
																	
																	if(ModeChangeFlag)         //变到activate模式下时，自动切换风速
																	{
																		Clr_ModeChangeFlag;
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
																	else                    //在自动模式下，如果是2档风速，就保持2档
																	{
																		if(gcSpeedLevel < 2)
																		{
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
																		}
																	}
														     }
															 
															}
													
													/*按客户要求，在手动关闭灯之后，关闭所有阀头，在打开一个阀头，烟机上的灯会亮起  7.1 （这个是一上电之后，就要发开灯信号）*/	
												  if ((FirstLightOnFlag == 0)&&(LightOffDelayStartFlag == 0))
													{
															Clr_IRSendEnFlag;
														  //Clr_SendLightOffEnFlag;
														  //Clr_SendSpeedOffEnFlag;
														  //Clr_LightOffDelay250ms_Flag;              //如果为了防止炉头断开闭合操作太快干扰到开灯信号的操作（23.1.5）
														  Set_ToBurnerOpen_Flag;                    //设置有炉头闭合标志，准备发射后续开风扇的信号（开始计时）
															Set_FirstLightOnFlag;
															Set_SendLightOnCommandFlag;                //炉头闭合时，自动开灯
															Clr_FirSendLightOnCommandFlag;
															gcIRSendLightOnTime = LIGHTONTIME;	   	 	 //为了使其首次进入时立即发送.	
													}	
														
                        }
                        else        // deactivate mode 
                        {
                            if (gcSpeedLevel == 0)
                            {
                                if (AllSwitchOFFFlag)
                                {
                                    Clr_AllSwitchOFFFlag;
                                    Set_DeactivateModeFirstLightFlag;
                                }
                            }
                        }
                     }
							  }
             }
             else               // all off change to status 1
             {
                 gcBurnerCheckStatus = 1;
             }
         }
         break;
         case 1:                  //所有的炉头断开
         {
              if ((gcBurnerStatus == 0)&&(FirstPowerUpFlag == 0))      // 不是第一次上电，且没有炉头开启
              {
								  Set_BatLowWarrnEnFlag;             //低电压检测使能									
                  gcBurnerCheckCount++;
                  if (gcBurnerCheckCount >= 12)         //12
                  {
                    gcBurnerCheckCount = 0; 
                    
                    if (gcBurnerStatus != gcBurnerStatusBak)      //表示有操作过炉头
                    {                    
											  if(BatLowWarrnFlag == 0)           //没有发生低电压报警
												{	
													if(ActivateModeFlag)
															Set_AllHodCloseFlag;            //发出所有炉头关闭的声音
												}
												else
												{
													
													 Clr_BatLowWarrnFlag;
													 Delay(500);        //延时500ms
													 if(ActivateModeFlag)
															Set_AllHodCloseFlag;            //发出所有炉头关闭的声音（在Active模式下才有这个声音 11.4）												 
												}
												
                        Set_AllSwitchOFFFlag;
                        if (ActivateModeFlag) 
                        {
														if (AutoModeFlag)         //如果在自动模式下，灯闪5分钟，之后发送关风扇的指令
                                {
																	//
																	Clr_FirstLightOnFlag;
																	
																	/*这里的两个Flag是在有炉头开启时清掉的，在这里开启计时5min*/
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

																	Clr_IRSendEnFlag;
																	Set_SendSpeedCommandFlag;
																	gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;
																	Clr_FirstSendSpeedCommandFlag;
																	gcSpeedLevel = 1;                            
                                }
                            else
                                {
                                    Set_AutoModeFlag;
																	  Clr_FirstLightOnFlag;
                                    if (gcSpeedLevel == 0)
                                    {
                                        Set_AutoModeFlag;
                                        Clr_IRSendEnFlag;
																					 
																				gcIRSendLightOffTime = LIGHTOFFTIME;
																				Set_SendLightOffCommandFlag; 
																					 
                                    }
                                    else       //
                                    {
                                        if (gcSpeedLevel!=4)
                                        {
                                            Clr_IRSendEnFlag;
                                            Set_SendSpeedCommandFlag;
																				    gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;
                                            Clr_FirstSendSpeedCommandFlag;
                                            gcSpeedLevel = 1;      
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
                                        else   // 4档
                                        {
                                            Clr_IRSendEnFlag;
                                            Set_SendSpeedOffCommandFlag;
                                            Clr_FirstSendSpeedOffCommandFlag;
                                            gcSpeedLevel = 0;   
                                            Set_INTENSIVEONModeFlag;
																				  	gcIRSendSpeedOffTime = 100;
																																										
                                        } 
                                    }
                                }
                        }    //end  if (ActivateModeFlag)																						
                       
                    }
                    
                    gcBurnerStatusBak = 0;

                  }
									
              }
              else
              {
                  gcBurnerCheckStatus = 0;
								 
              }
         }
         break;
     }
	 }
 }
 
 
 /*延时函数*/
void Delay (uint16_t giDelay_Times)
 {
	 while (giDelay_Times--)
	 {
		 Delay1ms();
	 }
 }	
