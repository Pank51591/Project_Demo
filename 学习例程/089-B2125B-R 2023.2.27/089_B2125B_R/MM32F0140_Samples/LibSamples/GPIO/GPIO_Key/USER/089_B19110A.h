#ifndef __089_B19110A_H__
#define __089_B19110A_H__
 
#include "main.h"
   
/******************     通信协议位    ***********************/	 
#define  Set_MainFun_flag     gcMainSubPair_Flag=0
#define  Set_SubFun_flag      gcMainSubPair_Flag=1
#define  Set_PairFun_flag      gcMainSubPair_Flag=2

extern struct Flag_Struct MyFlag;
struct Flag_Struct
{
    uint8_t Key2Down;  //  
	  uint8_t KeyReturn;
		uint8_t Key1Down;  //  
		uint8_t Key4Down;  //
		uint8_t Key5Down;  //
	  uint8_t Key6Down;
	  uint8_t Key10Down;  // 
		uint8_t Key11Down;  // 
  	uint8_t Key12Down;  // 
	  uint8_t LEDon;
		uint8_t KeyAddDelay;
	  uint8_t RfSendEnable;
		uint8_t RfwaitXbmsA;
		uint8_t RfwaitXamsA;
		uint8_t Rfwait500ms;
		uint8_t Isintest;
	  uint8_t SubFun;
		uint8_t PairFun;
		uint8_t MainFun;
	  uint8_t WindFun;
		uint8_t IWDGCheck;
		uint8_t IWDGCheckEnd;
		uint8_t OneSecond;
		uint8_t WdtWakeUp;
		uint8_t KeyWakeUp;
};   
 


#define Key2Down_Flag                 MyFlag.Key2Down			// 
#define Set_Key2Down_Flag            MyFlag.Key2Down = 1
#define Clr_Key2Down_Flag            MyFlag.Key2Down = 0

#define KeyReturnFlag                 MyFlag.KeyReturn			//按键返回标志
#define Set_KeyReturn_Flag            MyFlag.KeyReturn = 1
#define Clr_KeyReturn_Flag            MyFlag.KeyReturn = 0

#define Key1Down_Flag                 MyFlag.Key1Down			// 
#define Set_Key1Down_Flag            MyFlag.Key1Down = 1
#define Clr_Key1Down_Flag            MyFlag.Key1Down = 0

#define Key4Down_Flag                 MyFlag.Key4Down			// 
#define Set_Key4Down_Flag            MyFlag.Key4Down = 1
#define Clr_Key4Down_Flag            MyFlag.Key4Down = 0


#define Key5Down_Flag                 MyFlag.Key5Down			// 
#define Set_Key5Down_Flag            MyFlag.Key5Down = 1
#define Clr_Key5Down_Flag            MyFlag.Key5Down = 0

#define Key6Down_Flag                 MyFlag.Key6Down			// 
#define Set_Key6Down_Flag            MyFlag.Key6Down = 1
#define Clr_Key6Down_Flag            MyFlag.Key6Down = 0

#define Key10Down_Flag                 MyFlag.Key10Down			// 
#define Set_Key10Down_Flag            MyFlag.Key10Down = 1
#define Clr_Key10Down_Flag            MyFlag.Key10Down = 0

#define Key11Down_Flag                 MyFlag.Key11Down			// 
#define Set_Key11Down_Flag            MyFlag.Key11Down = 1
#define Clr_Key11Down_Flag            MyFlag.Key11Down = 0

#define Key12Down_Flag                 MyFlag.Key12Down			// 
#define Set_Key12Down_Flag            MyFlag.Key12Down = 1
#define Clr_Key12Down_Flag            MyFlag.Key12Down = 0

#define LEDon_Flag                 		MyFlag.LEDon			// 
#define Set_LEDon_Flag            		MyFlag.LEDon = 1
#define Clr_LEDon_Flag           		  MyFlag.LEDon = 0


#define KeyAddDelay_flag                 		MyFlag.KeyAddDelay			// 
#define Set_KeyAddDelay_flag            		MyFlag.KeyAddDelay = 1
#define Clr_KeyAddDelay_flag           		  MyFlag.KeyAddDelay = 0

