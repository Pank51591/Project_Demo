#include"config.h"
#include"faucet.h"


FAUCET	faucet;

static INT8U GetSum(INT8U *pbuf,INT8U len)
{
	INT8U i,sum=0;

	for(i=0;i<len;i++)
	{
		sum += 	pbuf[i];
	}
	
	return sum;
}


INT8U Faucet_workstate(void)
{
	INT8U state=0;


	if(systemseting.uartdisplayError)
	{
		state = FAUCET_workmode_error;//
	}
	else if(systemseting.WaterFlowError)
	{
		state = FAUCET_workmode_error;//
	}	
	else if(systemseting.uartWifiError)
	{
		state = FAUCET_workmode_error;//
	}
	else if(gReg.WorkState==WORKSTATE_PowerOnProc)
	{
		state = FAUCET_workmode_poweron;//�ϵ�,
	}
	else if(gReg.WorkState==WORKSTATE_free)
	{
		state = FAUCET_workmode_free;//����  ,ֻ��ʾ��ˮ
	}
	else if(gReg.WorkState==WORKSTATE_working)
	{
		state = FAUCET_workmode_working;//��ˮ,ԭˮ��ˮ������ʾ
	}
	else if(gReg.WorkState==WORKSTATE_Leaking||gReg.WorkState==WORKSTATE_LongTimeWork)
	{
		state = FAUCET_workmode_error;//����, E1
	}
	else if(gReg.WorkState==WORKSTATE_standby)
	{	
		state = FAUCET_workmode_standby;//����,
	}
	else if(gReg.WorkState==WORKSTATE_FCT)
	{
		state = FAUCET_workmode_FCT;//����
	}
	else 
	{
		state = FAUCET_workmode_free;//
	}
	return state;
}


void Faucet_PowneOnDisplay(void)
{
	
	if(systemseting.PowerOnTimerCount>360)//����
	{
		if(systemseting.FilterLife_PCB==PCB_level_1||systemseting.FilterLife_RO==PCB_level_1)
		{
			faucet.QR=3;UartSendFaucetData("\n\nfaucet.QR=3  2\n\n",sizeof("\n\nfaucet.QR=3  2\n\n"));   //��ɫ
		}
		else if(systemseting.FilterLife_PCB==PCB_level_2||systemseting.FilterLife_RO==PCB_level_2)
		{
			faucet.QR=2; UartSendFaucetData("\n\nfaucet.QR=2  2\n\n",sizeof("\n\nfaucet.QR=2  2\n\n"));   //��ɫ
		}
		else 
		{
			faucet.QR=1;//��ɫ
		}
	}
	else if(systemseting.PowerOnTimerCount==240)//3����
	{
		faucet.QR=2;UartSendFaucetData("\n\nfaucet.QR=2  1\n\n",sizeof("\n\nfaucet.QR=2  1\n\n"));
	}
	else if(systemseting.PowerOnTimerCount==120)//2����
	{
		faucet.QR=3;UartSendFaucetData("\n\nfaucet.QR=3  1\n\n",sizeof("\n\nfaucet.QR=3  1\n\n"));
	}
	else //1����
	{
		faucet.QR=1;//��ɫ
	}	 

	//uart_printf1("PCB=%d,RO=%d,QR=%d\n",systemseting.FilterLife_PCB,systemseting.FilterLife_RO,faucet.QR);
}

//ˮ��ͷ��ʾ 1����ˢ��һ��
void Faucet_Display(void)
{
	INT8U *p=(INT8U*)&faucet;
	
	faucet.error = 0x00;

	faucet.head1 = 0xA5;
	faucet.head2 = 0xA6;
	
	faucet.len = sizeof(FAUCET); 

	faucet.cmd = 0x01;//��ʾָ��
	
	faucet.workstate =Faucet_workstate();

	if(gReg.fruits)
	{
		if(gReg.WorkState==WORKSTATE_live)
		{
			faucet.fruits = 4;
		}
		else 
		{
			faucet.fruits = 1;
		}
	}
	else 
	{
		faucet.fruits = 0;
	}
	
	faucet.wifi = gReg.wifi;

	Faucet_PowneOnDisplay(); 

	if(faucet.workstate==FAUCET_workmode_poweron)
	{
	
	}
	else if(systemseting.FirstBootGetTDSFlag==0)
	{
			
	}	
	else if(faucet.workstate==FAUCET_workmode_error)
	{
		if(gReg.WorkState==WORKSTATE_Leaking)
		{
			faucet.error = 0x05;
		}
		else if(gReg.WorkState==WORKSTATE_LongTimeWork)
		{
			faucet.error = 0x02;//FA ��ʱ����ˮ
		}
		else if(systemseting.uartdisplayError&&gReg.WorkState==WORKSTATE_free)
		{
			faucet.error = 0x03;//EU
		}	
		else if(systemseting.uartWifiError&&gReg.WorkState==WORKSTATE_free)
		{
			faucet.error = 0x04;//F0
		}
		else if(systemseting.WaterFlowError)
		{
			faucet.error = 0x01;//FU
		}		
	}
	else 
	{
		
	}

	if(faucet.error)
	{
		faucet.digi = 0;
	}
	else 
	{
		faucet.TDS = 1;faucet.Mg_L = 1;
		faucet.digi = Small2BigMode((INT8U*)&gReg.netTDS);//��ˮTDS
	}
	
	faucet.crc = GetSum(p+2, sizeof(FAUCET)-3)+0X11;

	//UartSendFaucetData(p,sizeof(FAUCET)); 	
}




void Faucet_proc(INT8U*pbuf,INT16U len)
{
	INT8U crc,flag=0;

	if(pbuf[0]!=0xA5||pbuf[1]!=0xA6)
	{
		return;
	}

	crc = pbuf[2]+pbuf[3]+0X11;

	if(crc!=pbuf[4])
	{
		return;
	}

	if(pbuf[3]==0x81)//ˮ��ͷ����
	{
		systemseting.HVS_faucet=1;
		systemseting.FaucetGetCmdCount=0;

		flag=1;//UartSendFaucetData(pbuf,len);//����һ����ָ�� 
	}
	else if(pbuf[3]==0x82)//�ر�
	{
		systemseting.HVS_faucet=0;
		systemseting.FaucetGetCmdCount=0;
		
		flag=1;//UartSendFaucetData(pbuf,len);//����һ����ָ��
	}

	if(flag)
	{
		Faucet_Display();
	}

	return;	
}


