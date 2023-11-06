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
	


	save->crc = GetModbusCRC(buff, sizeof(SAVEDATA)-2);

	FlashDataSave(buff,&userstaflashblk,USERSTATUSBLOCKSIZE,USERSTATUSADDR,USEPAGES);
}























