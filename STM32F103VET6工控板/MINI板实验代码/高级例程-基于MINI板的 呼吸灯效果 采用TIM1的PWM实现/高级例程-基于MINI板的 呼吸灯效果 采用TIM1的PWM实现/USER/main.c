/****************************************
 * �ļ���  ��main.c
 * ����    ����ʱ��TIM1����2·PWM������LED,ģ�������Ч�� 
 *       
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * ��汾  ��ST3.0.0
*********************************************************/
#include "stm32f10x.h"
#include "pwm_output.h"


int main(void)
{
  
	SystemInit(); //����ϵͳʱ��Ϊ72M   
	
	TIM1_PWM_Init(); //TIM3 PWM�������ʼ������ʹ��TIM3 PWM���
    
  	pwm_led_out(); //��PWM����LEDģ�������Ч��
}




