/****************************************
 * �ļ���  ��exti.c
 * ����    ��I/O���ж�Ӧ�ú�����        
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * Ӳ�����ӣ�  PB1 - key1  PB15 - key2 PA8 - key3
 * ��汾  ��ST3.0.0
*********************************************************/


#include "exti.h"

/*����Ƕ�������жϿ�����NVIC */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);// �������ȼ�����
  
  /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*  ���� PB0 Ϊ���жϿڣ��������ж����ȼ� */
void EXTI_PB1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); //ʹ�ܶ˿ں͸���IOʱ�� 
	
	NVIC_Configuration();

		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1); //ѡ��PB�ڵ�1�ſ�Ϊ�ж���·
  EXTI_InitStructure.EXTI_Line = EXTI_Line1; //�ⲿ�ж���1
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //����Ϊ�ж�����
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}



