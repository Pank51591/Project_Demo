#ifndef APPSYSTEM_H
#define APPSYSTEM_H


// ���Ƭ
#define ELECTROLYTIC_STRIP_PIN_LEVEL_0   PORT_ClrBit(PORT7,PIN4)
#define ELECTROLYTIC_STRIP_PIN_LEVEL_1   PORT_SetBit(PORT7,PIN4)

//��ѹ��
#define PUMP_ENABLE_PIN_LEVEL_0   PORT_ClrBit(PORT3,PIN1)
#define PUMP_ENABLE_PIN_LEVEL_1   PORT_SetBit(PORT3,PIN1)

#define PUMP_VOLTAGE_6V_14V_PIN_LEVEL_0   PORT_ClrBit(PORT6,PIN3)
#define PUMP_VOLTAGE_6V_14V_PIN_LEVEL_1   PORT_SetBit(PORT6,PIN3)

#define PUMP_VOLTAGE_24V_PIN_LEVEL_0   	PORT_ClrBit(PORT7,PIN5)
#define PUMP_VOLTAGE_24V_PIN_LEVEL_1   	PORT_SetBit(PORT7,PIN5)

#define PUMP_OFF		do {(PUMP_ENABLE_PIN_LEVEL_0); (PORT_Init(PORT6,PIN3,INPUT));PUMP_VOLTAGE_24V_PIN_LEVEL_0;} while(0)
#define PUMP_6V_OUT		do {(PUMP_ENABLE_PIN_LEVEL_1); (PORT_Init(PORT6,PIN3,INPUT));PUMP_VOLTAGE_24V_PIN_LEVEL_0;} while(0)
#define PUMP_14V_OUT	do {(PUMP_ENABLE_PIN_LEVEL_1); (PORT_Init(PORT6,PIN3,OUTPUT));(PUMP_VOLTAGE_6V_14V_PIN_LEVEL_0);PUMP_VOLTAGE_24V_PIN_LEVEL_0;} while(0)
#define PUMP_24V_OUT	do {(PUMP_ENABLE_PIN_LEVEL_0); (PORT_Init(PORT6,PIN3,INPUT));(PUMP_VOLTAGE_24V_PIN_LEVEL_1); } while(0)

#define PUMP_OUT_24V		(3)// ���24V
#define PUMP_OUT_14V		(2)// ���14V
#define PUMP_OUT_6V			(1)// ���6V
#define PUMP_OUT_OFF		(0)//


#define GET_HVS_PIN()			PORT_GetBit(PORT12, PIN4)
#define GET_LEAK_PIN()			//pp//(FlagStatus)GPIO_ReadInBit(HT_GPIOA, GPIO_PIN_1)
#define GET_POWERDOWN_PIN()		PORT_GetBit(PORT12, PIN2)


#define SET_INLET_VALVE_PIN(x)	GPIO_Output(PORT13,PIN0,x)//��ˮ��1��ԭˮ��
#define SET_WASTE_VALVE_PIN(x)	GPIO_Output(PORT12,PIN0,x)//��ˮ�������ɵ���
#define SET_PUMP_PIN(x)			GPIO_Output(PORT3,PIN1,x)//

#define SET_INLET_VALVE2_PIN(x)	GPIO_Output(PORT3,PIN0,x)


#define FILTERTYPE_PCB	0
#define FILTERTYPE_RO	1



#define PCB_PowerOnRemained_MAX			(8640*60)//Сʱ
#define RO_PowerOnRemained_MAX			(25920*60)//Сʱ
#define PCB_MakingRemained_MAX			(30*60)//Сʱ
#define RO_MakingRemained_MAX			(120*60)//Сʱ

#define PCBRO_PowerOnTime_exceed		30//��
#define PCBRO_MakingTime_exceed			30//��

#define  WORKING_ContinuousTime			5//������ˮ5����
#define  WORKING_LongTime				(60)//��ʱ����ˮ���� 1Сʱ
#define  WORKING_ExitLongTime			(60*(3+1))//�˳���ʱ����ˮ 3Сʱ
#define  WORKING_LongTimeWorkTimesCount	(7)//7��

#define	STANDBY_longtime			(48*3600)//��������48Сʱ
#define BACKFLOW_entertime2			(24*3600)//���봿ˮ����24Сʱ֮��	
#define BACKFLOW_entertime1			(10)//����ʱ��


