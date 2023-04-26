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
extern uint8_t gcMCBuzzerstatus;
extern uint8_t gcAHCloseBuzzerStatus;


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
					 if (gcBatLowWarrnBuzzerTime >= 200)
					 {
						 gcBatLowWarrnBuzzerTime = 0;
						 SC_PWM3_Init_2Khz();
						 Set_Buzzer_2Khz;
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
					 if (gcBatLowWarrnBuzzerTime >= 200)
					 {
						 gcBatLowWarrnBuzzerTime = 0;
						SC_PWM3_Init_2Khz();
						Set_Buzzer_2Khz;
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
					 if (gcBatLowWarrnBuzzerTime >= 200)
					 {
						 gcBatLowWarrnBuzzerTime = 0;
						 Clr_Buzzer;
						 gcBatLowWarrnBuzzerStatus = 7;
				 }
				 }
				 break;
				 case 7:
				 {
					 gcBatLowWarrnBuzzerTime++;
					 if (gcBatLowWarrnBuzzerTime > 1410)
					 {
						 gcBatLowWarrnBuzzerTime = 0;
						 gcBatLowWarrnBuzzerStatus = 0;
//						 gcBatLowWarrnBuzzerCount++;
//						 if (gcBatLowWarrnBuzzerCount > 26)        //低电压报警1分钟
//						 {
//							 gcBatLowWarrnBuzzerCount = 0;
//							 Clr_BatLowWarrnEnFlag;
//							 Clr_BatLowWarrnFlag;           //清低电压报警，此时LED闪烁停止
//						 }
					 }
				 }
				 break;
				 default:
					 
				 break;
			 }
		 }
////		 else if (ModeChangeFlag)    //模式切换
////		 {
////			 switch(gcMCBuzzerstatus)
////			 { 
////				 case 0 :
////				 {
////					 SC_PWM3_Init_41Khz();
////					 Set_Buzzer_41Khz;
////					 gcMCBuzzerTime = 0;
////           gcMCBuzzerstatus = 1;
////					 
////				 }
////				 break;
////				 case 1 :
////				 {
////					 gcMCBuzzerTime++;
////					 if(gcMCBuzzerTime >= 100) 
////					 {
////						 gcMCBuzzerTime = 0;
////						 Clr_Buzzer;
////						 gcMCBuzzerstatus = 2;
////					 }
////				 }
////				 break;
////				 case 2 :
////				 {
////					 gcMCBuzzerTime++;
////					 if(gcMCBuzzerTime >= 100) 
////					 {
////						 gcMCBuzzerTime = 0;
////						 SC_PWM3_Init_41Khz();
////						 Set_Buzzer_41Khz;
////						 gcMCBuzzerstatus = 3;
////					 }
////				 }
////				 break;
////				 case 3 :
////				 {
////					 gcMCBuzzerTime++;
////					 if(gcMCBuzzerTime >= 100) 
////					 {
////						 gcMCBuzzerTime = 0;
////						 Clr_Buzzer;
////						 gcMCBuzzerstatus = 0;
////						 Clr_ModeChangeFlag;
////					 }
////				 }
////				 break;
////				 default :
////					 break;
////			 }
////	
////		 }
		 else if (AllHodCloseFlag)    //所有的炉头都关闭
		 {
			switch(gcAHCloseBuzzerStatus)
			{
				case 0:
				{
					 SC_PWM3_Init_41Khz();
					 Set_Buzzer_41Khz;
					 gcAHCloseBuzzerTime = 0;
           gcAHCloseBuzzerStatus = 1;
				}
				break;
				case 1:
				{
					gcAHCloseBuzzerTime++;
					 if(gcAHCloseBuzzerTime >= 100) 
					 {
						 gcAHCloseBuzzerTime = 0;
						 Clr_Buzzer;
						 gcAHCloseBuzzerStatus = 2;
					 }
				}
				break;
				case 2:
				{
						gcAHCloseBuzzerTime++;
					 if(gcAHCloseBuzzerTime >= 100) 
					 {
						 gcAHCloseBuzzerTime = 0;
						 SC_PWM3_Init_41Khz();
							Set_Buzzer_41Khz;
						 gcAHCloseBuzzerStatus = 3;
					 }
				}
				break;
				case 3:
				{
					gcAHCloseBuzzerTime++;
					 if(gcAHCloseBuzzerTime >= 100) 
					 {
						 gcAHCloseBuzzerTime = 0;
						 Clr_Buzzer;
						 gcAHCloseBuzzerStatus = 4;
					 }
				}
				break;		
				case 4:
				{
						gcAHCloseBuzzerTime++;
					 if(gcAHCloseBuzzerTime >= 100) 
					 {
						 gcAHCloseBuzzerTime = 0;
						 SC_PWM3_Init_41Khz();
							Set_Buzzer_41Khz;
						 gcAHCloseBuzzerStatus = 5;
					 }
				}
				break;
				case 5:
				{
					gcAHCloseBuzzerTime++;
					 if(gcAHCloseBuzzerTime >= 100) 
					 {
						 gcAHCloseBuzzerTime = 0;
						 Clr_Buzzer;
						 gcAHCloseBuzzerStatus = 0;
						 Clr_AllHodCloseFlag;
					 }
				}
				break;
				default:
					break;
				
			}
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