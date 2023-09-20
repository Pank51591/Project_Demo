#include"config.h"
#include"appsystem.h"
#include"stdio.h"
#include <stdlib.h>



INT8U RecBuff[SERIAL_BUFF_NUM];
CODE INT8U Digitaltube[11]={0x3F,0x03,0x5D,0x4F,0x63,0x6E,0x7E,0x0B,0x7F,0x6F,0x7C};//0123456789E



SYSTEMSETING systemseting;
UARTPROC UartDispProc=ParsingDisplayData;//ModbusProc;
UARTPROC UartFaucetProc=Faucet_proc;
UARTPROC UartWifiProc=WifiMsgProc;
DISPLAY_REG gDisplayReg;
REG gReg;


void AppSystemInit(void)
{
	gReg.DeviceAddr = RS_ADDR;	
	gReg.ProductType = 0;
	gReg.productName = 0;
	gReg.ProductModel = 800;
	gReg.version = 0x2010;
	gReg.cmd = 0;
	
	gReg.fruits=1;
	gReg.error.BitFlag.sparklingWaterStatus = 1;
	
	systemseting.HVS_faucet=0;
	
	systemseting.uartdisplayError=0;
	systemseting.uartWifiError=0;
	systemseting.WaterFlowError=0;

	systemseting.PowerOnTimerCount=0;

	systemseting.uartFaucetTimeOutTime=20;//10s
	
}

//�ָ��������ã��ָ��������ã���о��������ˮ���������TDS��WIFI�������������㡣
void RestoreFactory(void)
{
	gReg.DeviceAddr = RS_ADDR;	
	gReg.ProductType = 0;
	gReg.productName = 0;
	gReg.ProductModel = 800;
	gReg.version = 0x2010;
	gReg.cmd = 0;

	gReg.WorkState = WORKSTATE_free;
	gReg.wifi = 0;
	gReg.PeriState.u16flag = 0;
	gReg.error.u16flag = 0;

	gReg.PowerOnTimeTotal_PCB=0;
	gReg.PumpWorkeTimeTotal_PCB=0;
	gReg.PowerOnTimeTotal_RO=0;
	gReg.PumpWorkeTimeTotal_RO=0;
	
	gReg.RawWaterVolume=0;
	gReg.NetWaterVolume=0;
	gReg.RawWaterVolumeSingle=0;
	gReg.NetWaterVolumeSingle=0;

	gReg.PriFilterResetTimes=0;
	gReg.RoFilterResetTimes=0;

	gReg.rawTDS=0;
	gReg.netTDS=0;

	gReg.SenFlag.rawTdsFlag = 1;
	gReg.SenFlag.pureTdsFlag = 1;

	gReg.fruits=1;
	gReg.error.BitFlag.sparklingWaterStatus = 1;

	systemseting.FirstBootGetTDSFlag = 0;
	systemseting.FirstBootFlushFlag = 0;
	
	UpdateFilterLife();	
}


//��ˮ������
void WaterCounter(void)
{
	INT32U val;
	//  2.0L/min     sec:33.3333ML     ms:33.3333UL  100ms:3333.33UL   600ms:20ML   20210425
	
	val = gReg.NetWaterVolume;
	val += 20;

	if(val>9999800)//����ˮ��Ϊ9999��������0��ʼ��
	{
		val = 0;
	}
	
	gReg.NetWaterVolume = val;
	//gReg.RawWaterVolume = val;


	if(gReg.WorkState!=WORKSTATE_working)
	{
		KillTimer(0, SYS_TIMER_WATERCOUNT);
	}

	systemseting.makewaterSingle+=20;
	
}


/*INT16U GetFilterLifeLevel(INT8U type)
{
	INT32S remain;
	INT16U FilterLife;

	if(type==FILTERTYPE_PCB)
	{
		remain = gReg.FilterLife_PCB;
	}
	else 
	{
		remain = gReg.FilterLife_RO;
	}

	if(remain>=60)//����720h
	{
		FilterLife = PCB_level_1;//
	}
	else if(remain>=30)
	{
		FilterLife = PCB_level_2;//
	}
	else if(remain>=10)
	{
		FilterLife = PCB_level_3;//
	}
	else if(remain>=1)
	{
		FilterLife = PCB_level_4;//
	}
	else //
	{
		FilterLife = PCB_level_5;
	}

	return FilterLife;
}*/


//��������������
INT16U FilterLifeLive(INT32U powerontime,INT32U pumptime,INT8U type)
{
	static INT32S makingRemained,remain;
//	INT16U FilterLife;

	if(type==FILTERTYPE_PCB)
	{
		//remain = ((PCB_PowerOnRemained_MAX - powerontime+86)*100)/PCB_PowerOnRemained_MAX;
		//makingRemained = ((PCB_MakingRemained_MAX - pumptime+1)*100)/PCB_MakingRemained_MAX;
		remain = ((PCB_PowerOnRemained_MAX - powerontime));
		makingRemained = ((PCB_MakingRemained_MAX - pumptime));		
	}
	else 
	{
		//remain = ((RO_PowerOnRemained_MAX - powerontime+345)*100)/RO_PowerOnRemained_MAX;
		//makingRemained = ((RO_MakingRemained_MAX - pumptime+1)*100)/RO_MakingRemained_MAX;
		remain = ((RO_PowerOnRemained_MAX - powerontime));
		makingRemained = ((RO_MakingRemained_MAX - pumptime));		
	}


	/*if(remain>makingRemained)
	{
		remain = makingRemained;
	}*/

	if((remain>(720*60))&&(makingRemained>(2.5*60)))//720h-2.4h 
	{
		remain = PCB_level_3;
	}
	else if(remain>0&&makingRemained>0)
	{
		remain = PCB_level_2;
	}
	else 
	{
		remain = PCB_level_1;
	}

	return remain;
}

