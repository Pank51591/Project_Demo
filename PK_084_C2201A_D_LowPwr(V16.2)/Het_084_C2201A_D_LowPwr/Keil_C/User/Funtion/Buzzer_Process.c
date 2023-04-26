#include "SC_System.h"
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

uint8_t gcMCBuzzerstatus = 0;
uint8_t gcAHCloseBuzzerStatus = 0;
uint16_t gcBatLowWarrnBuzzerTime = 0;
uint8_t  gcBatLowWarrnBuzzerStatus = 0;
uint8_t  gcBatLowWarrnBuzzerCount = 0;
uint8_t  gcMCBuzzerTime = 0;
uint8_t  gcAHCloseBuzzerTime = 0;

void Buzzer_Process(void)
 {
		 
     if (KeyBuzzerFlag)
     {
        if (gcBuzzerTime == 0)        //6.30
        {
					SC_PWM3_Init();    //4KHz
          Set_Buzzer;
        }
        gcBuzzerTime++;
        if (gcBuzzerTime > 2)
        {
            gcBuzzerTime = 0;
            Clr_Buzzer;
            Clr_KeyBuzzerFlag;
        }

     }
     else if (KeySureBuzzerFlag)     //按键确认声音
     {
        if (gcBuzzerTime == 0)
        {
					SC_PWM3_Init_41Khz();
          Set_Buzzer_41Khz;
        }
        gcBuzzerTime++;
        if (gcBuzzerTime > 100)
        {
            gcBuzzerTime = 0;
            Clr_Buzzer;
            Clr_KeySureBuzzerFlag;
        }
     }
		 
		 else if (BuzzerTestFlag)    //按键测试音
		 {
////			 if (gcBuzzerTime == 0)
////        {
					SC_PWM3_Init_41Khz();
          Set_Buzzer_41Khz;
////        }
////        gcBuzzerTime++;
////        if (gcBuzzerTime > 200)
////        {
////            gcBuzzerTime = 0;
////            Clr_Buzzer;
////            Clr_BuzzerTestFlag;
////        }
	
		 }

		 else if(BatLowWarrnFlag)     //低电压报警
		 {
				 switch(gcBatLowWarrnBuzzerStatus)
				 {
					 case 0:
					 {
							SC_PWM3_Init_2Khz();
							Set_Buzzer_2Khz;
							gcBatLowWarrnBuzzerStatus = 1;
							gcBatLowWarrnBuzzerTime = 0;
					 }
					 break;
					 case 1:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime >= 80)     //（1）
						 {
							 gcBatLowWarrnBuzzerTime = 0;
							 Clr_Buzzer;
							 gcBatLowWarrnBuzzerStatus = 2;
						 }
					 }
					 break;
					 case 2:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime >= 80)
						 {
							 gcBatLowWarrnBuzzerTime = 0;
//							 SC_PWM3_Init_2Khz();
//							 Set_Buzzer_2Khz;
							 SC_PWM3_Init_33Khz();
							 Set_Buzzer_33Khz;
							 gcBatLowWarrnBuzzerStatus = 3;
						 }
					 }
					 break;
					 case 3:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime >= 80)     //(2)
						 {
							 gcBatLowWarrnBuzzerTime = 0;
							 Clr_Buzzer;
							 gcBatLowWarrnBuzzerStatus = 4;
						 }
					 }
					 break;
					 case 4:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime >= 80)
						 {
							 gcBatLowWarrnBuzzerTime = 0;
//							SC_PWM3_Init_2Khz();
//							Set_Buzzer_2Khz;
							 SC_PWM3_Init_41Khz();
							 Set_Buzzer_41Khz;
							 gcBatLowWarrnBuzzerStatus = 5;
						 }
					 }
					 break; 
					 case 5:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime >= 80)    //(3)
						 {
							 gcBatLowWarrnBuzzerTime = 0;
							 Clr_Buzzer;
							 gcBatLowWarrnBuzzerStatus = 6;
						 }
					 }
					 break;
					 case 6:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime >= 80)
						 {
							 gcBatLowWarrnBuzzerTime = 0;
							 SC_PWM3_Init_33Khz();
							 Set_Buzzer_33Khz;
//							 Clr_Buzzer;
							 gcBatLowWarrnBuzzerStatus = 7;
					 }
					 }
					 break;
					 case 7:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime >= 80)    //(3)
						 {
							 gcBatLowWarrnBuzzerTime = 0;
							 Clr_Buzzer;
							 gcBatLowWarrnBuzzerStatus = 8;
						 }
					 }
					 break;
					 case 8:
					 {
						 gcBatLowWarrnBuzzerTime++;
						 if (gcBatLowWarrnBuzzerTime > 850)
						 {
							 gcBatLowWarrnBuzzerTime = 0;
							 gcBatLowWarrnBuzzerStatus = 0;
							 gcBatLowWarrnBuzzerCount++;
							 if (gcBatLowWarrnBuzzerCount > 3)        //低电压报警5s
							 {				
								 gcBatLowWarrnBuzzerCount = 0;
								 if(gcBurnerStatus != 0)	    //有炉头开启，可以继续使用
								 {
									 Clr_BatLowWarrnEnFlag;
								 }
//								 else          //没有炉头开启
//								 {	
//									  Set_AllHodCloseFlag;      //发出所有炉头关闭的声音
//								 }
								   
								   Clr_BatLowWarrnFlag;           //清低电压报警，此时LED闪烁停止
								}
							}
						
					 }
					 break;
					 default:
						 
					 break;
				 }
