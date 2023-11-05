#include"config.h"
#include"FactoryMode.h"



void EnterFactoryMode(INT8U mode)
{
	gReg.WorkState = mode;
	
	systemseting.StandbyFlag=0;
	systemseting.FreeFlag=0;
	systemseting.AutoFlushFlag=0;//自动冲洗标志
	systemseting.WorkingFlag=0;
	systemseting.ManualFlushFlag=0;
	//systemseting.LongTimeWorkFlag=0;//E2 长时间制水
	systemseting.PowerOnFlushFlag=0;//上电清洗标志
	//systemseting.ErrorFlag=0;//E1漏水
	//systemseting.FCTFlag=0;

}



void ExitGasDetection(void)
{
	KillTimer(0, SYS_TIMER_FACTORYMODE);
	systemseting.GasDetectionFlag=0;

	gReg.WorkState = WORKSTATE_free;

	SetInletValve(RESET);//进水阀
	SetWasteWaterValve(RESET);//废水阀  
}

void ExitWaterDetection(void)
{
	KillTimer(0, SYS_TIMER_FACTORYMODE);
	systemseting.WaterDetectionFlag=0;

	gReg.WorkState = WORKSTATE_free;
	
	SetInletValve(RESET);//进水阀
	SetWasteWaterValve(RESET);//废水阀
	SetBoosterPump(PUMP_OUT_OFF);//曾压泵

}

void ExitFilterFast(void)
{
	systemseting.FilterDetectionFlag=0;

	gReg.WorkState = WORKSTATE_free;
	
	UpdateFilterLife();
	
	KillTimer(0, SYS_TIMER_FACTORYMODE);
}

//工厂气检模式：所有阀类通电开启，时间持续15分钟；
void GasDetection(void)
{
	systemseting.GasDetectionFlag=1;	

	SetInletValve(SET);//进水阀
	SetWasteWaterValve(SET);//废水阀

	SetBoosterPump(PUMP_OUT_OFF);//关闭曾压泵
	
	TimeSetEvent(SYS_TIMER_FACTORYMODE, min(15), ExitGasDetection, TIME_ONESHOT);//15分钟
}

void delayopenpump(void)
{
	SetBoosterPump(PUMP_OUT_24V);//曾压泵
}
//工厂水检模式：增压泵开启，所有阀类通电开启，时间持续15分钟；
void WaterDetection(void)
{
	systemseting.WaterDetectionFlag=1;	

	SetInletValve(SET);//进水阀
	SetWasteWaterValve(SET);//废水阀

	TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, delayopenpump, TIME_ONESHOT);//延时200ms开启水泵
	TimeSetEvent(SYS_TIMER_FACTORYMODE, min(15), ExitWaterDetection, TIME_ONESHOT);//15分钟
}


static INT32U powerPCB=0,powerRO=0;

void FilterFast(void)
{
	static INT8U count=0;

	powerPCB += (720*60);
	powerRO += (720*60);
	
	if(powerPCB>PCB_PowerOnRemained_MAX)
	{
		powerPCB = PCB_PowerOnRemained_MAX;
	}
	if(powerRO>RO_PowerOnRemained_MAX)
	{
		powerRO = RO_PowerOnRemained_MAX;
	}

	gReg.FilterLife_PCB = FilterLifeCalculate(powerPCB,gReg.PumpWorkeTimeTotal_PCB,FILTERTYPE_PCB);
	gReg.FilterLife_RO  = FilterLifeCalculate(powerRO,gReg.PumpWorkeTimeTotal_RO,FILTERTYPE_RO);

	if(gReg.FilterLife_PCB==0&&gReg.FilterLife_RO==0)
	{
		count++;

		if(count>5)
		{
			count = 0;
			ExitFilterFast();
		}
	}
}

//上电10秒内，三击两键后，再短按“选择”，最后短按“复位”，进滤芯快检。途中必须满足这个顺序，
//不然就不再进入（后台操作不写进说明书）。蜂鸣器鸣叫三声，水泵关闭，原水阀关闭，冲洗阀关闭。
//进入快检模式后，实际滤芯剩余上电寿命，以720小时在滤芯快检模式下等于1s计算，用于模拟滤芯使
//用寿命到后的显示情况。例如：当某个滤芯寿命到后，滤芯对应灯红色常亮，蜂鸣器响5声，1秒1声；
//滤芯寿命未到，滤芯对应灯白色或橙色常亮。机器在所有滤芯到达寿命后，5秒内维持显示状态，若5S
//内无任意操作则自动退出快检模式，回到正常工作模式；或机器在进入快检模式到自动退出的时间段内
//按任意按键或断电，退出快检模式。滤芯寿命快检模式下计算的滤芯寿命不能有掉电记忆。
void FilterDetection(void)
{
	systemseting.FilterDetectionFlag=1;
	
	powerPCB = gReg.PowerOnTimeTotal_PCB;
	powerRO = gReg.PowerOnTimeTotal_RO;
	

	SetInletValve(RESET);//进水阀
	SetWasteWaterValve(RESET);//废水阀

	SetBoosterPump(PUMP_OUT_OFF);//关闭曾压泵
	
	TimeSetEvent(SYS_TIMER_FACTORYMODE, sec(1), FilterFast, TIME_PERIODIC);//
}

void ExitFactoryMode(void)
{
	if(systemseting.GasDetectionFlag)
	{
		ExitGasDetection();
	}
	else if(systemseting.WaterDetectionFlag)
	{
		ExitWaterDetection();
	}
	else if(systemseting.FilterDetectionFlag)
	{
		ExitFilterFast();
	}
}

