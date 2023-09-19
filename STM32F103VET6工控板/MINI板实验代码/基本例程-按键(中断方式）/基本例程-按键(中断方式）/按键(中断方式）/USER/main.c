/****************************************
 * 文件名  ：main.c
 * 描述    ：PB1配置为线中断模式，key1按下时，进入线中断处理函数，翻转LED1.
 *           LED1状态取反。         
 * 实验平台：MINI STM32开发板 基于STM32F103VET6
 * 库版本  ：ST3.0.0
*********************************************************/


#include "stm32f10x.h"
#include "led.h"
#include "exti.h"


int main(void)
{ 
 SystemInit();	// 配置系统时钟为72M 	
 LED_GPIO_Config(); //LED 端口初始化
 EXTI_PB1_Config(); //配置PB1的中断端口线

  while(1)   //等待中断                         
  {
  }
}