//			 }
			 
		 }
		 
		 else if (AllHodCloseFlag )    //所有的炉头都关闭 （在Active模式下才会有这个声音 11.4）（将三声改为一声 2023.1.4）
		 {
			 if (gcAHCloseBuzzerTime == 0)
        {
					SC_PWM3_Init_41Khz();
          Set_Buzzer_41Khz;
        }
        gcAHCloseBuzzerTime++;
        if (gcAHCloseBuzzerTime > 100)
        {
            gcAHCloseBuzzerTime = 0;
            Clr_Buzzer;
            Clr_AllHodCloseFlag;
        }
			 
////			switch(gcAHCloseBuzzerStatus)
////			{
////				case 0:
////				{
////					 SC_PWM3_Init_41Khz();
////					 Set_Buzzer_41Khz;
////					 gcAHCloseBuzzerTime = 0;
////           gcAHCloseBuzzerStatus = 1;
////				}
////				break;
////				case 1:
////				{
////					gcAHCloseBuzzerTime++;
////					 if(gcAHCloseBuzzerTime >= 100) 
////					 {
////						 gcAHCloseBuzzerTime = 0;
////						 Clr_Buzzer;
////						 gcAHCloseBuzzerStatus = 2;
////					 }
////				}
////				break;
////				case 2:
////				{
////						gcAHCloseBuzzerTime++;
////					 if(gcAHCloseBuzzerTime >= 100) 
////					 {
////						 gcAHCloseBuzzerTime = 0;
////						 SC_PWM3_Init_41Khz();
////							Set_Buzzer_41Khz;
////						 gcAHCloseBuzzerStatus = 3;
////					 }
////				}
////				break;
////				case 3:
////				{
////					gcAHCloseBuzzerTime++;
////					 if(gcAHCloseBuzzerTime >= 100) 
////					 {
////						 gcAHCloseBuzzerTime = 0;
////						 Clr_Buzzer;
////						 gcAHCloseBuzzerStatus = 4;
////					 }
////				}
////				break;		
////				case 4:
////				{
////						gcAHCloseBuzzerTime++;
////					 if(gcAHCloseBuzzerTime >= 100) 
////					 {
////						 gcAHCloseBuzzerTime = 0;
////						 SC_PWM3_Init_41Khz();
////							Set_Buzzer_41Khz;
////						 gcAHCloseBuzzerStatus = 5;
////					 }
////				}
////				break;
////				case 5:
////				{
////					gcAHCloseBuzzerTime++;
////					 if(gcAHCloseBuzzerTime >= 100) 
////					 {
////						 gcAHCloseBuzzerTime = 0;
////						 Clr_Buzzer;
////						 gcAHCloseBuzzerStatus = 0;
////						 Clr_AllHodCloseFlag;
////					 }
////				}
////				break;
////				default:
////					break;
////				
////			}
		 }
		 else  /*蜂鸣器不响*/
     {
         Clr_Buzzer;
         gcBuzzerTime = 0;
				 gcBatLowWarrnBuzzerTime = 0;
			   gcBatLowWarrnBuzzerCount = 0;
		 	   gcBatLowWarrnBuzzerStatus = 0;
     }
     		 
		 
 }