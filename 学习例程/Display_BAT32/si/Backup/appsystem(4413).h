#ifndef APPSYSTEM_H
#define APPSYSTEM_H










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



	//SYSTEMTIME time;
}
REG;


typedef struct
{
	INT8U EE;	
}
WORKERROR;


enum Language
{
	Language_English,
	Language_French,
	Language_Spanish,
};

enum LEDLevel
{
	LEDLevel_LOW,
	LEDLevel_Medium,
	LEDLevel_High,
	LEDLevel_max,
};


enum type_e
{
	type_Shaken,
	type_Blended,
	type_ColdFoam,
	type_max=type_ColdFoam,
};

enum size_e
{
	size_NULL,
	size_Tall,
	size_Grande,
	size_Venti,
	size_Trenta,
	size_max=size_Trenta,
};


typedef struct
{
	INT8U Language;
	INT8U CalibrationFlag;//ûУ׼����1У׼����
	INT8U ActivateCleanFlag;
	INT8U LEDLevel;//����LED�ȼ�
}
Oreration_t;

typedef struct
{
	INT8U Language;
	INT8U CalibrationFlag;//ûУ׼����1У׼����
	INT8U ActivateCleanFlag;
}
Service_t;

typedef struct
{
	INT8U Language;
	INT8U CalibrationFlag;//ûУ׼����1У׼����
	INT8U ActivateCleanFlag;
}
Data_t;

typedef struct
{
	INT8U Type;
	INT8U Size;//
	INT8U Flow;//
}
TypeSize_t;

typedef struct
{
	Oreration_t Oreration;
	Service_t 	Service;
	Data_t		Data;
	TypeSize_t	TypeSize;
}
UIset_t;




typedef struct
{
	INT8U BackLight:1;//����
	INT8U StateChangeFlag:1;//0�豸״̬û�и��£�1�豸״̬�����˸ı�

	INT8U systimeupdateflag:1;//ϵͳʱ�����

	INT8U HVS:1;//��ѹ����״̬ 0�أ�1��

	INT8U StandbyFlag:1;

	INT8U AutoFlushtime;//�Զ���ϴʱ��,��λ��
	
	INT16U BackTimerCount;//����ʱ�����
	INT16U WinTimerCount;

	
	INT16U heartbeat;//������ʱ�� ��λ��

	INT16U uartdisplayTimeOutCnt;//ͨѶ��ʱ����

 	INT8U wifi;//0δ���ӣ�1������2���ӳɹ���3�ź���
	
	INT16U PowerOnTimerCount;//�ϵ��ʱ ���ڰ����ϵ�15���ڵĲ���
	INT8U flash:1;//��ʾ��˸

	INT8U WinTimerOutFlag:1;
	
	INT8U ElectrolyticFlag:1;//���Ƭ�򿪱�־

	INT8U uartdisplayError:1;//��ʾ��ͨѶ1�쳣��0����

	INT8U uartWifiError:1;//WIFIͨѶ1�쳣��0����

	INT8U pc_en:1;

	INT16U FCTsave;

	WORKERROR workerror;//��������

	
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
extern UIset_t gUISet;

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


