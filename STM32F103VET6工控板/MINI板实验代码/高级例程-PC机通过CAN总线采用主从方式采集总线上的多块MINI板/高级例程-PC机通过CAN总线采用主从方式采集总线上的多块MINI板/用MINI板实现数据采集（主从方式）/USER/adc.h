#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
void ADC1_Init(void);
void filter(void);

#define  N   50              //每通道采50次
#define  M  4               //为4个通道
#endif /* __ADC_H */

