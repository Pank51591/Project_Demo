#include"config.h"
#include"drvFZH119.h"


#define SDA(x)	GPIO_Output(GPIOA,GPIO_Pin_12,x)
#define SCL(x)	GPIO_Output(GPIOA,GPIO_Pin_11,x)
#define GetSDA	GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_12)


#define SetSDA_input	//GPIO_SetMode(GPIOA,GPIO_Pin_12,GPIO_Mode_IPU)//GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_IN)	
#define SetSDA_output	//GPIO_SetMode(GPIOA,GPIO_Pin_12,GPIO_Mode_Out_PP)//GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_OUT)


#define CLR_WDT	FeedWDT()


 static void delayus(unsigned int q)
 {
	 unsigned int i,j;
	 for(i=0;i<q;i++)
	 {
		 for(j=0;j<100;j++);
		 CLR_WDT;
	 }
 }


 void IIC_Init(void)
{
    SCL(1);                    //拉高时钟线
    delayus(5);                 //延时
    SDA(1);                    //拉高数据线
    delayus(5);                 //延时 
}

 
/**************************************
起始信号
**************************************/
void IIC_Start(void)
{
 
    SDA(1);                    //拉高数据线
    delayus(5);                 //延时
    SCL(1);                    //拉高时钟线
    delayus(5);                 //延时
    SDA(0);                    //产生下降沿
    delayus(5);                 //延时
    SCL(0);
}
 
/**************************************
停止信号
**************************************/
void IIC_Stop(void)
{
 
    SDA(0);                    //拉低数据线
    delayus(5);                 //延时
    SCL(1);                    //拉高时钟线
    delayus(5);                 //延时
    SDA(1);                    //产生上升沿
    delayus(5);                 //延时
 	SCL(0);
}
 
/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK(BOOL ack)
{
 	if(ack==1)SDA(1);                  //写应答信号
	else SDA(0); 
    
    SCL(1);                    //拉高时钟线
    delayus(5);                 //延时
    SCL(0);                    //拉低时钟线
    delayus(5);                 //延时
 
}
 
/**************************************
接收应答信号
**************************************/
BOOL IIC_RecvACK(void)
{
 	BOOL ack;
 	INT8U i;

	SCL(1);
	SDA(1);
	delayus(5);
	SetSDA_input;
	delayus(1);
	while((GetSDA)&&(i<255)){i++;delayus(10);}
	SetSDA_output;
	delayus(1);
	SCL(0);
	delayus(5);
 
    return ack;
 
}
 
/**************************************
向IIC总线发送一个字节数据
**************************************/
void IIC_SendByte(INT8U dat)
{
 
    signed char i;

	SDA(0);
    SCL(0);				//拉低时钟线
 	delayus(5);				//延时
 	
    for (i=0; i<8; i++)         //8位计数器
    {
    	SCL(0);
    	delayus(5);				//延时
        if( (dat)&0x01 ){SDA(1);}  //SDA(1);//先发低位
        else {SDA(0);}  //SDA(0);
		delayus(5);				//延时
		SCL(1);				//拉高时钟线
		delayus(5);				//延时

		dat>>=1;
	}	
    IIC_RecvACK();

    SCL(0);				//拉低时钟线
 	delayus(5);				//延时
 	SDA(0);
}


void FZH119AWriteByte(unsigned char *pdat, unsigned char len)
{
	 unsigned char i;

	 IIC_Start();
	 IIC_SendByte(0x40);	//数据命令设置：普通模式，地址自动加一
	 IIC_Stop();

	 IIC_Start();
	 IIC_SendByte(0xc0);	//地址命令设置：初始地址00H

	 
	 for(i=0;i<len;i++)	//发送16位显示数据
	 {
	   	IIC_SendByte(pdat[i]);
	 }
	 IIC_Stop();

	 IIC_Start();
	 IIC_SendByte(0x8c);	//显示控制：显示开，脉冲宽度设为11/16 0X8C
	 IIC_Stop();	
}




