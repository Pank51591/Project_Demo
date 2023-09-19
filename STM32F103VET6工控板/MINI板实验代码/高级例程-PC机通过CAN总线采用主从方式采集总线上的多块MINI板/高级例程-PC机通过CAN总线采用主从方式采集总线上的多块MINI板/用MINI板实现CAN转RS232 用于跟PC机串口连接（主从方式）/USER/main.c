/****************************************
 * �ļ���  ��main.c
 * ����    ��ͨ��CAN���߲������ӷ�ʽ�ɼ������ϵ���������        
 
 * ��汾  ��ST3.0.0   																										  
*********************************************************/
#include "stm32f10x.h"
#include "can.h"
#include "led.h"
#include "usart1.h"




int main(void)
{  
  	u8 i=0;
 	SystemInit(); //����ϵͳʱ��Ϊ72M   	
 	LED_GPIO_Config();//LED�ܽų�ʼ�� 		
    CAN_GPIO_Config();//CAN�ܽų�ʼ��
	USART1_Config();//USART1�ܽų�ʼ��	
	CAN_NVIC_Configuration(); //CAN�жϳ�ʼ��   
	CAN_INIT();//CAN��ʼ��Nģ��	
    printf("-------------------------------����˵��-------------------------------\r\n");	 
	printf("-------�ڷ���������ʮ�����ơ�11��,���ͳ�ȥ���ɶ�ȡIDΪ0x11���ӵĲɼ�����------\r\n");	 
	printf("-------�ڷ���������ʮ�����ơ�22��,���ͳ�ȥ���ɶ�ȡIDΪ0x22���ӵĲɼ�����------\r\n");	 
 	while(1)
    {
	  while(UART1GetByte(&i))
        {
          can_tx(i,0x55);
        }      
	   
  	}
}




