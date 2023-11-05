#include"config.h"
#include"FactoryMode.h"



void EnterFactoryMode(INT8U mode)
{
	gReg.WorkState = mode;
	
	systemseting.StandbyFlag=0;
	systemseting.FreeFlag=0;
	systemseting.AutoFlushFlag=0;//�Զ���ϴ��־
	systemseting.WorkingFlag=0;
	systemseting.ManualFlushFlag=0;
	//systemseting.LongTimeWorkFlag=0;//E2 ��ʱ����ˮ
	systemseting.PowerOnFlushFlag=0;//�ϵ���ϴ��־
	//systemseting.ErrorFlag=0;//E1©ˮ
	//systemseting.FCTFlag=0;

}



void ExitGasDetection(void)
{
	KillTimer(0, SYS_TIMER_FACTORYMODE);
	systemseting.GasDetectionFlag=0;

	gReg.WorkState = WORKSTATE_free;

	SetInletValve(RESET);//��ˮ��
	SetWasteWaterValve(RESET);//��ˮ��  
}

void ExitWaterDetection(void)
{
	KillTimer(0, SYS_TIMER_FACTORYMODE);
	systemseting.WaterDetectionFlag=0;

	gReg.WorkState = WORKSTATE_free;
	
	SetInletValve(RESET);//��ˮ��
	SetWasteWaterValve(RESET);//��ˮ��
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��

}

void ExitFilterFast(void)
{
	systemseting.FilterDetectionFlag=0;

	gReg.WorkState = WORKSTATE_free;
	
	UpdateFilterLife();
	
	KillTimer(0, SYS_TIMER_FACTORYMODE);
}

//��������ģʽ�����з���ͨ�翪����ʱ�����15���ӣ�
void GasDetection(void)
{
	systemseting.GasDetectionFlag=1;	

	SetInletValve(SET);//��ˮ��
	SetWasteWaterValve(SET);//��ˮ��

	SetBoosterPump(PUMP_OUT_OFF);//�ر���ѹ��
	
	TimeSetEvent(SYS_TIMER_FACTORYMODE, min(15), ExitGasDetection, TIME_ONESHOT);//15����
}

void delayopenpump(void)
{
	SetBoosterPump(PUMP_OUT_24V);//��ѹ��
}
//����ˮ��ģʽ����ѹ�ÿ��������з���ͨ�翪����ʱ�����15���ӣ�
void WaterDetection(void)
{
	systemseting.WaterDetectionFlag=1;	

	SetInletValve(SET);//��ˮ��
	SetWasteWaterValve(SET);//��ˮ��

	TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, delayopenpump, TIME_ONESHOT);//��ʱ200ms����ˮ��
	TimeSetEvent(SYS_TIMER_FACTORYMODE, min(15), ExitWaterDetection, TIME_ONESHOT);//15����
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

//�ϵ�10���ڣ������������ٶ̰���ѡ�񡱣����̰�����λ��������о��졣;�б����������˳��
//��Ȼ�Ͳ��ٽ��루��̨������д��˵���飩������������������ˮ�ùرգ�ԭˮ���رգ���ϴ���رա�
//������ģʽ��ʵ����оʣ���ϵ���������720Сʱ����о���ģʽ�µ���1s���㣬����ģ����оʹ
//�������������ʾ��������磺��ĳ����о����������о��Ӧ�ƺ�ɫ��������������5����1��1����
//��о����δ������о��Ӧ�ư�ɫ���ɫ������������������о����������5����ά����ʾ״̬����5S
//��������������Զ��˳����ģʽ���ص���������ģʽ��������ڽ�����ģʽ���Զ��˳���ʱ�����
//�����ⰴ����ϵ磬�˳����ģʽ����о�������ģʽ�¼������о���������е�����䡣
void FilterDetection(void)
{
	systemseting.FilterDetectionFlag=1;
	
	powerPCB = gReg.PowerOnTimeTotal_PCB;
	powerRO = gReg.PowerOnTimeTotal_RO;
	

	SetInletValve(RESET);//��ˮ��
	SetWasteWaterValve(RESET);//��ˮ��

	SetBoosterPump(PUMP_OUT_OFF);//�ر���ѹ��
	
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

