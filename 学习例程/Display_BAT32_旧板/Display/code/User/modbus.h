#ifndef MODBUS_H
#define MODBUS_H




#define RS_ADDR			0xFA



#define MODBUS_CMD_03	0X03
#define MODBUS_CMD_06	0X06
#define MODBUS_CMD_10	0X10//д����Ĵ���
#define MODBUS_CMD_05	0X05//д������Ȧ


#define MODBUS_ERROR_01	0X01//ָ������糬����Χ��
#define MODBUS_ERROR_02	0X02//��������Ч�������
#define MODBUS_ERROR_03	0X03//�Ĵ�����ַ�����糬����Χ��
#define MODBUS_ERROR_04	0X04//д���󣬼Ĵ���Ϊֻ��
#define MODBUS_ERROR_05	0X05//дʧ��
#define MODBUS_ERROR_06	0X06//





#define REG_ADDR_CMD	0x05





//����״̬
enum handle_cmd
{
	CMD_NULL,	
	
	CMD_ManualFlush_open =1,//�ֶ���ϴ
	CMD_ManualFlush_close,//�ֶ��ر� 
	
	CMD_FilterReset_PCB=10,//��о��λ
	CMD_FilterReset_RO,//��о��λ
	CMD_ExitWorking,//�˳�����ģʽ
	CMD_StandbyRestart,//�������¼�ʱ

	CMD_Factory=20,//�ָ�����
	CMD_GasDetection,//��������
	CMD_WaterDetection,//ˮ��
	CMD_FilterDetection,//��о���
	CMD_ExitDetection,//�˳��������ģʽ

	CMD_SetWifiOffline=30,//wifi����
	CMD_SetWifiNetwork,//wifi����
	CMD_SetWifiOnline,//����wifi����
	CMD_SetWifiSignalWeak,//�ź���

	CMD_EnterFCT=40,
	CMD_ExitFCT,	

	CMD_Emptyshell_Ready=50,//�տ�ģʽ
	CMD_Emptyshell_demo_a,
	CMD_Emptyshell_demo_b,
	CMD_Emptyshell_cycle,

	CMD_Error_ExitTimeout=100,//�˳���ʱ����ˮ����״̬

	
};




void Modbus_SetReg(void *reg,INT8U regnum);
BOOL ModbusProc(INT8U *pbuff,INT8U len);

INT16U GetModbusCRC(INT8U *pSendBuf, INT8U num);

BOOL SendModbusRegData(INT8U cmd,INT16U startaddr,INT16U regnum);


INT16U Small2BigMode(INT8U *pval);



#endif

