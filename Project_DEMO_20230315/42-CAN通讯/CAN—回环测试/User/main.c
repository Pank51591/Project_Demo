

#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"


__IO uint32_t flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值
CanTxMsg TxMessage;			     //发送缓冲区
CanRxMsg RxMessage;				   //接收缓冲区


/// 不精确的延时
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	LED_GPIO_Config();
	
  /*初始化USART1*/
  Debug_USART_Config();     //115200
	
	/*初始化按键*/
	Key_GPIO_Config();
 
	/*初始化can,在中断接收CAN数据包*/
	CAN_Config();

	printf("\r\nCAN回环测试\r\n");	
	
  while(1)
	{
		/*按一次按键发送一次数据*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{
			LED_BLUE;
			CAN_SetMsg(&TxMessage);	       //CAN通信报文内容设置,设置一个数据内容为0-7的数据包 
			CAN_Transmit(CANx, &TxMessage);		 	 //启动传输
			can_delay(10000);        //等待发送完毕，可使用CAN_TransmitStatus查看状态	
			LED_GREEN;
			
			printf("\r\n 扩展ID号ExtId：0x%x \r\n",TxMessage.ExtId);        //
			CAN_DEBUG_ARRAY(TxMessage.Data,8);         //按一定的格式输出
		}
		if(flag==1)
		{		
			LED_GREEN;
			printf("\r\nCAN接收到数据：\r\n");	
			CAN_DEBUG_ARRAY(RxMessage.Data,8); 		
			flag=0;
		}
	
	
	}
}

