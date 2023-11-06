#ifndef WATERFLOW_H
#define WATERFLOW_H






#define  C_FlowMeter1st_mLPerPulse       1.0823					//2000ml = 1848pulse
//#define  C_FlowMeter1st_mLPerPulse       1.1013					//1500ml = 1362pulse

#define  C_FlowMeter2nd_mLPerPulse       4.6083				//1000ml = 217pulse



typedef struct 
{
	uint8_t  PulseCnt;
	uint8_t  Err1Cnt;           	//流量计出错计数
	uint8_t  Err2Cnt;           	//流量计出错计数
	uint8_t  SensorError;       	//流量计故障，无水流时产生脉冲，或有水流时无脉冲
	uint8_t  PulsePerSec;    	//每秒脉冲数
	uint32_t TotalPulse;				//总计脉冲数
	uint32_t PerPulse;
	uint32_t SampleTime;
	float VolumePerSec;						//每秒流量单位ml
	uint32_t PerVolume;						//每秒流量单位ml
	uint32_t TotalVolume;		//每秒流量单位ml
}FlowMeterTypedef;








extern uint32_t 	SysTick1ms;
extern uint16_t 	SysTick1msD;
extern uint32_t 	SysTick1msC;

extern FlowMeterTypedef FlowMeter1st;
extern FlowMeterTypedef FlowMeter2nd;



void ExternalInterruptInit(void);
void UpdataFlowMeterWaterVolume(void);







#endif

