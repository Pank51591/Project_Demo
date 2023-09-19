/****************************************
 * 文件名  ：main.c
 * 描述    ：给相同两个MINI板下载此程序后，按下一个板子上的按键，可以点亮另一个板子
 *           上对应的LED。两个板子不分主从。         
 * 实验平台：MINI STM32开发板 基于STM32F103VET6
 * 库版本  ：ST3.0.0   																										  
*********************************************************/

#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*按键管脚初始化*/
void KeyInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能外设时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能外设时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_15 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //最高输出速率10MHz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //最高输出速率10MHz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*检测是否有按键按下*/
void  GetKey(void)
{
        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
        {
                Delay(1000000);//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)){ ; }//等待按键释放
                       RS485_SendByte(0X03); 
					   LED1(1);LED2(1);LED3(1);
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
        {
                Delay(1000000);//去抖动//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)){ ; }//等待按键释放                        
                        RS485_SendByte(0X02);
						LED1(1);LED2(1);LED3(1);
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
        {
                 Delay(1000000);//去抖动//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)){ ; }//等待按键释放                        
                        RS485_SendByte(0X01);	
						LED1(1);LED2(1);LED3(1);
                }
        }   

      
}
/*USART3 接收中断配置 */
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
	SystemInit();//配置系统时钟为 72M 
	KeyInit();	//按键管脚初始化
	LED_GPIO_Config(); //LED管脚初始化
	NVIC_Configuration();//USART3 接收中断配置
	USART3_int(); //USART1 配置		

  while (1)
  {	 
    GetKey(); //检测是否有按键按下
  }
}




