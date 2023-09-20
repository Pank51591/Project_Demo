#ifndef APPSYSTEM_H
#define APPSYSTEM_H


// 电解片
#define ELECTROLYTIC_STRIP_PIN_LEVEL_0   PORT_ClrBit(PORT7,PIN4)
#define ELECTROLYTIC_STRIP_PIN_LEVEL_1   PORT_SetBit(PORT7,PIN4)

//增压泵
#define PUMP_ENABLE_PIN_LEVEL_0   PORT_ClrBit(PORT3,PIN1)
#define PUMP_ENABLE_PIN_LEVEL_1   PORT_SetBit(PORT3,PIN1)

#define PUMP_VOLTAGE_6V_14V_PIN_LEVEL_0   PORT_ClrBit(PORT6,PIN3)
#define PUMP_VOLTAGE_6V_14V_PIN_LEVEL_1   PORT_SetBit(PORT6,PIN3)

#define PUMP_VOLTAGE_24V_PIN_LEVEL_0   	PORT_ClrBit(PORT7,PIN5)
#define PUMP_VOLTAGE_24V_PIN_LEVEL_1   	PORT_SetBit(PORT7,PIN5)

#define PUMP_OFF		do {(PUMP_ENABLE_PIN_LEVEL_0); (PORT_Init(PORT6,PIN3,INPUT));PUMP_VOLTAGE_24V_PIN_LEVEL_0;} while(0)
#define PUMP_6V_OUT		do {(PUMP_ENABLE_PIN_LEVEL_1); (PORT_Init(PORT6,PIN3,INPUT));PUMP_VOLTAGE_24V_PIN_LEVEL_0;} while(0)
#define PUMP_14V_OUT	do {(PUMP_ENABLE_PIN_LEVEL_1); (PORT_Init(PORT6,PIN3,OUTPUT));(PUMP_VOLTAGE_6V_14V_PIN_LEVEL_0);PUMP_VOLTAGE_24V_PIN_LEVEL_0;} while(0)
#define PUMP_24V_OUT	do {(PUMP_ENABLE_PIN_LEVEL_0); (PORT_Init(PORT6,PIN3,INPUT));(PUMP_VOLTAGE_24V_PIN_LEVEL_1); } while(0)

#define PUMP_OUT_24V		(3)// 输出24V
#define PUMP_OUT_14V		(2)// 输出14V
#define PUMP_OUT_6V			(1)// 输出6V
#define PUMP_OUT_OFF		(0)//


#define GET_HVS_PIN()			PORT_GetBit(PORT12, PIN4)
#define GET_LEAK_PIN()			//pp//(FlagStatus)GPIO_ReadInBit(HT_GPIOA, GPIO_PIN_1)
#define GET_POWERDOWN_PIN()		PORT_GetBit(PORT12, PIN2)


#define SET_INLET_VALVE_PIN(x)	GPIO_Output(PORT13,PIN0,x)//进水阀1（原水）
#define SET_WASTE_VALVE_PIN(x)	GPIO_Output(PORT12,PIN0,x)//废水阀（不可调）
#define SET_PUMP_PIN(x)			GPIO_Output(PORT3,PIN1,x)//

#define SET_INLET_VALVE2_PIN(x)	GPIO_Output(PORT3,PIN0,x)


#define FILTERTYPE_PCB	0
#define FILTERTYPE_RO	1



#define PCB_PowerOnRemained_MAX			(8640*60)//小时
#define RO_PowerOnRemained_MAX			(25920*60)//小时
#define PCB_MakingRemained_MAX			(30*60)//小时
#define RO_MakingRemained_MAX			(120*60)//小时

#define PCBRO_PowerOnTime_exceed		30//天
#define PCBRO_MakingTime_exceed			30//天

#define  WORKING_ContinuousTime			5//连续制水5分钟
#define  WORKING_LongTime				(60)//长时间制水超过 1小时
#define  WORKING_ExitLongTime			(60*(3+1))//退出长时间制水 3小时
#define  WORKING_LongTimeWorkTimesCount	(7)//7次

#define	STANDBY_longtime			(48*3600)//待机长达48小时
#define BACKFLOW_entertime2			(24*3600)//进入纯水回流24小时之后	
#define BACKFLOW_entertime1			(10)//回流时间


#define FLUSH_time_auto				20//自动冲洗时长,秒
#define	FLUSH_time_Manual			20//手动冲洗时长,秒
#define	FLUSH_time_PowerOn			30//上电冲洗,秒
#define	FLUSH_time_FirstPowerOn		30//首次上电冲洗,秒
#define	FLUSH_time_standby48h		60//待机时长达48小时自动冲洗,秒

#define PUMP_OFF_ad_val				20// 水泵没打开的电流AD值
#define PUMP_open_delaytime			200//打开水泵延时(ms)					

#define BACKFLOW_time_run			60//回流60秒




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



enum pcb_item 
{
	PCB_level_1,
	PCB_level_2,
	PCB_level_3,
};


