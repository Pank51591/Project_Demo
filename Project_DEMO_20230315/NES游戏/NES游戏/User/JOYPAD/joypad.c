#include  "joypad.h"

//��ʼ���ֱ��ӿ�.	 
void JOYPAD_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(macJOYPAD_CLK_GPIO_CLK|macJOYPAD_LAT_GPIO_CLK|macJOYPAD_DAT_GPIO_CLK, ENABLE);	 //ʹ��PB,PD�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = macJOYPAD_CLK_GPIO_PIN;				 //
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(macJOYPAD_CLK_GPIO_PORT, &GPIO_InitStructure); //��ʼ��GPIO
 	GPIO_SetBits(macJOYPAD_CLK_GPIO_PORT,macJOYPAD_CLK_GPIO_PIN);	//����

 	GPIO_InitStructure.GPIO_Pin = macJOYPAD_LAT_GPIO_PIN;				 //
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(macJOYPAD_LAT_GPIO_PORT, &GPIO_InitStructure); //��ʼ��GPIO
 	GPIO_SetBits(macJOYPAD_LAT_GPIO_PORT,macJOYPAD_LAT_GPIO_PIN);	//����
	
	
 	GPIO_InitStructure.GPIO_Pin  = macJOYPAD_DAT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
 	GPIO_Init(macJOYPAD_DAT_GPIO_PORT, &GPIO_InitStructure); //��ʼ��GPIO
	GPIO_SetBits(macJOYPAD_DAT_GPIO_PORT,macJOYPAD_DAT_GPIO_PIN);	//����

}

//�ֱ��ӳٺ���
//t:Ҫ�ӳٵ�ʱ��
void JOYPAD_Delay(uint16_t t)
{
	while(t--);
}
//��ȡ�ֱ�����ֵ.
//FC�ֱ����������ʽ:
//ÿ��һ������,���һλ����,���˳��:
//A->B->SELECT->START->UP->DOWN->LEFT->RIGHT.
//�ܹ�8λ,������C��ť���ֱ�,����C��ʵ�͵���A+Bͬʱ����.
//������1,�ɿ���0.
//����ֵ:
//[7]:��
//[6]:��
//[5]:��
//[4]:��
//[3]:Start
//[2]:Select
//[1]:B
//[0]:A
uint8_t JOYPAD_Read(void)
{
	__IO uint8_t temp=0;
 	uint8_t t;
	JOYPAD_LAT_HIGH;	//���浱ǰ״̬
 	JOYPAD_Delay(80);
	JOYPAD_LAT_LOW; 
	for(t=0;t<8;t++)
	{
		temp>>=1;	 
		if(macJOYPAD_DAT_READ==0)temp|=0x80;//LOAD֮�󣬾͵õ���һ������
		JOYPAD_CLK_HIGH;			   	//ÿ��һ�����壬�յ�һ������
		JOYPAD_Delay(80);
		JOYPAD_CLK_LOW;	
		JOYPAD_Delay(80); 
	}
	return temp;
}


