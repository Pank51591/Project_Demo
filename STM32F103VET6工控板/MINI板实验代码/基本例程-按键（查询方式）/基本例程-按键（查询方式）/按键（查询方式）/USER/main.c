/****************************************
 * �ļ���  ��main.c
 * ����    ������KEY1��KEY2��KEY3���ֱ�תLED1�� LED2 ��LED3�����ò�ѯ��ʽ��         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * ��汾  ��ST3.0.0
*********************************************************/ 

#include "stm32f10x.h"
#include "led.h"
#include "key.h"  


int main(void)
{   
  SystemInit();	// ����ϵͳʱ��Ϊ72M 	
  LED_GPIO_Config(); //LED �˿ڳ�ʼ��   	
  Key_GPIO_Config();//�����˿ڳ�ʼ��


  while(1)                            
  {	   
		if( Key_Scan(GPIOB,GPIO_Pin_1) == KEY_ON  )	 //�ж�KEY1�Ƿ���
		{			
			 GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_14))));//LED1��ת
		} 
		
		if( Key_Scan(GPIOB,GPIO_Pin_15) == KEY_ON  ) //�ж�KEY2�Ƿ���
		{			
			 GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12))));//LED2��ת
		} 
		
		if( Key_Scan(GPIOA,GPIO_Pin_8) == KEY_ON  )	 //�ж�KEY3�Ƿ���
		{			
			 GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13))));//LED3��ת
		}     
  }
}


