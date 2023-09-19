/****************************************
 * �ļ���  ��main.c
 * ����    ��3��LED�� SysTick �Ŀ����£���500ms��Ƶ����˸��         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * ��汾  ��ST3.0.0 
*********************************************************/
#include "stm32f10x.h"
#include "SysTick.h"
#include "led.h"

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{
	
SystemInit();	// ����ϵͳʱ��Ϊ72M 	
LED_GPIO_Config(); //LED �˿ڳ�ʼ�� 

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();
	
  while (1)
  {
	
    LED1( 0 ); 
	LED2( 0 );
	LED3( 0 );
    Delay_us(50000);    // 50000 * 10us = 500ms
	LED1( 1 );    	
	LED2( 1 );    	
    LED3( 1 );
	Delay_us(50000);
		
  }
}
 






