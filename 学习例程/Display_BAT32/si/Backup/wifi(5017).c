#include"config.h"
#include"wifi.h"

#define WIFI_BUF_LEN	260

#define TYPEID			"201461071080c014220401904001020000000000000000000000000000000040"
#define DeviceKey		"28585A4276824Da5B689b24857136954"
#define VERSION			"E++2.17"
//#define SOFT_VERSION	"20211115"
#define HARD_VERSION	"20220609"
#define SOFTAP_NAME		"U-WTD"




INT8U WIFI_Sendbuf[WIFI_BUF_LEN];
WIFISET gWifiSet;



void SmallMode2BitMode(INT8U *buf,INT8U byte)
{
	INT8U temp;

	if(byte==2)
	{
		temp = buf[0];
		buf[0] = buf[1];
		buf[1] = temp;
	}
	else if(byte==3)
	{
		temp = buf[0];
		buf[0] = buf[2];
		buf[2] = temp;		
	}
}


INT8U GetSum(INT8U *pbuf,INT8U len)
{
	INT8U i,sum=0;

	for(i=0;i<len;i++)
	{
		sum += 	pbuf[i];
	}
	
	return sum;
}


INT8U WIFI_AddData2protocol(INT8U cmd,INT8U *pbuf,INT8U *pdat,INT8U len)
{
	INT8U i,*p=pbuf,datalen=len;
	
	*pbuf++ = WIFI_HEAD1;
	*pbuf++ = WIFI_HEAD2;

	*pbuf++ = len+8;//帧长
	
	*pbuf++ = 0;//标志位

	*pbuf++ = 0;//预留位
	*pbuf++ = 0;
	*pbuf++ = 0;
	*pbuf++ = 0;
	*pbuf++ = 0;

	*pbuf++ = cmd;//帧类型

	for( i=0;i<datalen;i++)//数据信息
	{
		*pbuf = *pdat++;
		
		if(*pbuf==0xFF){pbuf++;*pbuf = 0x55;len++;}
		
		pbuf++;	
	}
	
	*pbuf++ = GetSum(p+2,len+8);//累加和

	if(*pbuf==0xFF){pbuf++;*pbuf = 0x55;len++;}


	len+=11;

	gWifiSet.SendStatus=0;
	UartSendWifiData(p,len);

	return len;//数据长加11协议长
}

INT16U ASCII2Hex(const char *pBuf,INT8U num)
 {
 	int hex;
 	INT8U i;
 	char temp[11];
 	
	for(i=0;i<num;i++)
	{
		if((pBuf[i]>=0X30&&pBuf[i]<=0X39)||(pBuf[i]>=0X41&&pBuf[i]<=0X46)||(pBuf[i]>=0X61&&pBuf[i]<=0X66))
		{
			temp[i] = (char)pBuf[i];
		}
		else
		{
			return 0;
		}
	}
	temp[i]='\0';
	sscanf(temp,"%X",&hex);
	
	return (INT16U)hex;
 }

void WIFI_SendTypeID(INT8U cmd)
{
	INT8U buf[40],len,i,k=0;
	const char str[]={TYPEID};

	len = strlen(str);
	
	if(len!=64)return;

	for(i=0;i<len;i+=2)
	{
		buf[k++] = ASCII2Hex(str+i,2);
	}

	WIFI_AddData2protocol(cmd,WIFI_Sendbuf,buf,len/2);
}


void GetEncryptionFlag(INT8U *p)
{
	p[0]=0xF1;
	p[1]=0;
	p[2]=0;
}

void WIIF_SendEquiVersion(INT8U cmd)
{
	INT8U buf[36]={0};

	strcpy((char*)buf,VERSION);//8
	strcpy((char*)buf+8,SOFT_VERSION);//8
	GetEncryptionFlag(buf+8+8);//3
	strcpy((char*)buf+8+8+3,HARD_VERSION);//8
										//1
	strcpy((char*)buf+8+8+3+8+1,SOFTAP_NAME);//8
	
	WIFI_AddData2protocol(cmd,WIFI_Sendbuf,buf,36);
}