INT16U FilterLifeCalculate(INT32U powerontime,INT32U pumptime,INT8U type)
{
	static INT32S makingRemained,remain;
	//INT16U FilterLife;

	if(type==FILTERTYPE_PCB)
	{
		remain = ((PCB_PowerOnRemained_MAX - powerontime+86)*100)/PCB_PowerOnRemained_MAX;
		makingRemained = ((PCB_MakingRemained_MAX - pumptime+1)*100)/PCB_MakingRemained_MAX;		
	}
	else 
	{
		remain = ((RO_PowerOnRemained_MAX - powerontime+345)*100)/RO_PowerOnRemained_MAX;
		makingRemained = ((RO_MakingRemained_MAX - pumptime+1)*100)/RO_MakingRemained_MAX;		
	}

	if(remain<0)
	{
		remain=0;
	}
	if(makingRemained<0)
	{
		makingRemained=0;
	}

	if(remain>makingRemained)
	{
		remain = makingRemained;
	}

	return remain;
}


void UpdateFilterLife(void)
{
	if(systemseting.FilterDetectionFlag)return;
	
	gReg.FilterLife_PCB = FilterLifeCalculate(gReg.PowerOnTimeTotal_PCB,gReg.PumpWorkeTimeTotal_PCB,FILTERTYPE_PCB);
	gReg.FilterLife_RO =  FilterLifeCalculate(gReg.PowerOnTimeTotal_RO,gReg.PumpWorkeTimeTotal_RO,FILTERTYPE_RO);
	
	systemseting.FilterLife_PCB = FilterLifeLive(gReg.PowerOnTimeTotal_PCB,gReg.PumpWorkeTimeTotal_PCB,FILTERTYPE_PCB);
	systemseting.FilterLife_RO =  FilterLifeLive(gReg.PowerOnTimeTotal_RO,gReg.PumpWorkeTimeTotal_RO,FILTERTYPE_RO);

	/*if(gReg.FilterLife_PCB==0||gReg.FilterLife_RO==0)//��ˮ���رս�ˮ������ѹ�á���ˮ������ֱ����λ�����е�����о�������ϵ����ʹ��
	{
		systemseting.LockWaterFlag = 1;
	}*/
}

void FilterReset_PCB(void)
{
	gReg.PowerOnTimeTotal_PCB = 0;
	gReg.PumpWorkeTimeTotal_PCB = 0;

	UpdateFilterLife();
}

void FilterReset_RO(void)
{
	gReg.PowerOnTimeTotal_RO = 0;
	gReg.PumpWorkeTimeTotal_RO = 0;

	UpdateFilterLife();
}

void ExitTimer(void)
{
	KillTimer(0, SYS_TIMERPUMP);
	KillTimer(0, SYS_TIMER_FLUSHTIME);
	KillTimer(0, SYS_TIMER_WATERCOUNT);
	KillTimer(0, SYS_TIMER_Backflow);
}

//��ˮ��
void SetInletValve(FlagStatus state)
{
	if(state==SET)SET_INLET_VALVE_PIN(SET);
	else SET_INLET_VALVE_PIN(RESET);
}

//��ˮ��2
void SetInletValve2(FlagStatus state)
{
	if(state==SET)SET_INLET_VALVE2_PIN(SET);
	else SET_INLET_VALVE2_PIN(RESET);
}

//��ˮ��
void SetWasteWaterValve(FlagStatus state)
{
	if(state==SET)SET_WASTE_VALVE_PIN(SET);
	else SET_WASTE_VALVE_PIN(RESET);
}

//��ѹ��
void SetBoosterPump(INT8U state)
{
	if(state==PUMP_OUT_24V)PUMP_24V_OUT;
	else if(state==PUMP_OUT_14V)PUMP_14V_OUT;
	else if(state==PUMP_OUT_6V)PUMP_6V_OUT;
	else
	{
		PUMP_OFF;
	}
}

void OpenPump(void)
{
	SetBoosterPump(PUMP_OUT_24V);

	if(gReg.WorkState==WORKSTATE_working)
	{
		TimeSetEvent(SYS_TIMER_WATERCOUNT, msc(600), WaterCounter, TIME_PERIODIC);//600ms��һ��
	}
}

void OpenPump_InletValve2(void)
{
	SetInletValve2(SET);
	SetBoosterPump(PUMP_OUT_24V);

	//if(gReg.WorkState==WORKSTATE_working)
	{
	//	TimeSetEvent(SYS_TIMER_WATERCOUNT, msc(600), WaterCounter, TIME_PERIODIC);//600ms��һ��
	}
}

void CloseInletValve(void)
{
	SetInletValve(RESET);//��ˮ��
}

void ExitAutoFlushing(void)
{
	gReg.WorkState = WORKSTATE_free;

	systemseting.AutoFlushFlag = 0;
	systemseting.makewaterTimer = 0;//ÿ�γ�ϴ�󣬽��ۼ���ˮ15���Ӽ�ʱ������

	SetWasteWaterValve(RESET);//��ˮ��
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��

	delayms(200);
	SetInletValve(RESET);//��ˮ��	
}

void EnterAutoFlushing(void)
{//��ϴʱ����������ˮ���ͷ�ˮ��������ʱ200ms������ѹ��
	ExitTimer();
	
	gReg.WorkState = WORKSTATE_autoflush;
	
	SetInletValve(SET);//��ˮ��1
	SetWasteWaterValve(SET);//��ˮ��

	TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, OpenPump, TIME_ONESHOT);//��ʱ200ms����ˮ��

	TimeSetEvent(SYS_TIMER_FLUSHTIME, sec(systemseting.AutoFlushtime), ExitAutoFlushing, TIME_ONESHOT);//�Զ���ϴ18��
}

