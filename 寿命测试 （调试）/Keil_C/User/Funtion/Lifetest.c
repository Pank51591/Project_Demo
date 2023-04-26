#include "Lifetest.h"
#include "SC_System.h"
#include "Burner_Process.h"
#include "Output_Process.h"
#include "Key_Process.h"
#include "Time_Process.h"

extern void Write_EEPROM(void);

extern void Life_Process(void);
extern uint8_t gcSpeedLevel;
extern uint8_t gcBurnerStatus;
extern uint8_t gcKeyValue;
extern uint8_t gcIRSendSpeedOffTime;
extern uint8_t gcIRSendSpeedCommandTime; 
extern uint8_t gcIRSendLightOffTime ;
extern uint8_t gcIRSendSpeedOffTime;
extern uint8_t gcIRSendLightOnTime;
extern uint8_t gcTestDay = 0;

extern unsigned char Readbuff[12];
extern uint8_t RadioFREQ[10];
extern uint16_t  giTimesCount;	
uint8_t gclifeteststatus = 0;
uint8_t gcCookingCount = 0;
uint16_t gcWait30minCount = 0;
uint8_t gcWaitCount;
uint8_t gctime;
uint16_t gcCookingTimes = 0;

extern uint8_t gchightbit; 
extern uint8_t gcmediumbit;
extern uint8_t gclowbit;
extern uint8_t gcfallowbit;

