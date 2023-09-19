/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_led.h"  
#include  "joypad.h"

static void Delay(__IO uint32_t nCount)
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
	uint8_t joykey=0;
	
	LED_GPIO_Config();
	JOYPAD_Init();
	/* USART1 ����ģʽΪ 115200 8-N-1���жϽ��� */
	USARTx_Config();
	printf("��Ϸ�ֱ�\n");
	LED2_ON;
	while(1)
	{
		joykey=JOYPAD_Read();
		if(joykey)
		{
			//printf("joykey:%d\n",joykey);
			if(joykey&0x10)printf("��");
			if(joykey&0x20)printf("��");
			if(joykey&0x40)printf("��");
			if(joykey&0x80)printf("��");
			if(joykey&0x04)printf("ѡ��");
			if(joykey&0x08)printf("��ʼ");
			if(joykey&0x01)printf("A");
			if(joykey&0x02)printf("B");
			printf("\n");
		}
		Delay(0x2ffff);		
	}
}

/*********************************************END OF FILE**********************/
