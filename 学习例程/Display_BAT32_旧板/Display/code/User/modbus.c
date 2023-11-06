#include"config.h"
#include"modbus.h"


#define UartSend485Data UartSendDisplayData



INT8U REG_ADDR_MAX=sizeof(REG)/2;

static INT8U *pReg=(INT8U*)&gReg;


void Modbus_SetReg(void *reg,INT8U regnum)
{
	pReg = (INT8U*)reg;
	REG_ADDR_MAX = regnum;
}

INT16U Small2BigMode(INT8U *pval)
{
	INT16U temp;

	temp = pval[0];
	temp <<= 8;
	temp |= pval[1];

	return temp;
}

//发送错误数据
BOOL SendModbusError(INT8U cmd,INT8U error)
{
	INT16U crc;
	INT8U p[10];

	p[0]=RS_ADDR;//设备地址
	p[1]=cmd+0x80;//错误码
	p[2]=error;//异常码

	crc=GetModbusCRC(p,3);
	p[3]=crc&0x00ff;
	p[4]=((crc>>8)&0x00ff);
	
	UartSend485Data(p,5);

	return TRUE;  
}

BOOL WriteRegData(INT16U startaddr,INT8U *p,INT16U regnum)
{
	INT8U *preg=pReg+startaddr*2;
	INT16U i;
	
	for(i=0;i<regnum;i++)
	{
		*(preg+1) = *(p);
		*(preg)   = *(p+1);

		preg++;p++;
		preg++;p++;
	}
	
	return TRUE;
}

BOOL SendModbusRegData(INT8U cmd,INT16U startaddr,INT16U regnum)
{
	INT8U pbuff[100]={0};
	INT8U i,k,num; 
	INT8U *p;
	INT16U crc;

	p = pReg;

	num = regnum*2;

	if(num<1)
	{
		return 0;
	}
	
	pbuff[0]=RS_ADDR;
	pbuff[1]=cmd;
	pbuff[2]=num;
	
	for(i=0;i<regnum;i++)
	{
		k=i*2;
		pbuff[3+k]=p[k+1];//((temp>>8)&0x00ff);
		pbuff[4+k]=p[k];//(temp&0x00ff);
	}
	
	crc=GetModbusCRC(pbuff,i*2+3);
	pbuff[3+i*2]=crc&0x00ff;
	pbuff[4+i*2]=((crc>>8)&0x00ff);

	UartSend485Data(pbuff,4+i*2+1);
	
	return TRUE;
}

BOOL ReturnWriteMultiRegOK(INT8U cmd,INT16U startaddr,INT16U regnum)
{
	INT16U temp;
	INT8U pbuff[10];      
	
	pbuff[0]=RS_ADDR;
	pbuff[1]=cmd;
	pbuff[2]=((startaddr>>8)&0x00ff);
	pbuff[3]=((startaddr)&0x00ff);
	
	pbuff[4]=((regnum>>8)&0x00ff);
	pbuff[5]=((regnum)&0x00ff);
	
	temp=GetModbusCRC(pbuff,6);
	pbuff[6]=temp&0x00ff;
	pbuff[7]=((temp>>8)&0x00ff);

	UartSend485Data(pbuff,8);
	
	return TRUE;
}


//操作寄存器处理
BOOL CmdREGHandle(INT16U cmd)
{
	switch(cmd)
	{	
	case CMD_ManualFlush_open:
		systemseting.ManualFlushFlag=1;
		break;
	case CMD_ManualFlush_close:
		ExitManualFlush();
		break;
	case CMD_FilterReset_PCB:
		FilterReset_PCB();
		break;
	case CMD_FilterReset_RO:
		FilterReset_RO();
		break;	
	case CMD_ExitWorking:
		systemseting.PowerOnFlushFlag=0;
		systemseting.AutoFlushFlag=0;
		break;
	case CMD_Factory:
		RestoreFactory();
		break;
	case CMD_GasDetection://工厂气检
		GasDetection();
		break;
	case CMD_WaterDetection://水检
		WaterDetection();
		break;
	case CMD_FilterDetection://滤芯快检
		FilterDetection();
		break;
	case CMD_ExitDetection:
		ExitFactoryMode();
		break;
		
		
	case CMD_SetWifiOffline:
		gReg.wifi = 0;
		break;
	case CMD_SetWifiNetwork:
		gReg.wifi = 1;
		break;
	case CMD_SetWifiOnline:
		gReg.wifi = 2;
		break;
	case CMD_SetWifiSignalWeak:
		gReg.wifi = 3;
		break;

	case CMD_EnterFCT:
		systemseting.FCTFlag=1;
		EnterFCTMode();
		break;
	case CMD_ExitFCT:
		systemseting.FCTFlag=0;
		ExitFCTMode();
		break;

	case CMD_Emptyshell_Ready:
		systemseting.EmptyshellFlag = DEMOMODE_Ready;
		break;	
	case CMD_Emptyshell_demo_a:
		systemseting.EmptyshellFlag = DEMOMODE_demo_a;
		break;		
	case CMD_Emptyshell_demo_b:
		systemseting.EmptyshellFlag = DEMOMODE_demo_b;
		break;
		
	case CMD_Error_ExitTimeout:
		ClearLongTimeWorkFlag();
		break;
	default:
		return FALSE;
	}
	
	return TRUE;
}



