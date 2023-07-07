 

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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{ 

//	char *pbuf;
	uint16_t len;
	
	//LED_GPIO_Config();	
	
  /*��ʼ��USART1*/
  Debug_USART_Config();
	
	/*��ʼ��485ʹ�õĴ��ڣ�ʹ���ж�ģʽ����*/
	RS485_Config();       //�뷢�͵Ĳ�������ƥ��   19200
	
	Key_GPIO_Config();
	
	RS485_RX_EN();    //����ʹ��
	
  while(1)
  {
		
		
//		pbuf = get_rebuff(&len);
		
//		printf("\r\n���յ�����Ϊ%d������\r\n",len);	
		
//		RS485_DEBUG_ARRAY((uint8_t*)pbuf,len);      //ͨ��������ʾ485������
		
		
//		clean_rebuff();
//		
//		/*�Ӷ�����ʱ����֤485�����������*/
//		Delay(0xFFF);
		
		#if 0
		/*��һ�ΰ�������һ������*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{
			uint16_t i;
			
			RS485_TX_EN();
			
			for(i=0;i<=0xff;i++)
			{
				RS485_SendByte(i);	 //��������
			}
			
			/*�Ӷ�����ʱ����֤485�����������*/
			Delay(0xFFF);
			
			RS485_RX_EN();         //PC2Ϊ�͵�ʱ��RS485Ϊ����ģʽ
				
			printf("\r\n�������ݳɹ���\r\n"); //ʹ�õ��Դ��ڴ�ӡ������Ϣ���ն�

		}
		else    //û�а������£����ǽ���
		{	  
			pbuf = get_rebuff(&len);
			
			if(len>=256)
			{
				printf("\r\n���յ�����Ϊ%d������\r\n",len);	
				RS485_DEBUG_ARRAY((uint8_t*)pbuf,len);
				clean_rebuff();
			}
		}
		
		#endif
  }

}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/
