/******************** 深圳市轩微胜电子科技有限公司********************
 ********************    www.xws-control.com     ********************
 * 文件名  ：main.c
 * 描述    ：板子上的D2 D3轮流闪烁。         
 * 实验平台：MINI STM32开发板 基于STM32F103VET6
 * 库版本  ：ST3.0.0  																										  
 *********************************************************/	

#include "stm32f10x.h"
#include "led.h"

void Delay(__IO u32 nCount); 

int main(void)
{
	    
 SystemInit();	// 配置系统时钟为72M 	
 LED_GPIO_Config(); //LED 端口初始化 

  while (1)
  {
		LED2( ON );			  //  LED D2点亮
		Delay(0x200000);
		LED2( OFF );		  //  LED D2熄灭

		LED3( ON );			  //  LED D3点亮
		Delay(0x200000);
		LED3( OFF );      	  //  LED D3熄灭
  }
}

void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 



