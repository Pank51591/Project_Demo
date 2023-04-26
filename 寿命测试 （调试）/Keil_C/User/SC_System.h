#ifndef SC_SYS
#define SC_SYS
#include "SC_Init.h" // MCU initialization header file, including all firmware library header files
#include "SC_it.h"
#include "Key_Process.h"
#include "ADC_Process.h"
#include "Time_Process.h"
#include "Output_Process.h"
#include "Buzzer_Process.h"
#include "Burner_Process.h"
#include "HeadFiles\SC_itExtern.h"
#include "..\Drivers\SCDriver_List.h"
#include "HeadFiles\SysFunVarDefine.h"



extern bit Time_100us_Flag;

#define FLASHTIME				100     //50*10ms= 500ms闪烁变化   

#define LIGHTONTIME			100
#define SPEEDCOMMANDTIME 75
#define LIGHTOFFTIME		100
#define SPEEDOFFTIME     75


/* ------未来定时器8分频再填值--------- */
#define Time_5ms  52203
#define Time_100us 62336
#define Time_1088ms 30720
#define Time_742us 41792
#define Time_691us 43424
#define Time_738us 63568+16
#define Time_705us 63656+16
#define Time_1ms 62870
/* ----------------- */
#define PWM_1KPressel 31999
#define PWM_4_1KPressel 7779
#define PWM_4KPressel 7999

#define PWM_2KPressel 15999
#define PWM_3_3KPressel 9599



#define SW6_KEY_VALUE 0x01      //
#define SW6_KEY_LONG_VALUE 0x81 //
#define SW6_LONGDOWN_TIME 494   // 5000*10ms = 5S
#define BURNER_STATUS_ON 0      //
#define BURNER_STATUS_CLOSE 1
#define BURNER_TIME 20 // 20*10ms=200ms

#define BURNER_1_STATUS 0x01
#define BURNER_2_STATUS 0x02
#define BURNER_3_STATUS 0x04
#define BURNER_4_STATUS 0x08
#define BURNER_5_STATUS 0x10
#define BURNER_6_STATUS 0x20
/* EX IR ADC的值 */
#define EXTIR_ADC_MAX_VALUE 2100 // on=2732  yes=1652
#define EXTIR_ADC_MIN_VALUE 300
#define PWM_MAX 300
#define PWM_ADD_VALUE 6
#define FLASH_LED_VALUE 50 // 50*10ms=500ms

#define Set_BAT_EN P36 = 1 // BAT_EN_Set()
#define Clr_BAT_EN P36 = 0 // BAT_EN_Clear()

#define VOL_LOW_VALUE		295    //

#define Set_LED  P23 = 0 //PWM_IndependentModeConfigEX(PWM20, 0, PWM_OUTPUTSTATE_ENABLE);//P41 = 0 // LED_Clear()//TC2_Compare16bitMatch1Set(3000)
#define Clr_LED  P23 = 1 //PWM_IndependentModeConfigEX(PWM20, 31999, PWM_OUTPUTSTATE_ENABLE);//P41 = 1 // LED_Set() //TC2_Compare16bitMatch1Set(0)

#define Set_LED_LEVEL //  TC2_Compare16bitMatch1Set(1000)
#define Clr_LED_LEVEL //  TC2_Compare16bitMatch1Set(0)

#define Set_InsideIR_Send  PWM_IndependentModeConfigEX(PWM05, 55, PWM_OUTPUTSTATE_ENABLE);// TC4_CompareStart()
#define Clr_InsideIR_Send  PWM_IndependentModeConfigEX(PWM05, 0, PWM_OUTPUTSTATE_ENABLE);// TC4_CompareStop()

#define Set_ExternalIR_Send1 PWM_IndependentModeConfigEX(PWM07, 111, PWM_OUTPUTSTATE_ENABLE);// TC5_CompareStart()


#define Set_ExternalIR_Send PWM_IndependentModeConfigEX(PWM07, 55, PWM_OUTPUTSTATE_ENABLE);// TC5_CompareStart()
#define Clr_ExternalIR_Send PWM_IndependentModeConfigEX(PWM07, 0, PWM_OUTPUTSTATE_ENABLE);// TC5_CompareStop()

#define Set_Buzzer_2Khz   PWM_IndependentModeConfigEX(PWM30, 8000, PWM_OUTPUTSTATE_ENABLE); //TC3_CompareStart()
#define Set_Buzzer_41Khz   PWM_IndependentModeConfigEX(PWM30, 3889, PWM_OUTPUTSTATE_ENABLE); //TC3_CompareStart()
#define Set_Buzzer_33Khz   PWM_IndependentModeConfigEX(PWM30, 4799, PWM_OUTPUTSTATE_ENABLE); //TC3_CompareStart()


