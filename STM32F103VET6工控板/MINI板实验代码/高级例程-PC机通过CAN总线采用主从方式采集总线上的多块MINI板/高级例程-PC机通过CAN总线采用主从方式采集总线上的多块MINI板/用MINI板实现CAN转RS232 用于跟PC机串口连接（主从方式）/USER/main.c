/****************************************
 * 文件名  ：main.c
 * 描述    ：通过CAN总线采用主从方式采集总线上的两个板子        
 
 * 库版本  ：ST3.0.0   																										  
*********************************************************/
#include "stm32f10x.h"
#include "can.h"
#include "led.h"
#include "usart1.h"




int main(void)
{  
  	u8 i=0;
 	SystemInit(); //设置系统时钟为72M   	
 	LED_GPIO_Config();//LED管脚初始化 		
    CAN_GPIO_Config();//CAN管脚初始化
	USART1_Config();//USART1管脚初始化	
	CAN_NVIC_Configuration(); //CAN中断初始化   
	CAN_INIT();//CAN初始化N模块	
    printf("-------------------------------操作说明-------------------------------\r\n");	 
	printf("-------在发送栏输入十六进制”11”,发送出去，可读取ID为0x11板子的采集数据------\r\n");	 
	printf("-------在发送栏输入十六进制“22”,发送出去，可读取ID为0x22板子的采集数据------\r\n");	 
 	while(1)
    {
	  while(UART1GetByte(&i))
        {
          can_tx(i,0x55);
        }      
	   
  	}
}




