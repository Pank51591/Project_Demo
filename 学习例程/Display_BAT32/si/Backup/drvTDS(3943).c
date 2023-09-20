#include"config.h"
#include"drvTDS.h"
#include"math.h"
#include"stdlib.h"

	
#define VOLT_ADC_R 		10000//分压电阻
#define VOLT_ADC_VCC	3.3//3300.0//3.3V


#define WATER_COMPENSATION_35C						(-16)       // 33
#define WATER_COMPENSATION_30C						(-17)		// 28
#define WATER_COMPENSATION_25C						(0)			// 25
#define WATER_COMPENSATION_20C						(-16)		// 18
#define WATER_COMPENSATION_15C						(-24)		// 13
#define WATER_COMPENSATION_10C						(-26) 		// 8
#define WATER_COMPENSATION_5C		  				(-28)		// 7



INT16S gTDSTemp;//TDS温度
INT16S gTDSTemp2;//TDS温度

INT16U tdsbefore1mincount=0;
INT8U  UpdateEN=0;

//温度计算 r为要计算的热敏电阻阻值
FP32 CalculateTemp(INT32U r)
{
	FP32 t,rx;
	
	rx=(FP32)r;
	//rx=rx/1000.0;

	if(r>=18074)//0-10
	{
		t=29.108-0.0011*rx;
	}
	else if(r<18074&&r>=12116)//10-20
	{
		t=39.947-0.0017*rx;
	}
	else if(r<12116&&r>=8302)//20-30
	{
		t=51.438-0.0026*rx;
	}
	else if(r<8302&&r>=5815)//30-40
	{
		t=63.028-0.004*rx;
	}
	else if(r<5815&&r>=4149)//40-50
	{
		t=74.586-0.006*rx;
	}
	else if(r<4149&&r>=3011)//50-60
	{
		t=86.228-0.0088*rx;
	}
	else if(r<3011&&r>=2223)//60-70
	{
		t=97.964-0.0127*rx;
	}
	else if(r<2223&&r>=1577)//70-80
	{
		t=101.97-0.0144*rx;
	}
	else if(r<1577)//80-
	{
		t=109.16-0.0181*rx;
	}
	
	return t;
}


int TemperatureCompensation(INT16U tds,INT16S temperature)
{
	int temp,k;

	if(temperature > 3200)
		k = WATER_COMPENSATION_35C;
	else if(temperature > 2700)
		k = WATER_COMPENSATION_30C;
	else if(temperature > 2200)
		k = WATER_COMPENSATION_25C;
	else if(temperature > 1700)
		k = WATER_COMPENSATION_20C;
	else if(temperature > 1200)
		k = WATER_COMPENSATION_15C;
	else if(temperature > 700)
		k = WATER_COMPENSATION_10C;
	else
		k = WATER_COMPENSATION_5C;

	temp = ((temperature-2500)*k)/100+1000;

	//temp = (tds*temp)/1000;
	temp = (tds*temp);

	return temp;
}

static int UserTdsPatch(uint16_t tds)
{
	int tdsval;
	
	tdsval =  ( abs( pow( tds, 6 ) * ( 2.92513864e-18 )\
												+pow( tds, 5 ) * ( -3.14404716e-14 )\
												+pow( tds, 4 ) * ( 1.27389898e-10 )\
												+pow( tds, 3 ) * ( -2.33331311e-07 )\
												+pow( tds, 2 ) * ( 2.09917103e-04 )\
												+tds * ( 3.74496021e-02 )\
												+ 4.89216335e+00 ) ) ; 
	if(tdsval < 5)
		tdsval = 0;
	else if(tdsval < 8)
		tdsval -= 3;
	else if(tdsval < 11)
		tdsval -= 2;

	if(tdsval<3)
	{
		tdsval = 3;
	}

	if(tdsval>7)
	{
		tdsval = TemperatureCompensation(tdsval,gTDSTemp);
	}

	return tdsval;
}

