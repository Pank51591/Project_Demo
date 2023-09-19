/****************************************
 * �ļ���  ��main.c
 * ����    ������ͬ����MINI�����ش˳���󣬰���һ�������ϵİ��������Ե�����һ������
 *           �϶�Ӧ��LED���������Ӳ������ӡ�         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * ��汾  ��ST3.0.0   																										  
*********************************************************/

#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*�����ܽų�ʼ��*/
void KeyInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ������ʱ��
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ������ʱ��

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_15 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //����������10MHz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //����������10MHz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
        GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*����Ƿ��а�������*/
void  GetKey(void)
{
        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
        {
                Delay(1000000);//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)){ ; }//�ȴ������ͷ�
                       RS485_SendByte(0X03); 
					   LED1(1);LED2(1);LED3(1);
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
        {
                Delay(1000000);//ȥ����//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)){ ; }//�ȴ������ͷ�                        
                        RS485_SendByte(0X02);
						LED1(1);LED2(1);LED3(1);
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
        {
                 Delay(1000000);//ȥ����//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)){ ; }//�ȴ������ͷ�                        
                        RS485_SendByte(0X01);	
						LED1(1);LED2(1);LED3(1);
                }
        }   

      
}
/*USART3 �����ж����� */
void NVIC_Configuration(void)
{    
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
 
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  
}


int main(void)
{  	
	SystemInit();//����ϵͳʱ��Ϊ 72M 
	KeyInit();	//�����ܽų�ʼ��
	LED_GPIO_Config(); //LED�ܽų�ʼ��
	NVIC_Configuration();//USART3 �����ж�����
	USART3_int(); //USART1 ����		

  while (1)
  {	 
    GetKey(); //����Ƿ��а�������
  }
}