void ExitManualFlush(void)
{
	ExitTimer();
	
	gReg.WorkState = WORKSTATE_free;

	systemseting.ManualFlushFlag=0;
	systemseting.PowerOnFlushFlag=0;
	systemseting.AutoFlushFlag=0;
	systemseting.makewaterTimer = 0;//ÿ�γ�ϴ�󣬽��ۼ���ˮ15���Ӽ�ʱ������

	if(systemseting.WorkingFlag==0)//�����ѹ���ػ�û�ص���
	{
		SetInletValve(RESET);//��ˮ��
		SetBoosterPump(PUMP_OUT_OFF);//��ѹ��		
	}
	SetWasteWaterValve(RESET);//��ˮ��
}

void EnterManualFlush(void)
{
	ExitTimer();

	gReg.WorkState = WORKSTATE_manualflush;

	SetInletValve(SET);//��ˮ��
	SetWasteWaterValve(SET);//��ˮ��

	TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, OpenPump, TIME_ONESHOT);//��ʱ200ms����ˮ��

	TimeSetEvent(SYS_TIMER_FLUSHTIME, sec(FLUSH_time_Manual), ExitManualFlush, TIME_ONESHOT);//�ֶ�����ϴ15��	
}

void EnterStandby(void)
{
	gReg.WorkState = WORKSTATE_standby;
}


//������ˮģʽ
void EnterWorkMode(void)
{
	ExitTimer();
	
	gReg.WorkState = WORKSTATE_working;

	systemseting.makewaterSingle = 0;
	systemseting.PerAutoRawUL=0;

	SetWasteWaterValve(RESET);//�رշ�ˮ��
	
	SetInletValve(SET);//�򿪽�ˮ��1
	
	TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, OpenPump, TIME_ONESHOT);//��ʱ200ms����ˮ��
}

//�˳���ˮģʽ
void ExitWorkMode(void)
{
	ExitTimer();
	
	gReg.RawWaterVolumeSingle = systemseting.makewaterSingle;
	gReg.NetWaterVolumeSingle = systemseting.PerAutoRawUL;
	
	KillTimer(0, SYS_TIMER_WATERCOUNT);
	
	gReg.WorkState = WORKSTATE_free;
	
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��
	
	delayms(200);
	SetInletValve(RESET);//��ˮ��
}


//�˳��ϵ��ϴ
void ExitPowerOnFlushing(void)
{
	gReg.WorkState = WORKSTATE_free;

	systemseting.PowerOnFlushFlag=0;

	SetWasteWaterValve(RESET);//��ˮ��
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��
	
	delayms(200);
	SetInletValve(RESET);//��ˮ��	
}

//�����ϵ��ϴ
void EnterPowerOnFlushing(void)
{
	ExitTimer();

	gReg.WorkState = WORKSTATE_PowerOnFlush;
	
	SetInletValve(SET);//��ˮ��1
	SetWasteWaterValve(SET);//��ˮ��
	TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, OpenPump, TIME_ONESHOT);//��ʱ200ms����ˮ��
	TimeSetEvent(SYS_TIMER_FLUSHTIME, sec(FLUSH_time_standby48h), ExitPowerOnFlushing, TIME_ONESHOT);//��ϴ60��
}

void EnterLongTimeWork(void)
{
	ExitTimer();
	
	gReg.WorkState = WORKSTATE_LongTimeWork;
	gReg.error.BitFlag.TimeOutErrorFlag=1;

	SetWasteWaterValve(RESET);//��ˮ��
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��	

	delayms(200);
	SetInletValve(RESET);//��ˮ��	
}

void ExitLongTimeWork(void)
{
	gReg.WorkState = WORKSTATE_free;
	gReg.error.BitFlag.TimeOutErrorFlag=0;
}

void EnterErrorMode(void)
{
	ExitTimer();
	
	gReg.WorkState = WORKSTATE_Leaking;
	
	SetBoosterPump(PUMP_OUT_OFF);//�رո�ѹ��
	SetWasteWaterValve(RESET);

	delayms(200);
	SetInletValve(RESET);//��ˮ��
}

void ExitErrorMode(void)
{
	gReg.WorkState = WORKSTATE_free;
}

void EnterLockWaterMode(void)
{
	ExitTimer();
	
	gReg.WorkState = WORKSTATE_LockWater;
	
	SetWasteWaterValve(RESET);//��ˮ��
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��	

	delayms(200);
	SetInletValve(RESET);//��ˮ��
}

void ExitLockWaterMode(void)
{
	gReg.WorkState = WORKSTATE_free;
}

void EnterFCTMode(void)
{
	gReg.WorkState = WORKSTATE_FCT;

	FCT_ModeInit();
	TimeSetEvent(SYS_TIMER_FCT, 10, FCT_Monitor, TIME_PERIODIC);
}

void ExitFCTMode(void)
{
	gReg.WorkState = WORKSTATE_free;

	KillTimer(0, SYS_TIMER_FCT);

	Modbus_SetReg(&gReg,sizeof(gReg)/2);
	UartDispProc = Faucet_proc;
	//UartWifiProc = WifiMsgProc;
	AppADCInit();
}

//����������ˮģʽ
void EnterLiveMode(void)
{
	gReg.WorkState = WORKSTATE_live;

	SetBoosterPump(PUMP_OUT_14V);//��ѹ��	
}

//�˳�������ˮģʽ
void ExitLiveMode(void)
{
	gReg.WorkState = WORKSTATE_free;
	systemseting.LiveFlag=0;
	
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��	
}

