 /*********************************************
 *  说明：这个代码里面的串口3可以接收，但是现在的问题是用串口工具的话，好像不能接收485转成串口的信号。
 *
 *
 *
 **********************************************/

#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./485/bsp_485.h"
#include "bsp_SysTick.h"

#define Receive_Size 150
#define Send_Size  150
uint8_t  Flag_Receive;
volatile u16 Uart3MaxRxdByte;
static void Delay(__IO u32 nCount); 
uint8_t UART_Receive_Buffer[Receive_Size];
uint8_t UART_Send_Buffer[Send_Size];



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{ 

  // char *pbuf;
  //	uint16_t len;
	
	//LED_GPIO_Config();	
	
  /*初始化USART1*/
  Debug_USART_Config();
	
	/*初始化485使用的串口，使用中断模式接收*/
	RS485_Config();       //与发送的波特率相匹配   19200
	
	Key_GPIO_Config();
	
	RS485_RX_EN();    //接收使能
	
  while(1)
  {
		SysTick_Delay_Ms( 1000 );
		
		#if 1
		/*按一次按键发送一次数据*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{
			uint16_t i;
			
			RS485_TX_EN();
			
			for(i=0;i<=9;i++)
			{
				RS485_SendByte(i);	 //发送数据
			}
			
			/*加短暂延时，保证485发送数据完毕*/
			Delay(0xFFF);
			
			RS485_RX_EN();         //PC2为低的时候，RS485为接收模式
			

		}
		else    //没有按键按下
		{	 
			/* 将串口3接收到的数据用串口1发送出去 */
			usart1_send_data();
		}
		
		#endif
  }

}

static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/
