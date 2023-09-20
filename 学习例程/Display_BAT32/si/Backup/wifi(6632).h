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
	uint8_t outWaterTempSensorErrFlag: 1;//��ˮ�¶ȴ�������������
	uint8_t overheatErrFlag			: 1;//106�泬�¹�������
	uint8_t overheatAlarmFlag		: 1;//110�泬�±�������
	uint8_t inWaterTempSensorErrFlag: 1;//��ˮ�¶ȴ�������������
	uint8_t timeoutFlag				: 1;//��ˮ��ʱ������������
	uint8_t communicationErrFlag	: 1;//ͨѶ�쳣����
	uint8_t voltageSensorErrFlag	: 1;//��ѹ��������������
	uint8_t resever1				: 1;//Ԥ��
}ERRORFLAG_W;
typedef union 
{
	uint8_t u8flag;
	ERRORFLAG_W BitFlag;
}UN_ERROR_W;


//7D01
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
	uint8_t rawTdsFlag 		: 1;//��ˮTDS��������־λ,0���޴˴�����
	uint8_t pureTdsFlag		: 1;//��ˮTDS��������־λ,0���޴˴�����
	uint8_t rawCodFlag 		: 1;//Ԥ��
	uint8_t pureCodFlag		: 1;//Ԥ��
	uint8_t rawTocFlag 		: 1;//Ԥ��
	uint8_t pureTocFlag		: 1;//Ԥ��
	uint8_t rawUV254Flag	: 1;//Ԥ��
	uint8_t pureUV254Flag	: 1;//Ԥ��
	//Byte21-27
	uint16_t instantPurifiedWaterVolume;//˲ʱ��ˮ��,��λmL
	uint32_t pureVolume 		: 24;//�ۼƴ�ˮ��,��λmL
	uint32_t rawWaterTemperature: 8;//��ˮ�¶�
	uint32_t OutWaterTemp;//��ˮ�¶�
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
	uint8_t mnrFilterWarningFlag	: 1;//Ԥ��
	//36
	uint8_t priFilterAlarmFlag 	: 1;//���˵��ڱ�����ʣ��0%)
	uint8_t adsFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t rawFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t fineFilterAlarmFlag	: 1;//Ԥ��
	uint8_t roFilterAlarmFlag	: 1;//ro�˵��ڱ�����ʣ��0%)
	uint8_t tasFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t nanoFilterAlarmFlag	: 1;//Ԥ��
	uint8_t mnrFilterAlarm		: 1;//Ԥ��
	//37
	uint8_t priFilterSelectFlag		: 1;//����ѡ���־λ,0�޴���о
	uint8_t adsFilterSelectFlag		: 1;//Ԥ��
	uint8_t rawFilterSelectFlag		: 1;//Ԥ��
	uint8_t fineFilterSelectFlag	: 1;//Ԥ��
	uint8_t roFilterSelectFlag 		: 1;//ro��ѡ���־λ,0�޴���о
	uint8_t tasFilterSelectFlag		: 1;//Ԥ��
	uint8_t nanoFilterSelectFlag	: 1;//Ԥ��
	uint8_t mnrFilterSelectFlag		: 1;//Ԥ��
	//38
	uint8_t priFilterResetFlag 	: 1;//���˸�λ 0������1��λ�˼���о
	uint8_t adsFilterResetFlag 	: 1;//Ԥ��
	uint8_t rawFilterResetFlag 	: 1;//Ԥ��
	uint8_t fineFilterResetFlag	: 1;//Ԥ��
	uint8_t roFilterResetFlag	: 1;//ro�˸�λ 0������1��λ�˼���о
	uint8_t tasFilterResetFlag 	: 1;//Ԥ��
	uint8_t nanoFilterResetFlag	: 1;//Ԥ��
	uint8_t mnrFilterResetFlag	: 1;//Ԥ��
	//39
	uint8_t FlushStatus 			: 1;//��ϴ����״̬,0�رգ�1����
	uint8_t uvSterilizationStatus 	: 1;//UVɱ������״̬,0�رգ�1����
	uint8_t onOffStatus				: 1;//���ػ�״̬,0�رգ�1����
	uint8_t childLockStatus			: 1;//ͯ������״̬,0�رգ�1����
	uint8_t waterUseStatus			: 1;//ȡˮ����״̬,0�رգ�1����
	uint8_t waterChangingStatus		: 1;//��ˮ����״̬,0�رգ�1����
	uint8_t heatingStatus			: 1;//���ȹ���״̬,0�رգ�1����
	uint8_t heatKeepingStatus		: 1;//���¹���״̬,0�رգ�1����

	//40
	UN_ERROR_W AllError;

	//41
	uint8_t operationMode;//01����ϴ02����ˮ04��ȱˮ05������06������0F������10����ˮ����ˮ11����ˮ����ˮ
	
	//42
	uint8_t hotWaterType;//01������02����ˮ03���ݲ�04���̷�05������06��40��07��50��08��60��09��70��0A��80��0B��90��

	//43-44
	uint16_t outWaterVolume;//ʵ�ʳ�ˮˮ��ml
	//45
	uint8_t outWaterVolumeLevel;//��ˮˮ����λ 01��180ml02��300ml03��500ml04��1000ml05��900ml06��90ml07��120ml08��100ml09��200ml0A��400ml

	//46
	uint8_t resever1;
	//47-48
	uint16_t freeWaterVolume;//�����ˮˮ��mL

	//49-60
	uint8_t actualSetTempNormal;//���µ�λʵ���趨ֵ
	uint8_t actualSetTempTea;//�ݲ赵λʵ���趨ֵ
	uint8_t actualSetTempMilk;//�̷۵�λʵ���趨ֵ
	uint8_t actualSetTempCoffee;//���ȵ�λʵ���趨ֵ
	uint8_t actualSetTemp40;//40�浵λʵ���趨ֵ
	uint8_t actualSetTemp50;//50�浵λʵ���趨ֵ
	uint8_t actualSetTemp60;//60�浵λʵ���趨ֵ
	uint8_t actualSetTemp70;//70�浵λʵ���趨ֵ
	uint8_t actualSetTemp80;//
	uint8_t actualSetTemp90;//
	uint8_t	actualSetTempBoil;//��ˮ��λʵ���趨ֵ,00����Ӧ 80��01����Ӧ 81��02����Ӧ 82�棬12����Ӧ 98��13����Ӧ 99��14����Ӧ 100��
	uint8_t mnrFilterRemained;//����оʣ��ٷֱ�
}
UPStatuInfo_max;