#define RfSendEnable_Flag                 		MyFlag.RfSendEnable			// 
#define Set_RfSendEnable_Flag            			MyFlag.RfSendEnable = 1
#define Clr_RfSendEnable_Flag           		  MyFlag.RfSendEnable = 0

#define RfwaitXbms_Flag                 		MyFlag.RfwaitXbmsA			// 
#define Set_RfwaitXbms_Flag            			MyFlag.RfwaitXbmsA = 1
#define Clr_RfwaitXbms_Flag           		  MyFlag.RfwaitXbmsA = 0


#define RfwaitXams_Flag                 		MyFlag.RfwaitXamsA			// 
#define Set_RfwaitXams_Flag            			MyFlag.RfwaitXamsA = 1
#define Clr_RfwaitXams_Flag           		  MyFlag.RfwaitXamsA = 0



#define Rfwait500ms_Flag                 	MyFlag.Rfwait500ms			// 
#define Set_Rfwait500ms_Flag              MyFlag.Rfwait500ms = 1
#define Clr_Rfwait500ms_Flag           		MyFlag.Rfwait500ms = 0

#define Isintest_flag                 		MyFlag.Isintest			// 
#define Set_Isintest_flag            			MyFlag.Isintest = 1
#define Clr_Isintest_flag           		  MyFlag.Isintest = 0

#define IWDGCheck_Flag                 		MyFlag.IWDGCheck			// 
#define Set_IWDGCheck_Flag            		MyFlag.IWDGCheck = 1
#define Clr_IWDGCheck_Flag           		  MyFlag.IWDGCheck = 0

#define IWDGCheckEnd_Flag                 MyFlag.IWDGCheckEnd			// 
#define Set_IWDGCheckEnd_Flag            	MyFlag.IWDGCheckEnd = 1
#define Clr_IWDGCheckEnd_Flag           	MyFlag.IWDGCheckEnd = 0

#define OneSecond_Flag                 		MyFlag.OneSecond			// 
#define Set_OneSecond_Flag            		MyFlag.OneSecond = 1
#define Clr_OneSecond_Flag           		  MyFlag.OneSecond = 0

#define WdtWakeUp_Flag                 		MyFlag.WdtWakeUp			//看门狗唤醒标志
#define Set_WdtWakeUp_Flag           			MyFlag.WdtWakeUp = 1
#define Clr_WdtWakeUp_Flag           		  MyFlag.WdtWakeUp = 0

#define KeyWakeUp_Flag                 		MyFlag.KeyWakeUp			//按键按下唤醒标志 
#define Set_KeyWakeUp_Flag           			MyFlag.KeyWakeUp = 1
#define Clr_KeyWakeUp_Flag           		  MyFlag.KeyWakeUp = 0


#define Set_PB3		GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define Clr_PB3		GPIO_ResetBits(GPIOB,GPIO_Pin_3)

#define Set_PB4		GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define Clr_PB4		GPIO_ResetBits(GPIOB,GPIO_Pin_4)

#define Set_PB5		GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define Clr_PB5		GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define Set_PB6 	GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define Clr_PB6		GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define Set_PA4		GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define Clr_PA4		GPIO_ResetBits(GPIOA,GPIO_Pin_4)

#define Set_PA9		GPIO_SetBits(GPIOA,GPIO_Pin_9)
#define Clr_PA9		GPIO_ResetBits(GPIOA,GPIO_Pin_9)

#define Set_PA11		GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define Clr_PA11		GPIO_ResetBits(GPIOA,GPIO_Pin_11)

#define Set_PA12		GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define Clr_PA12		GPIO_ResetBits(GPIOA,GPIO_Pin_12)

#define Set_PA15		GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define Clr_PA15		GPIO_ResetBits(GPIOA,GPIO_Pin_15)


#define Set_TESTIO		GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define Clr_TESTIO		GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define TESTIO_TOGGLE()  (GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7))?(GPIO_ResetBits(GPIOB,GPIO_Pin_7)):(GPIO_SetBits(GPIOB,GPIO_Pin_7))

