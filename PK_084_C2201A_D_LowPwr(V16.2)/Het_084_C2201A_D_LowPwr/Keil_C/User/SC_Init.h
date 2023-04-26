//************************************************************
//  Copyright (c)
//	FileName	: SC_Init.h
//	Function	: Contains the MCU initialization function and its H file
//  Instructions        :  
//*************************************************************

#ifndef _SC_INIT_H_
#define _SC_INIT_H_

#if defined (SC95F8x1x) || defined (SC95F7x1x) || defined (SC95F8x2x)  || defined (SC95F7x2x)  || defined (SC95F8x3x)  || defined (SC95F7x3x) \
 || defined (SC95F8x6x)  || defined (SC95F7x6x)  || defined (SC95F8x1xB)  || defined (SC95F7x1xB)  
#include "sc95f_conf.h"
#else
#include "sc92f_conf.h"
#endif

void SC_Init(void);
void SC_OPTION_Init(void);
void SC_GPIO_Init(void);
void SC_GPIO_LowOutput(void);
void SC_TIM0_Init(void);
void SC_TIM1_Init(void);
void SC_PWM0_Init(void);
void SC_INT_Init(void);
void SC_ADC_Init(void);
void SC_BTM_Init(void);
void SC_WDT_Init(void);
void SC_PWM2_Init(void);
void SC_PWM3_Init(void);
void Clr_IO(void);
void SC_EXtern_Init(void);
void Clr_AllFlag(void);
void SC_JP1(void);
#endif

/***********************user_code_area*********************/
/*<UserCodeStart>*/
/*<UserCodeEnd>*/
/**********************.user_code_area.********************/
