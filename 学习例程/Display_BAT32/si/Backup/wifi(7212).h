#ifndef WIFI_H
#define WIFI_H

#define WIFI_HEAD1	0xFF
#define WIFI_HEAD2	0xFF




typedef enum
{
	WIFI_CMD_01=0x01,//控制或设置
	WIFI_CMD_02=0x02,//状态返回
	WIFI_CMD_03=0x03,//无效命令 
	WIFI_CMD_04=0x04,//报警状态汇报
	WIFI_CMD_05=0x05,//确认
	WIFI_CMD_06=0x06,//状态汇报
	WIFI_CMD_07=0x07,
	WIFI_CMD_09=0x09,//停止故障报警帧
	WIFI_CMD_11=0x11,//网络授时
	WIFI_CMD_60=0x60,
	WIFI_CMD_61=0x61,
	WIFI_CMD_62=0x62,
	WIFI_CMD_63=0x63,//获取密钥
	WIFI_CMD_64=0x64,//设置加密参数
	WIFI_CMD_70=0x70,
	WIFI_CMD_71=0x71,
	WIFI_CMD_73=0x73,//查询报警状态
	WIFI_CMD_74=0x74,//查询报警状态应答
	WIFI_CMD_7C=0x7C,
	WIFI_CMD_7D=0x7D,
	WIFI_CMD_E1=0xE1,
	WIFI_CMD_E2=0xE2,
	WIFI_CMD_E5=0xE5,
	WIFI_CMD_E6=0xE6,
	WIFI_CMD_E7=0xE7,
	WIFI_CMD_E8=0xE8,
	WIFI_CMD_E9=0xE9,
	WIFI_CMD_EA=0xEA,
	WIFI_CMD_EB=0xEB,
	WIFI_CMD_EC=0xEC,
	WIFI_CMD_ED=0XED,
	WIFI_CMD_EF=0xEF,
	WIFI_CMD_F0=0xF0,//网络状态查询
	WIFI_CMD_F1=0xF1,
	WIFI_CMD_F2=0xF2,
	WIFI_CMD_F3=0xF3,
	WIFI_CMD_F4=0xF4,
	WIFI_CMD_F5=0xF5,
	WIFI_CMD_F6=0xF6,
	WIFI_CMD_F7=0xF7,//主动汇报网络状态,WIFI模块->设备
	WIFI_CMD_F8=0xF8,
	WIFI_CMD_F9=0xF9,
	WIFI_CMD_FA=0xFA,//设备大数据汇报配置帧             WIFI模块->设备
	WIFI_CMD_FB=0xFB//设备大数据汇报配置应答帧
}WIFICMD;



typedef enum
{
	WIFI_CON_SetOutWaterTemp  = 0x01,//设置出水温
	WIFI_CON_SetTime,//2设置时间
	WIFI_CON_SetPriFilterReset,//3初滤复位
	WIFI_CON_SetAdsFilterReset,//4吸附复位
	WIFI_CON_SetRawFilterReset,//5粗滤复位
	WIFI_CON_SetFineFilterReset,//6精滤复位
	WIFI_CON_SetRoFilterReset,//7RO复位
	WIFI_CON_SetTasFilterReset,//8口感复位
	WIFI_CON_SetNanoFilterReset,//9纳滤复位
	WIFI_CON_SetFlushStatus,//A冲洗功能状态

	WIFI_CON_SetRO2Reset=0x0D,//复位RO2

	WIFI_CON_Setfruits=0x11,//蔬果
	
}WIFIControlCmd;


typedef enum
{
	WIFI_WORKMODE_softAp=0,
	WIFI_WORKMODE_smartlink=2,
	WIFI_WORKMODE_smartAp=3,
	WIFI_WORKMODE_closeinternet=9,
	WIFI_WORKMODE_work=0xFF,
}
WIFIWORKMODE;


#pragma pack(1)

typedef struct
{
	
	INT8U heartbeatEN:1;
	INT8U BigdataEN:1;
	INT8U SendStatus:1;//发送状态1成功
	INT8U alarmsendflag:1;
	INT8U alarmstopflag:1;
	
	INT8U beakcmd;//返回指令
	INT16U heartbeat;
	INT16U heartbeatCount;
	INT16U BigdataHeartbeat;//时间单位为100ms
	INT16U BigdataHeartbeatCount;

	INT8U wifistatus;
	INT8U wifisignal;
	INT8U workmode;
}
WIFISET;

