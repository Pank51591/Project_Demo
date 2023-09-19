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

extern uint8_t gcIRSendLightOffCount ;				//�ƿ����ͼ���
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
             if (gcBurnerStatus != 0)          //��¯ͷ����
             {
                 gcBurnerCheckCount++;
							 if (gcBurnerCheckCount >= 12)
                 {
                     gcBurnerCheckCount = 0;
									 
                     if (gcBurnerStatus != gcBurnerStatusBak)    
                     {											 
                        gcBurnerStatusBak = gcBurnerStatus;
											 
											 
                        /* ��¯ͷ����֮����3��״̬�ͱ�����ˣ������ٷ���һЩ�ź�ʱ�������ж�¯ͷ�Ƿ��ɿ���תΪ�˹رյı仯״̬ */                 
												Clr_FirstLightOffFlag; 
                        Clr_FirstSpeedOffFlag;
                        Clr_FirstPowerUpFlag;
  
                        if (ActivateModeFlag)       
                        {		
													  /*¯ͷ����ʱ�����ͷ����ź�*/													
                            if (AutoModeFlag)
                            {
																if(gcSpeedLevel == 4)
																{
																	Clr_IRSendEnFlag;
																	Set_SendSpeedOffCommandFlag;
																	gcSpeedLevel = 0;   
																	gcIRSendSpeedOffTime = 100;     //��������
																	Set_SendSpeedOffEnFlag;																			
//																	gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;
																	Set_AutoFanFlag;
																}
																else
																{	
																	/*�����Ŀ���ǣ���ֹ�ձպ�¯ͷʱ�����ͷ��ȵ��ź�*/
                                  if((ToBurnerOpen_Flag == 0)&&(FirstLightOnFlag))
																	{																		
																		Clr_IRSendEnFlag;                                
																		Clr_INTENSIVEONModeFlag;          //����ܼ�ģʽ 																																
																		Set_SendSpeedCommandFlag;
																		//Clr_FirstSendSpeedCommandFlag;
																		gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;      //75																  															
																		Clr_FirstSendSpeedOffCommandFlag; 
																	}
																	Clr_LightOffDelayStartFlag;
																	Clr_SpeedDelayOffStartFlag;														
																	
																	if(ModeChangeFlag)         //�䵽activateģʽ��ʱ���Զ��л�����
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
																	else                    //���Զ�ģʽ�£������2�����٣��ͱ���2��
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
													
													/*���ͻ�Ҫ�����ֶ��رյ�֮�󣬹ر����з�ͷ���ڴ�һ����ͷ���̻��ϵĵƻ�����  7.1 �������һ�ϵ�֮�󣬾�Ҫ�������źţ�*/	
												  if ((FirstLightOnFlag == 0)&&(LightOffDelayStartFlag == 0))
													{
															Clr_IRSendEnFlag;
														  //Clr_SendLightOffEnFlag;
														  //Clr_SendSpeedOffEnFlag;
														  //Clr_LightOffDelay250ms_Flag;              //���Ϊ�˷�ֹ¯ͷ�Ͽ��պϲ���̫����ŵ������źŵĲ�����23.1.5��
														  Set_ToBurnerOpen_Flag;                    //������¯ͷ�պϱ�־��׼��������������ȵ��źţ���ʼ��ʱ��
															Set_FirstLightOnFlag;
															Set_SendLightOnCommandFlag;                //¯ͷ�պ�ʱ���Զ�����
															Clr_FirSendLightOnCommandFlag;
															gcIRSendLightOnTime = LIGHTONTIME;	   	 	 //Ϊ��ʹ���״ν���ʱ��������.	
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
         case 1:                  //���е�¯ͷ�Ͽ�
         {
              if ((gcBurnerStatus == 0)&&(FirstPowerUpFlag == 0))      // ���ǵ�һ���ϵ磬��û��¯ͷ����
              {
								  Set_BatLowWarrnEnFlag;             //�͵�ѹ���ʹ��									
                  gcBurnerCheckCount++;
                  if (gcBurnerCheckCount >= 12)         //12
                  {
                    gcBurnerCheckCount = 0; 
                    
                    if (gcBurnerStatus != gcBurnerStatusBak)      //��ʾ�в�����¯ͷ
                    {                    
											  if(BatLowWarrnFlag == 0)           //û�з����͵�ѹ����
												{	
													if(ActivateModeFlag)
															Set_AllHodCloseFlag;            //��������¯ͷ�رյ�����
												}
												else
												{
													
													 Clr_BatLowWarrnFlag;
													 Delay(500);        //��ʱ500ms
													 if(ActivateModeFlag)
															Set_AllHodCloseFlag;            //��������¯ͷ�رյ���������Activeģʽ�²���������� 11.4��												 
												}
												
                        Set_AllSwitchOFFFlag;
                        if (ActivateModeFlag) 
                        {
														if (AutoModeFlag)         //������Զ�ģʽ�£�����5���ӣ�֮���͹ط��ȵ�ָ��
                                {
																	//
																	Clr_FirstLightOnFlag;
																	
																	/*���������Flag������¯ͷ����ʱ����ģ������￪����ʱ5min*/
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
                                        else   // 4��
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
 
 
 /*��ʱ����*/
void Delay (uint16_t giDelay_Times)
 {
	 while (giDelay_Times--)
	 {
		 Delay1ms();
	 }
 }	
