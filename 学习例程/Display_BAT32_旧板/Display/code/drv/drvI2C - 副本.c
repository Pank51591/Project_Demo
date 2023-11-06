#include"config.h"
#include"drvI2C.h"



#define   SCL(x)	GPIO_Output(PORT7,PIN3,x)      //IIC时钟引脚定义
#define   SDA(x)	GPIO_Output(PORT7,PIN2,x)      //IIC数据引脚定义
#define   GetSDA	PORT_GetBit(PORT7, PIN2)



#define SetSDA_input	PORT_Init(PORT7,PIN2,INPUT);////GPIO_SetMode(GPIOA,GPIO_Pin_12,GPIO_Mode_IPU)//GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_IN)	
#define SetSDA_output	PORT_Init(PORT7,PIN2,OUTPUT);////GPIO_SetMode(GPIOA,GPIO_Pin_12,GPIO_Mode_Out_PP)//GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_OUT)


#define	IIC_ADDR   0xA0  //定义器件在IIC总线中的从地址                             




 void IIC_Init(void)
{
    SCL(1);                    //拉高时钟线
    delayus(8);                //延时
    SDA(1);                    //拉高数据线
    delayus(8);                //延时 
}

 
/**************************************
起始信号
**************************************/
void IIC_Start(void)
{
 
    SDA(1);                    //拉高数据线
    delayus(8);                //延时
    SCL(1);                    //拉高时钟线
    delayus(8);                //延时
    SDA(0);                    //产生下降沿
    delayus(8);                //延时
    SCL(0);
}
 
/**************************************
停止信号
**************************************/
void IIC_Stop(void)
{
 
    SDA(0);                    //拉低数据线
    delayus(8);                //延时
    SCL(1);                    //拉高时钟线
    delayus(8);                //延时
    SDA(1);                    //产生上升沿
    //delayus(5);                //延时
 	//SCL(0);
}
 
/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK(BOOL ack)
{
    SCL(1);                    //拉高时钟线
    delayus(8);                //延时

 	if(ack==1)SDA(1);          //写应答信号
	else SDA(0); 
    

    SCL(0);                    //拉低时钟线
    delayus(15);                //延时
 
}
 
/**************************************
接收应答信号
**************************************/
#if 0
BOOL IIC_RecvACK(void)
{
 	BOOL ack;
 	INT8U i;

	SCL(1);
	//SDA(1);
	//delayus(5);
	SetSDA_input;
	//delayus(1);
	while((GetSDA)&&(i<255)){i++;delayus(10);}
	SetSDA_output;
	delayus(5);
	//SCL(0);
	//delayus(5);
	SDA(1);
 	
    return ack;
 
}
#else
BOOL IIC_RecvACK(void)
{
 	BOOL ack;
 	INT8U i;

	SCL(1);
	//SDA(1);
	//delayus(5);
	SetSDA_input;
	//delayus(1);
	while((GetSDA)&&(i<255)){i++;delayus(10);}
	SetSDA_output;
	delayus(8);
	//SCL(0);
	//delayus(5);
	//SDA(1);
 	
    return ack;
 
}

#endif
/**************************************
向IIC总线发送一个字节数据
**************************************/
void IIC_SendByte(INT8U dat)
{
    signed char i;

    SCL(0);							//拉低时钟线
 	delayus(8);					//延时
 	
    for(i=0; i<8; i++)         		//8位计数器
    {
        if( (dat<<i)&0x80 )SDA(1);  //SDA = 1;//先发高位
        else SDA(0);  //SDA = 0;
		delayus(8);				//延时
		SCL(1);						//拉高时钟线
		delayus(8);				//延时
		SCL(0);						//拉低时钟线
		//delayus(1);				//延时
	}
	SDA(0);
	delayus(8);				//延时
    IIC_RecvACK();
}
 
