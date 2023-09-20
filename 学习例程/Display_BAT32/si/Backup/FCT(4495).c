#include"config.h"
#include"FCT.h"


const char FaucetTest[]="{\"cmd\":\"FaucetTest\"}";
const char WifiTest[]="{\"cmd\":\"WifiTest\"}";
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

/*void FCT_LeakRes(void)
{
	INT16U ad;
	ADC_Start(gAppadc[ADC_CH_leak].channel);
	ad = GetADCValues();
	fctReg.LeakRes = GetLeakRes(ad);	
}*/
void FCT_PumpADC(void)
{
	INT16U ad;
	ADC_Start(gAppadc[ADC_CH_pumpA].channel);
	ad = GetADCValues();
	fctReg.PumpADC = GetNTCResVal(ad);	
}


/*void FCT_NTC2Res(void)
{
	INT16U ad;
	ADC_Start(gAppadc[ADC_CH_TDS_temp2].channel);
	ad = GetADCValues();
	fctReg.Temp2Res = GetNTCResVal(ad);	
}*/



INT8U sendcnt=0,sendcntwifi=0;
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
void FCT_WifiDataProc(INT8U *pdat,INT16U len)
{
	if(strstr((char*)pdat,WifiTest))
	{
		sendcntwifi=0;
		fctReg.wifi_Uart = 1;
		return;
	}

	return;
}


void FCT_FrontFlow(void)
{
	fctReg.FrontFlow=(systemseting.FlowMeterBeforeVelocity?1:0);
}