#define FLUSH_time_auto				20//�Զ���ϴʱ��,��
#define	FLUSH_time_Manual			20//�ֶ���ϴʱ��,��
#define	FLUSH_time_PowerOn			30//�ϵ��ϴ,��
#define	FLUSH_time_FirstPowerOn		30//�״��ϵ��ϴ,��
#define	FLUSH_time_standby48h		60//����ʱ����48Сʱ�Զ���ϴ,��

#define PUMP_OFF_ad_val				20// ˮ��û�򿪵ĵ���ADֵ
#define PUMP_open_delaytime			200//��ˮ����ʱ(ms)					

#define BACKFLOW_time_run			60//����60��




//����״̬
enum workstate
{
	WORKSTATE_standby,//����
	WORKSTATE_free,//����״̬

	WORKSTATE_backflow,//����
	
	WORKSTATE_autoflush,//�Զ���ϴ

	WORKSTATE_working,//�ƴ�ˮ
	WORKSTATE_live,//������ˮ
	
	WORKSTATE_manualflush,//�ֶ���ϴ
	WORKSTATE_LongTimeWork,//��ʱ����ˮ
	WORKSTATE_PowerOnFlush,//�ϵ���ϴ
	WORKSTATE_Leaking,//©ˮ
	WORKSTATE_LockWater,//��ˮ

	WORKSTATE_GasDetection,//����
	WORKSTATE_WaterDetection,//ˮ��
	WORKSTATE_FilterDetection,//��о���

	WORKSTATE_PowerOnProc,
	WORKSTATE_FCT,//FCT����

	WORKSTATE_PowerDown,//�ػ�
	
	WORKSTATE_MAX
};



#pragma pack(1)
#if 0
typedef struct
{
	INT8U run_r_en:1;//�� 
	INT8U pcb_r_en:1;//��

	INT8U ro_r_en:1;//�� 
	INT8U wifi_r_en:1;//��

	INT8U ro_w_en:1;//�� 
	INT8U wifi_w_en:1;//��	

	INT8U run_w_en:1;//�� 
	INT8U pcb_w_en:1;//��

	INT8U run_r_flash:1;//�� 
	INT8U pcb_r_flash:1;//��

	INT8U ro_r_flash:1;//�� 
	INT8U wifi_r_flash:1;//��

	INT8U ro_w_flash:1;//�� 
	INT8U wifi_w_flash:1;//��	

	INT8U run_w_flash:1;//�� 
	INT8U pcb_w_flash:1;//��
}
DISPLAY_REG;
#else 
typedef struct
{
	INT8U run_w_en:1;//
	INT8U pcb_w_en:1;//
	INT8U pcb_r_en:1;//
	INT8U run_r_en:1;//�� 
	INT8U wifi_w_en:1;//
	INT8U wifi_r_en:1;//
	INT8U ro_w_en:1;//
	INT8U ro_r_en:1;//�� 
		
	INT8U run_w_flash:1;//
	INT8U pcb_w_flash:1;//
	INT8U pcb_r_flash:1;//
	INT8U run_r_flash:1;//�� 
	INT8U wifi_w_flash:1;//
	INT8U wifi_r_flash:1;//
	INT8U ro_w_flash:1;//
	INT8U ro_r_flash:1;//��

}
DISPLAY_REG;
#endif

typedef struct
{
	INT8U head[2];
	INT8U len;
	INT8U addr;
	INT8U keyval;//����ֵ
	INT8U sum;
}
serial_getcomm;

typedef struct
{
	INT8U head[2];
	INT8U len;
	INT8U addr;
	INT8U LED;//Ϊ1����L1-L8
	INT8U LEDFlash_EN;//��˸
	INT8U sum;
}
serial_sendcomm;



enum pcb_item 
{
	PCB_level_1,
	PCB_level_2,
	PCB_level_3,
};


typedef struct
{
	INT16U rawTdsFlag 		: 1;//��ˮUV254��������־λ,0���޴˴�����
	INT16U pureTdsFlag		: 1;
	INT16U rawCodFlag 		: 1;
	INT16U pureCodFlag		: 1;
	INT16U rawTocFlag 		: 1;
	INT16U pureTocFlag		: 1;
	INT16U rawUV254Flag		: 1;
	INT16U pureUV254Flag	: 1;
	
	INT16U resever:8;
}
SENFLAG;