#define Set_PA5				GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define Clr_PA5				GPIO_ResetBits(GPIOA,GPIO_Pin_5)

#define Set_PA7				GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define Clr_PA7				GPIO_ResetBits(GPIOA,GPIO_Pin_7)

#define Set_PB1				GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define Clr_PB1				GPIO_ResetBits(GPIOB,GPIO_Pin_1)

#define Set_PB0			  GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define Clr_PB0				GPIO_ResetBits(GPIOB,GPIO_Pin_0)

#define ReadKEY_PA6		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define ReadKEY_PA8		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define ReadKEY_PA10	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)


#define     warmhouse  0x04     //取暖
#define     changeair  0x06     //换气
#define     cold_dry   0x08     //冷干燥
#define     hot_dry    0x0a     //热干燥
#define     degerming  0x0d     //除菌
#define     standby    0x00     //待机

#define     noneset    0xff     //无设定
 
#define     strong     0x0      //强  风量
//#define     weak       0x1      //弱  风量

#define     fixed      0x00     //固定   风向
#define     fixed90    0x03     //固定90°   风向
#define     automat    0x06      //自动   风向


#define     focus      0x01     //集中   风种
#define     spread     0x02     //扩散   风种

//#define     lampoff       0x00     //OFF   照明
//#define     warmon        0x01     //暖on   照明
//#define     coldon        0x02     //冷on   照明
//#define     lamp_change   0x04     //照明切换
//#define     nightlamp     0x05     //夜灯切换

#define     wifioff       0x00     //OFF   wifi
#define     wifion        0x01     //on    wifi
#define     resetsoft     0x02     //reset  softAP   wifi
#define     resetquick    0x03     //reset  快连    wifi
#define     TianMao_Rst   0x04     //天猫reset


#define     voice_off     0x00
#define     voice_on      0x01

#define     Mod54BET1C       0x01     //机型
#define     Mod54BE1C        0x02     //
#define     Mod20GBY1        0x03     //
#define     ModRB20V1        0x08     //

#define     timer15min    0x03    //定時  
#define     timer30min    0x06
#define     timer1hour    0x0C
#define     timer3hour    0x10
#define     timer6hour    0x16
#define     timerconti    0x23

#define     ModeOfpair    0xaa


extern volatile unsigned char gc10msCount;
extern volatile unsigned char gc1MsCount;
extern volatile unsigned int giRf500msCount;
extern volatile unsigned char gcRfXamsCount;
extern volatile unsigned char gcRfXbmsCount;
extern volatile unsigned char gcIDcode1;
extern volatile unsigned char gcIDcode2;
extern volatile unsigned char gcIDcode3;
extern volatile unsigned char gcIDcode4;

extern volatile unsigned char  gcTimeVal_sec; 

extern volatile unsigned char gcPtcolBuff[11]; 
extern volatile unsigned char gcTxBuff[17];
extern volatile unsigned char gcEEPROM_Init_flag;

extern volatile unsigned int gcLamp1sCount;
extern volatile unsigned int giSleepTime;
extern volatile unsigned int giTimeVal;
extern volatile unsigned int gi1sCount;

#define   MAX_SLEEP_VALUE   100    // 1s

#define   Ptcol_RunMode     gcPtcolBuff[0]
#define   Ptcol_AirVol      gcPtcolBuff[1]
#define   Ptcol_AirDir      gcPtcolBuff[2]
#define   Ptcol_Airkind     gcPtcolBuff[3]
#define   Ptcol_TimeSet     gcPtcolBuff[4]
#define   Ptcol_HourRem     gcPtcolBuff[5]
#define   Ptcol_MinRem      gcPtcolBuff[6]
#define   Ptcol_light       gcPtcolBuff[7]
#define   Ptcol_Wifi        gcPtcolBuff[8]
#define   Ptcol_voice       gcPtcolBuff[9]
#define   Ptcol_Model       gcPtcolBuff[10]

extern void Write_Iwdg_ON(u16 IWDG_Prescaler, u16 Reload);

#endif


/* [] END OF FILE */