//�˳���ˮ����
void ExitBackFlowMode(void)
{
	ExitTimer();//uart_printf1("ExitBackFlowMode\n");
	
	gReg.WorkState = WORKSTATE_free;
	systemseting.BackflowFlag=0;
	
	SetBoosterPump(PUMP_OUT_OFF);//��ѹ��	
	SetInletValve2(RESET);//��ˮ��2
	delayms(200);
	SetInletValve(RESET);//��ˮ��1
}

//���봿ˮ����
void EnterBackFlowMode(void)
{
	ExitTimer();//uart_printf1("EnterBackFlowMode\n");
	
	gReg.WorkState = WORKSTATE_backflow;

	SetInletValve(SET);//��ˮ��1

	TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, OpenPump_InletValve2, TIME_ONESHOT);//��ʱ200ms����ˮ��
	TimeSetEvent(SYS_TIMER_Backflow, sec(BACKFLOW_time_run), ExitBackFlowMode, TIME_ONESHOT);//��ϴ60��
}

void SetAutoFlushFlag(INT8U flushtime)
{
	systemseting.AutoFlushFlag = 1;
	systemseting.AutoFlushtime = flushtime;
}

void ClearLongTimeWorkFlag(void)
{
	systemseting.makewaterTimer = 0;
	systemseting.LongTimeWorkTimesCount=0;//��ʱ����ˮ��������
	systemseting.LongTimeWorkFlag = 0;
	gReg.error.BitFlag.TimeOutErrorFlag=0;
}

void MonitorWater(void)
{
	static INT8U min=0,flag=0;
	SYSTEMTIME time;

	GetSystemTime(&time);

	if(time.Minute!=min)
	{
		min = time.Minute;

		
		gReg.PowerOnTimeTotal_PCB++;
		gReg.PowerOnTimeTotal_RO++;

		if(gReg.PowerOnTimeTotal_PCB>(PCB_PowerOnRemained_MAX+86))
		{
			gReg.PowerOnTimeTotal_PCB=PCB_PowerOnRemained_MAX+86;
		}
		if(gReg.PowerOnTimeTotal_RO>(RO_PowerOnRemained_MAX+345))
		{
			gReg.PowerOnTimeTotal_RO=RO_PowerOnRemained_MAX+345;
		}		
		
		if(gReg.WorkState==WORKSTATE_working)
		{
			gReg.PumpWorkeTimeTotal_PCB++;
			gReg.PumpWorkeTimeTotal_RO++;

			if(gReg.PumpWorkeTimeTotal_PCB>(PCB_MakingRemained_MAX+1))
			{
				gReg.PumpWorkeTimeTotal_PCB=PCB_MakingRemained_MAX+1;
			}
			if(gReg.PumpWorkeTimeTotal_RO>(RO_MakingRemained_MAX+1))
			{
				gReg.PumpWorkeTimeTotal_RO=RO_MakingRemained_MAX+1;
			}			
			
			systemseting.makewaterTimer++;

			systemseting.StandbyTimeCount=0;
			systemseting.BackflowFlag=0;//�������¼�ʱ

			if(systemseting.makewaterTimer==WORKING_ContinuousTime)
			{
				SetAutoFlushFlag(FLUSH_time_auto);//�ۼ���ˮ5min���Զ���ϴ20s
			}
			else if(systemseting.makewaterTimer>=WORKING_LongTime)//������������ˮ1Сʱ�����볤ʱ����ˮ����״̬
			{
				systemseting.LongTimeWorkFlag = 1;//E2 ��ʱ����ˮ����
				systemseting.LongTimeWorkTimesCount++;

				systemseting.makewaterTimer=0;

				SetBeep(30,1);//��30S
			}
		}
		else 
		{
			//systemseting.makewaterTimer = 0;
			
			if(++systemseting.StandbyTimeCount>=STANDBY_longtime)//��������48Сʱʱ
			{
				systemseting.StandbyTimeCount = 0;
				SetAutoFlushFlag(FLUSH_time_standby48h);
			}
			else if(systemseting.StandbyTimeCount==BACKFLOW_entertime1)//��ˮ����1
			{
				if(gReg.BackFlow)//����ʹ�ܲŽ�
				{
					if(flag)systemseting.BackflowFlag=1;//����1����
				}			
			}
			else if(systemseting.StandbyTimeCount==BACKFLOW_entertime2)//��ˮ����2
			{
				if(gReg.BackFlow)//����ʹ�ܲŽ�
				{
					if(flag)systemseting.BackflowFlag=1;//����1����
				}
			}			
			/*else if(systemseting.StandbyTimeCount==WORKING_ExitLongTime)
			{
				if(systemseting.LongTimeWorkFlag)//����Сʱ֮���������
				{
					if(systemseting.LongTimeWorkTimesCount<WORKING_LongTimeWorkTimesCount)//�������7���򲻽��������������ֶ��������������ϵ�
					{
						systemseting.LongTimeWorkFlag = 0;
					}
				}
			}*/			
		}

		UpdateFilterLife();
	}

	if(gReg.WorkState==WORKSTATE_working)
	{
		systemseting.StandbyTimeCount=0;
		flag=1;
	}
}

//������
BOOL PowerDownCheck(void)
{
	static INT8U count=0,flag = 1,powecount=30;

	if(powecount)//�����ʱ���ѹ���ȣ�������λ�������˵�
	{
		powecount--;
		return 0;
	}

	if(GET_POWERDOWN_PIN()==0)
	{
		count++;
		if(count>=2)//
		{
			count = 0;

			if(flag)
			{
				flag = 0;
				return TRUE;
			}	
		}
	}
	else 
	{
		count = 0;
	}

	return FALSE;
}

