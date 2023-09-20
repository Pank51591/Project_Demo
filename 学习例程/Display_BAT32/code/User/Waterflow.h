#ifndef WATERFLOW_H
#define WATERFLOW_H






#define  C_FlowMeter1st_mLPerPulse       1.0823					//2000ml = 1848pulse
//#define  C_FlowMeter1st_mLPerPulse       1.1013					//1500ml = 1362pulse

#define  C_FlowMeter2nd_mLPerPulse       4.6083				//1000ml = 217pulse



typedef struct 
{
	uint8_t  PulseCnt;
	uint8_t  Err1Cnt;           	//�����Ƴ������
	uint8_t  Err2Cnt;           	//�����Ƴ������
	uint8_t  SensorError;       	//�����ƹ��ϣ���ˮ��ʱ�������壬����ˮ��ʱ������
	uint8_t  PulsePerSec;    	//ÿ��������
	uint32_t TotalPulse;				//�ܼ�������
	uint32_t PerPulse;
	uint32_t SampleTime;
	float VolumePerSec;						//ÿ��������λml
	uint32_t PerVolume;						//ÿ��������λml
	uint32_t TotalVolume;		//ÿ��������λml
}FlowMeterTypedef;








extern uint32_t 	SysTick1ms;
extern uint16_t 	SysTick1msD;
extern uint32_t 	SysTick1msC;

extern FlowMeterTypedef FlowMeter1st;
extern FlowMeterTypedef FlowMeter2nd;



void ExternalInterruptInit(void);
void UpdataFlowMeterWaterVolume(void);







#endif

