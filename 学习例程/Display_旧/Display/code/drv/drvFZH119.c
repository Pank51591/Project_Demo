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
    SCL(1);                    //����ʱ����
    delayus(5);                 //��ʱ
    SDA(1);                    //����������
    delayus(5);                 //��ʱ 
}

 
/**************************************
��ʼ�ź�
**************************************/
void IIC_Start(void)
{
 
    SDA(1);                    //����������
    delayus(5);                 //��ʱ
    SCL(1);                    //����ʱ����
    delayus(5);                 //��ʱ
    SDA(0);                    //�����½���
    delayus(5);                 //��ʱ
    SCL(0);
}
 
/**************************************
ֹͣ�ź�
**************************************/
void IIC_Stop(void)
{
 
    SDA(0);                    //����������
    delayus(5);                 //��ʱ
    SCL(1);                    //����ʱ����
    delayus(5);                 //��ʱ
    SDA(1);                    //����������
    delayus(5);                 //��ʱ
 	SCL(0);
}
 
/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK(BOOL ack)
{
 	if(ack==1)SDA(1);                  //дӦ���ź�
	else SDA(0); 
    
    SCL(1);                    //����ʱ����
    delayus(5);                 //��ʱ
    SCL(0);                    //����ʱ����
    delayus(5);                 //��ʱ
 
}
 
/**************************************
����Ӧ���ź�
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
��IIC���߷���һ���ֽ�����
**************************************/
void IIC_SendByte(INT8U dat)
{
 
    signed char i;

	SDA(0);
    SCL(0);				//����ʱ����
 	delayus(5);				//��ʱ
 	
    for (i=0; i<8; i++)         //8λ������
    {
    	SCL(0);
    	delayus(5);				//��ʱ
        if( (dat)&0x01 ){SDA(1);}  //SDA(1);//�ȷ���λ
        else {SDA(0);}  //SDA(0);
		delayus(5);				//��ʱ
		SCL(1);				//����ʱ����
		delayus(5);				//��ʱ

		dat>>=1;
	}	
    IIC_RecvACK();

    SCL(0);				//����ʱ����
 	delayus(5);				//��ʱ
 	SDA(0);
}


void FZH119AWriteByte(unsigned char *pdat, unsigned char len)
{
	 unsigned char i;

	 IIC_Start();
	 IIC_SendByte(0x40);	//�����������ã���ͨģʽ����ַ�Զ���һ
	 IIC_Stop();

	 IIC_Start();
	 IIC_SendByte(0xc0);	//��ַ�������ã���ʼ��ַ00H

	 
	 for(i=0;i<len;i++)	//����16λ��ʾ����
	 {
	   	IIC_SendByte(pdat[i]);
	 }
	 IIC_Stop();

	 IIC_Start();
	 IIC_SendByte(0x8c);	//��ʾ���ƣ���ʾ������������Ϊ11/16 0X8C
	 IIC_Stop();	
}