BOOL leakflag=0,pumpAflag=0;
#if 0
//©ˮ���
BOOL WaterLeakageCheck(void)
{
	static INT16U entercount=0,outcount=0;

	if(GET_LEAK_PIN())
	{
		outcount=0;
		if(gReg.leaking==0)
		{
			entercount++;
			if(entercount>=294)//��������⵽©ˮ����5�룬��������©ˮ����
			{
				entercount = 294;
				gReg.leaking = 1;
				return TRUE;
			}
		}
	}
	else 
	{	
		entercount=0;

		if(gReg.leaking)
		{
			outcount++;
			if(outcount>=294)
			{
				outcount = 294;
				gReg.leaking = 0;
				return TRUE;			
			}
		}
	}

	return FALSE;
}
#else
void GetLeakADC(INT16U ad)
{
	static INT8U count=0;
	
	if(ad>3673)
	{
		count++;
		
		if(count>=15) //20ms�ɼ�һ�Σ��ɼ�16�Σ�5000/20*16 �ͻ��޸���5�� (20)
		{
			count = 0;
			gReg.error.BitFlag.WaterLeakErrorFlag = 1;	
		}
	}
	else
	{
		if(count)count--;
	}

	leakflag=1;
}

#endif

//ˮ�õ���
void GetPumpADC(INT16U ad)
{
	static INT16U pumpcurrent=0;

	if(gReg.WorkState == WORKSTATE_working)
	{
		if(ad < PUMP_OFF_ad_val)
		{
			if(++pumpcurrent > 20)
			{
				pumpcurrent = 20;
				
				SetInletValve(SET);//�򿪽�ˮ��
				TimeSetEvent(SYS_TIMERPUMP, PUMP_open_delaytime, OpenPump, TIME_ONESHOT);//��ʱ200ms����ˮ��
			}
		}
		else
		{
			if(pumpcurrent ) --pumpcurrent;
		}
	}
	else
	{
		pumpcurrent = 0;
	}	

	pumpAflag=1;
}

//��ѹ���ؼ��
BOOL GetHVSstate(void)
{
	static INT8U count=0;
	static INT8U old=0xff;
	
	if(GET_HVS_PIN()!=old)
	{
		count++;
		if(count>=5)//����⵽��ѹ���رպϳ���50����
		{
			count=3;
			old = GET_HVS_PIN();
			systemseting.HVS = old;

			return TRUE;
		}
	}
	else 
	{
		count = 0;
	}
	
	return FALSE;
}


void ExitProc(void)
{
	switch(gReg.WorkState)  
	{
	case WORKSTATE_FCT:
	{
		if(systemseting.FCTFlag==0)
		{
			ExitFCTMode();
		}		
	}break;	
	case WORKSTATE_PowerOnProc:
	{
		if(systemseting.PowerOnProcFlag==0)
		{
			gReg.WorkState = WORKSTATE_free;
		}		
	}break;	
	case WORKSTATE_FilterDetection:
	{
		if(systemseting.FilterDetectionFlag==0)
		{
			ExitFilterFast();
		}		
	}break;		
	case WORKSTATE_WaterDetection:
	{
		if(systemseting.WaterDetectionFlag==0)
		{
			ExitWaterDetection();
		}		
	}break;		
	case WORKSTATE_GasDetection:
	{
		if(systemseting.GasDetectionFlag==0)
		{
			ExitGasDetection();
		}		
	}break;	
	case WORKSTATE_LockWater:
	{
		if(systemseting.LockWaterFlag==0)
		{
			ExitLockWaterMode();
		}
	}break;	
	case WORKSTATE_Leaking:
	{
		if(systemseting.LeakFlag==0)
		{
			ExitErrorMode();
		}
	}break;
	case WORKSTATE_PowerOnFlush:
	{	
		if(systemseting.PowerOnFlushFlag==0)
		{
			ExitPowerOnFlushing();
		}
	}break;
	case WORKSTATE_LongTimeWork:
	{
		if(systemseting.LongTimeWorkFlag==0)
		{
			ExitLongTimeWork();
		}	
	}break;
	case WORKSTATE_manualflush:
	{
		if(systemseting.ManualFlushFlag==0)
		{
			ExitManualFlush();
		}
	}break;
	case WORKSTATE_live:
	{
		if(systemseting.LiveFlag==0)
		{
			ExitLiveMode();
		}
	}break;		
	case WORKSTATE_working:
	{
		if(systemseting.WorkingFlag==0)
		{
			ExitWorkMode();
		}
	}break;
	case WORKSTATE_autoflush:
	{
		if(systemseting.AutoFlushFlag==0)
		{
			ExitAutoFlushing();
		}
	}break;
	case WORKSTATE_backflow:
	{
		if(systemseting.BackflowFlag==0)
		{
			ExitBackFlowMode();
		}
	}break;	
	case WORKSTATE_free:
	{

	}break;
	case WORKSTATE_standby:
	{

	}break;
	}

}

