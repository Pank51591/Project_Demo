#include "SC_System.h"
#include "Key_Process.h"
#include "Buzzer_Process.h"
#include "SR_EEPROM.h"
#include "IapOperation.h"

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

extern uint8_t gchightbit; 
extern uint8_t gcmediumbit;
extern uint8_t gclowbit;
extern uint8_t gcfallowbit;
extern uint16_t  giTimesCount;

extern uint8_t gcTestDay;
extern uint8_t gcKey;
extern uint8_t gcLedCount;
uint8_t gcKey_Count = 0;

extern unsigned char Readbuff[12];
extern void IAP_Read_NByte(unsigned long Sadd,unsigned long Eadd,unsigned char Iapade);
extern uint8_t L1x,L2x,L3x,L4x;
extern uint8_t TestLowPower;


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
							  if(gcBurnerStatus != 0)        //��ʾ��¯ͷ����
								{
//									if(BatLowWarrnFlag == 0)     //��¯ͷ���������Ҳ��ڵ͵�ѹģʽ��
//									{
										Set_KeyBuzzerFlag;     //������
//									  Set_ToEEPROMFlag;          //������
//									}
								}
            }
            gcKeyStatus = 2;
						
						Clr_Buzzer;
						
        }
        break;
        case 2:
        {
					 gcSleepDelayTime = 0;
            if (gcButton1State == 0) 
            {
                gcKeyCount++;
                if (gcKeyCount >= 2)
                {
                    gcKeyCount = 0;
                    gcKeyStatus = 0;
                    giKeySW6LongDownTime = 0;
                    if (KeyDownFlag) 
                    {
                        Set_KeyReturnFlag;
                        Set_KeyFlashFlag;
											  Set_ShortDownFlag;
                        gcKeyValue = SW6_KEY_VALUE;      
                    }
                }     
            }
            else     
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
				 
					 if(DisPlayModeFlag)         //�ȳ���֮�󣬶̰�����Ч
					 {
						 
//						 gchightbit = gcTestDay / 100;
//						 gcmediumbit = (gcTestDay - gchightbit *100)/10;
//						 gclowbit = (gcTestDay - gchightbit *100)%10;	
						 
             if(ShortDownFlag)
						 {
							gcKey_Count++;      //��֤�а����ټ�
							Clr_ShortDownFlag;
						 }
						 
						 switch(gcKey_Count)
						 {
							 case 1:   //��ʾ��λ
							 {
								 gcLedCount = 0;
								 gcKey = 1;Clr_LED;
							 }
							 break;
							 case 2:   //��ʾ��λ
							 {
								 gcLedCount = 0;
								 gcKey = 2;Clr_LED;
							 }
							 break;
							 case 3:   //��ʾ��λ
							 {
								 gcLedCount = 0;
								 gcKey = 3;Clr_LED;
							 }
							 break;
							  case 4:   //��ʾ��λ
							 {
								 gcLedCount = 0;Clr_LED;
								 gcKey = 4;
								 gcKey_Count = 0;       //���㣬���´Ӹ�λ��ʼ��ʾ
							 } 
							 break;
						 
						}
	 
//					}
				}
					 
         }
         break;
				 
         case SW6_KEY_LONG_VALUE:           
         {
					 Set_KeySureBuzzerFlag;
					 	   				 
					 if(KeyLongDownFlag)
						{
							Clr_DisPlayModeFlag;
							Clr_KeyLongDownFlag;        //�ڲ���ģʽ��
						}
					else
						{
														
							Set_KeyLongDownFlag;        //���������������ѯ����
							Set_DisPlayModeFlag;
							Clr_LED;
							
							 /*������*/
						IAP_Read_NByte(0,10,EEPROM);
					 
					  L1x =  Readbuff[1];
					  L2x =  Readbuff[2];
					  L3x =  Readbuff[3];
					  L4x =  Readbuff[4];	
							
					  TestLowPower = Readbuff[5];
												
						}

				}
				 break;
     }
     
     gcKeyValue = 0;

 }