#define Set_Buzzer   PWM_IndependentModeConfigEX(PWM30, 3999, PWM_OUTPUTSTATE_ENABLE); //TC3_CompareStart()
#define Clr_Buzzer   PWM_IndependentModeConfigEX(PWM30, 0, PWM_OUTPUTSTATE_ENABLE); //TC3_CompareStop()

#define SW6_Get() P22
#define SW5_Get() P17
#define SW4_Get() P20
#define SW3_Get() P21
#define SW2_Get() P16
#define SW1_Get() P04

extern struct Flag_Struct MyFlag;


struct Flag_Struct
{
    unsigned char KeyReturn;        
    unsigned char KeyDown;  
    unsigned char IRSendEn;             //IR Send Enablie 
    unsigned char KeyBuzzer;            // Buzzer 
    unsigned char ExtIR;                // ext ir
    unsigned char PowerUp;              
    unsigned char LEDOn;
    unsigned char StartKeyDown;  
    unsigned char BrightnessIncreaseAdd;
    unsigned char HalfSecond;
	  unsigned char HalfSecond2;
    unsigned char KeyFlash;
    unsigned char KeySpeedStartOn;
    unsigned char SpeendOn;
    unsigned char SpeedStartOff;
    unsigned char AutoMode;
    unsigned char LongKeySure;
    unsigned char FirstBurnerOn;
    unsigned char FirstBurnerOff;
    unsigned char FirstLightOn;
    unsigned char SendLightOnCommand;
    unsigned char FirstLightOff;
    unsigned char SendLightOffCommand;    
    unsigned char FirSendLightOnCommand;
    unsigned char FirSendLightOffCommand;
    unsigned char LightOffDelayStart;
    unsigned char SendEnd;
    unsigned char FirstSpeedOff;
    unsigned char SendSpeedOffCommand;
    unsigned char SpeedDelayOffStart;
    unsigned char FirstSendSpeedOffCommand;
    unsigned char SendSpeedCommand;
    unsigned char FirstSendSpeedCommand;
    unsigned char KeySureBuzzer;
    unsigned char FirstPowerUp;
    unsigned char ActivateMode;
    unsigned char DeactivateModeFirstLight;
    unsigned char AllSwitchOFF;
    unsigned char INTENSIVEONMode;
		unsigned char SleepEn;
		unsigned char SendLightOnEn;
		unsigned char SendLightOffEn;
		unsigned char SendSpeedOffEn;
		unsigned char SendSpeedCommandEn;
		unsigned char BatLowWarrn;   //电池低电压报警
		unsigned char LowFlashLed;
		unsigned char BatLowWarrnEn;
		unsigned char AllDataSendEnd;   //所有数据发送完成标志
		unsigned char SysWakeUpSleep;
    unsigned char ModeChange;
		unsigned char AllHodClose;
		unsigned char AutoFan;
		unsigned char DisPlayMode;
		unsigned char TimesDisplay;
		unsigned char KeyLongDown;
		unsigned char TestMode;
		unsigned char TestLowPower;
		unsigned char ShortDown;
		unsigned char ToEEPROM;
};  
#define SysWakeUpSleepFlag              MyFlag.SysWakeUpSleep		 
#define Set_SysWakeUpSleepFlag          MyFlag.SysWakeUpSleep = 1
#define Clr_SysWakeUpSleepFlag          MyFlag.SysWakeUpSleep = 0

#define AllDataSendEndFlag              MyFlag.AllDataSendEnd		 
#define Set_AllDataSendEndFlag          MyFlag.AllDataSendEnd = 1
#define Clr_AllDataSendEndFlag          MyFlag.AllDataSendEnd = 0


#define BatLowWarrnEnFlag              MyFlag.BatLowWarrnEn		 
#define Set_BatLowWarrnEnFlag          MyFlag.BatLowWarrnEn = 1
#define Clr_BatLowWarrnEnFlag          MyFlag.BatLowWarrnEn = 0


#define LowFlashLedFlag              MyFlag.LowFlashLed		 
#define Set_LowFlashLedFlag          MyFlag.LowFlashLed = 1
#define Clr_LowFlashLedFlag          MyFlag.LowFlashLed = 0

#define BatLowWarrnFlag              MyFlag.BatLowWarrn		 
#define Set_BatLowWarrnFlag          MyFlag.BatLowWarrn = 1
#define Clr_BatLowWarrnFlag          MyFlag.BatLowWarrn = 0