void EnterProc(void)
{

	if(systemseting.FCTFlag)
	{
		if(gReg.WorkState!=WORKSTATE_FCT)
		{
			EnterFCTMode();
		}
	}
	else if(systemseting.PowerOnProcFlag)
	{
		gReg.WorkState = WORKSTATE_PowerOnProc;
	}
	else if(systemseting.GasDetectionFlag)
	{
		EnterFactoryMode(WORKSTATE_GasDetection);	
	}
	else if(systemseting.WaterDetectionFlag)
	{
		EnterFactoryMode(WORKSTATE_WaterDetection);
	}
	else if(systemseting.FilterDetectionFlag)
	{
		EnterFactoryMode(WORKSTATE_FilterDetection);
	}
	else if(systemseting.LockWaterFlag)
	{
		if(gReg.WorkState!=WORKSTATE_LockWater)
		{	
			EnterLockWaterMode();
		}
	}
	else if(systemseting.LeakFlag)
	{
		if(gReg.WorkState!=WORKSTATE_Leaking)
		{
			EnterErrorMode();
		}
	}
	else if(systemseting.PowerOnFlushFlag)
	{
		if(gReg.WorkState!=WORKSTATE_PowerOnFlush)
		{	
			EnterPowerOnFlushing();
		}
	}
	else if(systemseting.LongTimeWorkFlag)
	{
		if(gReg.WorkState!=WORKSTATE_LongTimeWork)
		{	
			EnterLongTimeWork();
		}
	}
	else if(systemseting.ManualFlushFlag)
	{
		if(gReg.WorkState!=WORKSTATE_manualflush)
		{	
			EnterManualFlush();
		}
	}
	else if(systemseting.LiveFlag)
	{
		if(gReg.WorkState!=WORKSTATE_live)
		{	
			EnterLiveMode();	
		}
	}	
	else if(systemseting.WorkingFlag)
	{
		if(gReg.WorkState!=WORKSTATE_working)
		{	
			EnterWorkMode();	
		}
	}	
	else if(systemseting.AutoFlushFlag)
	{
		if(gReg.WorkState!=WORKSTATE_autoflush)
		{	
			EnterAutoFlushing();
		}
	}
	else if(systemseting.BackflowFlag)
	{
		if(gReg.WorkState!=WORKSTATE_backflow)
		{	
			EnterBackFlowMode();
		}
	}	
	else if(systemseting.StandbyFlag)
	{
		if(gReg.WorkState!=WORKSTATE_standby)
		{	
			EnterStandby();
		}
	}
}


void CheckFlushState(void)
{
	if(gReg.WorkState==WORKSTATE_autoflush
	||gReg.WorkState==WORKSTATE_manualflush
	||gReg.WorkState==WORKSTATE_PowerOnFlush)
	{
		gReg.PeriState.BitFlag.flush = 1;
	}
	else 
	{
		gReg.PeriState.BitFlag.flush = 0;
	}
}

void Faucet_UartErrorCheck(void)
{
	systemseting.uartFaucetTimeOutCnt++;
	
	if(systemseting.uartFaucetTimeOutCnt>systemseting.uartFaucetTimeOutTime)//�ϵ�10��δ�յ�����֮��120sû�յ�
	{
		systemseting.uartFaucetTimeOutCnt=systemseting.uartFaucetTimeOutTime;
		systemseting.uartFaucetError=1;
	}
	else 
	{
		systemseting.uartFaucetError=0;
	}
}

//ˮ��ͷ��ѹ���أ�������ˮ
void MonitorHVS_Faucet(void)
{
	static INT16U opencount=0;

	Faucet_UartErrorCheck();

	if(gReg.WorkState==WORKSTATE_live)
	{
		if(systemseting.ElectrolyticFlag)
		{
			ELECTROLYTIC_STRIP_PIN_LEVEL_1;//uart_printf1("open djm \n");
		}
		else 
		{
			ELECTROLYTIC_STRIP_PIN_LEVEL_0;//uart_printf1("close djm \n");
		}
	
		if(systemseting.FlowMeterBeforeVelocity>=1000)//�򿪵��Ƭ
		{
			if(opencount==0)
			{
				opencount++;
				if(gReg.fruits)//�߹�������ʱ��Ŵ򿪵��Ĥ
				{
					systemseting.ElectrolyticFlag=1;
				}
			}
			else if(systemseting.ElectrolyticFlag)
			{
				if(++opencount>900)//15����
				{
					systemseting.ElectrolyticFlag=0;
				}
			}
		}
		else if(systemseting.FlowMeterBeforeVelocity<=500)//�رյ��ģ
		{
			opencount=0;
			systemseting.ElectrolyticFlag=0;
		}
	}
	else 
	{
		opencount=0;
		ELECTROLYTIC_STRIP_PIN_LEVEL_0;
		systemseting.ElectrolyticFlag=0;
	}


	if(systemseting.HVS_faucet)//������ˮ��ѹ����
	{
		systemseting.LiveFlag=1;
		if(++systemseting.FaucetGetCmdCount>3)
		{
			systemseting.HVS_faucet=0;
		}		
	}
	else 
	{
		systemseting.LiveFlag=0;
		systemseting.FaucetGetCmdCount=0;
	}
	//uart_printf1("HVS_faucet=%d   LiveFlag=%d  gReg.WorkState=%d\n",systemseting.HVS_faucet,systemseting.LiveFlag,gReg.WorkState);
}


void powerDownSave(void)
{
	static INT8U count=0;

	if(++count>=2)
	{
		KillTimer(0, SYS_TIMER_powerdownsave);
	}
	gReg.WorkState = WORKSTATE_PowerDown;
	fctReg.WorkState = WORKSTATE_PowerDown;
	//SendModbusRegData(MODBUS_CMD_03,0,7);
}

void WifiErrorTimeOut(void)
{
	static INT16U timecount=0;//10ms����һ��

	if(gReg.WorkState==WORKSTATE_working
	||gReg.WorkState==WORKSTATE_autoflush
	||gReg.WorkState==WORKSTATE_manualflush
	||systemseting.HVS_faucet)
	{
		systemseting.uartWifiError=0;
	}

	if(systemseting.uartWifiError)
	{
		if(++timecount>6000)//1����
		{
			systemseting.uartWifiError=0;
		}
	}
	else 
	{
		timecount=0;
	}
}


