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
		state = FAUCET_workmode_poweron;//上电,
	}
	else if(gReg.WorkState==WORKSTATE_free)
	{
		state = FAUCET_workmode_free;//待机  ,只显示纯水
	}
	else if(gReg.WorkState==WORKSTATE_working)
	{
		state = FAUCET_workmode_working;//制水,原水纯水交替显示
	}
	else if(gReg.WorkState==WORKSTATE_Leaking||gReg.WorkState==WORKSTATE_LongTimeWork)
	{
		state = FAUCET_workmode_error;//故障, E1
	}
	else if(gReg.WorkState==WORKSTATE_standby)
	{	
		state = FAUCET_workmode_standby;//休眠,
	}
	else if(gReg.WorkState==WORKSTATE_FCT)
	{
		state = FAUCET_workmode_FCT;//测试
	}
	else 
	{
		state = FAUCET_workmode_free;//
	}
	return state;
}


void Faucet_PowneOnDisplay(void)
{
	
	if(systemseting.PowerOnTimerCount>360)//三秒
	{
		if(systemseting.FilterLife_PCB==PCB_level_1||systemseting.FilterLife_RO==PCB_level_1)
		{
			faucet.QR=3;UartSendFaucetData("\n\nfaucet.QR=3  2\n\n",sizeof("\n\nfaucet.QR=3  2\n\n"));   //红色
		}
		else if(systemseting.FilterLife_PCB==PCB_level_2||systemseting.FilterLife_RO==PCB_level_2)
		{
			faucet.QR=2; UartSendFaucetData("\n\nfaucet.QR=2  2\n\n",sizeof("\n\nfaucet.QR=2  2\n\n"));   //黄色
		}
		else 
		{
			faucet.QR=1;//白色
		}
	}
	else if(systemseting.PowerOnTimerCount==240)//3秒钟
	{
		faucet.QR=2;UartSendFaucetData("\n\nfaucet.QR=2  1\n\n",sizeof("\n\nfaucet.QR=2  1\n\n"));
	}
	else if(systemseting.PowerOnTimerCount==120)//2秒钟
	{
		faucet.QR=3;UartSendFaucetData("\n\nfaucet.QR=3  1\n\n",sizeof("\n\nfaucet.QR=3  1\n\n"));
	}
	else //1秒钟
	{
		faucet.QR=1;//白色
	}	 

	//uart_printf1("PCB=%d,RO=%d,QR=%d\n",systemseting.FilterLife_PCB,systemseting.FilterLife_RO,faucet.QR);
}

//水龙头显示 1秒钟刷新一次
void Faucet_Display(void)
{
	INT8U *p=(INT8U*)&faucet;
	
	faucet.error = 0x00;

	faucet.head1 = 0xA5;
	faucet.head2 = 0xA6;
	
	faucet.len = sizeof(FAUCET); 

	faucet.cmd = 0x01;//显示指令
	
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
			faucet.error = 0x02;//FA 长时间制水
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
		faucet.digi = Small2BigMode((INT8U*)&gReg.netTDS);//纯水TDS
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

	if(pbuf[3]==0x81)//水龙头唤醒
	{
		systemseting.HVS_faucet=1;
		systemseting.FaucetGetCmdCount=0;

		flag=1;//UartSendFaucetData(pbuf,len);//返回一样的指令 
	}
	else if(pbuf[3]==0x82)//关闭
	{
		systemseting.HVS_faucet=0;
		systemseting.FaucetGetCmdCount=0;
		
		flag=1;//UartSendFaucetData(pbuf,len);//返回一样的指令
	}

	if(flag)
	{
		Faucet_Display();
	}

	return;	
}


