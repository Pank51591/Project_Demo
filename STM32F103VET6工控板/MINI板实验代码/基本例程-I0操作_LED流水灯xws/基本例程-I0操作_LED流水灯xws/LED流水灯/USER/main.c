/******************** ��������΢ʤ���ӿƼ����޹�˾********************
 ********************    www.xws-control.com     ********************
 * �ļ���  ��main.c
 * ����    �������ϵ�D2 D3������˸��         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * ��汾  ��ST3.0.0  																										  
 *********************************************************/	

#include "stm32f10x.h"
#include "led.h"

void Delay(__IO u32 nCount); 

int main(void)
{
	    
 SystemInit();	// ����ϵͳʱ��Ϊ72M 	
 LED_GPIO_Config(); //LED �˿ڳ�ʼ�� 

  while (1)
  {
		LED2( ON );			  //  LED D2����
		Delay(0x200000);
		LED2( OFF );		  //  LED D2Ϩ��

		LED3( ON );			  //  LED D3����
		Delay(0x200000);
		LED3( OFF );      	  //  LED D3Ϩ��
  }
}

void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 



