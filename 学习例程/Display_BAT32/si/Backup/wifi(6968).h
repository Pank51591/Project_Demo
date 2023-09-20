#ifndef WIFI_H
#define WIFI_H

#define WIFI_HEAD1	0xFF
#define WIFI_HEAD2	0xFF




typedef enum
{
	WIFI_CMD_01=0x01,//���ƻ�����
	WIFI_CMD_02=0x02,//״̬����
	WIFI_CMD_03=0x03,//��Ч���� 
	WIFI_CMD_04=0x04,//����״̬�㱨
	WIFI_CMD_05=0x05,//ȷ��
	WIFI_CMD_06=0x06,//״̬�㱨
	WIFI_CMD_07=0x07,
	WIFI_CMD_09=0x09,//ֹͣ���ϱ���֡
	WIFI_CMD_11=0x11,//������ʱ
	WIFI_CMD_60=0x60,
	WIFI_CMD_61=0x61,
	WIFI_CMD_62=0x62,
	WIFI_CMD_63=0x63,//��ȡ��Կ
	WIFI_CMD_64=0x64,//���ü��ܲ���
	WIFI_CMD_70=0x70,
	WIFI_CMD_71=0x71,
	WIFI_CMD_73=0x73,//��ѯ����״̬
	WIFI_CMD_74=0x74,//��ѯ����״̬Ӧ��
	WIFI_CMD_7C=0x7C,
	WIFI_CMD_7D=0x7D,
	WIFI_CMD_E1=0xE1,
	WIFI_CMD_E2=0xE2,
	WIFI_CMD_E5=0xE5,
	WIFI_CMD_E6=0xE6,
	WIFI_CMD_E7=0xE7,
	WIFI_CMD_E8=0xE8,
	WIFI_CMD_E9=0xE9,
	WIFI_CMD_EA=0xEA,
	WIFI_CMD_EB=0xEB,
	WIFI_CMD_EC=0xEC,
	WIFI_CMD_ED=0XED,
	WIFI_CMD_EF=0xEF,
	WIFI_CMD_F0=0xF0,//����״̬��ѯ
	WIFI_CMD_F1=0xF1,
	WIFI_CMD_F2=0xF2,
	WIFI_CMD_F3=0xF3,
	WIFI_CMD_F4=0xF4,
	WIFI_CMD_F5=0xF5,
	WIFI_CMD_F6=0xF6,
	WIFI_CMD_F7=0xF7,//�����㱨����״̬,WIFIģ��->�豸
	WIFI_CMD_F8=0xF8,
	WIFI_CMD_F9=0xF9,
	WIFI_CMD_FA=0xFA,//�豸�����ݻ㱨����֡             WIFIģ��->�豸
	WIFI_CMD_FB=0xFB//�豸�����ݻ㱨����Ӧ��֡
}WIFICMD;



typedef enum
{
	WIFI_CON_SetOutWaterTemp  = 0x01,//���ó�ˮ��
	WIFI_CON_SetTime,//2����ʱ��
	WIFI_CON_SetPriFilterReset,//3���˸�λ
	WIFI_CON_SetAdsFilterReset,//4������λ
	WIFI_CON_SetRawFilterReset,//5���˸�λ
	WIFI_CON_SetFineFilterReset,//6���˸�λ
	WIFI_CON_SetRoFilterReset,//7RO��λ
	WIFI_CON_SetTasFilterReset,//8�ڸи�λ
	WIFI_CON_SetNanoFilterReset,//9���˸�λ
	WIFI_CON_SetFlushStatus,//A��ϴ����״̬

	WIFI_CON_SetRO2Reset=0x0D,//��λRO2

	WIFI_CON_Setfruits=0x11,//�߹�
	
}WIFIControlCmd;


