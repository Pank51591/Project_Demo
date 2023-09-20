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

	INT32U PowerOnTimeTotal_PCB;//���ϵ�ʱ�� ��λ����
	INT32U PumpWorkeTimeTotal_PCB;//��ˮ�ù���ʱ��
	INT32U PowerOnTimeTotal_RO;//���ϵ�ʱ�� ��λ����
	INT32U PumpWorkeTimeTotal_RO;//��ˮ�ù���ʱ��	

	INT32U RawWaterVolume;//ԭˮ�� mL
	INT32U NetWaterVolume;//��ˮ�� mL
	INT32U RawWaterVolumeSingle;//����ˮ�� mL
	INT32U NetWaterVolumeSingle;//����ˮ�� mL	

	INT16U PriFilterResetTimes;//������о���ô���
	INT16U RoFilterResetTimes;//RO��о���ô���

	INT16U rawTDS;//ԭˮTDS	
	INT16U netTDS;//��ˮTDS

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

