#ifndef APPSYSTEM_H
#define APPSYSTEM_H




#pragma pack(1)

typedef struct
{
	INT8U EE;	
}
WORKERROR;


enum Language
{
	Language_English,
	Language_French,
	Language_Spanish,
};

enum LEDLevel
{
	LEDLevel_LOW,
	LEDLevel_Medium,
	LEDLevel_High,
	LEDLevel_max,
};


enum type_e
{
	type_Shaken,
	type_Blended,
	type_ColdFoam,
	type_max=type_ColdFoam,
};

enum size_e
{
	size_NULL,
	size_Tall,
	size_Grande,
	size_Venti,
	size_Trenta,
	size_max=size_Trenta,
};


typedef struct
{
	INT8U Language;
	INT8U CalibrationFlag;//没校准过，1校准过了
	INT8U ActivateCleanFlag;
	INT8U LEDLevel;//按键LED等级
}
Oreration_t;

typedef struct
{
	INT8U Language;
	INT8U CalibrationFlag;//没校准过，1校准过了
	INT8U ActivateCleanFlag;
}
Service_t;

typedef struct
{
	INT8U Language;
	INT8U CalibrationFlag;//没校准过，1校准过了
	INT8U ActivateCleanFlag;
}
Data_t;

typedef struct
{
	INT8U Type;
	INT8U Size;//
	INT8U Flow;//
}
TypeSize_t;

typedef struct
{
	Oreration_t Oreration;
	Service_t 	Service;
	Data_t		Data;
	TypeSize_t	TypeSize;
}
UIset_t;




typedef struct
{
	INT8U BackLight:1;//背光
	INT8U StateChangeFlag:1;//0设备状态没有更新，1设备状态发生了改变

	INT8U systimeupdateflag:1;//系统时间更新

	INT8U StandbyFlag:1;

	INT8U AutoFlushtime;//自动冲洗时长,单位秒
	
	INT16U BackTimerCount;//背光时间计数
	INT16U WinTimerCount;

	
	INT16U heartbeat;//心跳包时间 单位秒

	INT16U uartdisplayTimeOutCnt;//通讯超时计数
	
	INT8U flash:1;//显示闪烁

	INT8U WinTimerOutFlag:1;

	INT8U uartdisplayError:1;//显示板通讯1异常，0正常

	INT8U uartWifiError:1;//WIFI通讯1异常，0正常

	INT8U pc_en:1;

	INT16U FCTsave;

	WORKERROR workerror;//工作错误

	
}
SYSTEMSETING;

#pragma pack()


enum demomode
{
	DEMOMODE_Ready,
	DEMOMODE_demo_a,
	DEMOMODE_demo_b,
};



extern INT8U RecBuff[SERIAL_BUFF_NUM];
extern SYSTEMSETING systemseting;
extern CODE INT8U Digitaltube[];
extern UARTPROC UartDispProc;
extern UARTPROC UartFaucetProc;
extern UARTPROC UartWifiProc;

extern UIset_t gUISet;

void RestoreFactory(void);
void AppSystemInit(void);

void Standby(void);

void ParsingDisplayData(INT8U *pbuff,INT16U len);

void DesktopUpdate(void);
void DisplayUpdate(void);

INT8U Jump2Boot(void);


void MonitorWater(void);
INT16U FilterLifeCalculate(INT32U powerontime,INT32U pumptime,INT8U type);


void PowerOnDisplay(void);
void MonitorState(void);

void GetLeakADC(INT16U ad);
void GetPumpADC(INT16U ad);

void FilterReset_PCB(void);
void FilterReset_RO(void);

void SetInletValve(FlagStatus state);
void SetInletValve2(FlagStatus state);
void SetWasteWaterValve(FlagStatus state);
void SetBoosterPump(INT8U state);
void UpdateFilterLife(void);

void FeedWDT(void);


void ExitManualFlush(void);
void ClearLongTimeWorkFlag(void);

void EnterFCTMode(void);
void ExitFCTMode(void);

void StandbyRestart(void);
void WinTimerOut(void);
BOOL PowerDownCheck(void);


#endif


