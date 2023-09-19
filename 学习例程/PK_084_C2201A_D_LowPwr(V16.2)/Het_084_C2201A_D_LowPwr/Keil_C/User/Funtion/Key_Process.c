#include "SC_System.h"
#include "Key_Process.h"
#include "Buzzer_Process.h"
#include "Time_Process.h"

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

extern uint8_t  gcPowerUpTime;
extern uint16_t giLEDPwmValue;
extern uint16_t giLEDFlashTime;
extern uint8_t gcLEDFlashCount;
extern uint8_t gcSpeedLevel;

extern uint32_t gllIRSendData;                   //IR Send Data
extern uint32_t gllIRSendDataBak;                //IR Send Data

extern uint8_t gcPWMCly;
extern uint8_t  gcPWMWaitTime;
extern uint16_t gcPWMCount;
extern uint8_t gcLEDFlashCount;
extern uint16_t giLEDFlashTime;

extern uint8_t gcIRSendLightOnCount;
extern uint8_t gcIRSendLightOnTime;

extern uint8_t gcIRSendLightOffCount ;				//�ƿ����ͼ���
extern uint8_t gcIRSendLightOffTime ;

extern uint8_t gcIRSendSpeedOffCount;				 
extern uint8_t gcIRSendSpeedOffTime;

extern uint8_t gcIRSendSpeedCommandCount ;	 
extern uint8_t gcIRSendSpeedCommandTime ;

extern uint8_t gcSleepDelayTime;

extern uint8_t gcBurnerStatusBak;

extern uint8_t gcVar;
extern uint16_t gcVar2;
extern uint8_t gcTemp;

extern uint8_t gcTestSendIRStatus;

uint8_t TestKeyStatus = 0;
uint8_t gcTestKeyCount = 0;

//=======================================================================================
//                  uint16_t Key_Check(void)
//                  10ms ????
//                  ??????
//=======================================================================================
uint8_t Key_Check(void)
{
    gcButton1State = exKeyValueFlag;
  
    switch (gcKeyStatus)
    {
        case 0:
        {
            if (gcButton1State) 
            {
                gcKeyCount++;
                if (gcKeyCount >= 1)
                {
                    gcKeyCount = 0;
                    gcKeyStatus = 1;
                }
            }
        }
        break;
        case 1:
        {
            if (gcButton1State)
            {
                Set_KeyDownFlag;
                gcKeyValue = SW6_KEY_VALUE; 
							if(TestONFlag == 0)
							{
							  if(gcBurnerStatus != 0)        //��ʾ��¯ͷ����
								{
//									if(BatLowWarrnFlag == 0)     //��¯ͷ���������Ҳ��ڵ͵�ѹģʽ��
//									{
										Set_KeyBuzzerFlag;     //������
//									}
								}
							}
							else     //����ģʽ
							{
								Set_BuzzerTestFlag;           //������
                gcVar2 = RawData[0] - BaseLine[0];         //����仯��		
                if(gcVar2 > 0x00ff)
									gcVar = 0xff;
								else
									gcVar = gcVar2;								
                Set_TestKeyDownFlag;
								Set_LEDONFlag;	
                if (KeyDownFlag)    //�а�������
								{
										Set_KeyReturnFlag;
										gcKeyValue = SW6_KEY_VALUE;      
								}				
							}
            }
            gcKeyStatus = 2;						
						Clr_Buzzer;
						
        }
        break;
        case 2:
        {
					 gcSleepDelayTime = 0;
            if (gcButton1State == 0)        //����̧��
            {
                gcKeyCount++;
                if (gcKeyCount >= 2)
                {
									
									gcKeyCount = 0;
									gcKeyStatus = 0;
									if(TestONFlag == 0)        //�û�ģʽ̧��
									{                  
                    giKeySW6LongDownTime = 0;
                    if (KeyDownFlag) 
                    {
                        Set_KeyReturnFlag;
                        Set_KeyFlashFlag;
                        gcKeyValue = SW6_KEY_VALUE;      
                    }
									}
									else    //����ģʽ��̧��
									{
//										Clr_LEDONFlag;     // �ص�
										Clr_Buzzer;
										Clr_BuzzerTestFlag;
										
//										gcTestSendIRStatus = 0;     //���¿�ʼѭ������
//										
//										Set_SendTestAFlag;
//										Set_SendTestBFlag;
//										Set_SendTestCFlag;
//										Clr_IRSendEnFlag;														
					          //  Clr_TestKeyDownFlag;        //������־��Ҫ���������
									}
                }     
            }
            else     
            { 
							if(TestONFlag == 0)    //�û�ģʽ����
							{
                if (giKeySW6LongDownTime < SW6_LONGDOWN_TIME)
                {
                    giKeySW6LongDownTime++;
                }
                
                if (giKeySW6LongDownTime == SW6_LONGDOWN_TIME)
                {								
									  
                    if (gcBurnerStatus != 0)
                    {
//											  gcKeyStatus = 0;
                        gcKeyValue = SW6_KEY_LONG_VALUE; 
                        giKeySW6LongDownTime = SW6_LONGDOWN_TIME+1;
                        Clr_KeyDownFlag;
                        Set_KeyReturnFlag;
                    }
									//	gcKeyStatus = 0;
                }
							}
            } // end else
        }
        break;
    }
    
    if (KeyReturnFlag)
    {
        Clr_KeyReturnFlag;
        return gcKeyValue;
    }
    else
    {
        return 0x00;
    }
}

