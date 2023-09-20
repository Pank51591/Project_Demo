#include"config.h"
#include"FCT.h"


const char FaucetTest[]="{\"cmd\":\"FaucetTest\"}";
FCTREG fctReg;

#define VOLT_ADC_VCC	3.3




INT32U GetTDSRes(INT16U ad)
{
	FP32 I,vdd=VOLT_ADC_VCC,vol;
	
	vol=GetVoltageValue(vdd,ad);
	I = (vol)/470;//I=U/R
	I = (vdd-vol)/I;


	return (INT32U)I;
}

INT32U GetLeakRes(INT16U ad)
{
	FP32 I,vdd=VOLT_ADC_VCC,vol;
	
	vol=GetVoltageValue(vdd,ad);
	I = (vol)/1000000;//I=U/R
	I = (vdd-vol)/I;

	return (INT32U)I;
}


void FCT_NTCRes(void)
{
	INT16U ad;
	ADC_Start(gAppadc[ADC_CH_TDS_temp].channel);
	ad = GetADCValues();
	fctReg.TempRes = GetNTCResVal(ad);	
}
void FCT_rawTDSRes(void)
{
	INT16U ad;
	Set_rawTDS_Out_Reverse();
	ADC_Start(gAppadc[ADC_CH_TDS_raw].channel);
	ad = GetADCValues();
	fctReg.rawTDSRes = GetTDSRes(ad);	
}
void FCT_netTDSRes(void)
{
	INT16U ad;
	Set_netTDS_Out_Reverse();
	ADC_Start(gAppadc[ADC_CH_TDS_net].channel);
	ad = GetADCValues();

	fctReg.netTDSRes = GetTDSRes(ad);	
}

void FCT_LeakRes(void)
{
	INT16U ad;
	ADC_Start(gAppadc[ADC_CH_leak].channel);
	ad = GetADCValues();
	fctReg.LeakRes = GetLeakRes(ad);	
}
void FCT_PumpADC(void)
{
	INT16U ad;
	ADC_Start(gAppadc[ADC_CH_pumpA].channel);
	ad = GetADCValues();
	fctReg.PumpADC = GetNTCResVal(ad);	
}


void FCT_NTC2Res(void)
{
	INT16U ad;
	ADC_Start(gAppadc[ADC_CH_TDS_temp2].channel);
	ad = GetADCValues();
	fctReg.Temp2Res = GetNTCResVal(ad);	
}



INT8U sendcnt=0;
void FCT_FaucetDataProc(INT8U *pdat,INT16U len)
{
	if(strstr((char*)pdat,FaucetTest))
	{
		sendcnt=0;
		fctReg.faucet_Uart = 1;
		return;
	}

	return;
}

void FCT_Monitor(void)
{
	static INT8U pumpold=0,InletValveold=0,wasteValveold=0;
	static INT8U faucetcnt=10;

	FCT_NTCRes();
	FCT_rawTDSRes();
	FCT_netTDSRes();
	FCT_LeakRes();
	FCT_PumpADC();

	FCT_NTC2Res();
	
	fctReg.HVS = GET_HVS_PIN();	
	

	if(fctReg.Pump!=pumpold)
	{
		pumpold = fctReg.Pump;
		SetBoosterPump((FlagStatus)fctReg.Pump);//增压泵	
	}

	if(fctReg.InletValve!=InletValveold)
	{
		InletValveold = fctReg.InletValve;
		SetInletValve((FlagStatus)fctReg.InletValve);//进水阀
	}
	
	if(fctReg.wasteValve!=wasteValveold)
	{
		wasteValveold = fctReg.wasteValve;
		SetWasteWaterValve((FlagStatus)fctReg.wasteValve);//废水阀
	}

	if(++faucetcnt>30)
	{
		faucetcnt=0;
		sendcnt++;
		UartSendFaucetData((INT8U*)FaucetTest,strlen(FaucetTest));
	}
	if(sendcnt>2)
	{
		sendcnt = 0;
		fctReg.faucet_Uart = 0;
	}
}


void FCT_ModeInit(void)
{
	fctReg.DeviceAddr = gReg.DeviceAddr;
	fctReg.ProductType = gReg.ProductType;
	fctReg.productName = gReg.productName;
	fctReg.ProductModel= gReg.ProductModel;
	fctReg.version = gReg.version;
	fctReg.WorkState = gReg.WorkState;
	
	Modbus_SetReg(&fctReg,sizeof(fctReg)/2);
	
	UartFaucetProc = FCT_FaucetDataProc;
	
	//AppADCSetProc(ADC_CH_TDS_temp,FCT_NTCRes);
	//AppADCSetProc(ADC_CH_TDS_raw,FCT_rawTDSRes);
	//AppADCSetProc(ADC_CH_TDS_net,FCT_netTDSRes);
	//AppADCSetProc(ADC_CH_leak,FCT_LeakRes);
	//AppADCSetProc(ADC_CH_pumpA,FCT_PumpADC);


	//AppADCStart(ADC_CH_TDS_temp);
	//AppADCStart(ADC_CH_TDS_raw);
	//AppADCStart(ADC_CH_TDS_net);
	//AppADCStart(ADC_CH_leak);
	//AppADCStart(ADC_CH_pumpA);	
}


