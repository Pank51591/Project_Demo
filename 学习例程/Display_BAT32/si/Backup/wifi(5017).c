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

	*pbuf++ = len+8;//֡��
	
	*pbuf++ = 0;//��־λ

	*pbuf++ = 0;//Ԥ��λ
	*pbuf++ = 0;
	*pbuf++ = 0;
	*pbuf++ = 0;
	*pbuf++ = 0;

	*pbuf++ = cmd;//֡����

	for( i=0;i<datalen;i++)//������Ϣ
	{
		*pbuf = *pdat++;
		
		if(*pbuf==0xFF){pbuf++;*pbuf = 0x55;len++;}
		
		pbuf++;	
	}
	
	*pbuf++ = GetSum(p+2,len+8);//�ۼӺ�

	if(*pbuf==0xFF){pbuf++;*pbuf = 0x55;len++;}


	len+=11;

	gWifiSet.SendStatus=0;
	UartSendWifiData(p,len);

	return len;//���ݳ���11Э�鳤
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
{//ʱ��������λΪ100ms
	INT16U temp;

	temp = pbuf[0];
	temp <<= 8;
	temp |= pbuf[1];

	if(temp==0xFFFF)
	{
		temp = 50;//5��	
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
{//ʱ��������λΪ100ms
	INT16U temp;

	temp = pbuf[0];
	temp <<= 8;
	temp |= pbuf[1];

	if(temp==0xFFFF)
	{
		temp = 50;//5��	
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
		case WIFI_CON_SetOutWaterTemp://���ó�ˮ��
			break;
		case WIFI_CON_SetTime://����ʱ��
			WIFI_SetTime(pbuf+2);
			break;
		case WIFI_CON_SetPriFilterReset://���˸�λ
			WIFI_SetPriFilterReset(concmd);
			break;
		case WIFI_CON_SetAdsFilterReset://������λ
			break;
		case WIFI_CON_SetRawFilterReset://���˸�λ
			break;
		case WIFI_CON_SetFineFilterReset://���˸�λ
			break;
		case WIFI_CON_SetRoFilterReset://RO��λ
			WIFI_SetRoFilterReset(concmd);
			break;
		case WIFI_CON_SetTasFilterReset://�ڸи�λ
			break;
		case WIFI_CON_SetNanoFilterReset://���˸�λ
			break;
		case WIFI_CON_SetFlushStatus://��ϴ����״̬
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


//�豸�������ͱ�����Ϣ
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
		
		if(++gWifiSet.BigdataHeartbeatCount>gWifiSet.BigdataHeartbeat)//������
		{
			gWifiSet.BigdataHeartbeatCount=0;
			if(gWifiSet.BigdataHeartbeat==0)
			{
				gWifiSet.BigdataHeartbeat=600;//Ĭ��60��
			}
			EQUI_UpdataState(WIFI_CMD_06);
		}		
	}
}

void MonitrorAlarm(void)
{
	static INT16U old=0,count=0,updatacount=0,oldcrc=0xff;
	INT16U crc;

	if(systemseting.wifi==0)//û������������
	{
		return;
	}

	if(++updatacount>150)//������ 30��һ��
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

		if(gWifiSet.wifisignal<30)//���ź�
		{
			systemseting.wifi = 3;
		}
		else if(gWifiSet.wifistatus==0)//���ӳɹ�
		{
			systemseting.wifi = 2;
		}
	}
	else if(gWifiSet.wifistatus==3)
	{
		systemseting.wifi = 1;//����ģʽ
	}
	else 
	{
		systemseting.wifi = 0;
	}

	WIFI_AddData2protocol(cmd,WIFI_Sendbuf,pbuf,0);

	gReg.wifi=systemseting.wifi;//SendModbusCmd(REG_ADDR_CMD,CMD_SetWifiOffline+systemseting.wifi);
}


//��������ģʽ
void EQUI_SendWifiNetwork(WIFIWORKMODE mode)
{
	INT8U buf[2];
	
	buf[0] = 0;
	buf[1] = mode;
	WIFI_AddData2protocol(WIFI_CMD_F2,WIFI_Sendbuf,buf,2);
}

//���빤��ģʽ
void EQUI_SendWifiEnterwork(void)
{
	INT8U buf[2];
	
	buf[0] = 0;
	buf[1] = 0;
	WIFI_AddData2protocol(WIFI_CMD_F4,WIFI_Sendbuf,buf,2);
}

//���WIFI������Ϣ
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
		
		if(networkcount>=600)//10����
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
		if(networkcount>5)//5��û�յ�WIFI��Ϣ
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
	TimeSetEvent(SYS_TIMER_wifinetwork, sec(1), NetworkTimer, TIME_PERIODIC);//��ʱ1���ӷ�һ��  20220706��30���Ӹĳ�10����
}