typedef struct
{
	INT16U TempErrorFlag		: 1;//�¶ȴ���������
	INT16U rawTdsErrorFlag		: 1;//ԭˮTDS����������
	INT16U pureTdsErrorFlag		: 1;//��ˮTDS����������
	INT16U WaterLeakErrorFlag	: 1;//©ˮ����
	INT16U TimeOutErrorFlag		: 1;//��ˮ��ʱ
	INT16U WasteWaterErrorFlag	: 1;//��ˮ�ȷ�����
	INT16U InWaterErrorFlag		: 1;//��ˮ������
	INT16U sparklingWaterStatus	: 1;//����ˮ����״̬

	INT16U Temp2ErrorFlag		: 1;
	
	INT16U resever:7;
}ERRORFLAG_t;

typedef union 
{
	INT16U		u16flag;
	ERRORFLAG_t	BitFlag;
}UN_ERROR_t;



typedef struct
{
	INT16U flush	: 1;//��ϴ 0�أ�1��
	INT16U uv		: 1;//uv�� 0�أ�1��

	INT16U resever:14;
}PERIPSTATE_t;

typedef union 
{
	INT16U			u16flag;
	PERIPSTATE_t	BitFlag;
}PERIPHERAL_t;


typedef struct
{
	INT16U DeviceAddr;//�豸��ַ
	INT16U ProductType;//��Ʒ���� 0��ˮ����1����
	INT16U productName;//��Ʒ���� 0�ƾ���1������2���ۣ�3����о��4miniϵ��(0x0401mni1,0x0402mini2)
	INT16U ProductModel;//��Ʒ�ͺ�(500,600,700,800)
	INT16U version;//�汾��8λӲ���汾,��8λ����汾

	INT16U cmd;//���ƼĴ���
	
	INT16U WorkState;//����״̬ 0�����У�1��ˮ��
	INT16U wifi;//0δ���ӣ�1������2���ӳɹ���3�ź���
	
	PERIPHERAL_t PeriState;//����״̬
	
	UN_ERROR_t error;//����

	INT32U PowerOnTimeTotal_PCB;//���ϵ�ʱ�� ��λ����
	INT32U PumpWorkeTimeTotal_PCB;//��ˮ�ù���ʱ��
	INT32U PowerOnTimeTotal_RO;//���ϵ�ʱ�� ��λ����
	INT32U PumpWorkeTimeTotal_RO;//��ˮ�ù���ʱ��	

	INT32U RawWaterVolume;//ԭˮ�� mL
	INT32U NetWaterVolume;//��ˮ�� mL
	INT32U RawWaterVolumeSingle;//����ˮ�� mL
	INT32U NetWaterVolumeSingle;//����ˮ�� mL	

	INT16U PriFilterResetTimes;//������о���ô���
	INT16U RoFilterResetTimes;//RO��о���ô���
	
	INT16U rawTDS;//ԭˮTDS	
	INT16U netTDS;//��ˮTDS

	INT16U rawTemperature;//ԭˮˮ�� bit16Ϊ1������������,Ϊ0���ڣ���8λΪˮ��
	
	INT16U FilterLife_PCB;//��о����	�ٷֱ�
	INT16U FilterLife_RO;//��о�����ٷֱ�	

	SENFLAG SenFlag;//��������־��0�޴˴�������1��

	INT16U fruits;//�߹� ���ģʽ
	INT16U BackFlow;//��ˮ����ʹ��

	//SYSTEMTIME time;
}
REG;


typedef struct
{
	INT8U EE;	
}
WORKERROR;