typedef struct
{
	uint8_t TempErrorFlag			: 1;//温度传感器故障
	uint8_t rawTdsErrorFlag			: 1;//预留，原水TDS传感器故障
	uint8_t pureTdsErrorFlag		: 1;//预留，纯水TDS传感器故障
	uint8_t WaterLeakErrorFlag		: 1;//漏水报警
	uint8_t TimeOutErrorFlag		: 1;//制水超时
	uint8_t WasteWaterErrorFlag		: 1;//预留，废水比阀故障
	uint8_t InWaterErrorFlag		: 1;//预留，进水阀故障
	uint8_t sparklingWaterStatus	: 1;//预留，气泡水功能状态
}ERRORFLAG_W;
typedef union 
{
	uint8_t u8flag;
	ERRORFLAG_W BitFlag;
}UN_ERROR_W;


//7D01
typedef struct
{	//1-16
	uint8_t	 cmd1;
	uint8_t	 cmd2;
	uint16_t rawTds;//进水TDS
	uint16_t pureTds;//出水TDS
	uint16_t rawCod;//预留，入水COD值
	uint16_t pureCod;//预留，出水COD值
	uint16_t rawToc;//预留，
	uint16_t pureToc;//预留，
	uint16_t rawUV254;//预留，
	uint16_t pureUV254;//预留，
	//17-19
	uint8_t  hour;
	uint8_t  min;
	uint8_t  sec;
	
	//Byte20  from bit0 to bit7
	uint32_t rawTdsFlag 		: 1;//入水TDS传感器标志位,0：无此传感器
	uint32_t pureTdsFlag		: 1;//出水TDS传感器标志位,0：无此传感器
	uint32_t rawCodFlag 		: 1;//预留
	uint32_t pureCodFlag		: 1;//预留
	uint32_t rawTocFlag 		: 1;//预留
	uint32_t pureTocFlag		: 1;//预留
	uint32_t rawUV254Flag		: 1;//预留
	uint32_t pureUV254Flag		: 1;//预留
	//Byte21-27
	uint32_t rawVolume			: 24;//预留，累计源水量,单位L
	uint32_t pureVolume 		: 24;//累计纯水量,单位mL
	uint32_t OutWaterTemp		:  8;//预留，出水温度
	//28-34
	uint8_t priFilterRemain;//初滤剩余百分比(0~100%)
	uint8_t adsFilterRemain;//预留
	uint8_t RawFilterRemain;//预留
	uint8_t fineFilterRemain;//预留
	uint8_t roFilterRemain;//ro滤剩余百分比(0~100%)
	uint8_t tasFilterRemain;//预留
	uint8_t nanoFilterRemain;//预留
	//35
	uint8_t priFilterWarningFlag	: 1;//初滤到期预警(剩余10%),0无预警
	uint8_t adsFilterWarningFlag	: 1;//预留
	uint8_t rawFilterWarningFlag	: 1;//预留
	uint8_t fineFilterWarningFlag	: 1;//预留
	uint8_t roFilterWarningFlag		: 1;//ro滤到期预警(剩余10%),0无预警
	uint8_t tasFilterWarningFlag	: 1;//预留
	uint8_t nanoFilterWarningFlag	: 1;//预留
	uint8_t null_1					: 1;//预留
	//36
	uint8_t priFilterAlarmFlag 	: 1;//初滤到期报警（剩余0%)
	uint8_t adsFilterAlarmFlag 	: 1;//预留
	uint8_t rawFilterAlarmFlag 	: 1;//预留
	uint8_t fineFilterAlarmFlag	: 1;//预留
	uint8_t roFilterAlarmFlag	: 1;//ro滤到期报警（剩余0%)
	uint8_t tasFilterAlarmFlag 	: 1;//预留
	uint8_t nanoFilterAlarmFlag	: 1;//预留
	uint8_t null_2				: 1;//预留
	//37
	uint8_t priFilterSelectFlag		: 1;//初滤选择标志位,0无此滤芯
	uint8_t adsFilterSelectFlag		: 1;//预留
	uint8_t rawFilterSelectFlag		: 1;//预留
	uint8_t fineFilterSelectFlag	: 1;//预留
	uint8_t roFilterSelectFlag 		: 1;//ro滤选择标志位,0无此滤芯
	uint8_t tasFilterSelectFlag		: 1;//预留
	uint8_t nanoFilterSelectFlag	: 1;//预留
	uint8_t null_3					: 1;//预留
	//38
	uint8_t priFilterResetFlag 	: 1;//初滤复位 0正常，1复位此级滤芯
	uint8_t adsFilterResetFlag 	: 1;//预留
	uint8_t rawFilterResetFlag 	: 1;//预留
	uint8_t fineFilterResetFlag	: 1;//预留
	uint8_t roFilterResetFlag	: 1;//ro滤复位 0正常，1复位此级滤芯
	uint8_t tasFilterResetFlag 	: 1;//预留
	uint8_t nanoFilterResetFlag	: 1;//预留
	uint8_t null_4				: 1;//预留
	//39
	uint8_t FlushStatus 			: 1;//冲洗功能状态,0关闭，1开启
	uint8_t uvSterilizationStatus 	: 1;//UV杀菌功能状态,0关闭，1开启
	uint8_t operationMode			: 3;//运行模式：01冲洗、02制水、03满水、04缺水、05待机、06检修
	uint8_t instantDrinkStatus		: 1;//预留
	uint8_t null_5					: 2;
	//40
	UN_ERROR_W AllError;
	//41-42
	uint8_t SaltRejectionRate;				//预留， 脱盐率
	uint8_t RawWaterTemperature;			//预留， 进水温度
#if 1	
	//43-46 20200725 新增
	uint8_t roFilter2Remain;				// RO2剩余百分比
	uint8_t mnrFilter1Remain;				// 矿化1剩余百分比
	uint8_t mnrFilter2Remain;				// 矿化2剩余百分比
	uint8_t mnrFilter3Remain;				// 矿化3剩余百分比
	//47
	uint64_t mnrFilter3AlarmFlag	: 1;//矿化3到期报警（剩余0%）0无、1有
	uint64_t mnrFilter2AlarmFlag	: 1;
	uint64_t mnrFilter1AlarmFlag	: 1;
	uint64_t roFilter2AlarmFlag		: 1;
	uint64_t mnrFilter3WarningFlag 	: 1;//矿化3到期预警（剩余10%）
	uint64_t mnrFilter2WarningFlag 	: 1;
	uint64_t mnrFilter1WarningFlag 	: 1;
	uint64_t roFilter2WarningFlag	: 1;
	//48-51
	uint64_t mnrFilter3ResetFlag	: 1;//矿化3复位 0正常、1复位此级滤芯
	uint64_t mnrFilter2ResetFlag	: 1;
	uint64_t mnrFilter1ResetFlag	: 1;
	uint64_t roFilter2ResetFlag		: 1;
	uint64_t mnrFilter3SelectFlag	: 1;
	uint64_t mnrFilter2SelectFlag	: 1;
	uint64_t mnrFilter1SelectFlag	: 1;
	uint64_t roFilter2SelectFlag	: 1;
	uint64_t perRawVolume			: 24;// 单次原水量，单位mL
	//52-54  //大数据只到54
	uint64_t PerPureVolume			: 24;// 单次纯水量,单位mL

#if 1	
	//55-65 20201117 客户新增加
	uint8_t PriFilterResetTimes;		// 初滤重置次数  0-100   byte55
	uint8_t AdsFilterResetTimes;		// 吸附滤重置次数  0-100
	uint8_t RawFilterResetTimes;		// 粗滤重置次数  0-100
	uint8_t FineFilterResetTimes;		// 精滤重置次数  0-100
	uint8_t RoFilterResetTimes;			// Ro滤重置次数  0-100
	uint8_t TasFilterResetTimes;		// 口感滤重置次数  0-100   byte60
	uint8_t NanoFilterResetTimes;		// 纳滤重置次数  0-100
	uint8_t RoFilter2ResetTimes;		// Ro2滤重置次数  0-100
	uint8_t MnrFilter1ResetTimes;		// 吸附滤重置次数  0-100
	uint8_t MnrFilter2ResetTimes;		// 吸附滤重置次数  0-100
	uint32_t MnrFilter3ResetTimes:8;	// 吸附滤重置次数  0-100   byte65
	//66-68
	uint32_t perClearWaterVolume:24;	//单次净水量
	//69-71
	uint32_t clearWaterVolume:24;		//累计净水量
	//72
	uint32_t resever1:8;				// 预留   byte66
	//73-74
	uint16_t RawHardness;				// 原水硬度		// byte73-74
	//75-76
	uint16_t PurifiedHardness;			// 出水硬度		75-76
#endif	
#endif
}
UPStatuInfo;


#pragma pack()


extern WIFISET gWifiSet;


void WifiMsgProc(INT8U *pbuf,INT16U len);
void EQUI_EnterWifiNetwork(void);
void EQUI_ClearWifiConfig(void);
void EQUI_UpdataState(INT8U cmd);
void EQUI_UpdataState_Bigdata(INT8U cmd);
void MonitorBigData(void);

void MonitrorAlarm(void);
void EQUI_SendWifiNetwork(WIFIWORKMODE mode);

INT8U GetSum(INT8U *pbuf,INT8U len);
INT16U GetCommData(INT8U *pbuf,INT16U len);

#endif

