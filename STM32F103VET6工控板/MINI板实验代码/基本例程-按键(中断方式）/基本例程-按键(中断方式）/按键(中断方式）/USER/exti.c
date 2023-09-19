/****************************************
 * 文件名  ：exti.c
 * 描述    ：I/O线中断应用函数库        
 * 实验平台：MINI STM32开发板 基于STM32F103VET6
 * 硬件连接：  PB1 - key1  PB15 - key2 PA8 - key3
 * 库版本  ：ST3.0.0
*********************************************************/


#include "exti.h"

/*配置嵌套向量中断控制器NVIC */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);// 设置优先级分组
  
  /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*  配置 PB0 为线中断口，并设置中断优先级 */
void EXTI_PB1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); //使能端口和复用IO时钟 
	
	NVIC_Configuration();

		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // 上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1); //选择PB口的1号口为中断线路
  EXTI_InitStructure.EXTI_Line = EXTI_Line1; //外部中断线1
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //设置为中断请求
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}



