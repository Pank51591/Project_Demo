 

#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./485/bsp_485.h"

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

//	char *pbuf;
	uint16_t len;
	
	//LED_GPIO_Config();	
	
  /*初始化USART1*/
  Debug_USART_Config();
	
	/*初始化485使用的串口，使用中断模式接收*/
	RS485_Config();       //与发送的波特率相匹配   19200
	
	Key_GPIO_Config();
	
	RS485_RX_EN();    //接收使能
	
  while(1)
  {
		
		
//		pbuf = get_rebuff(&len);
		
//		printf("\r\n接收到长度为%d的数据\r\n",len);	
		
//		RS485_DEBUG_ARRAY((uint8_t*)pbuf,len);      //通过串口显示485的数据
		
		
//		clean_rebuff();
//		
//		/*加短暂延时，保证485发送数据完毕*/
//		Delay(0xFFF);
		
		#if 0
		/*按一次按键发送一次数据*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{
			uint16_t i;
			
			RS485_TX_EN();
			
			for(i=0;i<=0xff;i++)
			{
				RS485_SendByte(i);	 //发送数据
			}
			
			/*加短暂延时，保证485发送数据完毕*/
			Delay(0xFFF);
			
			RS485_RX_EN();         //PC2为低的时候，RS485为接收模式
				
			printf("\r\n发送数据成功！\r\n"); //使用调试串口打印调试信息到终端

		}
		else    //没有按键按下，就是接收
		{	  
			pbuf = get_rebuff(&len);
			
			if(len>=256)
			{
				printf("\r\n接收到长度为%d的数据\r\n",len);	
				RS485_DEBUG_ARRAY((uint8_t*)pbuf,len);
				clean_rebuff();
			}
		}
		
		#endif
  }

}

static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/