#define SendSpeedCommandEnFlag              MyFlag.SendSpeedCommandEn		 
#define Set_SendSpeedCommandEnFlag          MyFlag.SendSpeedCommandEn = 1
#define Clr_SendSpeedCommandEnFlag          MyFlag.SendSpeedCommandEn = 0

#define SendSpeedOffEnFlag              MyFlag.SendSpeedOffEn		 
#define Set_SendSpeedOffEnFlag          MyFlag.SendSpeedOffEn = 1
#define Clr_SendSpeedOffEnFlag          MyFlag.SendSpeedOffEn = 0


#define SendLightOffEnFlag              MyFlag.SendLightOffEn		 
#define Set_SendLightOffEnFlag          MyFlag.SendLightOffEn = 1
#define Clr_SendLightOffEnFlag          MyFlag.SendLightOffEn = 0

#define SendLightOnEnFlag              MyFlag.SendLightOnEn		 
#define Set_SendLightOnEnFlag          MyFlag.SendLightOnEn = 1
#define Clr_SendLightOnEnFlag          MyFlag.SendLightOnEn = 0


#define SleepEnFlag              MyFlag.SleepEn		 
#define Set_SleepEnFlag          MyFlag.SleepEn = 1
#define Clr_SleepEnFlag          MyFlag.SleepEn = 0


#define INTENSIVEONModeFlag                MyFlag.INTENSIVEONMode		 
#define Set_INTENSIVEONModeFlag          MyFlag.INTENSIVEONMode = 1
#define Clr_INTENSIVEONModeFlag           MyFlag.INTENSIVEONMode = 0


#define AllSwitchOFFFlag                MyFlag.AllSwitchOFF		 
#define Set_AllSwitchOFFFlag          MyFlag.AllSwitchOFF = 1
#define Clr_AllSwitchOFFFlag           MyFlag.AllSwitchOFF = 0

#define DeactivateModeFirstLightFlag                MyFlag.DeactivateModeFirstLight		 
#define Set_DeactivateModeFirstLightFlag          MyFlag.DeactivateModeFirstLight = 1
#define Clr_DeactivateModeFirstLightFlag           MyFlag.DeactivateModeFirstLight = 0

#define ActivateModeFlag                MyFlag.ActivateMode		 
#define Set_ActivateModeFlag          MyFlag.ActivateMode = 1
#define Clr_ActivateModeFlag           MyFlag.ActivateMode = 0


#define FirstPowerUpFlag                MyFlag.FirstPowerUp		 
#define Set_FirstPowerUpFlag          MyFlag.FirstPowerUp = 1
#define Clr_FirstPowerUpFlag            MyFlag.FirstPowerUp = 0

#define KeySureBuzzerFlag                MyFlag.KeySureBuzzer		 
#define Set_KeySureBuzzerFlag           MyFlag.KeySureBuzzer = 1
#define Clr_KeySureBuzzerFlag            MyFlag.KeySureBuzzer = 0

#define FirstSendSpeedCommandFlag                MyFlag.FirstSendSpeedCommand		 
#define Set_FirstSendSpeedCommandFlag           MyFlag.FirstSendSpeedCommand = 1
#define Clr_FirstSendSpeedCommandFlag            MyFlag.FirstSendSpeedCommand = 0

#define SendSpeedCommandFlag                MyFlag.SendSpeedCommand		 
#define Set_SendSpeedCommandFlag           MyFlag.SendSpeedCommand = 1
#define Clr_SendSpeedCommandFlag            MyFlag.SendSpeedCommand = 0

#define FirstSendSpeedOffCommandFlag                MyFlag.FirstSendSpeedOffCommand		 
#define Set_FirstSendSpeedOffCommandFlag           MyFlag.FirstSendSpeedOffCommand = 1
#define Clr_FirstSendSpeedOffCommandFlag             MyFlag.FirstSendSpeedOffCommand = 0

#define SpeedDelayOffStartFlag                MyFlag.SpeedDelayOffStart		 
#define Set_SpeedDelayOffStartFlag            MyFlag.SpeedDelayOffStart = 1
#define Clr_SpeedDelayOffStartFlag             MyFlag.SpeedDelayOffStart = 0


#define FirstSpeedOffFlag                MyFlag.FirstSpeedOff		 
#define Set_FirstSpeedOffFlag            MyFlag.FirstSpeedOff = 1
#define Clr_FirstSpeedOffFlag             MyFlag.FirstSpeedOff = 0