void WIFI_SetHeartbeat(INT8U cmd, INT8U *pbuf)
{//时间间隔，单位为100ms
	INT16U temp;

	temp = pbuf[0];
	temp <<= 8;
	temp |= pbuf[1];

	if(temp==0xFFFF)
	{
		temp = 50;//5秒	
	}

	if(temp==0)
	{
		gWifiSet.heartbeatEN=0;
	}
	else 
	{
		gWifiSet.heartbeatEN=1;
	}

	
	gWifiSet.heartbeat = temp*100;
	gWifiSet.heartbeatCount=0;

	WIFI_AddData2protocol(cmd,WIFI_Sendbuf,pbuf,2);
}

void WIFI_SetBigDataHeartbeat(INT8U cmd, INT8U *pbuf)
{//时间间隔，单位为100ms
	INT16U temp;

	temp = pbuf[0];
	temp <<= 8;
	temp |= pbuf[1];

	if(temp==0xFFFF)
	{
		temp = 50;//5秒	
	}

	if(temp==0)
	{
		gWifiSet.BigdataEN=0;
	}
	else 
	{
		gWifiSet.BigdataEN=1;
	}

	
	gWifiSet.BigdataHeartbeat = temp;
	gWifiSet.BigdataHeartbeatCount=0;

	WIFI_AddData2protocol(cmd,WIFI_Sendbuf,pbuf,2);
}


void WIFI_SetTime(INT8U*pbuf)
{
	SYSTEMTIME time;

	time.Hour = pbuf[1];
	time.Minute = pbuf[3];
	time.Second = pbuf[5];

	if(time.Hour>23||time.Minute>59||time.Second>59)
	{
		return;	
	}

	SetSystemTime(&time);

	//WIFI_AddData2protocol(cmd,WIFI_Sendbuf,pbuf,0);
}


void WIFI_SetPriFilterReset(INT16U concmd)
{	
	if(concmd==0x01)
	{
		StandbyRestart();

		FilterReset_PCB();
		//BeepStart(BEEP_TIME,1);
		SetBeep(1,1);
		//SendModbusCmd(REG_ADDR_CMD, CMD_FilterReset_PCB);
	}
}
void WIFI_SetRoFilterReset(INT16U concmd)
{
	if(concmd==0x01)
	{
		StandbyRestart();
		FilterReset_RO();
		
		//BeepStart(BEEP_TIME,1);
		SetBeep(1,1);
		//SendModbusCmd(REG_ADDR_CMD, CMD_FilterReset_RO);
	}
}

void WIFI_ControlHand(INT8U cmd,INT8U *pbuf)
{
	INT16U concmd;
	
	if(pbuf[0]==0x5D)
	{
		concmd = pbuf[2];
		concmd <<= 8;
		concmd |= pbuf[3];
		
		switch(pbuf[1])
		{
		case WIFI_CON_SetOutWaterTemp://设置出水温
			break;
		case WIFI_CON_SetTime://设置时间
			WIFI_SetTime(pbuf+2);
			break;
		case WIFI_CON_SetPriFilterReset://初滤复位
			WIFI_SetPriFilterReset(concmd);
			break;
		case WIFI_CON_SetAdsFilterReset://吸附复位
			break;
		case WIFI_CON_SetRawFilterReset://粗滤复位
			break;
		case WIFI_CON_SetFineFilterReset://精滤复位
			break;
		case WIFI_CON_SetRoFilterReset://RO复位
			WIFI_SetRoFilterReset(concmd);
			break;
		case WIFI_CON_SetTasFilterReset://口感复位
			break;
		case WIFI_CON_SetNanoFilterReset://纳滤复位
			break;
		case WIFI_CON_SetFlushStatus://冲洗功能状态
			if(concmd==0x01)
			{
				StandbyRestart();

				systemseting.ManualFlushFlag=1;
				//SendModbusCmd(REG_ADDR_CMD, CMD_ManualFlush_open);
			}
			else if(concmd==0x00)
			{
				ExitManualFlush();
				//SendModbusCmd(REG_ADDR_CMD, CMD_ManualFlush_close);
			}
			//BeepStart(BEEP_TIME,1);
			SetBeep(1,1);
			break;
		case WIFI_CON_SetRO2Reset:
		
			break;
		case WIFI_CON_Setfruits:
			if(concmd==0x01)
			{
				gReg.fruits=1;
			}
			else if(concmd==0x00)
			{
				gReg.fruits=0;
			}
			SetBeep(1,1);
			gReg.error.BitFlag.sparklingWaterStatus = gReg.fruits;
			break;			
		default:
			return;
		}
	}
	else if(pbuf[0]==0x4D)
	{
		
	}

	EQUI_UpdataState(WIFI_CMD_02);
}


