#include"config.h"
#include"AppUart.h"

void IRQ10_Handler(void) __attribute__((alias("uart0_interrupt_send")));//WIFI
void IRQ11_Handler(void) __attribute__((alias("uart0_interrupt_receive")));
void IRQ13_Handler(void) __attribute__((alias("uart1_interrupt_send")));//显示
void IRQ14_Handler(void) __attribute__((alias("uart1_interrupt_receive")));
void IRQ07_Handler(void) __attribute__((alias("uart2_interrupt_send")));//水龙头
void IRQ08_Handler(void) __attribute__((alias("uart2_interrupt_receive")));


INT8U uarttimeout;
INT8U uart1timeout;
INT8U uart2timeout;
//INT8U uart5timeout;


static BOOL RecFlag;
static BOOL Rec1Flag;
static BOOL Rec2Flag;
//static BOOL Rec5Flag;
 
static INT8U UartGetData[100]={0};
static INT8U Uart1GetData[100]={0};//
static INT8U Uart2GetData[100]={0};//
//static INT8U Uart5GetData[100]={0};//


static INT16U uartcount=0;//接收数据个数
static INT16U uart1count=0;
static INT16U uart2count=0;
//static INT16U uart5count=0;

#define RS485_SEND_MODE()	//PB8=1;
#define RS485_REC_MODE()	//PB8=0;


static SENDBUF uart0Sendcon;
static SENDBUF uart1Sendcon;
static SENDBUF uart2Sendcon;


//**************************************************************************************
//	函数名称	: UartInit	
//	作者		: yzy	
//	模块功能	: 串口1硬件初始化函数
//	返回值      : 无	
//  参数介绍    : port串口号，buad波特率 
//  更改记录	:
//**************************************************************************************
void UartInit(INT8U port,INT8U buad)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART0 */
    //SYS_ResetModule(UART1_RST);

    /* Configure UART0 and set UART0 Baudrate */
    //UART_Open(UART1, 115200);

   // UART_EnableInt(UART1,(UART_IER_RDA_IEN_Msk | UART_IER_THRE_IEN_Msk));
}

//**************************************************************************************
//	函数名称	: UartInterruput	
//	作者		: yzy	
//	模块功能	: 串口1中断函数
//	返回值      : 无	
//  参数介绍    : 无 
//  更改记录	:
//**************************************************************************************
//void UartInterruput(void) interrupt 4
void uart0_interrupt_receive(void)
{
    static INT16U i=0;

	INTC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
	
    if(uarttimeout>15){i=0;RecFlag = 0;}
    
	uarttimeout=0;

	
    UartGetData[i] = (INT8U)SCI0->RXD0;
 
	if(i>1)RecFlag = 1;

    if(i<SERIAL_BUFF_NUM-2)
    {
		i++;
    }
    uartcount = i;   
}

void uart1_interrupt_receive(void)
{
    static INT16U i=0;

	INTC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
	
    if(uart1timeout>15){i=0;Rec1Flag = 0;}
    
	uart1timeout=0;

	
    Uart1GetData[i] = (INT8U)SCI0->RXD1;
 
	if(i>1)Rec1Flag = 1;

    if(i<SERIAL_BUFF_NUM-2)
    {
		i++;
    }
    uart1count = i;

}

void uart2_interrupt_receive(void)
{
    static INT16U i=0;

	INTC_ClearPendingIRQ(SR2_IRQn); /* clear INTSR2 interrupt flag */
	
    if(uart2timeout>15){i=0;Rec2Flag = 0;}
    
	uart2timeout=0;

	
    Uart2GetData[i] = (INT8U)SCI1->RXD2;
 
	if(i>1)Rec2Flag = 1;

    if(i<SERIAL_BUFF_NUM-2)
    {
		i++;
    }
    uart2count = i;

}

void uart0_interrupt_send(void)
{
	INTC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
	if (uart0Sendcon.len > 1U)
	{
		SCI0->TXD0 = uart0Sendcon.buf[uart0Sendcon.isend];
		uart0Sendcon.isend++;
		
		if(uart0Sendcon.len == uart0Sendcon.isend)
		{
			uart0Sendcon.isend=0;
			uart0Sendcon.len=0;
			uart0Sendcon.busy=0;
			INTC_DisableIRQ(ST0_IRQn); /* disable INTST1 interrupt */
		}
	}
	else 
	{
		INTC_DisableIRQ(ST0_IRQn);
	}
}
void uart1_interrupt_send(void)
{
	INTC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
	if (uart1Sendcon.len > 1U)
	{
		SCI0->TXD1 = uart1Sendcon.buf[uart1Sendcon.isend];
		uart1Sendcon.isend++;
		
		if(uart1Sendcon.len == uart1Sendcon.isend)
		{
			uart1Sendcon.isend=0;
			uart1Sendcon.len=0;
			uart1Sendcon.busy=0;
			INTC_DisableIRQ(ST1_IRQn); /* disable INTST1 interrupt */
		}
	}
	else 
	{
		INTC_DisableIRQ(ST1_IRQn);
	}

}
void uart2_interrupt_send(void)
{
	INTC_ClearPendingIRQ(ST2_IRQn); /* clear INTST1 interrupt flag */
	if (uart2Sendcon.len > 1U)
	{
		SCI1->TXD2 = uart2Sendcon.buf[uart2Sendcon.isend];
		uart2Sendcon.isend++;
		
		if(uart2Sendcon.len == uart2Sendcon.isend)
		{
			uart2Sendcon.isend=0;
			uart2Sendcon.len=0;
			uart2Sendcon.busy=0;
			INTC_DisableIRQ(ST2_IRQn); /* disable INTST1 interrupt */
		}
	}
	else 
	{
		INTC_DisableIRQ(ST2_IRQn);
	}

}