void FCT_Monitor(void)
{
	static INT8U pumpold=0,InletValveold=0,wasteValveold=0;
	static INT8U faucetcnt=10,faucetcntwifi=10;

	FCT_NTCRes();
	FCT_rawTDSRes();
	FCT_netTDSRes();
	//FCT_LeakRes();
	FCT_PumpADC();

	//FCT_NTC2Res();

	FCT_FrontFlow();
	
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

	if(++faucetcntwifi>30)
	{
		faucetcntwifi=0;
		sendcntwifi++;
		UartSendWifiData((INT8U*)WifiTest,strlen(WifiTest));
	}
	if(sendcntwifi>2)
	{
		sendcntwifi = 0;
		fctReg.wifi_Uart = 0;
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


//阮工FCT
//==============================================================================================

INT8U fctmode;
FCT_rg_data fct_rg_data;
INT16U fcttimeTic;


void FCT_rg_UartTest(void)
{
	static INT8U faucetcnt=10,faucetcntwifi=10;

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

	if(++faucetcntwifi>30)
	{
		faucetcntwifi=0;
		sendcntwifi++;
		UartSendWifiData((INT8U*)WifiTest,strlen(WifiTest));
	}
	if(sendcntwifi>2)
	{
		sendcntwifi = 0;
		fctReg.wifi_Uart = 0;
	}

}

void FCT_rg_SendData(void)
{
	INT8U *p=(INT8U*)&fct_rg_data;
	
	fct_rg_data.hand=0x5A;
	fct_rg_data.len=0x10;
	fct_rg_data.cmd=0x05;

	//fct_rg_data.FCTstep=9;

	fct_rg_data.rawTDS_H=0;//16-32
	fct_rg_data.rawTDS_L=20;
	
	if(fctReg.netTDSRes>8000&&fctReg.netTDSRes<12000){fct_rg_data.purTDS=20;}//16-36
	else {fct_rg_data.purTDS=0;}

	fct_rg_data.wifi=((fctReg.wifi_Uart==1)?0:1);

	fct_rg_data.purHVS=fctReg.HVS;

	fct_rg_data.liveHVS=fct_rg_data.purHVS;

	fct_rg_data.FrontFlow=(systemseting.FlowMeterBeforeVelocity?0:1);

	fct_rg_data.faucetCOMM=fctReg.faucet_Uart;

	if(fctReg.TempRes){fct_rg_data.rawNTC=25;fct_rg_data.outNTC=25;}//24-26
	else {fct_rg_data.outNTC=0;fct_rg_data.rawNTC=0;}

	fct_rg_data.type=80;

	fct_rg_data.sfw_Ver=(INT8U)(gReg.version&0x00ff);

	fct_rg_data.sum = GetSum(p+1,fct_rg_data.len-1);

	UartSendDisplayData(p,fct_rg_data.len+1);
}

void FCT_powerdown(void)
{
	if(fct_rg_data.FCTstep == 7)
	{
		FCT_rg_SendData();
		fct_rg_data.FCTstep++;
	}
}

//10ms
void FCT_rg_testout(void)
{
	static INT8U i=1,tic=0;

	if(++tic>100)//1s
	{
		tic=0;i++;
	}
	else
	{
		return;
	}

	switch(i)
	{
		case 1:
			PUMP_24V_OUT;
			SetWasteWaterValve(SET);;
			break;
		case 2:
			SetWasteWaterValve(RESET);
			SetInletValve(SET);
			break;
		case 3:
			SetInletValve(RESET);
			ELECTROLYTIC_STRIP_PIN_LEVEL_1;
			break;
		case 4:
			PUMP_14V_OUT;
			ELECTROLYTIC_STRIP_PIN_LEVEL_0;
			SetInletValve2(SET);
			break;
		case 5:
			SetInletValve2(RESET);
			PORT_ClrBit(PORT2,PIN6);
			break;
		case 6:
			PORT_SetBit(PORT2,PIN6);
			PORT_SetBit(PORT1,PIN1);
			break;
		case 7:
			PUMP_6V_OUT;
			PORT_ClrBit(PORT1,PIN1);
			PORT_SetBit(PORT1,PIN0);
			break;
		case 8:
			PORT_ClrBit(PORT1,PIN0);
			PORT_SetBit(PORT14,PIN6);
			break;
		case 9:
			PORT_ClrBit(PORT14,PIN6);
			PORT_SetBit(PORT14,PIN7);
			break;
		case 10:
			PORT_ClrBit(PORT14,PIN7);
			PUMP_OFF;
			if(fct_rg_data.FCTstep == 5)
			{
				fct_rg_data.FCTstep = 6;
				FCT_rg_SendData();
			}
			break;
		default :
			i=11;
			break;
	}
}


void FCT_rg_Msg_proc(void)
{
	static INT16U timecount=0;

	switch(fct_rg_data.FCTstep)
	{
	case 1://进入测试模式
		timecount=50;
		FCT_rg_SendData();
		fct_rg_data.FCTstep++;
		break;
	case 2://关闭所有负载
		GPIO_Output(PORT2,PIN6,1);//低电平打开//关闭WIFI电源 
		
		SetBoosterPump(PUMP_OUT_OFF);//增压泵//关闭泵
		SetInletValve(RESET);//进水阀
		SetWasteWaterValve(RESET);//废水阀		

		if(--timecount==0)
		{
			timecount=50;
			FCT_rg_SendData();
			fct_rg_data.FCTstep++;
		}
		break;
	case 3://检测两个高压开关

		if(GET_HVS_PIN())
		{
			fct_rg_data.purHVS=1;
		}
		else 
		{
			fct_rg_data.purHVS=0;
		}
		fct_rg_data.liveHVS = 1;//水龙头发的

		if(--timecount==0)
		{
			FCT_rg_SendData();
		}
		if(fctmode==0x0C)
		{
			fct_rg_data.FCTstep++;
		}
		break;
	case 4://收到关闭高压开关电源
		FCT_rg_SendData();
		timecount=50;
		fct_rg_data.FCTstep++;
		break;
	case 5://检测高压开关低电平
		if(fct_rg_data.purHVS)
		{
			if(GET_HVS_PIN())
			{
				fct_rg_data.purHVS=0;
			}
		}
		if(--timecount==0)
		{
			timecount=50;
			FCT_rg_SendData();
			fct_rg_data.FCTstep++;
		}
		break;
	case 6://断电24V
		if(--timecount==0)
		{
			timecount=50;
			FCT_rg_SendData();
			fct_rg_data.FCTstep++;
		}		
		break;
	case 7://掉电检测
		if(--timecount==0)
		{

		}		
		break;
	case 8:
		break;
	}

}

void FCT_rg_main(INT8U*buf,INT8U len)
{
	INT8U fcttimeout=0; //20秒
	
	if(buf[len-1]!=GetSum(buf+2,len-3))
	{
		return;
	}
	
	if(buf[7]==0x0B)
	{
		fct_rg_data.FCTstep=1;
	}
	else 
	{
		return;
	}
	
	while(1)
	{
		WDT_Restart();	

		len = GetDisplayData(RecBuff);
		if(len)
		{
			if(buf[len-1]==GetSum(buf+2,len-3))
			{
				fctmode = buf[7];
				if(fctmode==0x0B)
				{
					fct_rg_data.FCTstep=1;
				}
			}
		}
		len = GetFaucetData(RecBuff);
		if(len)
		{
			FCT_FaucetDataProc(RecBuff,len);
		}
		len = GetWifiData(RecBuff);
		if(len)
		{
			FCT_WifiDataProc(RecBuff,len);
		}		

		if(fcttimeTic==0)
		{
			fcttimeTic=10;

			FCT_NTCRes();
			FCT_NTC2Res();
			FCT_rawTDSRes();
			FCT_netTDSRes();			

			FCT_rg_UartTest();

			fctReg.HVS = GET_HVS_PIN();	
			
			UpdataFlowMeterWaterVolume();

			if(PowerDownCheck())
			{
				FCT_powerdown();
			}
			
			FCT_rg_Msg_proc();
			FCT_rg_testout();
			
			if(++fcttimeout>200)//20秒
			{
				//return;
			}			
		}
	}
}