typedef struct
{
	INT8U BackLight:1;//����
	INT8U StateChangeFlag:1;//0�豸״̬û�и��£�1�豸״̬�����˸ı�

	INT8U systimeupdateflag:1;//ϵͳʱ�����

	INT8U HVS:1;//��ѹ����״̬ 0�أ�1��

	INT8U StandbyFlag:1;
	INT8U FreeFlag:1;
	INT8U BackflowFlag:1;//����
	INT8U AutoFlushFlag:1;//�Զ���ϴ��־
	INT8U WorkingFlag:1;
	INT8U LiveFlag:1;//������ˮ
	INT8U ManualFlushFlag:1;
	INT8U LongTimeWorkFlag:1;//E2 ��ʱ����ˮ
	INT8U PowerOnFlushFlag:1;//�ϵ���ϴ��־
	INT8U LeakFlag:1;//E1©ˮ
	INT8U LockWaterFlag:1;
	INT8U PowerOnProcFlag:1;
	INT8U FCTFlag:1;

	INT8U GasDetectionFlag:1;//����
	INT8U WaterDetectionFlag:1;//ˮ��
	INT8U FilterDetectionFlag:1;//��о���
	INT8U FirstBootGetTDSFlag:1;//��һ���ϵ��ʶ��0���ǵ�һ���ϵ磬1��һ���ϵ�
	INT8U FirstBootFlushFlag:1;//��һ���ϵ��ϴ��ʶ��0���ǵ�һ���ϵ磬1��һ���ϵ�
	INT8U EmptyshellFlag;//�տ�ģʽ

	INT8U AutoFlushtime;//�Զ���ϴʱ��,��λ��
	
	INT16U BackTimerCount;//����ʱ�����
	INT16U WinTimerCount;

	
	INT16U heartbeat;//������ʱ�� ��λ��

	INT8U makewaterTimer;//��ˮ��ʱ ��λ����
 	INT32U makewaterSingle;//������ˮ�� ��λmL
	INT8U LongTimeWorkTimesCount;//��ʱ����ˮ���� 7��
 	INT32U StandbyTimeCount;//����ʱ��
 	INT8U FilterLife_PCB;//��ʾ����ʾ�ȼ�
 	INT8U FilterLife_RO;//��ʾ����ʾ�ȼ�

 	INT8U wifi;//0δ���ӣ�1������2���ӳɹ���3�ź���
	
	INT16U PowerOnTimerCount;//�ϵ��ʱ ���ڰ����ϵ�15���ڵĲ���
	INT8U flash:1;//��ʾ��˸

	INT8U HVS_faucet:1;//ˮ��ͷ��ѹ����

	INT8U WinTimerOutFlag:1;

	INT8U ElectrolyticFlag:1;//���Ƭ�򿪱�־

	INT8U uartdisplayError:1;//��ʾ��ͨѶ1�쳣��0����

	INT8U uartWifiError:1;//��ʾ��ͨѶ1�쳣��0����

	INT8U WaterFlowError:1;//�����쳣

	INT16U FCTsave:1;

	WORKERROR workerror;//��������

	INT32U PerAutoRawUL;// ���δ�ˮ��    ��ʱ����
	INT32U PowerOnPumpMakeWater2H;// ��¼�ϵ����ˮǰ2Сʱ
	INT16U FlowMeterBeforeVelocity;	// ǰ�������Ƶ�����

	INT8U FaucetGetCmdCount;//ˮ��ͷ���ָ�����
	INT8U displaydelaysend;//��ʾ��ʱ����
}
SYSTEMSETING;

#pragma pack()


enum demomode
{
	DEMOMODE_Ready,
	DEMOMODE_demo_a,
	DEMOMODE_demo_b,
};



extern INT8U RecBuff[SERIAL_BUFF_NUM];
extern SYSTEMSETING systemseting;
extern CODE INT8U Digitaltube[];
extern UARTPROC UartDispProc;
extern UARTPROC UartFaucetProc;
extern UARTPROC UartWifiProc;
extern REG gReg;
extern DISPLAY_REG gDisplayReg;


void RestoreFactory(void);
void AppSystemInit(void);

void Standby(void);

void ParsingDisplayData(INT8U *pbuff,INT16U len);

void DesktopUpdate(void);
void DisplayUpdate(void);

INT8U Jump2Boot(void);


void MonitorWater(void);
INT16U FilterLifeCalculate(INT32U powerontime,INT32U pumptime,INT8U type);


void PowerOnDisplay(void);
void MonitorState(void);

void GetLeakADC(INT16U ad);
void GetPumpADC(INT16U ad);

void FilterReset_PCB(void);
void FilterReset_RO(void);

void SetInletValve(FlagStatus state);
void SetInletValve2(FlagStatus state);
void SetWasteWaterValve(FlagStatus state);
void SetBoosterPump(INT8U state);
void UpdateFilterLife(void);

void FeedWDT(void);


void ExitManualFlush(void);
void ClearLongTimeWorkFlag(void);

void EnterFCTMode(void);
void ExitFCTMode(void);

void StandbyRestart(void);
void WinTimerOut(void);
BOOL PowerDownCheck(void);


#endif


