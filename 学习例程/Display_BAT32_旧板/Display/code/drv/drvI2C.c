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


INT8U I2C_ReadKey(void)
{
	INT8U temp[3];
	static INT16U count=0,waittime=1000;//10秒

	IIC_Start();
	IIC_SendByte(IIC_ADDR+0x01);
	temp[0] = IIC_RecvByte();      //读数据
	IIC_SendACK(0);
	temp[1] = IIC_RecvByte();      //读数据
	IIC_SendACK(1);	
	IIC_Stop();

	temp[2] = temp[0]+0xA1;
	
	if(temp[1]==temp[2])
	{
		count=0;
		systemseting.uartdisplayError=0;//显示通讯正常
		waittime=12000;//120秒
		return temp[0];
	}

	if(++count>waittime)
	{
		count=0;
		systemseting.uartdisplayError=1;//显示通讯错误
	}

	return 0;
}


void I2C_SendDisplay(INT8U *pdat,INT8U len)
{
	INT8U sum;
	
	sum=0xA0+pdat[0]+pdat[1];

    IIC_Start();	
    IIC_SendByte(IIC_ADDR);//
	IIC_SendByte(pdat[0]);//
	IIC_SendByte(pdat[1]);//
	IIC_SendByte(sum);//		
    IIC_Stop();
}