//设备主动发送报警信息
void EQUI_SendAlarmInfo(INT8U cmd)
{
	INT8U buf[4];

	buf[0] = 0x0F;
	buf[1] = 0x5A;
	
	buf[2] = gReg.error.u16flag>>8;
	buf[3] = gReg.error.u16flag&0xFF;
	
	WIFI_AddData2protocol(cmd,WIFI_Sendbuf,buf,4);
}

void MonitorBigData(void)
{
	if(gWifiSet.BigdataEN)
	{
		
		if(++gWifiSet.BigdataHeartbeatCount>gWifiSet.BigdataHeartbeat)//心跳包
		{
			gWifiSet.BigdataHeartbeatCount=0;
			if(gWifiSet.BigdataHeartbeat==0)
			{
				gWifiSet.BigdataHeartbeat=600;//默认60秒
			}
			EQUI_UpdataState(WIFI_CMD_06);
		}		
	}
}

void MonitrorAlarm(void)
{
	static INT16U old=0,count=0,updatacount=0,oldcrc=0xff;
	INT16U crc;

	if(systemseting.wifi==0)//没有连接上网络
	{
		return;
	}

	if(++updatacount>150)//心跳包 30秒一次
	{
		updatacount=0;
		EQUI_UpdataState(WIFI_CMD_06);
		return;
	}

	crc = GetModbusCRC((INT8U*)&gReg,sizeof(REG));
	if(crc!=oldcrc)
	{
		oldcrc = crc;
		EQUI_UpdataState(WIFI_CMD_06);
	}	

	if(old != gReg.error.u16flag)
	{
		old = gReg.error.u16flag;

		gWifiSet.alarmsendflag=0;
		gWifiSet.alarmstopflag=0;
	}

	if(gWifiSet.alarmstopflag==0)
	{
		if(gWifiSet.alarmsendflag)
		{
			if(++count>25)
			{
				gWifiSet.alarmsendflag=0;
				EQUI_SendAlarmInfo(WIFI_CMD_04);
			}
		}
		else 
		{
			EQUI_SendAlarmInfo(WIFI_CMD_04);
		}
	}
}


void WIFI_GetWifiStatus(INT8U cmd,INT8U *pbuf)
{
	INT16U status,signal;

	status = pbuf[0];
	status <<= 8;
	status |= pbuf[1];

	signal = pbuf[2];
	signal <<= 8;
	signal |= pbuf[3];

	gWifiSet.wifistatus = status;

	if(gWifiSet.wifistatus==0||gWifiSet.wifistatus ==2)
	{
		gWifiSet.wifisignal = signal;

		if(gWifiSet.wifisignal<30)//弱信号
		{
			systemseting.wifi = 3;
		}
		else if(gWifiSet.wifistatus==0)//连接成功
		{
			systemseting.wifi = 2;
		}
	}
	else if(gWifiSet.wifistatus==3)
	{
		systemseting.wifi = 1;//配网模式
	}
	else 
	{
		systemseting.wifi = 0;
	}

	WIFI_AddData2protocol(cmd,WIFI_Sendbuf,pbuf,0);

	gReg.wifi=systemseting.wifi;//SendModbusCmd(REG_ADDR_CMD,CMD_SetWifiOffline+systemseting.wifi);
}


//进入配网模式
void EQUI_SendWifiNetwork(WIFIWORKMODE mode)
{
	INT8U buf[2];
	
	buf[0] = 0;
	buf[1] = mode;
	WIFI_AddData2protocol(WIFI_CMD_F2,WIFI_Sendbuf,buf,2);
}

//进入工作模式
void EQUI_SendWifiEnterwork(void)
{
	INT8U buf[2];
	
	buf[0] = 0;
	buf[1] = 0;
	WIFI_AddData2protocol(WIFI_CMD_F4,WIFI_Sendbuf,buf,2);
}

//清除WIFI配网信息
void EQUI_ClearWifiConfig(void)
{
	WIFI_AddData2protocol(WIFI_CMD_F8,WIFI_Sendbuf,NULL,0);
}


