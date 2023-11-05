#ifndef FCT_H
#define FCT_H

#pragma pack(1)

typedef struct
{
	INT16U DeviceAddr;//设备地址
	INT16U ProductType;//产品类型 0净水器，1其他
	INT16U productName;//产品名称 0云鲸，1云鳟，2博观，3三根芯，4mini系列(0x0401mni1,0x0402mini2)
	INT16U ProductModel;//产品型号(500,600,700,800)
	INT16U version;//版本高8位硬件版本,低8位软件版本

	INT16U cmd;//控制寄存器
	
	INT16U WorkState;//
	
	INT16U TempRes;//
	INT16U rawTDSRes;
	INT16U netTDSRes;//
	
	INT16U PumpADC;
	INT16U HVS;//高压开关状态0关，1开
	
	INT16U faucet_Uart;//水龙头通讯状态，1正常
	INT16U wifi_Uart;//1正常
	INT16U FrontFlow;//前置流量计
	
	INT16U Pump;//水泵状态
	INT16U wasteValve;//废水阀
	INT16U InletValve;//进水阀
}
FCTREG;

typedef struct
{
	INT8U NTCFlag:1;//
	INT8U rawTDSFlag:1;
	INT8U netTDSFlag:1;//
	INT8U LeakFlag:1;//
	INT8U PumpFlag:1;

	INT8U HVSFlag:1;//高压开关状态0关，1开
	INT8U wifiFlag:1;//wifi通讯状态，1正常
	INT8U FaucetFlag:1;//水龙头通讯状态，1正常 
}
FCT_FLAG;


//====================================
typedef struct
{
	INT8U hand;//
	INT8U len;
	INT8U cmd;//
	INT8U FCTstep;//
	
	INT8U rawTDS_H;
	INT8U rawTDS_L;//
	
	INT8U purTDS;//纯水TDS
	
	INT8U wifi;//

	INT8U purHVS;//纯水高压开关
	INT8U liveHVS;//生活水高压开关
	INT8U FrontFlow;//前置流量计
	INT8U faucetCOMM;//水龙头通讯
	INT8U rawNTC;//原水NTC
	INT8U outNTC;//出水NTC

	INT8U type;//机型
	INT8U sfw_Ver;//软件版本
	INT8U sum;
}
FCT_rg_data;




#pragma pack()

extern FCTREG fctReg;

extern void FCT_FaucetDataProc(INT8U *pdat,INT16U len);
extern void FCT_ModeInit(void);
extern void FCT_Monitor(void);

extern void FCT_rg_main(INT8U*buf,INT8U len);
extern void FCT_powerdown(void);

#endif