/***运行周期：125ms***/
void Life_Process(void)
{
//		 P31=~P31;				//非BTM唤醒，用户根据需要自行增添处理程序
	if((DisPlayModeFlag == 0)&&(BatLowWarrnEnFlag == 1))             //测试模式，且没有发生过低电压报警
	{
		
		
		
	switch (gclifeteststatus)
		{
			
		case 0 :
			{
        Set_TestModeFlag;
				gctime++;
				if(gctime >= 1)
				{
					gctime = 2;
					Hood_light_on();	
					Set_SysWakeUpSleepFlag;         //退出低功耗模式			
					gcWaitCount = 0;
					gclifeteststatus = 1;
					
				}					
			}
			break;
		case 1 :     //等待6秒
			{
				gcWaitCount++;
				if(gcWaitCount>=8*6)
				{
					gctime = 0;
					gcSpeedLevel = 1;
					Hood_level();
					Set_SysWakeUpSleepFlag;         //退出低功耗模式
					Set_KeyBuzzerFlag;    //发出按键音
					gcWaitCount = 26;
					gclifeteststatus = 2;
				}	
			}
			break;
		case 2 :
			{ 
				gctime++;
				if(gctime >= 1)
				{
					gctime = 2;
					Hood_light_on();	
					Set_SysWakeUpSleepFlag;         //退出低功耗模式			
					gcWaitCount = 0;
					gclifeteststatus = 3;
				}	
			}
			break;
		case 3 :
			{
				gcWaitCount++;
				if(gcWaitCount>=8*6)
				{
					gctime = 0;
					Set_KeyBuzzerFlag;
					Hood_level();
					Set_SysWakeUpSleepFlag;         //退出低功耗模式
					gcSpeedLevel = 2;
					gcWaitCount = 26;
					gclifeteststatus = 4;
				}	
			}
			break;
		case 4 :
			{		
				gctime++;
				if(gctime >= 1)
				{
					gctime = 2;
					Hood_light_on();	
					Set_SysWakeUpSleepFlag;         //退出低功耗模式			
					gcWaitCount = 0;
					gclifeteststatus = 5;
				}	
					
			}
			break;
		case 5 :
			{	
				gcWaitCount++;
				if(gcWaitCount>=8*6)
				{
					gctime = 0;
					Set_KeyBuzzerFlag;    //发出按键音
					Hood_level();
					Set_SysWakeUpSleepFlag;         //退出低功耗模式
					gcSpeedLevel = 3;
					gcWaitCount = 26;
					gclifeteststatus = 6;
				}	
		
			}
			break;
		case 6 :
			{			
				gctime++;
				if(gctime >= 1)
				{
					gctime = 2;
					Hood_light_on();	
					Set_SysWakeUpSleepFlag;         //退出低功耗模式			
					gcWaitCount = 0;
					gclifeteststatus = 7;
				}	
				
			}
			break;
		case 7 :   
			{
				gcWaitCount++;
				if(gcWaitCount>=8*6)
				{
					gctime = 0;
					Set_KeyBuzzerFlag;      //发出按键音
					Hood_level();
					Set_SysWakeUpSleepFlag;         //退出低功耗模式
					gcSpeedLevel = 4;
					gcWaitCount = 26;
					gclifeteststatus = 8;
					
				}	
				
			}
			break;
		case 8 :       //烹饪30分钟
			{
				gcWait30minCount++;
				if(gcWait30minCount >= 8 * 6)        // 6
				{			
					gclifeteststatus = 9;
				}			
			}
			break;
		case 9 :     //关风扇
			{
        Clr_TestModeFlag;				
				gcWait30minCount = 0;
				Clr_IRSendEnFlag;
				Set_SendSpeedOffCommandFlag;
				gcSpeedLevel = 0;                 //风速为0时  
				gcIRSendSpeedOffTime = 100;
			  gclifeteststatus = 10;
				
				Set_SysWakeUpSleepFlag;           //退出低功耗模式
			}
			break;
		case 10:
		{
			   /* 关灯的指令 */	
//				Set_LightOffDelayStartFlag;
//				Set_SpeedDelayOffStartFlag;
//				Set_SendLightOffCommandFlag;  
//				Set_SendLightOffEnFlag;
//				Set_SendSpeedOffEnFlag;
//				Clr_IRSendEnFlag;
//			
//			  Set_SysWakeUpSleepFlag;          //退出低功耗模式
					
			 
				gcCookingTimes++;
//			  gcCookingCount++;
//				if(gcCookingCount >= 3)           //每3次存储一次，防止断电
//				{
//					gcCookingCount = 0;
					
//					RadioFREQ[0] =  gcCookingTimes / 1000;          
//					RadioFREQ[1] =  gcCookingTimes / 100 % 10;   //(gcCookingTimes - (gcCookingTimes / 1000) *1000)/100 ;
//					RadioFREQ[2] =  gcCookingTimes / 10 % 10;    //(gcCookingTimes - (gcCookingTimes / 1000) *1000 - ((gcCookingTimes - (gcCookingTimes / 1000) *1000)/100 ) *100) / 10; 
//					RadioFREQ[3] =  gcCookingTimes % 10;         //(gcCookingTimes - (gcCookingTimes / 1000) *1000 - ((gcCookingTimes - (gcCookingTimes / 1000) *1000)/100 ) *100) % 10;
//          RadioFREQ[4] = 0x01;     //测试用
//					Write_EEPROM();
//							
//				}
		 Set_KeySureBuzzerFlag;		
     gclifeteststatus = 0;   //测试用			
		}		
		break;		
			default :
				break;				
	}

}
	

//if(ToEEPROMFlag)         //如果发生低电压报警，就存储
//		{		
//        Clr_ToEEPROMFlag;
//			  Clr_BatLowWarrnEnFlag;      //禁止低电压检测 （保证这段程序只在低电压的时候跑一次）
//			
//				RadioFREQ[0] =  gcCookingTimes / 1000;          
//				RadioFREQ[1] =  gcCookingTimes / 100 % 10; 
//				RadioFREQ[2] =  gcCookingTimes / 10 % 10;				
//			  RadioFREQ[3] =  gcCookingTimes % 10;	
//			  RadioFREQ[4] = 0x01;
//						
//				Write_EEPROM();	
//		}


}

/*发送 Hood light ON 指令*/
void Hood_light_on(void)
{
	Set_SendLightOnCommandFlag;
	Set_SendLightOnEnFlag;
	gcIRSendLightOnTime = LIGHTONTIME;
	Clr_LightOffDelayStartFlag;
  Clr_IRSendEnFlag;	
}
	
/*发送 Hood_level指令*/
void Hood_level(void)
{
  Set_SendSpeedCommandFlag;
	Set_SendSpeedCommandEnFlag;
	gcIRSendSpeedCommandTime =  SPEEDCOMMANDTIME;
	Clr_IRSendEnFlag; 
  Clr_SpeedDelayOffStartFlag; 
}




