#include"config.h"
#include"drvI2C.h"



#define   SCL(x)	GPIO_Output(PORT7,PIN3,x)      //IICʱ�����Ŷ���
#define   SDA(x)	GPIO_Output(PORT7,PIN2,x)      //IIC�������Ŷ���
#define   GetSDA	PORT_GetBit(PORT7, PIN2)



#define SetSDA_input	PORT_Init(PORT7,PIN2,INPUT);////GPIO_SetMode(GPIOA,GPIO_Pin_12,GPIO_Mode_IPU)//GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_IN)	
#define SetSDA_output	PORT_Init(PORT7,PIN2,OUTPUT);////GPIO_SetMode(GPIOA,GPIO_Pin_12,GPIO_Mode_Out_PP)//GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_OUT)


#define	IIC_ADDR   0xA0  //����������IIC�����еĴӵ�ַ                             




 void IIC_Init(void)
{
    SCL(1);                    //����ʱ����
    delayus(8);                //��ʱ
    SDA(1);                    //����������
    delayus(8);                //��ʱ 
}

 
/**************************************
��ʼ�ź�
**************************************/
void IIC_Start(void)
{
 
    SDA(1);                    //����������
    delayus(8);                //��ʱ
    SCL(1);                    //����ʱ����
    delayus(8);                //��ʱ
    SDA(0);                    //�����½���
    delayus(8);                //��ʱ
    SCL(0);
}
 
/**************************************
ֹͣ�ź�
**************************************/
void IIC_Stop(void)
{
 
    SDA(0);                    //����������
    delayus(8);                //��ʱ
    SCL(1);                    //����ʱ����
    delayus(8);                //��ʱ
    SDA(1);                    //����������
    //delayus(5);                //��ʱ
 	//SCL(0);
}
 
/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK(BOOL ack)
{
    SCL(1);                    //����ʱ����
    delayus(8);                //��ʱ

 	if(ack==1)SDA(1);          //дӦ���ź�
	else SDA(0); 
    

    SCL(0);                    //����ʱ����
    delayus(15);                //��ʱ
 
}
 
/**************************************
����Ӧ���ź�
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
��IIC���߷���һ���ֽ�����
**************************************/
void IIC_SendByte(INT8U dat)
{
    signed char i;

    SCL(0);							//����ʱ����
 	delayus(8);					//��ʱ
 	
    for(i=0; i<8; i++)         		//8λ������
    {
        if( (dat<<i)&0x80 )SDA(1);  //SDA = 1;//�ȷ���λ
        else SDA(0);  //SDA = 0;
		delayus(8);				//��ʱ
		SCL(1);						//����ʱ����
		delayus(8);				//��ʱ
		SCL(0);						//����ʱ����
		//delayus(1);				//��ʱ
	}
	SDA(0);
	delayus(8);				//��ʱ
    IIC_RecvACK();
}
 
/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
INT8U IIC_RecvByte(void)
{
    INT8U i;
    INT8U dat = 0;

    SetSDA_input;//	
    
    for(i=0; i<8; i++)     //8λ������
    {
        SCL(0); 			//����ʱ����  
        delayus(8);         //��ʱ
        SCL(1);             //����ʱ����
		dat <<= 1;
		delayus(1);         //��ʱ		
        if(GetSDA) dat |= 0x01;//������ 
         
        delayus(8);         //��ʱ
	}
	SetSDA_output//
	SCL(0); 				//����ʱ���� 
	delayus(20); 
	
    return dat;
}

INT8U I2C_ReadOneByte(INT8U ReadAddr)
{
    INT8U temp = 0;
#if 0
    IIC_Start();     //IIC start
    IIC_SendByte(IIC_ADDR);   //slave address+W:0
	IIC_SendByte(ReadAddr);   //�����������
	
	IIC_Start();
	IIC_SendByte(IIC_ADDR+0x01);//slave address+R:1
	temp = IIC_RecvByte();      //������
	IIC_SendACK(1);                
	IIC_Stop();
#else	
	IIC_Start();
	IIC_SendByte(IIC_ADDR+0x01);//slave address+R:1
	temp = IIC_RecvByte();      //������
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
	static INT16U count=0,waittime=1000;//10��

	IIC_Start();
	IIC_SendByte(IIC_ADDR+0x01);
	temp[0] = IIC_RecvByte();      //������
	IIC_SendACK(0);
	temp[1] = IIC_RecvByte();      //������
	IIC_SendACK(1);	
	IIC_Stop();

	temp[2] = temp[0]+0xA1;
	
	if(temp[1]==temp[2])
	{
		count=0;
		systemseting.uartdisplayError=0;//��ʾͨѶ����
		waittime=12000;//120��
		return temp[0];
	}

	if(++count>waittime)
	{
		count=0;
		systemseting.uartdisplayError=1;//��ʾͨѶ����
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