//**************************************************************************************
//	函数名称	: GetDisplayData	
//	作者		: yzy	
//	模块功能	: 获取串口1接收到的数据
//	返回值      : 1获取成功，0获取失败。	
//  参数介绍    : buff为获取到串口接收的数据放在这个地址中。 
//  更改记录	:
//**************************************************************************************
INT16U GetDisplayData(INT8U *buff)
{
	INT16U i;
	INT16U len=0;	

	len = uart1count;
	if(Rec1Flag == 0||uart1timeout<20){return FALSE;}


	memset(buff,'\0',SERIAL_BUFF_NUM);

	//len=Uart_data_handle(buff);
	
	for(i=0;i<(len);i++)
	{
		buff[i] = Uart1GetData[i];
		Uart1GetData[i] = 0;
	}

	Rec1Flag = 0;//使能接收
	uart1count = 0;

	return len;
}


INT16U GetFaucetData(INT8U *buff)
{
	INT16U i;
	INT16U len=0;

  
	len = uart2count;

	if(Rec2Flag == 0||uart2timeout<20){return FALSE;}

	memset(buff,0,SERIAL_BUFF_NUM);

	for(i=0;i<(len);i++)
	{
		buff[i] = Uart2GetData[i];
		Uart2GetData[i] = 0;
	}

	Rec2Flag = 0;//使能接收
	uart2count = 0;

	return len;
}


INT16U GetWifiData(INT8U *buff)
{
	INT16U i;
	INT16U len=0;

  
	len = uartcount;

	if(RecFlag == 0||uarttimeout<20){return FALSE;}

	memset(buff,0,SERIAL_BUFF_NUM);

	for(i=0;i<(len);i++)
	{
		buff[i] = UartGetData[i];
		UartGetData[i] = 0;
	}

	RecFlag = 0;//使能接收
	uartcount = 0;

	return len;
}


#if 1
BOOL UartSendDisplayData(INT8U *buff,INT8U len)
{
	INT8U i;

	if(uart1Sendcon.busy==1)
	{
		return FALSE;
	}
	uart1Sendcon.isend=1;
	uart1Sendcon.len=len;
	uart1Sendcon.busy=1;
	for(i=0;i<len;i++)
	{
		uart1Sendcon.buf[i]=buff[i];
	}
	SCI0->TXD1 = uart1Sendcon.buf[0];
	INTC_EnableIRQ(ST1_IRQn); /* Enable INTST0 interrupt */
	
	return TRUE;
}
#endif

#if 1
BOOL UartSendFaucetData(INT8U *buff,INT8U len)
{
	INT8U i;

	if(uart2Sendcon.busy==1)
	{
		return FALSE;
	}
	uart2Sendcon.isend=1;
	uart2Sendcon.len=len;
	uart2Sendcon.busy=1;
	for(i=0;i<len;i++)
	{
		uart2Sendcon.buf[i]=buff[i];
	}
	SCI1->TXD2 = uart2Sendcon.buf[0];
	INTC_EnableIRQ(ST2_IRQn); /* Enable INTST0 interrupt */
	
	return TRUE;
}
#endif

#if 1
BOOL UartSendWifiData(INT8U *buff,INT8U len)
{
	INT8U i;

	if(uart0Sendcon.busy==1)
	{
		return FALSE;
	}
	uart0Sendcon.isend=1;
	uart0Sendcon.len=len;
	uart0Sendcon.busy=1;
	for(i=0;i<len;i++)
	{
		uart0Sendcon.buf[i]=buff[i];
	}
	SCI0->TXD0 = uart0Sendcon.buf[0];
	INTC_EnableIRQ(ST0_IRQn); /* Enable INTST0 interrupt */
	
	return TRUE;
}
#endif


#if UART_DEBUG

BOOL UartSendString(CONST INT8S *buff)
{
	//INT8U i=0;
	//INT8U length=strlen((INT8S*)buff);
	
	//for(i=0; i<length; i++)
	{

	}
	return TRUE;
}


void UartDisInfo(const char* pBuf,INT32S num)
{
	#if 0
//	INT8U len;
	char buff[30]={"\0"},pf[6]={"\0"};

	strcat(buff,pBuf);
	//sprintf(pf,"0x%02x",num);//整数转换成字符串	
	sprintf(pf,"%d",num);//整数转换成字符串	
	strcat(buff,pf);
	strcat(buff,"\r\n");

	len = strlen(buff);
	
	//UartSend485Data((INT8U*)buff,len);
	//UartSendGPRSData((INT8U*)buff,len);
#endif
}



#if 0
void Uartprintf(const char* pBuf,INT16U num)	
{
	INT8U buff[6];
	INT8U i=0;
	//INT8U length=strlen((unsigned char *)pBuf);


}
#endif


#if 1
int uart_printf1(const char *fmt,...)
{ 
	int n;
	char sprint_buf[50];
    va_list args; 
//    INT8U i;
	
    va_start(args, fmt); 
    n = vsprintf(sprint_buf, fmt, args); 
    va_end(args);
    
    //write(stdout, sprint_buf, n); 
    //for(i=0;i<n;i++)
    {
	//	UART1_SpiUartWriteTxData((uint32) sprint_buf[i]);
    }

	//UartSendWifiData((INT8U*)sprint_buf,n);
	UartSendFaucetData((INT8U*)sprint_buf,n);

	delayms(200);
    
    return n; 
}
#endif
#endif