void PCB_RO_Warning(void)
{
	static INT8U flag=0;

	if(gReg.WorkState==WORKSTATE_working)//ÿ����ˮ
	{
		if(flag)
		{
			flag=0;
			
			if((systemseting.FilterLife_PCB==PCB_level_1)||(systemseting.FilterLife_RO==PCB_level_1))
			{
				SetBeep(10,1);
			}	
			else if((systemseting.FilterLife_PCB==PCB_level_2)||(systemseting.FilterLife_RO==PCB_level_2))
			{
				SetBeep(5,1);
			}
		}	
	}
	else 
	{
		flag=1;
	}
}


//״̬���
void MonitorState(void)
{
	if(PowerDownCheck())//������
	{
		if(gReg.WorkState!=WORKSTATE_FCT)
		{
			SaveSysSeting();
			gReg.WorkState = WORKSTATE_PowerDown;
		}
		else 
		{
			fctReg.WorkState = WORKSTATE_PowerDown;
		//	SendModbusRegData(MODBUS_CMD_03,0,7);
		}
		
		TimeSetEvent(SYS_TIMER_powerdownsave, 100, powerDownSave, TIME_PERIODIC);
	}
	//else if(WaterLeakageCheck())//©ˮ���
	else if(gReg.error.BitFlag.WaterLeakErrorFlag)
	{
		systemseting.LeakFlag=1;
	}
	else if(GetHVSstate())//��ˮ���
	{
		if(systemseting.HVS==0)//������ˮ״̬
		{
			systemseting.WorkingFlag=1;
		}
		else 
		{
			systemseting.WorkingFlag=0;
		}
	}

	WifiErrorTimeOut();

	CheckFlushState();

	ExitProc();
	EnterProc();

	//uart_printf("WorkState=%d   ElectrolyticFlag=%d\n",gReg.WorkState,systemseting.ElectrolyticFlag);
}


BOOL SendDisplayMsg(INT8U *pdat,INT8U len)
{
	INT8U buf[10],*pbuf;
	int i,datalen=2;

	pbuf=buf;

	*pbuf++ = 0xFF;//ͷ
	*pbuf++ = 0XFF;
	*pbuf++ = 0x06;//���ݳ���
	*pbuf++ = 0x01;//��ַ��

	for( i=0;i<datalen;i++)//������Ϣ
	{
		*pbuf = *pdat++;
		
		if(*pbuf==0xFF){pbuf++;*pbuf = 0x55;len++;}
		
		pbuf++;	
	}
	
	*pbuf++ = GetSum(buf+2,len+2);//�ۼӺ�

	if(*pbuf==0xFF){pbuf++;*pbuf = 0x55;len++;}

	len+=5;
	
	UartSendDisplayData(buf,len);
	
	return TRUE;
}

//������ȡ
void ParsingDisplayData(INT8U *pbuff,INT16U len)
{
	/*if(pbuff[0]==0xFA)
	{
		systemseting.displaydelaysend=40;
		//ModbusProc(pbuff,len);
		return;
	}*/

	if((pbuff[0]==0x5A)&&(pbuff[1]==0xA5)&&(pbuff[2]==0x06))//FCT
	{
		FCT_rg_main(pbuff,len);
	}

	if(pbuff[len-1]!=GetSum(pbuff+2,len-3))
	{
		return;
	}	

	len=GetCommData(pbuff,len);//ȥ��������FF���ݺ����55

	Uart_KeyHandle(pbuff,len);

	return;	
}

BOOL DisplayError(void)
{
	if(gReg.WorkState==WORKSTATE_LongTimeWork)//��ʱ����ˮ
	{
		gDisplayReg.run_w_en = 1;gDisplayReg.run_w_flash = 1;
		gDisplayReg.pcb_w_en = 1;gDisplayReg.pcb_w_flash = 1;
		gDisplayReg.ro_w_en = 1;gDisplayReg.ro_w_flash = 1;
		gDisplayReg.wifi_w_en = 1;gDisplayReg.wifi_w_flash = 1;

		return 1;
	}
	return 0;
}

void DesktopUpdate(void)
{
	if(systemseting.PowerOnProcFlag)
	{
		return;
	}
	memset((INT8U*)&gDisplayReg,0x00,sizeof(DISPLAY_REG));

	if(DisplayError())
	{
		Uart_SendDisplay((INT8U*)&gDisplayReg,2);
		return;
	}
	
	if(gReg.WorkState==WORKSTATE_working){gDisplayReg.run_w_en = 1;}//����ͼ��
	else if(gReg.WorkState==WORKSTATE_autoflush||gReg.WorkState==WORKSTATE_manualflush||gReg.WorkState==WORKSTATE_PowerOnFlush){gDisplayReg.run_w_en = 1;gDisplayReg.run_w_flash = 1;}
	else if(gReg.WorkState==WORKSTATE_backflow){gDisplayReg.run_r_en = 1;gDisplayReg.run_r_flash = 1;}
	else {gDisplayReg.run_w_en = 0;}
	
	if(systemseting.FilterLife_PCB==PCB_level_3){gDisplayReg.pcb_w_en = 1;gDisplayReg.pcb_w_flash = 0;}//PCB
	else if(systemseting.FilterLife_PCB==PCB_level_2){gDisplayReg.pcb_r_en = 1;gDisplayReg.pcb_r_flash = 1;}
	else {gDisplayReg.pcb_r_en = 1;gDisplayReg.pcb_r_flash = 0;}

	if(systemseting.FilterLife_RO==PCB_level_3){gDisplayReg.ro_w_en = 1;gDisplayReg.ro_w_flash = 0;}//RO
	else if(systemseting.FilterLife_RO==PCB_level_2){gDisplayReg.ro_r_en = 1;gDisplayReg.ro_r_flash = 1;}
	else {gDisplayReg.ro_r_en = 1;gDisplayReg.ro_r_flash = 0;}

	if(gReg.wifi==2){gDisplayReg.wifi_w_en = 1;}//WIFI
	else if(gReg.wifi==1){gDisplayReg.wifi_w_en = 1;gDisplayReg.wifi_w_flash = 1;}
	else {gDisplayReg.wifi_w_en = 0;}

	PCB_RO_Warning();
	
	Uart_SendDisplay((INT8U*)&gDisplayReg,2);

	//SendDisplayMsg((INT8U*)&buf,2);

	//uart_printf("temp11=%d  temp2=%d  rawtds=%d  nettds=%d  leak=%d  \n",gTDSTemp,gTDSTemp2,gReg.rawTDS,gReg.netTDS,gReg.error.BitFlag.WaterLeakErrorFlag);
	//uart_printf("wifi=%d \n",gReg.wifi);
}