static INT16U networkcount=0;
void NetworkTimer(void)
{
	networkcount++;
	
	if(systemseting.wifi==2||gWifiSet.workmode==WIFI_WORKMODE_work)
	{
		networkcount=0;
		systemseting.uartWifiError=0;
		KillTimer(0, SYS_TIMER_wifinetwork);
	}
	else if(systemseting.wifi==1)
	{
		systemseting.uartWifiError=0;
		
		if(networkcount>=600)//10分钟
		{
			systemseting.wifi=0;
			EQUI_SendWifiEnterwork();

			if(networkcount>605)
			{
				systemseting.uartWifiError=1;
				KillTimer(0, SYS_TIMER_wifinetwork);
			}
		}
	}
	else 
	{
		if(networkcount>5)//5秒没收到WIFI信息
		{
			systemseting.uartWifiError=1;
			KillTimer(0, SYS_TIMER_wifinetwork);
		}	
		else 
		{
			EQUI_SendWifiNetwork(WIFI_WORKMODE_smartlink);
		}
	}
}
void EQUI_EnterWifiNetwork(void)
{
	networkcount=0;
	gWifiSet.workmode = WIFI_WORKMODE_smartlink;
	EQUI_SendWifiNetwork(WIFI_WORKMODE_smartlink);
	TimeSetEvent(SYS_TIMER_wifinetwork, sec(1), NetworkTimer, TIME_PERIODIC);//定时1秒钟发一次  20220706由30分钟改成10分钟
}

enum runmode
{
	runmode_flush=1,
	runmode_wroking,
	runmode_fullwater,
	runmode_hydropenia,//缺水
	runmode_standby,
	runmode_error,
};

INT8U GetOperationMode(INT8U mode)
{
	switch(mode)
	{
	case WORKSTATE_standby://待机
	case WORKSTATE_free://空闲状态
		return runmode_standby;
		
	case WORKSTATE_autoflush://自动清洗
	case WORKSTATE_PowerOnFlush://上电清洗
	case WORKSTATE_manualflush://手动清洗
		return runmode_flush;
		
	case WORKSTATE_working://制水
		return runmode_wroking;
		
	case WORKSTATE_LongTimeWork://长时间制水
	case WORKSTATE_Leaking://锁水，漏水
		return runmode_error;
		
	case WORKSTATE_GasDetection://气检
	case WORKSTATE_WaterDetection://水检
	case WORKSTATE_FilterDetection://滤芯快检
	case WORKSTATE_PowerOnProc:
	case WORKSTATE_FCT://FCT测试	
	default:
		return 0;
	}
}

UN_ERROR_W GetAllError(ERRORFLAG_t flag)
{
	UN_ERROR_W error;

	error.BitFlag.TempErrorFlag = flag.TempErrorFlag;//温度传感器故障
	error.BitFlag.rawTdsErrorFlag = flag.rawTdsErrorFlag;//原水TDS传感器故障
	error.BitFlag.pureTdsErrorFlag = flag.pureTdsErrorFlag;//纯水TDS传感器故障
	error.BitFlag.WaterLeakErrorFlag = flag.WaterLeakErrorFlag;//漏水报警
	error.BitFlag.TimeOutErrorFlag = flag.TimeOutErrorFlag;//制水超时
	error.BitFlag.WasteWaterErrorFlag = flag.WasteWaterErrorFlag;//废水比阀故障
	error.BitFlag.InWaterErrorFlag = flag.InWaterErrorFlag;//进水阀故障
	error.BitFlag.sparklingWaterStatus = flag.sparklingWaterStatus;//气泡水功能状态
	
	return error;
}