#define SendSpeedOffCommandFlag                MyFlag.SendSpeedOffCommand		 
#define Set_SendSpeedOffCommandFlag            MyFlag.SendSpeedOffCommand = 1
#define Clr_SendSpeedOffCommandFlag             MyFlag.SendSpeedOffCommand = 0

#define LightOffDelayStartFlag                MyFlag.LightOffDelayStart		 
#define Set_LightOffDelayStartFlag            MyFlag.LightOffDelayStart = 1
#define Clr_LightOffDelayStartFlag             MyFlag.LightOffDelayStart = 0


#define FirstLightOffFlag                MyFlag.FirstLightOff		 
#define Set_FirstLightOffFlag            MyFlag.FirstLightOff = 1
#define Clr_FirstLightOffFlag             MyFlag.FirstLightOff = 0

#define SendLightOffCommandFlag                MyFlag.SendLightOffCommand		 
#define Set_SendLightOffCommandFlag            MyFlag.SendLightOffCommand = 1
#define Clr_SendLightOffCommandFlag             MyFlag.SendLightOffCommand = 0

#define FirSendLightOnCommandFlag                MyFlag.FirSendLightOnCommand		 
#define Set_FirSendLightOnCommandFlag            MyFlag.FirSendLightOnCommand = 1
#define Clr_FirSendLightOnCommandFlag             MyFlag.FirSendLightOnCommand = 0


#define FirSendLightOffCommandFlag                MyFlag.FirSendLightOffCommand		 
#define Set_FirSendLightOffCommandFlag            MyFlag.FirSendLightOffCommand = 1
#define Clr_FirSendLightOffCommandFlag             MyFlag.FirSendLightOffCommand = 0


#define SendEndFlag                MyFlag.SendEnd		 
#define Set_SendEndFlag            MyFlag.SendEnd = 1
#define Clr_SendEndFlag             MyFlag.SendEnd = 0


#define SendLightOnCommandFlag                MyFlag.SendLightOnCommand		 
#define Set_SendLightOnCommandFlag            MyFlag.SendLightOnCommand = 1
#define Clr_SendLightOnCommandFlag             MyFlag.SendLightOnCommand = 0


#define FirstLightOnFlag                MyFlag.FirstLightOn		 
#define Set_FirstLightOnFlag            MyFlag.FirstLightOn = 1
#define Clr_FirstLightOnFlag             MyFlag.FirstLightOn = 0

#define FirstBurnerOnFlag                MyFlag.FirstBurnerOn		 
#define Set_FirstBurnerOnFlag            MyFlag.FirstBurnerOn = 1
#define Clr_FirstBurnerOnFlag             MyFlag.FirstBurnerOn = 0

#define LongKeySureFlag                MyFlag.LongKeySure		 
#define Set_LongKeySureFlag            MyFlag.LongKeySure = 1
#define Clr_LongKeySureFlag             MyFlag.LongKeySure = 0

#define AutoModeFlag                MyFlag.AutoMode		 
#define Set_AutoModeFlag            MyFlag.AutoMode = 1
#define Clr_AutoModeFlag        MyFlag.AutoMode = 0

#define SpeedStartOffFlag                MyFlag.SpeedStartOff		 
#define Set_SpeedStartOffFlag            MyFlag.SpeedStartOff = 1
#define Clr_SpeedStartOffFlag          MyFlag.SpeedStartOff = 0

#define SpeendOnFlag                MyFlag.SpeendOn		 
#define Set_SpeendOnFlag            MyFlag.SpeendOn = 1
#define Clr_SpeendOnFlag           MyFlag.SpeendOn = 0

#define KeySpeedStartOnFlag                MyFlag.KeySpeedStartOn		 
#define Set_KeySpeedStartOnFlag            MyFlag.KeySpeedStartOn = 1
#define Clr_KeySpeedStartOnFlag           MyFlag.KeySpeedStartOn = 0

#define KeyFlashFlag                MyFlag.KeyFlash		 
#define Set_KeyFlashFlag            MyFlag.KeyFlash = 1
#define Clr_KeyFlashFlag           MyFlag.KeyFlash = 0


#define HalfSecondFlag                MyFlag.HalfSecond		 
#define Set_HalfSecondFlag            MyFlag.HalfSecond = 1
#define Clr_HalfSecondFlag            MyFlag.HalfSecond = 0

#define HalfSecond2Flag                MyFlag.HalfSecond2		 
#define Set_HalfSecond2Flag            MyFlag.HalfSecond2 = 1
#define Clr_HalfSecond2Flag            MyFlag.HalfSecond2 = 0

