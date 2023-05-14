

#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"


__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
CanTxMsg TxMessage;			     //���ͻ�����
CanRxMsg RxMessage;				   //���ջ�����


/// ����ȷ����ʱ
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	LED_GPIO_Config();
	
  /*��ʼ��USART1*/
  Debug_USART_Config();     //115200
	
	/*��ʼ������*/
	Key_GPIO_Config();
 
	/*��ʼ��can,���жϽ���CAN���ݰ�*/
	CAN_Config();

	printf("\r\nCAN�ػ�����\r\n");	
	
  while(1)
	{
		/*��һ�ΰ�������һ������*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{
			LED_BLUE;
			CAN_SetMsg(&TxMessage);	       //CANͨ�ű�����������,����һ����������Ϊ0-7�����ݰ� 
			CAN_Transmit(CANx, &TxMessage);		 	 //��������
			can_delay(10000);        //�ȴ�������ϣ���ʹ��CAN_TransmitStatus�鿴״̬	
			LED_GREEN;
			
			printf("\r\n ��չID��ExtId��0x%x \r\n",TxMessage.ExtId);        //
			CAN_DEBUG_ARRAY(TxMessage.Data,8);         //��һ���ĸ�ʽ���
		}
		if(flag==1)
		{		
			LED_GREEN;
			printf("\r\nCAN���յ����ݣ�\r\n");	
			CAN_DEBUG_ARRAY(RxMessage.Data,8); 		
			flag=0;
		}
	
	
	}
}