BOOL ModbusProc(INT8U *pbuff,INT8U len)
{
	INT16S temp;
	INT16U addr;//寄存器起始地址
	INT16U regnum;
	INT8U cmd;
	
	pbuff = pbuff;

	//匹配地址
	if(RS_ADDR!=pbuff[0])
	{
		return FALSE;
	}

	cmd = pbuff[1];

	//指令超出范围
	if(cmd>0x7f)
	{
		SendModbusError(cmd,MODBUS_ERROR_01);	
		return FALSE;
	}
	
	//数据校验
	if(GetModbusCRC(pbuff,len)!=0)
	{
		return FALSE;
	}

	addr = pbuff[2];
	addr <<= 8;
	addr |= pbuff[3];

	//地址超出范围
	if(addr>=REG_ADDR_MAX)
	{
		SendModbusError(cmd,MODBUS_ERROR_03);	
		return FALSE;
	}	

	switch(cmd)
	{
	case MODBUS_CMD_03://读寄存器数据
		regnum = pbuff[4];
		regnum <<= 8;
		regnum |= pbuff[5];
		
		if((addr+regnum)<=REG_ADDR_MAX)//寄存器数量超出范围
		{
			SendModbusRegData(MODBUS_CMD_03,addr,regnum);
		}
		else
		{
			SendModbusError(cmd,MODBUS_ERROR_03);
			return FALSE;
		}
		break;
	case MODBUS_CMD_06://写单个寄存器数据
	
		regnum = 1;
	
		if(addr==REG_ADDR_CMD)//操作寄存器
		{
			temp = pbuff[4];
			temp <<= 8;
			temp |= pbuff[5];

			if(CmdREGHandle(temp))
			{
				SaveSysSeting();
				UartSend485Data(pbuff,len);
			}
			else
			{
				SendModbusError(cmd,MODBUS_ERROR_05);
			}
		}
		else 
		{
			if(WriteRegData(addr,&pbuff[4],regnum))
			{
				UartSend485Data(pbuff,len);
				SaveSysSeting();
			}
			else
			{
				SendModbusError(cmd,MODBUS_ERROR_05);
			}
		}
		break;
	case MODBUS_CMD_10:

		regnum = pbuff[4];
		regnum <<= 8;
		regnum |= pbuff[5];

		if((addr+regnum)>REG_ADDR_MAX)//寄存器数量超出范围
		{
			SendModbusError(cmd,MODBUS_ERROR_03);
			return FALSE;
		}
		
		if(WriteRegData(addr,&pbuff[7],regnum))
		{
			ReturnWriteMultiRegOK(MODBUS_CMD_10,addr,regnum);
			SaveSysSeting();
		}
		else
		{
			SendModbusError(cmd,MODBUS_ERROR_05);
		}
		break;
	default:
		break;
	}

	return TRUE;
}

INT16U GetModbusCRC(INT8U *pSendBuf, INT8U num)//获得校验码 
{ 
	  INT8U i,j;
	  INT16U c,wCrc = 0xFFFF;

       for(i=0; i<num; i++)
       {
       	  c=pSendBuf[i];
          wCrc ^= c;
          for(j=0; j<8; j++)
          {
             if(wCrc & 1)
             {
                wCrc >>= 1; 
                wCrc ^= 0xA001; 
             }
             else
			 {
                wCrc >>= 1; 
             }
          }
       }
	   
       return wCrc;
}


