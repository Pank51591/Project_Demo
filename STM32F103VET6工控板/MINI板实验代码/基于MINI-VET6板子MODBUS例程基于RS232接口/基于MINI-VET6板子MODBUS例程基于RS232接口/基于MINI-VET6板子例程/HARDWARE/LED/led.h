#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED1_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define LED1_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define LED2_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define LED2_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define LED3_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define LED3_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_13)

//按键
#define BUTTON1_READ()      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define BUTTON2_READ()      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define BUTTON3_READ()      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)

void LED_Config(void);//LED控制端口初始化
void Button_Config(void); //按键控制端口初始化
		 				    
#endif