void EQUI_UpdataState(INT8U cmd)
{
	UPStatuInfo pupinfo;
	SYSTEMTIME time;
	INT8U i,*p=(INT8U*)&pupinfo;
	static INT16U PriFilterResetTimes=0,roFilterResetTimes=0;

	memset(p,0,sizeof(UPStatuInfo));
	GetSystemTime(&time);

	if(cmd==WIFI_CMD_7D)
	{
		cmd = WIFI_CMD_06;
		pupinfo.cmd1 = 0x6D;
	}
	else if(cmd==WIFI_CMD_FB)
	{
		cmd = WIFI_CMD_06;
		pupinfo.cmd1 = 0x7D;	
	}
	else 
	{
		pupinfo.cmd1 = 0x6D;
	}
	pupinfo.cmd2 = 0x01;
	
	pupinfo.rawTds = gReg.rawTDS;
	pupinfo.pureTds= gReg.netTDS;

	pupinfo.hour = time.Hour;
	pupinfo.min = time.Minute;
	pupinfo.sec = time.Second;

	pupinfo.rawTdsFlag = gReg.SenFlag.rawTdsFlag;
	pupinfo.pureTdsFlag = gReg.SenFlag.pureTdsFlag;	

	pupinfo.rawVolume = gReg.RawWaterVolume/1000;//累计源水量
	pupinfo.pureVolume = gReg.NetWaterVolume/1000;//累计纯水量

	pupinfo.priFilterRemain = gReg.FilterLife_PCB;
	pupinfo.roFilterRemain = gReg.FilterLife_RO;

	if(gReg.FilterLife_PCB==0){pupinfo.priFilterAlarmFlag = 1;}//初滤到期报警（剩余0%)
	else if(gReg.FilterLife_PCB<=10){pupinfo.priFilterWarningFlag = 1;}//初滤到期预警(剩余10%),0无预警

	if(gReg.FilterLife_RO==0){pupinfo.roFilterAlarmFlag = 1;}
	else if(gReg.FilterLife_RO<=10){pupinfo.roFilterWarningFlag = 1;}	

	pupinfo.priFilterSelectFlag = 1;//初滤选择标志位,0无此滤芯
	pupinfo.roFilterSelectFlag = 1;

	pupinfo.priFilterResetFlag = ((gReg.PriFilterResetTimes!=PriFilterResetTimes)?1:0);//初滤复位 0正常，1复位此级滤芯
	pupinfo.roFilterResetFlag = ((gReg.RoFilterResetTimes!=roFilterResetTimes)?1:0);

	PriFilterResetTimes = gReg.PriFilterResetTimes;
	roFilterResetTimes = gReg.RoFilterResetTimes;

	pupinfo.FlushStatus = gReg.PeriState.BitFlag.flush;
	pupinfo.uvSterilizationStatus = gReg.PeriState.BitFlag.uv;
	pupinfo.operationMode = GetOperationMode(gReg.WorkState);

	pupinfo.AllError = GetAllError(gReg.error.BitFlag);
	
	pupinfo.RawWaterTemperature = gReg.rawTemperature&0x00FF;//进水温度


	pupinfo.roFilter2Remain=100;
	

	//新增
	pupinfo.perRawVolume = gReg.RawWaterVolumeSingle;
	pupinfo.PerPureVolume = gReg.NetWaterVolumeSingle;

//	pupinfo.priFilterResetTimes = gReg.PriFilterResetTimes;
//	pupinfo.roFilter2ResetTimes = gReg.RoFilterResetTimes;

	
	
	//====小端转大端==============================================
	for(i=2;i<16;i+=2)
	{
		SmallMode2BitMode(p+i,2);
	}
	SmallMode2BitMode(p+20+2,3);//pupinfo.rawVolume
	SmallMode2BitMode(p+23+2,3);//pupinfo.pureVolume

	SmallMode2BitMode(p+48+2,3);//pupinfo.perRawVolume
	SmallMode2BitMode(p+51+2,3);//pupinfo.PerPureVolume

	SmallMode2BitMode(p+65+2,3);//perClearWaterVolume
	SmallMode2BitMode(p+68+2,3);//clearWaterVolume

	if(pupinfo.cmd1 == 0x7D)
	{
		WIFI_AddData2protocol(cmd,WIFI_Sendbuf,p,sizeof(UPStatuInfo)-22);
	}
	else 
	{
		WIFI_AddData2protocol(cmd,WIFI_Sendbuf,p,sizeof(UPStatuInfo));
	}
}

//去掉数据FF后面的55
INT16U GetCommData(INT8U *pbuf,INT16U len)
{
	INT16U i,k=2;
	INT8U *p=pbuf+2;

	for(i=2;i<len;i++)
	{
		*p++=pbuf[i];
		k++;
		if(pbuf[i]==0xFF)
		{
			i++;
		}
	}

	return k;
}