//=======================================================================================
//                  void Key_Process(void)
//                  10ms ????
//                  ????
//=======================================================================================
 void Key_Process(void)
 {
     switch (Key_Check())
     {
         case SW6_KEY_VALUE:
         {				   
					 if(TestONFlag)
					 {
						 gcTestSendIRStatus = 0;
						 Set_SendTestAFlag;
						 Set_SendTestBFlag;
						 Set_SendTestCFlag;
						 Clr_IRSendEnFlag;
						 
					 }
					 else
						 {
             /*��һ��һ���رյĹ���*/
					   if(((LightOffDelayStartFlag)||(SpeedDelayOffStartFlag)))
							 {
								 Set_KeyBuzzerFlag;
								 Clr_LightOffDelayStartFlag;
								 Clr_SpeedDelayOffStartFlag;
								 
								 Set_SendLightOffCommandFlag; 
								 
								 Clr_FirSendLightOnCommandFlag;	
								 Clr_FirstSendSpeedOffCommandFlag;									 
								 gcIRSendLightOffTime = LIGHTOFFTIME;
								 
								 /*�ڷ��͹ص�����󣬼��250ms���͹ط�������*/
								 							
							 }
					 
             if((gcBurnerStatus != 0)&&(BatLowWarrnFlag == 0))      //��ʾ��¯ͷ����,�Ҳ��ٵ͵�ѹ������
						 {
//								Set_KeyBuzzerFlag;
             if (gcSpeedLevel < 4)
                 gcSpeedLevel++;
             else
                 gcSpeedLevel = 0;
             
             if (ActivateModeFlag == 0)      // ��DeActivateģʽ�� 
             {
                 if (DeactivateModeFirstLightFlag)     // First Send Light On
                 {
                     if (gcSpeedLevel!=0)
                     {
                        Clr_DeactivateModeFirstLightFlag;
											  Set_FirstLightOnFlag;              //�а�������֮��Ż������λ����ʾ�Ƶ��ź��Ѿ����͹���  
                        Set_SendLightOnCommandFlag;
												gcIRSendLightOnTime = LIGHTONTIME;			    //Ϊ��ʹ���״ν���ʱ��������.	
                        Clr_IRSendEnFlag;
                        Clr_FirSendLightOnCommandFlag;
                        
                     }
                 }
             }

							if (gcSpeedLevel == 0)
							{
									Clr_IRSendEnFlag;
									Set_SendSpeedOffCommandFlag;
									Clr_FirstSendSpeedOffCommandFlag;
									gcIRSendSpeedOffTime = SPEEDOFFTIME;
							}
							else
							{
									Clr_IRSendEnFlag;
									Set_SendSpeedCommandFlag;
									gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;
									Clr_FirstSendSpeedCommandFlag;  
							}
            
             if (gcSpeedLevel == 1)
             {
								Clr_SendSpeedOffCommandFlag;
								Clr_SendLightOffCommandFlag;  
             }
                 
                Clr_AutoModeFlag;     //
						 
           }
					 if((gcBurnerStatus != 0)&&(BatLowWarrnFlag))      //�ڵ͵�ѹ����ģʽ��
					 {
						 Clr_BatLowWarrnFlag;	
             Clr_BatLowWarrnEnFlag;           //�͵�ѹ����ʹ��						 
					 }
         }
			 }
         break;
				 
         case SW6_KEY_LONG_VALUE:
         {
					               
//						if(BatLowWarrnFlag == 0)     //���ڵ͵�ѹģʽ��
//							{
								Set_KeySureBuzzerFlag;       //����ȷ�ϵ�����
//							}
             if (ActivateModeFlag)
							 {									
									 Clr_ActivateModeFlag;
							 }
             else
             { 
							   gcBurnerStatusBak = 0;         //����
                 Set_ActivateModeFlag;
							   Set_AutoModeFlag;              //�����Զ�����Ϊ��Ӧ��Hob״̬   7.6
							   Set_ModeChangeFlag;            //�л���activateģʽ
             }
         }
         break;
         default:
         gcKeyValue = 0;    
         break;
     }
     
     gcKeyValue = 0;

 }

 void TestKey_Process(void)
 {
	 switch (TestKeyStatus)
	 {
		 case 0:
		 {			
			 if(P32 == 1)      //P32�Ͽ����˳��Լ�
			 { 
				 gcTestKeyCount++;
				 if(gcTestKeyCount > 3)
				 {
					 gcTestKeyCount = 0;
					 TestKeyStatus = 1;
				 }
			 }
		 }
		 break;
		 case 1:      //���԰����Ĵ���
		 {
			   Clr_LEDONFlag;         //9.23 �Ͽ���LED��
				 Clr_IntoTestFlag;
				 Clr_TestONFlag;
				 Delay1ms();          
				 GPIO_Init(GPIO3, GPIO_PIN_2, GPIO_MODE_OUT_PP);    //��P32���ó�����������Դﵽʡ��
				 Delay1ms();
				 P32 = 0;
			 
			 TestKeyStatus = 0;
		 }
		 break;
		 default:
		 break;			
			 
	 }
		 
 
 }
 
 