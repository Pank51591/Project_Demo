#ifndef __CAN_H
#define	__CAN_H


#include "stm32f10x.h" 
 void CAN_INIT(void);
 void can_tx(u8 BANID,u8 Data);
 void can_rx(void);
 void CAN_NVIC_Configuration(void);
void CAN_GPIO_Config(void);

#endif /* __CAN_H */


