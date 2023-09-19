#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
//#include <stdio.h>

void RS485_SendByte(unsigned char SendData);
void USART3_int(void);
#endif /* __USART1_H */
