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
	INT16U BigdataHeartbeat;
	INT16U BigdataHeartbeatCount;

	INT8U wifistatus;
	INT8U wifisignal;
	INT8U workmode;
}
WIFISET;

typedef struct
{
	uint8_t outWaterTempSensorErrFlag: 1;//出水温度传感器故障有无
	uint8_t overheatErrFlag			: 1;//106℃超温故障有无
	uint8_t overheatAlarmFlag		: 1;//110℃超温报警有无
	uint8_t inWaterTempSensorErrFlag: 1;//进水温度传感器故障有无
	uint8_t timeoutFlag				: 1;//制水超时保护功能有无
	uint8_t communicationErrFlag	: 1;//通讯异常有无
	uint8_t voltageSensorErrFlag	: 1;//电压传感器故障有无
	uint8_t resever1				: 1;//预留
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
	uint8_t rawTdsFlag 		: 1;//入水TDS传感器标志位,0：无此传感器
	uint8_t pureTdsFlag		: 1;//出水TDS传感器标志位,0：无此传感器
	uint8_t rawCodFlag 		: 1;//预留
	uint8_t pureCodFlag		: 1;//预留
	uint8_t rawTocFlag 		: 1;//预留
	uint8_t pureTocFlag		: 1;//预留
	uint8_t rawUV254Flag	: 1;//预留
	uint8_t pureUV254Flag	: 1;//预留
	//Byte21-27
	uint16_t instantPurifiedWaterVolume;//瞬时纯水量,单位mL
	uint32_t pureVolume 		: 24;//累计纯水量,单位mL
	uint32_t rawWaterTemperature: 8;//进水温度
	uint32_t OutWaterTemp;//出水温度
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
	uint8_t mnrFilterWarningFlag	: 1;//预留
	//36
	uint8_t priFilterAlarmFlag 	: 1;//初滤到期报警（剩余0%)
	uint8_t adsFilterAlarmFlag 	: 1;//预留
	uint8_t rawFilterAlarmFlag 	: 1;//预留
	uint8_t fineFilterAlarmFlag	: 1;//预留
	uint8_t roFilterAlarmFlag	: 1;//ro滤到期报警（剩余0%)
	uint8_t tasFilterAlarmFlag 	: 1;//预留
	uint8_t nanoFilterAlarmFlag	: 1;//预留
	uint8_t mnrFilterAlarm		: 1;//预留
	//37
	uint8_t priFilterSelectFlag		: 1;//初滤选择标志位,0无此滤芯
	uint8_t adsFilterSelectFlag		: 1;//预留
	uint8_t rawFilterSelectFlag		: 1;//预留
	uint8_t fineFilterSelectFlag	: 1;//预留
	uint8_t roFilterSelectFlag 		: 1;//ro滤选择标志位,0无此滤芯
	uint8_t tasFilterSelectFlag		: 1;//预留
	uint8_t nanoFilterSelectFlag	: 1;//预留
	uint8_t mnrFilterSelectFlag		: 1;//预留
	//38
	uint8_t priFilterResetFlag 	: 1;//初滤复位 0正常，1复位此级滤芯
	uint8_t adsFilterResetFlag 	: 1;//预留
	uint8_t rawFilterResetFlag 	: 1;//预留
	uint8_t fineFilterResetFlag	: 1;//预留
	uint8_t roFilterResetFlag	: 1;//ro滤复位 0正常，1复位此级滤芯
	uint8_t tasFilterResetFlag 	: 1;//预留
	uint8_t nanoFilterResetFlag	: 1;//预留
	uint8_t mnrFilterResetFlag	: 1;//预留
	//39
	uint8_t FlushStatus 			: 1;//冲洗功能状态,0关闭，1开启
	uint8_t uvSterilizationStatus 	: 1;//UV杀菌功能状态,0关闭，1开启
	uint8_t onOffStatus				: 1;//开关机状态,0关闭，1开启
	uint8_t childLockStatus			: 1;//童锁功能状态,0关闭，1开启
	uint8_t waterUseStatus			: 1;//取水功能状态,0关闭，1开启
	uint8_t waterChangingStatus		: 1;//换水功能状态,0关闭，1开启
	uint8_t heatingStatus			: 1;//加热功能状态,0关闭，1开启
	uint8_t heatKeepingStatus		: 1;//保温功能状态,0关闭，1开启

	//40
	UN_ERROR_W AllError;

	//41
	uint8_t operationMode;//01：冲洗02：制水04：缺水05：待机06：检修0F：休眠10：净水箱满水11：废水箱满水
	
	//42
	uint8_t hotWaterType;//01：常温02：沸水03：泡茶04：奶粉05：咖啡06：40℃07：50℃08：60℃09：70℃0A：80℃0B：90℃

	//43-44
	uint16_t outWaterVolume;//实际出水水量ml
	//45
	uint8_t outWaterVolumeLevel;//出水水量档位 01：180ml02：300ml03：500ml04：1000ml05：900ml06：90ml07：120ml08：100ml09：200ml0A：400ml

	//46
	uint8_t resever1;
	//47-48
	uint16_t freeWaterVolume;//任意出水水量mL

	//49-60
	uint8_t actualSetTempNormal;//常温档位实际设定值
	uint8_t actualSetTempTea;//泡茶档位实际设定值
	uint8_t actualSetTempMilk;//奶粉档位实际设定值
	uint8_t actualSetTempCoffee;//咖啡档位实际设定值
	uint8_t actualSetTemp40;//40℃档位实际设定值
	uint8_t actualSetTemp50;//50℃档位实际设定值
	uint8_t actualSetTemp60;//60℃档位实际设定值
	uint8_t actualSetTemp70;//70℃档位实际设定值
	uint8_t actualSetTemp80;//
	uint8_t actualSetTemp90;//
	uint8_t	actualSetTempBoil;//沸水档位实际设定值,00：对应 80℃01：对应 81℃02：对应 82℃，12：对应 98℃13：对应 99℃14：对应 100℃
	uint8_t mnrFilterRemained;//矿化滤芯剩余百分比
}
UPStatuInfo_max;

