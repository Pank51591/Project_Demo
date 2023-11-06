#include"config.h"
#include"sim_eeprom.h"



#define SAVEDATA_ADDR_VERSION		  0//ϵͳ�汾��
#define SAVEDATA_ADDR_SYSSETING		  1024//ϵͳ�������ݱ����ַ
#define SAVEDATA_ADDR_REG			  2048//




//ϵͳ���ݳ�ʼ��
void SysSetingInit(void)
{
	systemseting.BackLight=1;
	systemseting.StateChangeFlag = TRUE;//�ϵ��ϱ��豸״̬	


}

unsigned int userstaflashblk = 0;  // globla  

//��ȡϵͳ����
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























