/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_key.h" 

/// ����ȷ����ʱ
static void Key_Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڣ�PA����ʱ��*/
	RCC_APB2PeriphClockCmd(macKEY1_GPIO_CLK|macKEY2_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = macKEY1_GPIO_PIN; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	
	GPIO_Init(macKEY1_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = macKEY2_GPIO_PIN; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	
	GPIO_Init(macKEY2_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief   ����Ƿ��а�������
  * @param   ����Ķ˿ںͶ˿�λ
  *		@arg GPIOx: x�����ǣ�A...G�� 
  *		@arg GPIO_PIN ������GPIO_PIN_x��x������1...16��
  *   @arg Down_state:��������ʱ�ĵ�ƽ��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ
  * @retval  ������״̬
  *		@arg KEY_ON:��������
  *		@arg KEY_OFF:����û����
  */
uint8_t Key1_Scan(void)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(macKEY1_GPIO_PORT,macKEY1_GPIO_PIN) == 1 ) 
	{	   
		/*��ʱ����*/
		Key_Delay(5000);		
		if(GPIO_ReadInputDataBit(macKEY1_GPIO_PORT,macKEY1_GPIO_PIN) == 1 )  
		{	 
			/*�ȴ������ͷ� */
			while(GPIO_ReadInputDataBit(macKEY1_GPIO_PORT,macKEY1_GPIO_PIN) == 1);   
			return 	KEY_ON;	 
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}

uint8_t Key2_Scan(void)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(macKEY2_GPIO_PORT,macKEY2_GPIO_PIN) == 1 ) 
	{	   
		/*��ʱ����*/
		Key_Delay(5000);		
		if(GPIO_ReadInputDataBit(macKEY2_GPIO_PORT,macKEY2_GPIO_PIN) == 1 )  
		{	 
			/*�ȴ������ͷ� */
			while(GPIO_ReadInputDataBit(macKEY2_GPIO_PORT,macKEY2_GPIO_PIN) == 1);   
			return 	KEY_ON;	 
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}
/*********************************************END OF FILE**********************/
