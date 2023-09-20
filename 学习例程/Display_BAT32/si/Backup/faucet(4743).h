#ifndef FAUCET_H
#define FAUCET_H

#pragma pack(1)

#if 0
//数码管显示
typedef struct
{
	INT8U en:1;//0不显示,1显示
	INT8U color:2;//0白色,1红色,2其他颜色
	INT8U mode:2;//显示模式，0常亮，1闪烁(灭0.5S，亮0.5S)
	INT8U type:3;//显示类型，0类型1，1类型2，2类型错误码
	INT16S val;//显示数值(1位小数点),
}
DIGIDIS;

//滤芯寿命显示
typedef struct
{
	INT8U en:1;//0不显示,1显示
	INT8U color:2;//0白色,1红色,2其他颜色
	INT8U mode:2;//显示模式，0常亮，1闪烁(灭0.5S，亮0.5S)
	INT8U val:3;//寿命值,0全白，1:2白1灭，2:1白2灭，3:全红。  
}
FLDIS;

//图标显示
typedef struct
{
	INT8U en:1;//0不显示,1显示
	INT8U color:2;//0白色,1红色,2其他颜色
	INT8U mode:2;//显示模式，0常亮，1闪烁(灭0.5S，亮0.5S)
	INT8U val:3;//  
}
ICONDIS;


typedef struct
{
	INT8U	head1;
	INT8U	head2;
	INT8U	drvtype;//设备类型
	INT8U	cmd;
	INT8U	datalen;//数据长度
	FLDIS	PCB;
	FLDIS	RO;
	DIGIDIS	TDS;
	ICONDIS	wifi;
	INT16U	crc;//MODBUS crc格式
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


//滤芯寿命显示
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
	INT8U fruits;//蔬果
	INT8U wifi;
	INT8U TDS;//
	INT8U Mg_L;//
	INT8U QR;//二维吗
	INT16U digi;//数码管
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