#define BrightnessIncreaseAddFlag      MyFlag.BrightnessIncreaseAdd		 
#define Set_BrightnessIncreaseAddFlag  MyFlag.BrightnessIncreaseAdd = 1
#define Clr_BrightnessIncreaseAddFlag  MyFlag.BrightnessIncreaseAdd = 0

#define StartKeyDownFlag                MyFlag.StartKeyDown		 
#define Set_StartKeyDownFlag            MyFlag.StartKeyDown = 1
#define Clr_StartKeyDownFlag            MyFlag.StartKeyDown = 0

#define LEDOnFlag                MyFlag.LEDOn		 
#define Set_LEDOnFlag            MyFlag.LEDOn = 1
#define Clr_LEDOnFlag            MyFlag.LEDOn = 0

#define PowerUpFlag                MyFlag.PowerUp		 
#define Set_PowerUpFlag            MyFlag.PowerUp = 1
#define Clr_PowerUpFlag            MyFlag.PowerUp = 0

#define KeyReturnFlag                MyFlag.KeyReturn		 
#define Set_KeyReturnFlag            MyFlag.KeyReturn = 1
#define Clr_KeyReturnFlag            MyFlag.KeyReturn = 0

#define KeyDownFlag                MyFlag.KeyDown		 
#define Set_KeyDownFlag            MyFlag.KeyDown = 1
#define Clr_KeyDownFlag            MyFlag.KeyDown = 0

#define IRSendEnFlag                MyFlag.IRSendEn		 
#define Set_IRSendEnFlag            MyFlag.IRSendEn = 1
#define Clr_IRSendEnFlag           MyFlag.IRSendEn = 0

#define KeyBuzzerFlag                MyFlag.KeyBuzzer		 
#define Set_KeyBuzzerFlag            MyFlag.KeyBuzzer = 1
#define Clr_KeyBuzzerFlag           MyFlag.KeyBuzzer = 0

#define ExtIRFlag                MyFlag.ExtIR		 
#define Set_ExtIRFlag            MyFlag.ExtIR = 1
#define Clr_ExtIRFlag           MyFlag.ExtIR = 0

#define ModeChangeFlag          MyFlag.ModeChange 
#define Set_ModeChangeFlag      MyFlag.ModeChange = 1
#define Clr_ModeChangeFlag      MyFlag.ModeChange = 0

#define AllHodCloseFlag         MyFlag.AllHodClose
#define Set_AllHodClodeFlag     MyFlag.AllHodClose = 1
#define Clr_AllHodCloseFlag     MyFlag.AllHodClose = 0

#define AutoFanFlag            MyFlag.AutoFan
#define Set_AutoFanFlag        MyFlag.AutoFan = 1
#define Clr_AutoFanFlag        MyFlag.AutoFan = 0

#define DisPlayModeFlag   MyFlag.DisPlayMode
#define Set_DisPlayModeFlag   MyFlag.DisPlayMode = 1
#define Clr_DisPlayModeFlag   MyFlag.DisPlayMode = 0

//#define CookingFlag       MyFlag.Cooking
//#define Set_CookingFlag   MyFlag.Cooking = 1
//#define Clr_CookingFlag   MyFlag.Cooking = 0

#define TimesDisplayFlag     MyFlag.TimesDisplay
#define Set_TimesDisplayFlag     MyFlag.TimesDisplay = 1
#define Clr_TimesDisplayFlag     MyFlag.TimesDisplay = 0

#define KeyLongDownFlag     MyFlag.KeyLongDown
#define Set_KeyLongDownFlag    MyFlag.KeyLongDown  = 1
#define Clr_KeyLongDownFlag    MyFlag.KeyLongDown  = 0

#define TestModeFlag      MyFlag.TestMode
#define Set_TestModeFlag        MyFlag.TestMode  = 1
#define Clr_TestModeFlag        MyFlag.TestMode  = 0

#define TestLowPowerFlag     MyFlag.TestLowPower
#define Set_TestLowPowerFlag      MyFlag.TestLowPower = 1
#define Clr_TestLowPowerFlag      MyFlag.TestLowPower = 0

#define ShortDownFlag   MyFlag.ShortDown
#define Set_ShortDownFlag   MyFlag.ShortDown = 1
#define Clr_ShortDownFlag   MyFlag.ShortDown = 0

#define ToEEPROMFlag   MyFlag.ToEEPROM 
#define Set_ToEEPROMFlag     MyFlag.ToEEPROM = 1
#define Clr_ToEEPROMFlag     MyFlag.ToEEPROM = 0

#endif