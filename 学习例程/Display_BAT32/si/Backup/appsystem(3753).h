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
	LEDLevel_LOW_Medium,
	LEDLevel_Medium,
	LEDLevel_Medium_High,
	LEDLevel_High,
	LEDLevel_NUM,
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
	//INT8U Language;
	//INT8U CalibrationFlag;//ûУ׼����1У׼����
	INT16U ActivateCleanTime;
	INT16U LEDLevel;//����LED�ȼ�
}
Oreration_t;

typedef struct
{
	INT8U MainButtonTestFlag;//���尴�����Ա�־
	INT8U MainButtonTestVal;//������԰���ֵ
	INT8U LowLevel;
	INT8U DripTray;
}
Service_t;

typedef struct
{
	INT16U year:7;
	INT16U months:4;//
	INT16U days:5;
}
DATETIME_T;

typedef struct
{
	DATETIME_T TotalOnTime;
	INT16U TotalDispTime;//�ܵ��Ʊ�ʱ�䣬��λСʱ
	INT16U DispenseCount;//�ܵ��·��Ʊ����� 
	DATETIME_T LastClean;//�ϴ�����������
}
Data_t;

typedef struct
{
	INT16U Size[4];//
	INT16U Size_DispenseCnt[4];
}
TypeSize_t;

typedef struct
{
	Oreration_t Oreration;
	Service_t 	Service;
	Data_t		Data;
	TypeSize_t	Type[3];
}
UIset_t;




typedef struct
{
	INT8U BackLight:1;//����
	INT8U StateChangeFlag:1;//0�豸״̬û�и��£�1�豸״̬�����˸ı�

	INT8U systimeupdateflag:1;//ϵͳʱ�����

	INT8U StandbyFlag:1;

	INT8U AutoFlushtime;//�Զ���ϴʱ��,��λ��

	INT8U WorkState;
	
	INT16U BackTimerCount;//����ʱ�����
	INT16U WinTimerCount;

	
	INT16U heartbeat;//������ʱ�� ��λ��

	INT16U uartdisplayTimeOutCnt;//ͨѶ��ʱ����
	
	INT8U flash:1;//��ʾ��˸

	INT8U WinTimerOutFlag:1;

	INT8U uartdisplayError:1;//��ʾ��ͨѶ1�쳣��0����

	INT8U uartWifiError:1;//WIFIͨѶ1�쳣��0����

	INT8U pc_en:1;

	INT16U FCTsave;

	WORKERROR workerror;//��������

	
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