typedef enum
{
	WIFI_WORKMODE_softAp=0,
	WIFI_WORKMODE_smartlink=2,
	WIFI_WORKMODE_smartAp=3,
	WIFI_WORKMODE_closeinternet=9,
	WIFI_WORKMODE_work=0xFF,
}
WIFIWORKMODE;


#pragma pack(1)

typedef struct
{
	
	INT8U heartbeatEN:1;
	INT8U BigdataEN:1;
	INT8U SendStatus:1;//����״̬1�ɹ�
	INT8U alarmsendflag:1;
	INT8U alarmstopflag:1;
	
	INT8U beakcmd;//����ָ��
	INT16U heartbeat;
	INT16U heartbeatCount;
	INT16U BigdataHeartbeat;
	INT16U BigdataHeartbeatCount;

	INT8U wifistatus;
	INT8U wifisignal;
	INT8U workmode;
}
WIFISET;

typedef struct
{
	uint8_t TempErrorFlag			: 1;//�¶ȴ���������
	uint8_t rawTdsErrorFlag			: 1;//Ԥ����ԭˮTDS����������
	uint8_t pureTdsErrorFlag		: 1;//Ԥ������ˮTDS����������
	uint8_t WaterLeakErrorFlag		: 1;//©ˮ����
	uint8_t TimeOutErrorFlag		: 1;//��ˮ��ʱ
	uint8_t WasteWaterErrorFlag		: 1;//Ԥ������ˮ�ȷ�����
	uint8_t InWaterErrorFlag		: 1;//Ԥ������ˮ������
	uint8_t sparklingWaterStatus	: 1;//Ԥ��������ˮ����״̬
}ERRORFLAG_W;
typedef union 
{
	uint8_t u8flag;
	ERRORFLAG_W BitFlag;
}UN_ERROR_W;

