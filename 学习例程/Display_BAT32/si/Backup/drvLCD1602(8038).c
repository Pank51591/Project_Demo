#include"config.h"
#include"drvLCD1602.h"


#define RS(x)	GPIO_Output(PORT2,PIN1,x)
#define RW(x)	GPIO_Output(PORT2,PIN2,x)
#define EN(x)	GPIO_Output(PORT2,PIN3,x)
#define DB0(x)	GPIO_Output(PORT14,PIN7,x)
#define DB1(x)	GPIO_Output(PORT1,PIN0,x)
#define DB2(x)	GPIO_Output(PORT1,PIN1,x)
#define DB3(x)	GPIO_Output(PORT1,PIN2,x)
#define DB4(x)	GPIO_Output(PORT1,PIN3,x)
#define DB5(x)	GPIO_Output(PORT1,PIN4,x)
#define DB6(x)	GPIO_Output(PORT1,PIN5,x)
#define DB7(x)	GPIO_Output(PORT1,PIN6,x)




void WriteData(uchar dat)
{
	(dat&0x01)?DB0(1):DB0(0);
	(dat>>1&0x01)?DB1(1):DB1(0);
	(dat>>2&0x01)?DB2(1):DB2(0);
	(dat>>3&0x01)?DB3(1):DB3(0);
	(dat>>4&0x01)?DB4(1):DB4(0);
	(dat>>5&0x01)?DB5(1):DB5(0);
	(dat>>6&0x01)?DB6(1):DB6(0);
	(dat>>7&0x01)?DB7(1):DB7(0);	
}

void LcdWriteCom(uchar com)	  //д������
{
	EN(0);     //ʹ��
	RS(0);	   //ѡ��������
	RW(0);	   //ѡ��д��
	
	WriteData(com);     //�������P0~P7
	delayms(1);		//�ȴ������ȶ�

	EN(1);	        //д��ʱ��
	delayms(5);	  //����ʱ��
	EN(0);
}


void LcdWriteData(uchar dat)			//д������
{
	EN(0);	//ʹ������
	RS(1);	//ѡ����������
	RW(0);	//ѡ��д��

	WriteData(dat); //д������
	delayms(1);

	EN(1);   //д��ʱ��
	delayms(5);   //����ʱ��
	EN(0);
}


void LcdInit(void)						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ  ��������ָ�� 
	LcdWriteCom(0x0c);  //����ʾ����ʾ���  ��ʾ���ؿ���ָ�� 
	LcdWriteCom(0x06);  //дһ��ָ���1  ģʽ����ָ�� 
	LcdWriteCom(0x01);  //����  ����ָ�� 
	LcdWriteCom(0x80);  //��������ָ����� 0x00+0x80 = 0x80
}





void LcdWriteStrimg(uchar page,INT8U col,INT8S *str)
{
	INT16U i,len;

	len=strlen(str);

	LcdWriteCom(0x80);
	
	for(i=0;i<=len;i++)
	{
		LcdWriteData(str[i]);
	}
}




