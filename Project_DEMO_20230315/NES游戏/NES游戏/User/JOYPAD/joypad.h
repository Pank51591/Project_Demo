#ifndef __JOYPAD_H__
#define __JOYPAD_H__	 
 
#include "stm32f10x.h"

//�ֱ���������
#define macJOYPAD_CLK_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define macJOYPAD_CLK_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define macJOYPAD_CLK_GPIO_PIN		  GPIO_Pin_3			          /* ���ӵ�SCLʱ���ߵ�GPIO */

#define macJOYPAD_LAT_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define macJOYPAD_LAT_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define macJOYPAD_LAT_GPIO_PIN		  GPIO_Pin_2			          /* ���ӵ�SCLʱ���ߵ�GPIO */

#define macJOYPAD_DAT_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define macJOYPAD_DAT_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define macJOYPAD_DAT_GPIO_PIN		  GPIO_Pin_8			          /* ���ӵ�SCLʱ���ߵ�GPIO */

#define JOYPAD_CLK_HIGH				GPIO_SetBits(macJOYPAD_CLK_GPIO_PORT,macJOYPAD_CLK_GPIO_PIN)
#define JOYPAD_CLK_LOW			GPIO_ResetBits(macJOYPAD_CLK_GPIO_PORT,macJOYPAD_CLK_GPIO_PIN)

#define JOYPAD_LAT_HIGH				GPIO_SetBits(macJOYPAD_LAT_GPIO_PORT,macJOYPAD_LAT_GPIO_PIN)
#define JOYPAD_LAT_LOW			GPIO_ResetBits(macJOYPAD_LAT_GPIO_PORT,macJOYPAD_LAT_GPIO_PIN)

#define macJOYPAD_DAT_READ	GPIO_ReadInputDataBit(macJOYPAD_DAT_GPIO_PORT,macJOYPAD_DAT_GPIO_PIN)


void JOYPAD_Init(void);			//��ʼ��	
void JOYPAD_Delay(uint16_t t);		//��ʱ
uint8_t JOYPAD_Read(void);			//��ȡ��ֵ	 				    
#endif //end of __JOYPAD_H__