#if 0
//6D01
typedef struct
{	//1-16
	uint8_t	 cmd1;
	uint8_t	 cmd2;
	uint16_t rawTds;//��ˮTDS
	uint16_t pureTds;//��ˮTDS
	uint16_t rawCod;//Ԥ������ˮCODֵ
	uint16_t pureCod;//Ԥ������ˮCODֵ
	uint16_t rawToc;//Ԥ����
	uint16_t pureToc;//Ԥ����
	uint16_t rawUV254;//Ԥ����
	uint16_t pureUV254;//Ԥ����
	//17-19
	uint8_t  hour;
	uint8_t  min;
	uint8_t  sec;
	
	//Byte20  from bit0 to bit7
	uint32_t rawTdsFlag 		: 1;//��ˮTDS��������־λ,0���޴˴�����
	uint32_t pureTdsFlag		: 1;//��ˮTDS��������־λ,0���޴˴�����
	uint32_t rawCodFlag 		: 1;//Ԥ��
	uint32_t pureCodFlag		: 1;//Ԥ��
	uint32_t rawTocFlag 		: 1;//Ԥ��
	uint32_t pureTocFlag		: 1;//Ԥ��
	uint32_t rawUV254Flag		: 1;//Ԥ��
	uint32_t pureUV254Flag		: 1;//Ԥ��
	//Byte21-27
	uint32_t rawVolume			: 24;//Ԥ�����ۼ�Դˮ��,��λL
	uint32_t pureVolume 		: 24;//�ۼƴ�ˮ��,��λmL
	uint32_t OutWaterTemp		:  8;//Ԥ������ˮ�¶�
	//28-34
	uint8_t priFilterRemain;//����ʣ��ٷֱ�(0~100%)
	uint8_t adsFilterRemain;//Ԥ��
	uint8_t RawFilterRemain;//Ԥ��
	uint8_t fineFilterRemain;//Ԥ��
	uint8_t roFilterRemain;//ro��ʣ��ٷֱ�(0~100%)
	uint8_t tasFilterRemain;//Ԥ��
	uint8_t nanoFilterRemain;//Ԥ��
	//35
	uint8_t priFilterWarningFlag	: 1;//���˵���Ԥ��(ʣ��10%),0��Ԥ��
	uint8_t adsFilterWarningFlag	: 1;//Ԥ��
	uint8_t rawFilterWarningFlag	: 1;//Ԥ��
	uint8_t fineFilterWarningFlag	: 1;//Ԥ��
	uint8_t roFilterWarningFlag		: 1;//ro�˵���Ԥ��(ʣ��10%),0��Ԥ��
	uint8_t tasFilterWarningFlag	: 1;//Ԥ��
	uint8_t nanoFilterWarningFlag	: 1;//Ԥ��
	uint8_t null_1					: 1;//Ԥ��
	//36
	uint8_t priFilterAlarmFlag 	: 1;//���˵��ڱ�����ʣ��0%)
	uint8_t adsFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t rawFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t fineFilterAlarmFlag	: 1;//Ԥ��
	uint8_t roFilterAlarmFlag	: 1;//ro�˵��ڱ�����ʣ��0%)
	uint8_t tasFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t nanoFilterAlarmFlag	: 1;//Ԥ��
	uint8_t null_2				: 1;//Ԥ��
	//37
	uint8_t priFilterSelectFlag		: 1;//����ѡ���־λ,0�޴���о
	uint8_t adsFilterSelectFlag		: 1;//Ԥ��
	uint8_t rawFilterSelectFlag		: 1;//Ԥ��
	uint8_t fineFilterSelectFlag	: 1;//Ԥ��
	uint8_t roFilterSelectFlag 		: 1;//ro��ѡ���־λ,0�޴���о
	uint8_t tasFilterSelectFlag		: 1;//Ԥ��
	uint8_t nanoFilterSelectFlag	: 1;//Ԥ��
	uint8_t null_3					: 1;//Ԥ��
	//38
	uint8_t priFilterResetFlag 	: 1;//���˸�λ 0������1��λ�˼���о
	uint8_t adsFilterResetFlag 	: 1;//Ԥ��
	uint8_t rawFilterResetFlag 	: 1;//Ԥ��
	uint8_t fineFilterResetFlag	: 1;//Ԥ��
	uint8_t roFilterResetFlag	: 1;//ro�˸�λ 0������1��λ�˼���о
	uint8_t tasFilterResetFlag 	: 1;//Ԥ��
	uint8_t nanoFilterResetFlag	: 1;//Ԥ��
	uint8_t null_4				: 1;//Ԥ��
	//39
	uint8_t FlushStatus 			: 1;//��ϴ����״̬,0�رգ�1����
	uint8_t uvSterilizationStatus 	: 1;//UVɱ������״̬,0�رգ�1����
	uint8_t operationMode			: 3;//����ģʽ��01��ϴ��02��ˮ��03��ˮ��04ȱˮ��05������06����
	uint8_t instantDrinkStatus		: 1;//Ԥ��
	uint8_t null_5					: 2;
	//40
	UN_ERROR_W AllError;
	//41-42
	uint8_t SaltRejectionRate;				//Ԥ���� ������
	uint8_t RawWaterTemperature;			//Ԥ���� ��ˮ�¶�
#if 1	
	//43-46 20200725 ����
	uint8_t roFilter2Remain;				// RO2ʣ��ٷֱ�
	uint8_t mnrFilter1Remain;				// ��1ʣ��ٷֱ�
	uint8_t mnrFilter2Remain;				// ��2ʣ��ٷֱ�
	uint8_t mnrFilter3Remain;				// ��3ʣ��ٷֱ�
	//47
	uint64_t mnrFilter3AlarmFlag	: 1;//��3���ڱ�����ʣ��0%��0�ޡ�1��
	uint64_t mnrFilter2AlarmFlag	: 1;
	uint64_t mnrFilter1AlarmFlag	: 1;
	uint64_t roFilter2AlarmFlag		: 1;
	uint64_t mnrFilter3WarningFlag 	: 1;//��3����Ԥ����ʣ��10%��
	uint64_t mnrFilter2WarningFlag 	: 1;
	uint64_t mnrFilter1WarningFlag 	: 1;
	uint64_t roFilter2WarningFlag	: 1;
	//48-51
	uint64_t mnrFilter3ResetFlag	: 1;//��3��λ 0������1��λ�˼���о
	uint64_t mnrFilter2ResetFlag	: 1;
	uint64_t mnrFilter1ResetFlag	: 1;
	uint64_t roFilter2ResetFlag		: 1;
	uint64_t mnrFilter3SelectFlag	: 1;
	uint64_t mnrFilter2SelectFlag	: 1;
	uint64_t mnrFilter1SelectFlag	: 1;
	uint64_t roFilter2SelectFlag	: 1;
	uint64_t perRawVolume			: 24;// ����ԭˮ������λmL
	//52-54
	uint64_t PerPureVolume			: 24;// ���δ�ˮ��,��λmL
#if 1	
	//55-65 20201117 �ͻ�������
	uint8_t PriFilterResetTimes;		// �������ô���  0-100   byte55
	uint8_t AdsFilterResetTimes;		// ���������ô���  0-100
	uint8_t RawFilterResetTimes;		// �������ô���  0-100
	uint8_t FineFilterResetTimes;		// �������ô���  0-100
	uint8_t RoFilterResetTimes;			// Ro�����ô���  0-100
	uint8_t TasFilterResetTimes;		// �ڸ������ô���  0-100   byte60
	uint8_t NanoFilterResetTimes;		// �������ô���  0-100
	uint8_t RoFilter2ResetTimes;		// Ro2�����ô���  0-100
	uint8_t MnrFilter1ResetTimes;		// ���������ô���  0-100
	uint8_t MnrFilter2ResetTimes;		// ���������ô���  0-100
	uint8_t MnrFilter3ResetTimes;		// ���������ô���  0-100   byte65

	uint8_t resever1;					// Ԥ��   byte66
	uint8_t resever2;					// Ԥ�� 
	uint8_t resever3;					// Ԥ�� 
	uint8_t resever4;					// Ԥ�� 
	uint8_t resever5;					// Ԥ�� // 70
	uint8_t resever6;					// Ԥ�� 
	uint8_t resever7;					// Ԥ�� 
	uint16_t RawHardness;				// ԭˮӲ��		// byte73-74
	uint16_t PurifiedHardness;			// ��ˮӲ��		75-76
#endif	
#endif
}
UPStatuInfo;
#else
//6D01
typedef struct
{	//1-16
	uint8_t	 cmd1;
	uint8_t	 cmd2;
	uint16_t rawTds;//��ˮTDS
	uint16_t pureTds;//��ˮTDS
	uint16_t thickFilmTemperature;//Ԥ������Ĥ�¶�
	uint16_t iceCanTemperature;//Ԥ���������¶�
	//uint16_t rawToc;//Ԥ����
	//uint16_t pureToc;//Ԥ����
	//uint16_t rawUV254;//Ԥ����
	//uint16_t pureUV254;//Ԥ����
	//17-19
	uint8_t  hour;
	uint8_t  min;
	uint8_t  sec;
	
	//Byte20  from bit0 to bit7
	uint32_t rawTdsFlag 		: 1;//��ˮTDS��������־λ,0���޴˴�����
	uint32_t pureTdsFlag		: 1;//��ˮTDS��������־λ,0���޴˴�����
	uint32_t rawCodFlag 		: 1;//Ԥ��
	uint32_t pureCodFlag		: 1;//Ԥ��
	uint32_t rawTocFlag 		: 1;//Ԥ��
	uint32_t pureTocFlag		: 1;//Ԥ��
	uint32_t rawUV254Flag		: 1;//Ԥ��
	uint32_t pureUV254Flag		: 1;//Ԥ��
	//Byte21-27
	uint32_t rawVolume			: 24;//Ԥ�����ۼ�Դˮ��,��λL
	uint32_t pureVolume 		: 24;//�ۼƴ�ˮ��,��λmL
	uint32_t OutWaterTemp		:  8;//Ԥ������ˮ�¶�
	//28-34
	uint8_t priFilterRemain;//����ʣ��ٷֱ�(0~100%)
	uint8_t adsFilterRemain;//Ԥ��
	uint8_t RawFilterRemain;//Ԥ��
	uint8_t fineFilterRemain;//Ԥ��
	uint8_t roFilterRemain;//ro��ʣ��ٷֱ�(0~100%)
	uint8_t tasFilterRemain;//Ԥ��
	uint8_t nanoFilterRemain;//Ԥ��
	//35
	uint8_t priFilterWarningFlag	: 1;//���˵���Ԥ��(ʣ��10%),0��Ԥ��
	uint8_t adsFilterWarningFlag	: 1;//Ԥ��
	uint8_t rawFilterWarningFlag	: 1;//Ԥ��
	uint8_t fineFilterWarningFlag	: 1;//Ԥ��
	uint8_t roFilterWarningFlag		: 1;//ro�˵���Ԥ��(ʣ��10%),0��Ԥ��
	uint8_t tasFilterWarningFlag	: 1;//Ԥ��
	uint8_t nanoFilterWarningFlag	: 1;//Ԥ��
	uint8_t null_1					: 1;//Ԥ��
	//36
	uint8_t priFilterAlarmFlag 	: 1;//���˵��ڱ�����ʣ��0%)
	uint8_t adsFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t rawFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t fineFilterAlarmFlag	: 1;//Ԥ��
	uint8_t roFilterAlarmFlag	: 1;//ro�˵��ڱ�����ʣ��0%)
	uint8_t tasFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t nanoFilterAlarmFlag	: 1;//Ԥ��
	uint8_t null_2				: 1;//Ԥ��
	//37
	uint8_t priFilterSelectFlag		: 1;//����ѡ���־λ,0�޴���о
	uint8_t adsFilterSelectFlag		: 1;//Ԥ��
	uint8_t rawFilterSelectFlag		: 1;//Ԥ��
	uint8_t fineFilterSelectFlag	: 1;//Ԥ��
	uint8_t roFilterSelectFlag 		: 1;//ro��ѡ���־λ,0�޴���о
	uint8_t tasFilterSelectFlag		: 1;//Ԥ��
	uint8_t nanoFilterSelectFlag	: 1;//Ԥ��
	uint8_t null_3					: 1;//Ԥ��
	//38
	uint8_t priFilterResetFlag 	: 1;//���˸�λ 0������1��λ�˼���о
	uint8_t adsFilterResetFlag 	: 1;//Ԥ��
	uint8_t rawFilterResetFlag 	: 1;//Ԥ��
	uint8_t fineFilterResetFlag	: 1;//Ԥ��
	uint8_t roFilterResetFlag	: 1;//ro�˸�λ 0������1��λ�˼���о
	uint8_t tasFilterResetFlag 	: 1;//Ԥ��
	uint8_t nanoFilterResetFlag	: 1;//Ԥ��
	uint8_t null_4				: 1;//Ԥ��
	//39
	uint8_t FlushStatus 			: 1;//��ϴ����״̬,0�رգ�1����
	uint8_t uvSterilizationStatus 	: 1;//UVɱ������״̬,0�رգ�1����
	uint8_t operationMode			: 3;//����ģʽ��01��ϴ��02��ˮ��03��ˮ��04ȱˮ��05������06����
	uint8_t instantDrinkStatus		: 1;//Ԥ��
	uint8_t null_5					: 2;
	//40
	UN_ERROR_W AllError;
	//41-42
	uint8_t SaltRejectionRate;				//Ԥ���� ������
	uint8_t RawWaterTemperature;			//Ԥ���� ��ˮ�¶�
#if 1	
	//43-46 20200725 ����
	uint8_t roFilter2Remain;				// RO2ʣ��ٷֱ�
	uint8_t mnrFilter1Remain;				// ��1ʣ��ٷֱ�
	uint8_t mnrFilter2Remain;				// ��2ʣ��ٷֱ�
	uint8_t mnrFilter3Remain;				// ��3ʣ��ٷֱ�
	//47
	uint64_t mnrFilter3AlarmFlag	: 1;//��3���ڱ�����ʣ��0%��0�ޡ�1��
	uint64_t mnrFilter2AlarmFlag	: 1;
	uint64_t mnrFilter1AlarmFlag	: 1;
	uint64_t roFilter2AlarmFlag		: 1;
	uint64_t mnrFilter3WarningFlag 	: 1;//��3����Ԥ����ʣ��10%��
	uint64_t mnrFilter2WarningFlag 	: 1;
	uint64_t mnrFilter1WarningFlag 	: 1;
	uint64_t roFilter2WarningFlag	: 1;
	//48-51
	uint64_t mnrFilter3ResetFlag	: 1;//��3��λ 0������1��λ�˼���о
	uint64_t mnrFilter2ResetFlag	: 1;
	uint64_t mnrFilter1ResetFlag	: 1;
	uint64_t roFilter2ResetFlag		: 1;
	uint64_t mnrFilter3SelectFlag	: 1;
	uint64_t mnrFilter2SelectFlag	: 1;
	uint64_t mnrFilter1SelectFlag	: 1;
	uint64_t roFilter2SelectFlag	: 1;
	uint64_t perRawVolume			: 24;// ����ԭˮ������λmL
	//52-54
	uint64_t PerPureVolume			: 24;// ���δ�ˮ��,��λmL
#if 1	
	//55-65 20201117 �ͻ�������
	uint8_t PriFilterResetTimes;		// �������ô���  0-100   byte55
	uint8_t AdsFilterResetTimes;		// ���������ô���  0-100
	uint8_t RawFilterResetTimes;		// �������ô���  0-100
	uint8_t FineFilterResetTimes;		// �������ô���  0-100
	uint8_t RoFilterResetTimes;			// Ro�����ô���  0-100
	uint8_t TasFilterResetTimes;		// �ڸ������ô���  0-100   byte60
	uint8_t NanoFilterResetTimes;		// �������ô���  0-100
	uint8_t RoFilter2ResetTimes;		// Ro2�����ô���  0-100
	uint8_t MnrFilter1ResetTimes;		// ���������ô���  0-100
	uint8_t MnrFilter2ResetTimes;		// ���������ô���  0-100
	uint8_t MnrFilter3ResetTimes;		// ���������ô���  0-100   byte65

	uint8_t resever1;					// Ԥ��   byte66
	uint8_t resever2;					// Ԥ�� 
	uint8_t resever3;					// Ԥ�� 
	uint8_t resever4;					// Ԥ�� 
	uint8_t resever5;					// Ԥ�� // 70
	uint8_t resever6;					// Ԥ�� 
	uint8_t resever7;					// Ԥ�� 
	uint16_t RawHardness;				// ԭˮӲ��		// byte73-74
	uint16_t PurifiedHardness;			// ��ˮӲ��		75-76
#endif	
#endif
}
UPStatuInfo;

#endif

#pragma pack()


extern WIFISET gWifiSet;


void WifiMsgProc(INT8U *pbuf,INT16U len);
void EQUI_EnterWifiNetwork(void);
void EQUI_ClearWifiConfig(void);
void EQUI_UpdataState(INT8U cmd);

void MonitrorAlarm(void);
void EQUI_SendWifiNetwork(WIFIWORKMODE mode);

INT8U GetSum(INT8U *pbuf,INT8U len);
INT16U GetCommData(INT8U *pbuf,INT16U len);

#endif

