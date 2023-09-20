#include"config.h"
#include"sim_eeprom.h"



#define SAVEDATA_ADDR_VERSION		  0//系统版本号
#define SAVEDATA_ADDR_SYSSETING		  1024//系统设置数据保存地址
#define SAVEDATA_ADDR_REG			  2048//




//系统数据初始化
void SysSetingInit(void)
{
	systemseting.BackLight=1;
	systemseting.StateChangeFlag = TRUE;//上电上报设备状态	

	gReg.WorkState=WORKSTATE_free;
	gReg.error.u16flag = 0;

	gReg.SenFlag.rawTdsFlag=1;
	gReg.SenFlag.pureTdsFlag=1;	

	gWifiSet.alarmstopflag=1;

	UpdateFilterLife();
}

unsigned int userstaflashblk = 0;  // globla  

//获取系统设置
void GetSysSeting(void)
{
//	INT8U *p;
	INT8U buff[128]={0};
	SAVEDATA *save;
	INT16U crc;

	save = (SAVEDATA*)buff;

	FlashDataRead((INT8U*)buff,&userstaflashblk,USERSTATUSBLOCKSIZE,USERSTATUSADDR,USEPAGES);
	crc = GetModbusCRC(buff, sizeof(SAVEDATA)-2);
	
	if(crc==save->crc)
	{
		//gReg.time.Hour = save->time.Hour;
		//gReg.time.Minute = save->time.Minute;
	 	//gReg.time.Second = save->time.Second;	

		gReg.PowerOnTimeTotal_PCB = save->PowerOnTimeTotal_PCB;
		gReg.PumpWorkeTimeTotal_PCB = save->PumpWorkeTimeTotal_PCB;
		gReg.PowerOnTimeTotal_RO = save->PowerOnTimeTotal_RO;
		gReg.PumpWorkeTimeTotal_RO = save->PumpWorkeTimeTotal_RO;
		gReg.RawWaterVolume = save->RawWaterVolume;
		gReg.NetWaterVolume = save->NetWaterVolume;

		gReg.PriFilterResetTimes = save->PriFilterResetTimes;
		gReg.RoFilterResetTimes = save->RoFilterResetTimes;	

		gReg.rawTDS = save->rawTDS;
		gReg.netTDS = save->netTDS;

		systemseting.FirstBootGetTDSFlag = save->FirstBootGetTDSFlag;
		systemseting.FirstBootFlushFlag = save->FirstBootFlushFlag;

		gReg.fruits = save->fruits;
		gReg.BackFlow = save->BackFlow;

	}
	else 
	{
		RestoreFactory();
		SaveSysSeting();	
	}

	SysSetingInit();
}


void SaveSysSeting(void)
{
	INT8U buff[128]={0};
	SAVEDATA *save;

	save = (SAVEDATA*)buff;
	
	//save->time.Hour = gReg.time.Hour;
	//save->time.Minute = gReg.time.Minute;
	//save->time.Second = gReg.time.Second;

	save->PowerOnTimeTotal_PCB = gReg.PowerOnTimeTotal_PCB;
	save->PumpWorkeTimeTotal_PCB = gReg.PumpWorkeTimeTotal_PCB;
	save->PowerOnTimeTotal_RO = gReg.PowerOnTimeTotal_RO;
	save->PumpWorkeTimeTotal_RO = gReg.PumpWorkeTimeTotal_RO;
	save->RawWaterVolume = gReg.RawWaterVolume;
	save->NetWaterVolume = gReg.NetWaterVolume;

	save->PriFilterResetTimes = gReg.PriFilterResetTimes;
	save->RoFilterResetTimes = gReg.RoFilterResetTimes;

	save->rawTDS = gReg.rawTDS;
	save->netTDS = gReg.netTDS;

	save->FirstBootGetTDSFlag = systemseting.FirstBootGetTDSFlag;
	save->FirstBootFlushFlag = systemseting.FirstBootFlushFlag;

	save->fruits = gReg.fruits;
	save->BackFlow = gReg.BackFlow;

	save->crc = GetModbusCRC(buff, sizeof(SAVEDATA)-2);

	FlashDataSave(buff,&userstaflashblk,USERSTATUSBLOCKSIZE,USERSTATUSADDR,USEPAGES);
}