/**************************************
从IIC总线接收一个字节数据
**************************************/
#if 0
INT8U IIC_RecvByte(void)
{
    INT8U i;
    INT8U dat = 0;

    SetSDA_input;//	
 
    SCL(1);                 //使能内部上拉,准备读取数据,
    delayus(5);             //延时
    
    for (i=0; i<8; i++)     //8位计数器
    {
        dat <<= 1;
        SCL(0); 			//拉低时钟线  
        delayus(5);         //延时
        SCL(1);             //拉高时钟线
		delayus(5);         //延时
        if(GetSDA) dat |= 0x01;//读数据 
         
        //delayus(5);         //延时
	}
	SetSDA_output//
	SCL(0); 				//拉低时钟线 
	delayus(5); 
	
    return dat;
}
#else
INT8U IIC_RecvByte(void)
{
    INT8U i;
    INT8U dat = 0;

    SetSDA_input;//	
    
    for(i=0; i<8; i++)     //8位计数器
    {
        SCL(0); 			//拉低时钟线  
        delayus(8);         //延时
        SCL(1);             //拉高时钟线
		dat <<= 1;
		delayus(1);         //延时		
        if(GetSDA) dat |= 0x01;//读数据 
         
        delayus(8);         //延时
	}
	SetSDA_output//
	SCL(0); 				//拉低时钟线 
	delayus(20); 
	
    return dat;
}
#endif

INT8U I2C_ReadOneByte(INT8U ReadAddr)
{
    INT8U temp = 0;
#if 0
    IIC_Start();     //IIC start
    IIC_SendByte(IIC_ADDR);   //slave address+W:0
	IIC_SendByte(ReadAddr);   //发送命令代码
	
	IIC_Start();
	IIC_SendByte(IIC_ADDR+0x01);//slave address+R:1
	temp = IIC_RecvByte();      //读数据
	IIC_SendACK(1);                
	IIC_Stop();
#else	
	IIC_Start();
	IIC_SendByte(IIC_ADDR+0x01);//slave address+R:1
	temp = IIC_RecvByte();      //读数据
	IIC_SendACK(1);                
	IIC_Stop();	
#endif
    return (temp);     
} 

void I2C_WriteByte(INT8U addr, INT8U dat)
{
    IIC_Start();
    IIC_SendByte(IIC_ADDR);
    IIC_SendByte(addr);
    IIC_SendByte(dat);
    IIC_Stop();
}

//*********************************************************
//读出BMP085内部数据,连续两个
//*********************************************************
unsigned short Multiple_read(uchar ST_Address)
{
	INT8U msb, lsb;
	unsigned short _data;

	lsb = I2C_ReadOneByte(ST_Address);   
	msb = I2C_ReadOneByte(ST_Address+1);
    
    _data = msb;
	_data <<= 8;
	_data |= lsb;

	
	return _data;
}

long Multiple_ReadThree(unsigned char addr)
{
    unsigned char msb, lsb, xlsb;
    long temp = 0;
    
    msb = I2C_ReadOneByte(addr);
    lsb = I2C_ReadOneByte(addr + 1);
    xlsb = I2C_ReadOneByte(addr + 2);

    temp = (long)(((unsigned long)msb << 12)|((unsigned long)lsb << 4)|((unsigned long)xlsb >> 4));

    return temp;
}


INT8U I2C_ReadKey(void)
{
	INT8U temp[3];

	IIC_Start();
	IIC_SendByte(IIC_ADDR+0x01);//slave address+R:1
	temp[0] = IIC_RecvByte();      //读数据
	IIC_SendACK(1);
	temp[1] = IIC_RecvByte();      //读数据
	IIC_SendACK(0);	
	IIC_Stop();
	
	//temp[0] = I2C_ReadOneByte(IIC_ADDR);
	//temp[1] = I2C_ReadOneByte(IIC_ADDR);

	temp[2] = temp[0]+0xA1;

	UartSendWifiData(temp,3);
	if(temp[1]==temp[2])
	{
		return temp[0];
	}

	return 0;
}


void I2C_SendDisplay(INT8U *pdat,INT8U len)
{
	INT8U sum;
	
	sum=0xA0+pdat[0]+pdat[1];

	
    IIC_Start();
#if 0
    IIC_SendByte(0x55);//IIC_ADDR

	IIC_SendByte(0x55);//pdat[0]
	IIC_SendByte(0x55);//pdat[1]
	IIC_SendByte(0x55);//sum
#else	
    IIC_SendByte(IIC_ADDR);//
	IIC_SendByte(pdat[0]);//
	IIC_SendByte(pdat[1]);//
	IIC_SendByte(sum);//	
#endif	
    IIC_Stop();
}


