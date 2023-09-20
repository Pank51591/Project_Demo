#ifndef SAVEDATA_H
#define SAVEDATA_H

#pragma pack(1)

typedef struct
{
	char softver[50];
	char mcuinfor[200];
	char ip[50];
}
VERINFOR;



typedef struct
{
	SYSTEMTIME time;

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

	INT16U FirstBootGetTDSFlag:1;
	INT16U FirstBootFlushFlag:1;

	INT16U fruits:1;
	INT16U BackFlow:1;
	INT16U null:12;

	INT16U crc;
}
SAVEDATA;

#pragma pack()


void SysSetingInit(void);
void GetSysSeting(void);
void SaveSysSeting(void);








#endif