void WifiMsgProc(INT8U *pbuf,INT16U len)
{
	INT8U cmd;

	if(pbuf[len-1]!=GetSum(pbuf+2,len-3))
	{
		return;
	}

	GetCommData(pbuf,len);

	cmd = pbuf[9];

	systemseting.uartWifiError=0;
	
	switch(cmd)
	{
	case WIFI_CMD_01://控制或设置
		WIFI_ControlHand(cmd+1,pbuf+10);
		return;
	case WIFI_CMD_02://状态返回
		return;
	case WIFI_CMD_03:
		break;
	case WIFI_CMD_04://报警状态汇报
		break;
	case WIFI_CMD_05://确认
		gWifiSet.SendStatus=1;
		gWifiSet.alarmsendflag=1;
		WIFI_AddData2protocol(WIFI_CMD_05,WIFI_Sendbuf,NULL,0);
		break;
	case WIFI_CMD_06://状态汇报
		//EQUI_UpdataState(WIFI_CMD_06);
		//return;
		break;
	case WIFI_CMD_07:
		break;
	case WIFI_CMD_09://停止故障报警帧
		gWifiSet.alarmstopflag=1;
		break;
	case WIFI_CMD_11://网络授时
		WIFI_AddData2protocol(WIFI_CMD_05,WIFI_Sendbuf,NULL,0);
		return;
	case WIFI_CMD_60:
		break;
	case WIFI_CMD_61:
		WIIF_SendEquiVersion(cmd+1);
		return;
	case WIFI_CMD_62:
		break;
	case WIFI_CMD_63://获取密钥
		break;
	case WIFI_CMD_64:
		WIFI_AddData2protocol(WIFI_CMD_05,WIFI_Sendbuf,NULL,0);
		break;
	case WIFI_CMD_70://设备识别码查询,WIFI模块->设备
		WIFI_SendTypeID(cmd+1);
		return;
	case WIFI_CMD_71:
		break;
	case WIFI_CMD_73://查询报警状态,WIFI模块->设备
		EQUI_SendAlarmInfo(cmd+1);
		break;
	case WIFI_CMD_74://查询报警状态应答
		break;
	case WIFI_CMD_7C://设置设备主动汇报间隔
		WIFI_SetHeartbeat(cmd+1,pbuf+10);
		return;
	case WIFI_CMD_7D:
		break;
	case WIFI_CMD_E1:
		break;
	case WIFI_CMD_E2:
		break;
	case WIFI_CMD_E5:
		break;
	case WIFI_CMD_E6:
		break;
	case WIFI_CMD_E7:
		break;
	case WIFI_CMD_E8:
		break;
	case WIFI_CMD_E9:
		break;
	case WIFI_CMD_EA:
		break;
	case WIFI_CMD_EB:
		break;
	case WIFI_CMD_EC:
		break;
	case WIFI_CMD_ED:
		break;
	case WIFI_CMD_EF:
		break;
	case WIFI_CMD_F0://网络状态查询
		break;
	case WIFI_CMD_F1:
		break;
	case WIFI_CMD_F2://设备触发模块进入配置状态
		break;
	case WIFI_CMD_F3://配网返回
		systemseting.wifi=1;
		break;
	case WIFI_CMD_F4:
		break;
	case WIFI_CMD_F5:
		gWifiSet.workmode = WIFI_WORKMODE_work;//if(systemseting.wifi)systemseting.wifi=0;
		break;
	case WIFI_CMD_F6:
		break;
	case WIFI_CMD_F7://主动汇报网络状态  网络状态 信号强度。
		WIFI_GetWifiStatus(WIFI_CMD_05,pbuf+10);
		return;
	case WIFI_CMD_F8:
		break;
	case WIFI_CMD_F9:
		break;
	case WIFI_CMD_FA://设备大数据汇报配置帧
		WIFI_SetBigDataHeartbeat(cmd+1,pbuf+10);
		return;
	case WIFI_CMD_FB:
		break;
	default:
		WIFI_AddData2protocol(WIFI_CMD_03,WIFI_Sendbuf,NULL,0);
		return;
	}

	gWifiSet.beakcmd=cmd;
	
	WIFI_AddData2protocol(WIFI_CMD_05,WIFI_Sendbuf,NULL,0);
}