typedef struct
{
	INT16U rawTdsFlag 		: 1;//入水UV254传感器标志位,0：无此传感器
	INT16U pureTdsFlag		: 1;
	INT16U rawCodFlag 		: 1;
	INT16U pureCodFlag		: 1;
	INT16U rawTocFlag 		: 1;
	INT16U pureTocFlag		: 1;
	INT16U rawUV254Flag		: 1;
	INT16U pureUV254Flag	: 1;
	
	INT16U resever:8;
}
SENFLAG;

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

	INT32U PowerOnTimeTotal_PCB;//总上电时间 单位分钟
	INT32U PumpWorkeTimeTotal_PCB;//总水泵工作时间
	INT32U PowerOnTimeTotal_RO;//总上电时间 单位分钟
	INT32U PumpWorkeTimeTotal_RO;//总水泵工作时间	

	INT32U RawWaterVolume;//原水量 mL
	INT32U NetWaterVolume;//净水量 mL
	INT32U RawWaterVolumeSingle;//单次水量 mL
	INT32U NetWaterVolumeSingle;//单次水量 mL	

	INT16U PriFilterResetTimes;//初滤滤芯重置次数
	INT16U RoFilterResetTimes;//RO滤芯重置次数
	
	INT16U rawTDS;//原水TDS	
	INT16U netTDS;//净水TDS

	INT16U rawTemperature;//原水水温 bit16为1传感器不存在,为0存在，低8位为水温
	
	INT16U FilterLife_PCB;//滤芯寿命	百分比
	INT16U FilterLife_RO;//滤芯寿命百分比	

	SENFLAG SenFlag;//传感器标志，0无此传感器，1有

	INT16U fruits;//蔬果 电解模式
	INT16U BackFlow;//纯水回流使能

	//SYSTEMTIME time;
}
REG;


typedef struct
{
	INT8U EE;	
}
WORKERROR;

typedef struct
{
	INT8U BackLight:1;//背光
	INT8U StateChangeFlag:1;//0设备状态没有更新，1设备状态发生了改变

	INT8U systimeupdateflag:1;//系统时间更新

	INT8U HVS:1;//高压开关状态 0关，1开

	INT8U StandbyFlag:1;
	INT8U FreeFlag:1;
	INT8U BackflowFlag:1;//回流
	INT8U AutoFlushFlag:1;//自动冲洗标志
	INT8U WorkingFlag:1;
	INT8U LiveFlag:1;//制生活水
	INT8U ManualFlushFlag:1;
	INT8U LongTimeWorkFlag:1;//E2 长时间制水
	INT8U PowerOnFlushFlag:1;//上电清洗标志
	INT8U LeakFlag:1;//E1漏水
	INT8U LockWaterFlag:1;
	INT8U PowerOnProcFlag:1;
	INT8U FCTFlag:1;

	INT8U GasDetectionFlag:1;//气检
	INT8U WaterDetectionFlag:1;//水检
	INT8U FilterDetectionFlag:1;//滤芯快检
	INT8U FirstBootGetTDSFlag:1;//第一次上电标识，0不是第一次上电，1第一次上电
	INT8U FirstBootFlushFlag:1;//第一次上电冲洗标识，0不是第一次上电，1第一次上电
	INT8U EmptyshellFlag;//空壳模式

	INT8U AutoFlushtime;//自动冲洗时长,单位秒
	
	INT16U BackTimerCount;//背光时间计数
	INT16U WinTimerCount;

	
	INT16U heartbeat;//心跳包时间 单位秒

	INT8U makewaterTimer;//制水计时 单位分钟
 	INT32U makewaterSingle;//单次制水量 单位mL
	INT8U LongTimeWorkTimesCount;//长时间制水次数 7次
 	INT32U StandbyTimeCount;//待机时长
 	INT8U FilterLife_PCB;//显示板显示等级
 	INT8U FilterLife_RO;//显示板显示等级

 	INT8U wifi;//0未连接，1配网，2连接成功，3信号弱
	
	INT16U PowerOnTimerCount;//上电计时 用于按键上电15秒内的操作
	INT8U flash:1;//显示闪烁

	INT8U HVS_faucet:1;//水龙头高压开关

	INT8U WinTimerOutFlag:1;

	INT8U ElectrolyticFlag:1;//电解片打开标志

	INT8U uartdisplayError:1;//显示板通讯1异常，0正常

	INT8U uartWifiError:1;//显示板通讯1异常，0正常

	INT8U WaterFlowError:1;//流量异常

	INT16U FCTsave:1;

	WORKERROR workerror;//工作错误

	INT32U PerAutoRawUL;// 单次纯水量    即时计算
	INT32U PowerOnPumpMakeWater2H;// 记录上电的制水前2小时
	INT16U FlowMeterBeforeVelocity;	// 前置流量计的流速

	INT8U FaucetGetCmdCount;//水龙头获得指令计数
	INT8U displaydelaysend;//显示延时发送
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


