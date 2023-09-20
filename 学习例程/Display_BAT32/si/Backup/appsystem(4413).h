#ifndef APPSYSTEM_H
#define APPSYSTEM_H










//工作状态
enum workstate
{
	WORKSTATE_standby,//待机
	WORKSTATE_free,//空闲状态

	WORKSTATE_backflow,//回流
	
	WORKSTATE_autoflush,//自动清洗

	WORKSTATE_working,//制纯水
	WORKSTATE_live,//制生活水
	
	WORKSTATE_manualflush,//手动清洗
	WORKSTATE_LongTimeWork,//长时间制水
	WORKSTATE_PowerOnFlush,//上电清洗
	WORKSTATE_Leaking,//漏水
	WORKSTATE_LockWater,//锁水

	WORKSTATE_GasDetection,//气检
	WORKSTATE_WaterDetection,//水检
	WORKSTATE_FilterDetection,//滤芯快检

	WORKSTATE_PowerOnProc,
	WORKSTATE_FCT,//FCT测试

	WORKSTATE_PowerDown,//关机
	
	WORKSTATE_MAX
};



#pragma pack(1)
#if 0
typedef struct
{
	INT8U run_r_en:1;//红 
	INT8U pcb_r_en:1;//白

	INT8U ro_r_en:1;//红 
	INT8U wifi_r_en:1;//白

	INT8U ro_w_en:1;//红 
	INT8U wifi_w_en:1;//白	

	INT8U run_w_en:1;//红 
	INT8U pcb_w_en:1;//白

	INT8U run_r_flash:1;//红 
	INT8U pcb_r_flash:1;//白

	INT8U ro_r_flash:1;//红 
	INT8U wifi_r_flash:1;//白

	INT8U ro_w_flash:1;//红 
	INT8U wifi_w_flash:1;//白	

	INT8U run_w_flash:1;//红 
	INT8U pcb_w_flash:1;//白
}
DISPLAY_REG;
#else 
typedef struct
{
	INT8U run_w_en:1;//
	INT8U pcb_w_en:1;//
	INT8U pcb_r_en:1;//
	INT8U run_r_en:1;//红 
	INT8U wifi_w_en:1;//
	INT8U wifi_r_en:1;//
	INT8U ro_w_en:1;//
	INT8U ro_r_en:1;//红 
		
	INT8U run_w_flash:1;//
	INT8U pcb_w_flash:1;//
	INT8U pcb_r_flash:1;//
	INT8U run_r_flash:1;//红 
	INT8U wifi_w_flash:1;//
	INT8U wifi_r_flash:1;//
	INT8U ro_w_flash:1;//
	INT8U ro_r_flash:1;//红

}
DISPLAY_REG;
#endif

typedef struct
{
	INT8U head[2];
	INT8U len;
	INT8U addr;
	INT8U keyval;//按键值
	INT8U sum;
}
serial_getcomm;

typedef struct
{
	INT8U head[2];
	INT8U len;
	INT8U addr;
	INT8U LED;//为1点亮L1-L8
	INT8U LEDFlash_EN;//闪烁
	INT8U sum;
}
serial_sendcomm;








typedef struct
{
	INT16U TempErrorFlag		: 1;//温度传感器故障
	INT16U rawTdsErrorFlag		: 1;//原水TDS传感器故障
	INT16U pureTdsErrorFlag		: 1;//纯水TDS传感器故障
	INT16U WaterLeakErrorFlag	: 1;//漏水报警
	INT16U TimeOutErrorFlag		: 1;//制水超时
	INT16U WasteWaterErrorFlag	: 1;//废水比阀故障
	INT16U InWaterErrorFlag		: 1;//进水阀故障
	INT16U sparklingWaterStatus	: 1;//气泡水功能状态

	INT16U Temp2ErrorFlag		: 1;
	
	INT16U resever:7;
}ERRORFLAG_t;

typedef union 
{
	INT16U		u16flag;
	ERRORFLAG_t	BitFlag;
}UN_ERROR_t;



typedef struct
{
	INT16U flush	: 1;//冲洗 0关，1开
	INT16U uv		: 1;//uv灯 0关，1开

	INT16U resever:14;
}PERIPSTATE_t;

typedef union 
{
	INT16U			u16flag;
	PERIPSTATE_t	BitFlag;
}PERIPHERAL_t;


typedef struct
{
	INT16U DeviceAddr;//设备地址
	INT16U ProductType;//产品类型 0净水器，1其他
	INT16U productName;//产品名称 0云鲸，1云鳟，2博观，3三根芯，4mini系列(0x0401mni1,0x0402mini2)
	INT16U ProductModel;//产品型号(500,600,700,800)
	INT16U version;//版本高8位硬件版本,低8位软件版本

	INT16U cmd;//控制寄存器
	
	INT16U WorkState;//工作状态 0待机中，1制水中
	INT16U wifi;//0未连接，1配网，2连接成功，3信号弱
	
	PERIPHERAL_t PeriState;//外设状态
	
	UN_ERROR_t error;//故障



	//SYSTEMTIME time;
}
REG;


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

	INT8U HVS:1;//高压开关状态 0关，1开

	INT8U StandbyFlag:1;

	INT8U AutoFlushtime;//自动冲洗时长,单位秒
	
	INT16U BackTimerCount;//背光时间计数
	INT16U WinTimerCount;

	
	INT16U heartbeat;//心跳包时间 单位秒

	INT16U uartdisplayTimeOutCnt;//通讯超时计数

 	INT8U wifi;//0未连接，1配网，2连接成功，3信号弱
	
	INT16U PowerOnTimerCount;//上电计时 用于按键上电15秒内的操作
	INT8U flash:1;//显示闪烁

	INT8U WinTimerOutFlag:1;
	
	INT8U ElectrolyticFlag:1;//电解片打开标志

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
extern REG gReg;
extern DISPLAY_REG gDisplayReg;
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


