//*************************************************************************************************
//  Copyright (c) 	��������Ԫ΢�������޹�˾
//	�ļ�����	:  SensorMethod.h
//	����		: 
//	ģ�鹦��	:  �����㷨ͷ�ļ�
// 	�汾	    :
// 	���ļ�¼	:
//	ע������	:    
//************************************************************************************************
#ifndef	_TKDriver_H
#define	_TKDriver_H

#ifndef TK_USE_BTM
#define TK_USE_BTM
#endif

//<<<Use SPTML>>>
#define SCD_TK_Type 3//SCD_TK_Type 
#define SCD_Wheel 0//SCD_Wheel 
#define SCD_Slider 0//SCD_Slider 
#define SCD_Key 1//SCD_Key 
#define WakeUpKeyNum_Set 1//WakeUpKeyNum_Set 
#define WakeUpKeyChannel_Set 0x00001000//WakeUpKeyChannel_Set 
#define TK_SeepTimervSetting_Set BTM_TIMEBASE_125MS//TK_SeepTimervSetting_Set 
#define TK_WakeUpConfirmTouchCnt_Set 10//TK_WakeUpConfirmTouchCnt_Set 
extern unsigned char xdata SOCAPI_TouchKeyStatus;

extern unsigned long int TouchKeyScan();
extern void TouchKeyInit();
extern void TouchKeyRestart();

extern bit GetLowPowerScanFlag(void);
extern void LowPower_Touchkey_Scan(void);
extern void TouchKey_IntoLowPowerMode(void);
extern void TouchKey_QuitLowPowerMode(void);

extern void Customer_IntoLowPowerMode_Init();
extern void Customer_QuitLowPowerMode_Init();
extern void Customer_BTM_Dispose();
extern void Set_Cfg();
//<<<end of SPTML>>>

//�ⲿ����
extern	unsigned	char	xdata	SOCAPI_TouchKeyStatus;			//API?��?�����䨬?��obit7-��???����?������3������??								
extern 	unsigned 	char	xdata	ConfirmTouchCnt;							
extern 	unsigned 	int		xdata 	RawData[];			 				
extern 	unsigned 	int		data	BaseLine[];	
extern	unsigned  	int	 	xdata  	FilterData[];					 
extern	unsigned 	int 	xdata 	CurrentSensorKey;		 				
extern 	unsigned	char  	xdata 	RestAreaCnt[]; 					 
extern 	unsigned	char  	xdata 	TouchCnt[];
extern 	unsigned	char  	xdata 	NoTouchCnt[];  			  
extern  unsigned	char 	xdata 	CurrentChannel[];			 
extern  unsigned    char    xdata   LowFingerDataCnt[]; 
extern 				int     xdata 	DifferAccum[];
extern  unsigned	char  	xdata	FloatAreaCnt[]; 
extern 				char	xdata	SetNoiseThreshold;	
extern  unsigned 	char	xdata	MultipleDealTpye;
extern  unsigned 	char    xdata   ICHG_RawData_Ratio;
			

#endif 