void SetTDSUpdataEN(BOOL en)
{
	UpdateEN=en;	
}


INT32U GetNTCResVal(INT16U ad)
{
	FP32 I,vdd=VOLT_ADC_VCC,vol;
	
	vol=GetVoltageValue(vdd,ad);
	I = (vol)/VOLT_ADC_R;//I=U/R
	I = (vdd-vol)/I;

	return (INT32U)I;
}

void GetNTCTemp(INT16U ad)
{
	INT32U res;
	
	res = GetNTCResVal(ad);
	
	if(res>20000.0||res<1500.0)//R=1.5K~20K
	{
		gReg.error.BitFlag.TempErrorFlag=1;

		gTDSTemp = 2200;
	}
	else 
	{
		gReg.error.BitFlag.TempErrorFlag=0;

		gTDSTemp = (CalculateTemp(res)*100);

		if(gTDSTemp<=100||gTDSTemp>=5000)
		{
			gTDSTemp = 2200;
		}
	}

	AppADCStop(ADC_CH_TDS_temp);
}

void GetNTCTemp2(INT16U ad)
{
	INT32U res;
	
	res = GetNTCResVal(ad);
	
	if(res>20000.0||res<1500.0)//R=1.5K~20K
	{
		gReg.error.BitFlag.Temp2ErrorFlag=1;

		gTDSTemp2 = 2200;
	}
	else 
	{
		gReg.error.BitFlag.Temp2ErrorFlag=0;

		gTDSTemp2 = (CalculateTemp(res)*100);

		if(gTDSTemp2<=100||gTDSTemp2>=5000)
		{
			gTDSTemp2 = 2200;
		}
	}

	AppADCStop(ADC_CH_TDS_temp2);
}


void GetrawTDS(INT16U ad)
{
	if(UpdateEN)
	{
		gReg.rawTDS = UserTdsPatch(ad);

		if(gReg.rawTDS<3)
		{
			gReg.rawTDS=3;
		}
	}

	AppADCStop(ADC_CH_TDS_raw);	
}

void GetnetTDS(INT16U ad)
{
	int temp;
	
	if(UpdateEN)
	{
		temp = UserTdsPatch(ad);//不把纯水这路当原水用

		gReg.netTDS = ((temp *8)/7)/1000;

		if(gReg.netTDS<3)
		{
			gReg.netTDS=3;
		}		
	}

	AppADCStop(ADC_CH_TDS_net);
}

void GetTDS_temp(void)
{
	AppADCStart(ADC_CH_TDS_temp);
}

void GetTDS_net(void)
{
	AppADCStart(ADC_CH_TDS_net);
}

void GetTDS_raw(void)
{
	AppADCStart(ADC_CH_TDS_raw);
}


void MonitorTDS(void)
{
	static INT8S EveryTimeGetTDSTime=60;
	
	if(gReg.WorkState!=WORKSTATE_working)//只有制水的时候才采样	
	{
		if(systemseting.FirstBootGetTDSFlag==0)//第一次上电
		{
			systemseting.FirstBootGetTDSFlag = 1;
			EveryTimeGetTDSTime = 30;
		}
		else 
		{
			EveryTimeGetTDSTime = 30;
		}	
		SetTDSUpdataEN(0);
		return;
	}

	EveryTimeGetTDSTime--;
	
	if(EveryTimeGetTDSTime<=1)
	{
		EveryTimeGetTDSTime = 6;//间隔6秒检测一次
		GetTDS_net();
		SetTDSUpdataEN(1);
	}
	else if(EveryTimeGetTDSTime==TDS_get_5s)
	{
		GetTDS_raw();
		GetTDS_temp();
	}	
	else if(EveryTimeGetTDSTime==TDS_get_20s)
	{
		GetTDS_net();//预采集
	}
	else if(EveryTimeGetTDSTime==TDS_get_29s)
	{
		GetTDS_raw();//预采集
		GetTDS_temp();
	}

}