void DisplayUpdate(void)
{
	if(systemseting.PowerOnTimerCount<400)systemseting.PowerOnTimerCount++;
	SendMessage(0, WM_DISPLAY, 0);

	systemseting.flash = ~systemseting.flash;

	MonitorHVS_Faucet();//ˮ��ͷ��ѹ���ؼ��
}

void ResetPowerOnFlushFlag(void)
{
	systemseting.PowerOnFlushFlag=0;
}

void Standby(void)
{	
	if(gReg.WorkState==WORKSTATE_free)
	{
		if(systemseting.uartdisplayError
		||systemseting.uartFaucetError
		||systemseting.WaterFlowError
		||systemseting.uartWifiError)
		{
			systemseting.BackTimerCount=0;
			return;//�й��ϲ�����˯��
		}

		if(++systemseting.BackTimerCount>600)//120 10����
		{	
			systemseting.BackTimerCount=120;
			gReg.WorkState=WORKSTATE_standby;
		}
	}
	else 
	{
		systemseting.BackTimerCount=0;
	}
}

void StandbyRestart(void)
{
	if(gReg.WorkState==WORKSTATE_standby)
	{
		gReg.WorkState=WORKSTATE_free;
	}
	
	systemseting.BackTimerCount=0;
	TimeSetEvent(SYS_TIMER_BACKLIGHT,sec(1), Standby, TIME_PERIODIC);
}

void WinTimerOut(void)
{
	if(++systemseting.WinTimerCount<15)return;

	systemseting.WinTimerCount=0;
	systemseting.WinTimerOutFlag=1;

	KillTimer(0, SYS_TIMER_WINTIMEOUT);
}

//�ر���������
void CloseAllPeripheral(void)
{
	//�ر�����
	SetInletValve(RESET);//
	SetBoosterPump(PUMP_OUT_OFF);//�رո�ѹ��
	SetWasteWaterValve(RESET);

	//��������һ���ϵ����
	SetBeep(1, 1);

	//�ϵ���ϴ
	systemseting.PowerOnProcFlag = 0;
	systemseting.PowerOnFlushFlag = 1;

	//SendModbusRegData(MODBUS_CMD_03,0,sizeof(REG)/2);

	//�ر�������ʾ
	memset((INT8U*)&gDisplayReg,0x00,sizeof(DISPLAY_REG));
	
	if(systemseting.FirstBootFlushFlag)
	{
		TimeSetEvent(SYS_TIMER_POWERON_DISP,sec(FLUSH_time_PowerOn), ResetPowerOnFlushFlag, TIME_ONESHOT);//�ϵ���ϴ60����
	}
	else //�״��ϵ��ϴ
	{
		systemseting.FirstBootFlushFlag = 1;
		TimeSetEvent(SYS_TIMER_POWERON_DISP,sec(FLUSH_time_FirstPowerOn), ResetPowerOnFlushFlag, TIME_ONESHOT);//�ϵ��ϴ30����
	}
}


void LEDLight(void)
{
	//
	memset((INT8U*)&gDisplayReg,0x00,sizeof(DISPLAY_REG));
	gDisplayReg.run_w_en=1;
	gDisplayReg.pcb_r_en=1;
	gDisplayReg.ro_r_en=1;
	gDisplayReg.wifi_w_en=1;
	Uart_SendDisplay((INT8U*)&gDisplayReg,sizeof(DISPLAY_REG));

	TimeSetEvent(SYS_TIMER_POWERON_DISP,1000, CloseAllPeripheral, TIME_ONESHOT);//�ϵ���ʾ
}

void Beepring(void)
{
	//�����2��
	memset((INT8U*)&gDisplayReg,0x00,sizeof(DISPLAY_REG));
	gDisplayReg.run_r_en=1;
	gDisplayReg.pcb_r_en=1;
	gDisplayReg.ro_r_en=1;
	gDisplayReg.wifi_r_en=1;
	Uart_SendDisplay((INT8U*)&gDisplayReg,sizeof(DISPLAY_REG));  

	TimeSetEvent(SYS_TIMER_POWERON_DISP,1000, LEDLight, TIME_ONESHOT);//�ϵ���ʾ
}

void PowerOnDisplay(void)
{
	//�����ϵ����ʾ�塢��ͷ��ʾ�����а׵�ȫ����ʾ1��
	memset((INT8U*)&gDisplayReg,0x00,sizeof(DISPLAY_REG));
	gDisplayReg.run_w_en=1;
	gDisplayReg.pcb_w_en=1;
	gDisplayReg.ro_w_en=1;
	gDisplayReg.wifi_w_en=1;
	Uart_SendDisplay((INT8U*)&gDisplayReg,sizeof(DISPLAY_REG));

	systemseting.PowerOnProcFlag = 1;

	TimeSetEvent(SYS_TIMER_POWERON_DISP,1000, Beepring, TIME_ONESHOT);//�ϵ���ʾ
}