enum runmode
{
	runmode_flush=1,
	runmode_wroking,
	runmode_fullwater,
	runmode_hydropenia,//ȱˮ
	runmode_standby,
	runmode_error,
};

INT8U GetOperationMode(INT8U mode)
{
	switch(mode)
	{
	case WORKSTATE_standby://����
	case WORKSTATE_free://����״̬
		return runmode_standby;
		
	case WORKSTATE_autoflush://�Զ���ϴ
	case WORKSTATE_PowerOnFlush://�ϵ���ϴ
	case WORKSTATE_manualflush://�ֶ���ϴ
		return runmode_flush;
		
	case WORKSTATE_working://��ˮ
		return runmode_wroking;
		
	case WORKSTATE_LongTimeWork://��ʱ����ˮ
	case WORKSTATE_Leaking://��ˮ��©ˮ
		return runmode_error;
		
	case WORKSTATE_GasDetection://����
	case WORKSTATE_WaterDetection://ˮ��
	case WORKSTATE_FilterDetection://��о���
	case WORKSTATE_PowerOnProc:
	case WORKSTATE_FCT://FCT����	
	default:
		return 0;
	}
}

UN_ERROR_W GetAllError(ERRORFLAG_t flag)
{
	UN_ERROR_W error;

	error.BitFlag.TempErrorFlag = flag.TempErrorFlag;//�¶ȴ���������
	error.BitFlag.rawTdsErrorFlag = flag.rawTdsErrorFlag;//ԭˮTDS����������
	error.BitFlag.pureTdsErrorFlag = flag.pureTdsErrorFlag;//��ˮTDS����������
	error.BitFlag.WaterLeakErrorFlag = flag.WaterLeakErrorFlag;//©ˮ����
	error.BitFlag.TimeOutErrorFlag = flag.TimeOutErrorFlag;//��ˮ��ʱ
	error.BitFlag.WasteWaterErrorFlag = flag.WasteWaterErrorFlag;//��ˮ�ȷ�����
	error.BitFlag.InWaterErrorFlag = flag.InWaterErrorFlag;//��ˮ������
	error.BitFlag.sparklingWaterStatus = flag.sparklingWaterStatus;//����ˮ����״̬
	
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

	pupinfo.rawVolume = gReg.RawWaterVolume/1000;//�ۼ�Դˮ��
	pupinfo.pureVolume = gReg.NetWaterVolume/1000;//�ۼƴ�ˮ��

	pupinfo.priFilterRemain = gReg.FilterLife_PCB;
	pupinfo.roFilterRemain = gReg.FilterLife_RO;

	if(gReg.FilterLife_PCB==0){pupinfo.priFilterAlarmFlag = 1;}//���˵��ڱ�����ʣ��0%)
	else if(gReg.FilterLife_PCB<=10){pupinfo.priFilterWarningFlag = 1;}//���˵���Ԥ��(ʣ��10%),0��Ԥ��

	if(gReg.FilterLife_RO==0){pupinfo.roFilterAlarmFlag = 1;}
	else if(gReg.FilterLife_RO<=10){pupinfo.roFilterWarningFlag = 1;}	

	pupinfo.priFilterSelectFlag = 1;//����ѡ���־λ,0�޴���о
	pupinfo.roFilterSelectFlag = 1;

	pupinfo.priFilterResetFlag = ((gReg.PriFilterResetTimes!=PriFilterResetTimes)?1:0);//���˸�λ 0������1��λ�˼���о
	pupinfo.roFilterResetFlag = ((gReg.RoFilterResetTimes!=roFilterResetTimes)?1:0);

	PriFilterResetTimes = gReg.PriFilterResetTimes;
	roFilterResetTimes = gReg.RoFilterResetTimes;

	pupinfo.FlushStatus = gReg.PeriState.BitFlag.flush;
	pupinfo.uvSterilizationStatus = gReg.PeriState.BitFlag.uv;
	pupinfo.operationMode = GetOperationMode(gReg.WorkState);

	pupinfo.AllError = GetAllError(gReg.error.BitFlag);
	
	pupinfo.RawWaterTemperature = gReg.rawTemperature&0x00FF;//��ˮ�¶�


	pupinfo.roFilter2Remain=100;
	

	//����
	pupinfo.perRawVolume = gReg.RawWaterVolumeSingle;
	pupinfo.PerPureVolume = gReg.NetWaterVolumeSingle;

//	pupinfo.priFilterResetTimes = gReg.PriFilterResetTimes;
//	pupinfo.roFilter2ResetTimes = gReg.RoFilterResetTimes;

	
	
	//====С��ת���==============================================
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

//ȥ������FF�����55
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
	case WIFI_CMD_01://���ƻ�����
		WIFI_ControlHand(cmd+1,pbuf+10);
		return;
	case WIFI_CMD_02://״̬����
		return;
	case WIFI_CMD_03:
		break;
	case WIFI_CMD_04://����״̬�㱨
		break;
	case WIFI_CMD_05://ȷ��
		gWifiSet.SendStatus=1;
		gWifiSet.alarmsendflag=1;
		WIFI_AddData2protocol(WIFI_CMD_05,WIFI_Sendbuf,NULL,0);
		break;
	case WIFI_CMD_06://״̬�㱨
		//EQUI_UpdataState(WIFI_CMD_06);
		//return;
		break;
	case WIFI_CMD_07:
		break;
	case WIFI_CMD_09://ֹͣ���ϱ���֡
		gWifiSet.alarmstopflag=1;
		break;
	case WIFI_CMD_11://������ʱ
		WIFI_AddData2protocol(WIFI_CMD_05,WIFI_Sendbuf,NULL,0);
		return;
	case WIFI_CMD_60:
		break;
	case WIFI_CMD_61:
		WIIF_SendEquiVersion(cmd+1);
		return;
	case WIFI_CMD_62:
		break;
	case WIFI_CMD_63://��ȡ��Կ
		break;
	case WIFI_CMD_64:
		WIFI_AddData2protocol(WIFI_CMD_05,WIFI_Sendbuf,NULL,0);
		break;
	case WIFI_CMD_70://�豸ʶ�����ѯ,WIFIģ��->�豸
		WIFI_SendTypeID(cmd+1);
		return;
	case WIFI_CMD_71:
		break;
	case WIFI_CMD_73://��ѯ����״̬,WIFIģ��->�豸
		EQUI_SendAlarmInfo(cmd+1);
		break;
	case WIFI_CMD_74://��ѯ����״̬Ӧ��
		break;
	case WIFI_CMD_7C://�����豸�����㱨���
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
	case WIFI_CMD_F0://����״̬��ѯ
		break;
	case WIFI_CMD_F1:
		break;
	case WIFI_CMD_F2://�豸����ģ���������״̬
		break;
	case WIFI_CMD_F3://��������
		systemseting.wifi=1;
		break;
	case WIFI_CMD_F4:
		break;
	case WIFI_CMD_F5:
		gWifiSet.workmode = WIFI_WORKMODE_work;//if(systemseting.wifi)systemseting.wifi=0;
		break;
	case WIFI_CMD_F6:
		break;
	case WIFI_CMD_F7://�����㱨����״̬  ����״̬ �ź�ǿ�ȡ�
		WIFI_GetWifiStatus(WIFI_CMD_05,pbuf+10);
		return;
	case WIFI_CMD_F8:
		break;
	case WIFI_CMD_F9:
		break;
	case WIFI_CMD_FA://�豸�����ݻ㱨����֡
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