//6D01
typedef struct
{	
	uint8_t	 cmd1;
	uint8_t	 cmd2;
	//1-4
	uint16_t rawTds;//进水TDS
	uint16_t pureTds;//出水TDS
	//5-6
	uint8_t thickFilmTemperature;//预留，厚膜温度
	uint8_t iceCanTemperature;//预留，冰罐温度
	//7-16
	uint8_t reserved1;//预留，
	uint8_t reserved2;//预留，
	uint8_t reserved3;//预留，
	uint8_t reserved4;//预留，
	uint8_t reserved5;//预留，
	uint8_t reserved6;//预留，
	uint8_t reserved7;//预留，
	uint8_t reserved8;//预留，
	uint8_t reserved9;//预留，
	uint8_t reserved10;//预留，
	//17-19
	uint8_t  hour;
	uint8_t  min;
	uint8_t  sec;
	
	//20  
	uint8_t reserved11;//预留
	
	//21-22
	uint16_t perpureVolume;//单次纯水量,单位mL
	//23-26
	uint32_t pureVolume;//累计纯水量,单位mL
	//27
	uint32_t OutWaterTemp;//，出水温度
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
	uint8_t mnrFilterWarningFlag	: 1;//预留
	//36
	uint8_t priFilterAlarmFlag 	: 1;//初滤到期报警（剩余0%)
	uint8_t adsFilterAlarmFlag 	: 1;//预留
	uint8_t rawFilterAlarmFlag 	: 1;//预留
	uint8_t fineFilterAlarmFlag	: 1;//预留
	uint8_t roFilterAlarmFlag	: 1;//ro滤到期报警（剩余0%)
	uint8_t tasFilterAlarmFlag 	: 1;//预留
	uint8_t nanoFilterAlarmFlag	: 1;//预留
	uint8_t mnrFilterAlarmFlag	: 1;//预留
	//37
	uint8_t reserved12;//预留
	//38
	uint8_t priFilterResetFlag 	: 1;//初滤复位 0正常，1复位此级滤芯
	uint8_t adsFilterResetFlag 	: 1;//预留
	uint8_t rawFilterResetFlag 	: 1;//预留
	uint8_t fineFilterResetFlag	: 1;//预留
	uint8_t roFilterResetFlag	: 1;//ro滤复位 0正常，1复位此级滤芯
	uint8_t tasFilterResetFlag 	: 1;//预留
	uint8_t nanoFilterResetFlag	: 1;//预留
	uint8_t mnrFilterResetFlag	: 1;//预留
	//39
	uint8_t FlushStatus 			: 1;//冲洗功能状态,0关闭，1开启
	uint8_t uvSterilizationStatus 	: 1;//UV杀菌功能状态,0关闭，1开启
	uint8_t onOffStatus				: 1;//开关机状态,0关闭，1开启
	uint8_t childLockStatus			: 1;//童锁功能状态,0关闭，1开启
	uint8_t waterUseStatus			: 1;//取水功能状态,0关闭，1开启
	uint8_t waterChangingStatus		: 1;//换水功能状态,0关闭，1开启
	uint8_t heatingStatus			: 1;//加热功能状态,0关闭，1开启
	uint8_t heatKeepingStatus		: 1;//保温功能状态,0关闭，1开启
	
	//40
	uint8_t pailFlagReset		: 1;//水桶更换复位,0：否,1是
	uint8_t purifiedBoxFullFlag	: 1;//净水箱水满提醒
	uint8_t purifiedBoxLackFlag	: 1;//净水箱缺水提醒
	uint8_t rawBoxLackFlag		: 1;//原水箱缺水提醒
	uint8_t iceCanOnOffStatus	: 1;//冰罐开关
	uint8_t massiveWaterStatus	: 1;//大水量状态
	uint8_t resvHeatKeeping		: 1;//预约保温开关
	uint8_t oneKeyDrainage		: 1;//一键排水
	
	//41
	uint8_t operationMode;//运行模式01：冲洗02：制水04：缺水05：待机06：检修0F：休眠

	//42
	uint8_t hotWaterType;//热水温度档位00：无模式01：常温02：沸水03：泡茶04：奶粉05：咖啡06：40℃07：50℃08：60℃09：70℃0A：80℃0B：90℃0F：个性化10：冰水

	//43-44
	uint16_t outWaterVolume;//实际出水水量mL
	//45
	uint8_t outWaterVolumeLevel;//出水水量档位 02：300ml03：500ml04：1000ml05：900ml08：100ml09：200ml0A：400ml0C：600ml0D：700ml0E：800ml0F：1100ml10：1200ml
	//46
	uint8_t reserved13;//预留
	//47-48
	uint16_t freeWaterVolume;//任意出水水量
	//49-51
	uint8_t outWaterTempAdjust;//出水温度调节
	uint8_t highlandBpTemperature;//高原沸点温度
	uint8_t hotPotTemperature;//热罐温度
	//52-55
	uint16_t resvHeatKeepingStartTime_hour:8;//预约保温开始时间
	uint16_t resvHeatKeepingStartTime_min:8;//
	uint16_t resvHeatKeepingStopTime_hour:8;//预约保温关闭时间
	uint16_t resvHeatKeepingStopTime_min:8;//

	//56-60
	uint8_t setHeatKeepingDuration;//设置保温时长
	uint8_t thickFilmHeatPower;//厚膜加热功率
	uint8_t hotPotHeatPower;//热罐加热功率
	uint8_t rawWaterTemperature;//进水温度
	uint8_t mnrFilterRemained;//矿化滤芯剩余百分比

}
UPStatuInfo;


#pragma pack()


extern WIFISET gWifiSet;


void WifiMsgProc(INT8U *pbuf,INT16U len);
void EQUI_EnterWifiNetwork(void);
void EQUI_ClearWifiConfig(void);
void EQUI_UpdataState(INT8U cmd);

void MonitrorAlarm(void);
void EQUI_SendWifiNetwork(WIFIWORKMODE mode);

INT8U GetSum(INT8U *pbuf,INT8U len);
INT16U GetCommData(INT8U *pbuf,INT16U len);

#endif

