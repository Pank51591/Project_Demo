#ifndef FAUCET_H
#define FAUCET_H

#pragma pack(1)

#if 0
//�������ʾ
typedef struct
{
	INT8U en:1;//0����ʾ,1��ʾ
	INT8U color:2;//0��ɫ,1��ɫ,2������ɫ
	INT8U mode:2;//��ʾģʽ��0������1��˸(��0.5S����0.5S)
	INT8U type:3;//��ʾ���ͣ�0����1��1����2��2���ʹ�����
	INT16S val;//��ʾ��ֵ(1λС����),
}
DIGIDIS;

//��о������ʾ
typedef struct
{
	INT8U en:1;//0����ʾ,1��ʾ
	INT8U color:2;//0��ɫ,1��ɫ,2������ɫ
	INT8U mode:2;//��ʾģʽ��0������1��˸(��0.5S����0.5S)
	INT8U val:3;//����ֵ,0ȫ�ף�1:2��1��2:1��2��3:ȫ�졣  
}
FLDIS;

//ͼ����ʾ
typedef struct
{
	INT8U en:1;//0����ʾ,1��ʾ
	INT8U color:2;//0��ɫ,1��ɫ,2������ɫ
	INT8U mode:2;//��ʾģʽ��0������1��˸(��0.5S����0.5S)
	INT8U val:3;//  
}
ICONDIS;


typedef struct
{
	INT8U	head1;
	INT8U	head2;
	INT8U	drvtype;//�豸����
	INT8U	cmd;
	INT8U	datalen;//���ݳ���
	FLDIS	PCB;
	FLDIS	RO;
	DIGIDIS	TDS;
	ICONDIS	wifi;
	INT16U	crc;//MODBUS crc��ʽ
}
FAUCET;



void Faucet_Display(void);
void Faucet_proc(INT8U*pbuf,INT8U len);
#else

typedef enum
{
	FAUCET_workmode_poweron,
	FAUCET_workmode_free,
	FAUCET_workmode_working,
	FAUCET_workmode_error,
	FAUCET_workmode_standby,
	FAUCET_workmode_FCT=0xFF,
}
FAUCETMODE;

typedef enum
{
	BLUE,	
	RED,
}
FAUCETLED;

typedef enum
{
	OFF,	
	ON,
}
LEDSTATE;


//��о������ʾ
typedef struct
{
	INT8U PCB:1;//
	INT8U RO:1;//
	INT8U null:6;//  
}
FLDIS;



typedef struct
{
	INT8U head1;
	INT8U head2;
	INT8U len;
	INT8U cmd;
	INT8U workstate;//
	INT8U fruits;//�߹�
	INT8U wifi;
	INT8U TDS;//
	INT8U Mg_L;//
	INT8U QR;//��ά��
	INT16U digi;//�����
	INT8U error;
	INT8U crc;//
}
FAUCET;


void Faucet_Display(void);
void Faucet_proc(INT8U*pbuf,INT16U len);
void FaucetLEDSet(FAUCETLED led,LEDSTATE state);


#pragma pack()

#endif
#endif

