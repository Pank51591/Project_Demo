#ifndef MODBUS_H
#define MODBUS_H




#define RS_ADDR			0xFA



#define MODBUS_CMD_03	0X03
#define MODBUS_CMD_06	0X06
#define MODBUS_CMD_10	0X10//写多个寄存器
#define MODBUS_CMD_05	0X05//写单个线圈


#define MODBUS_ERROR_01	0X01//指令错误（如超出范围）
#define MODBUS_ERROR_02	0X02//接收数据效验码错误
#define MODBUS_ERROR_03	0X03//寄存器地址错误（如超出范围）
#define MODBUS_ERROR_04	0X04//写错误，寄存器为只读
#define MODBUS_ERROR_05	0X05//写失败
#define MODBUS_ERROR_06	0X06//





#define REG_ADDR_CMD	0x05





//工作状态
enum handle_cmd
{
	CMD_NULL,	
	
	CMD_ManualFlush_open =1,//手动冲洗
	CMD_ManualFlush_close,//手动关闭 
	
	CMD_FilterReset_PCB=10,//滤芯复位
	CMD_FilterReset_RO,//滤芯复位
	CMD_ExitWorking,//退出工作模式
	CMD_StandbyRestart,//休眠重新计时

	CMD_Factory=20,//恢复出厂
	CMD_GasDetection,//工厂气检
	CMD_WaterDetection,//水检
	CMD_FilterDetection,//滤芯快检
	CMD_ExitDetection,//退出工厂检测模式

	CMD_SetWifiOffline=30,//wifi离线
	CMD_SetWifiNetwork,//wifi配网
	CMD_SetWifiOnline,//设置wifi在线
	CMD_SetWifiSignalWeak,//信号弱

	CMD_EnterFCT=40,
	CMD_ExitFCT,	

	CMD_Emptyshell_Ready=50,//空壳模式
	CMD_Emptyshell_demo_a,
	CMD_Emptyshell_demo_b,
	CMD_Emptyshell_cycle,

	CMD_Error_ExitTimeout=100,//退出长时间制水保护状态

	
};




void Modbus_SetReg(void *reg,INT8U regnum);
BOOL ModbusProc(INT8U *pbuff,INT8U len);

INT16U GetModbusCRC(INT8U *pSendBuf, INT8U num);

BOOL SendModbusRegData(INT8U cmd,INT16U startaddr,INT16U regnum);


INT16U Small2BigMode(INT8U *pval);



#endif