//6D01
typedef struct
{	
	uint8_t	 cmd1;
	uint8_t	 cmd2;
	//1-4
	uint16_t rawTds;//��ˮTDS
	uint16_t pureTds;//��ˮTDS
	//5-6
	uint8_t thickFilmTemperature;//Ԥ������Ĥ�¶�
	uint8_t iceCanTemperature;//Ԥ���������¶�
	//7-16
	uint8_t reserved1;//Ԥ����
	uint8_t reserved2;//Ԥ����
	uint8_t reserved3;//Ԥ����
	uint8_t reserved4;//Ԥ����
	uint8_t reserved5;//Ԥ����
	uint8_t reserved6;//Ԥ����
	uint8_t reserved7;//Ԥ����
	uint8_t reserved8;//Ԥ����
	uint8_t reserved9;//Ԥ����
	uint8_t reserved10;//Ԥ����
	//17-19
	uint8_t  hour;
	uint8_t  min;
	uint8_t  sec;
	
	//20  
	uint8_t reserved11;//Ԥ��
	
	//21-22
	uint16_t perpureVolume;//���δ�ˮ��,��λmL
	//23-26
	uint32_t pureVolume;//�ۼƴ�ˮ��,��λmL
	//27
	uint32_t OutWaterTemp;//����ˮ�¶�
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
	uint8_t mnrFilterWarningFlag	: 1;//Ԥ��
	//36
	uint8_t priFilterAlarmFlag 	: 1;//���˵��ڱ�����ʣ��0%)
	uint8_t adsFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t rawFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t fineFilterAlarmFlag	: 1;//Ԥ��
	uint8_t roFilterAlarmFlag	: 1;//ro�˵��ڱ�����ʣ��0%)
	uint8_t tasFilterAlarmFlag 	: 1;//Ԥ��
	uint8_t nanoFilterAlarmFlag	: 1;//Ԥ��
	uint8_t mnrFilterAlarmFlag	: 1;//Ԥ��
	//37
	uint8_t reserved12;//Ԥ��
	//38
	uint8_t priFilterResetFlag 	: 1;//���˸�λ 0������1��λ�˼���о
	uint8_t adsFilterResetFlag 	: 1;//Ԥ��
	uint8_t rawFilterResetFlag 	: 1;//Ԥ��
	uint8_t fineFilterResetFlag	: 1;//Ԥ��
	uint8_t roFilterResetFlag	: 1;//ro�˸�λ 0������1��λ�˼���о
	uint8_t tasFilterResetFlag 	: 1;//Ԥ��
	uint8_t nanoFilterResetFlag	: 1;//Ԥ��
	uint8_t mnrFilterResetFlag	: 1;//Ԥ��
	//39
	uint8_t FlushStatus 			: 1;//��ϴ����״̬,0�رգ�1����
	uint8_t uvSterilizationStatus 	: 1;//UVɱ������״̬,0�رգ�1����
	uint8_t onOffStatus				: 1;//���ػ�״̬,0�رգ�1����
	uint8_t childLockStatus			: 1;//ͯ������״̬,0�رգ�1����
	uint8_t waterUseStatus			: 1;//ȡˮ����״̬,0�رգ�1����
	uint8_t waterChangingStatus		: 1;//��ˮ����״̬,0�رգ�1����
	uint8_t heatingStatus			: 1;//���ȹ���״̬,0�رգ�1����
	uint8_t heatKeepingStatus		: 1;//���¹���״̬,0�رգ�1����
	
	//40
	uint8_t pailFlagReset		: 1;//ˮͰ������λ,0����,1��
	uint8_t purifiedBoxFullFlag	: 1;//��ˮ��ˮ������
	uint8_t purifiedBoxLackFlag	: 1;//��ˮ��ȱˮ����
	uint8_t rawBoxLackFlag		: 1;//ԭˮ��ȱˮ����
	uint8_t iceCanOnOffStatus	: 1;//���޿���
	uint8_t massiveWaterStatus	: 1;//��ˮ��״̬
	uint8_t resvHeatKeeping		: 1;//ԤԼ���¿���
	uint8_t oneKeyDrainage		: 1;//һ����ˮ
	
	//41
	uint8_t operationMode;//����ģʽ01����ϴ02����ˮ04��ȱˮ05������06������0F������

	//42
	uint8_t hotWaterType;//��ˮ�¶ȵ�λ00����ģʽ01������02����ˮ03���ݲ�04���̷�05������06��40��07��50��08��60��09��70��0A��80��0B��90��0F�����Ի�10����ˮ

	//43-44
	uint16_t outWaterVolume;//ʵ�ʳ�ˮˮ��mL
	//45
	uint8_t outWaterVolumeLevel;//��ˮˮ����λ 02��300ml03��500ml04��1000ml05��900ml08��100ml09��200ml0A��400ml0C��600ml0D��700ml0E��800ml0F��1100ml10��1200ml
	//46
	uint8_t reserved13;//Ԥ��
	//47-48
	uint16_t freeWaterVolume;//�����ˮˮ��
	//49-51
	uint8_t outWaterTempAdjust;//��ˮ�¶ȵ���
	uint8_t highlandBpTemperature;//��ԭ�е��¶�
	uint8_t hotPotTemperature;//�ȹ��¶�
	//52-55
	uint16_t resvHeatKeepingStartTime_hour:8;//ԤԼ���¿�ʼʱ��
	uint16_t resvHeatKeepingStartTime_min:8;//
	uint16_t resvHeatKeepingStopTime_hour:8;//ԤԼ���¹ر�ʱ��
	uint16_t resvHeatKeepingStopTime_min:8;//

	//56-60
	uint8_t setHeatKeepingDuration;//���ñ���ʱ��
	uint8_t thickFilmHeatPower;//��Ĥ���ȹ���
	uint8_t hotPotHeatPower;//�ȹ޼��ȹ���
	uint8_t rawWaterTemperature;//��ˮ�¶�
	uint8_t mnrFilterRemained;//����оʣ��ٷֱ�

}
UPStatuInfo;


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

