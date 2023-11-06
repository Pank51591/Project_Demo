#ifndef MCU_H
#define MUC_H

/////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************************

#define NOP	__NOP()


#if defined(STC)
//------------------------头文件------------------------------------------------------------
//#include <intrins.h>

//------------------------ 串口 -------------------------------------------------------------
#define	UART_1_SENDDATA(ddata)	do{SBUF = ddata;while(!TI);TI = 0;}while(0);
#define	UART_2_SENDDATA(ddata)	do{S2BUF = ddata;while((S2CON&0X02)==0);CLR_TI2();}while(0);
#define	UART_3_SENDDATA(ddata)	do{S3BUF = ddata;while((S3CON&0X02)==0);CLR_TI3();}while(0);
#define	UART_4_SENDDATA(ddata)	do{S4BUF = ddata;while((S4CON&0X02)==0);CLR_TI4();}while(0);
		
#define UARTSENDDATA(com,ddata)	UART_##com##_SENDDATA(ddata)	

//------------------------wdog---------------------------------------------------------------

#define WDT_TimeSet(n)	WDT_CONTR |= n; //分频设置 1(2分屏),2,3,4,5,6,7
#define WDT_Stat()		WDT_CONTR |= 0X20;
#define WDT_Reset(n)	WDT_CONTR = 0x38+n;//WDT_reset(n)
#define SYS_Restart()	IAP_CONTR = 0X20;//系统重启


/////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************************
#elif defined(STM32)

/////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************************
#elif defined(STM8)

/////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************************
#elif defined(M0)


#include <string.h>

#elif defined(MM32F013X)

#define SETGPIO_RESET(x,y)	GPIO_ResetBits(x, y)
#define SETGPIO_SET(x,y)	GPIO_SetBits(x, y)

#define SETGPIO_0(x,y)		GPIO_ResetBits(x, y)
#define SETGPIO_1(x,y)		GPIO_SetBits(x, y)

#define GPIO_Output(x,y,z)	SETGPIO_##z(x,y)

#define GPIO_GetState(x,y)	GPIO_ReadOutputDataBit(x,y)

#elif defined(BAT32G137)

#include "gpio.h"
#include "adc.h"
#include "sci.h"
#include "wdt.h"
#include "flash.h"
#include "intp.h"

#define EXTI_CHANNEL0  0X0001
#define EXTI_CHANNEL1  0X0002
#define EXTI_CHANNEL2  0X0004
#define EXTI_CHANNEL3  0X0008
#define EXTI_CHANNEL4  0X0010
#define EXTI_CHANNEL5  0X0020
#define EXTI_CHANNEL6  0X0040
#define EXTI_CHANNEL7  0X0080
#define EXTI_CHANNEL8  0X0100
#define EXTI_CHANNEL9  0X0200
#define EXTI_CHANNEL10  0X0400
#define EXTI_CHANNEL11  0X0800

#define FlowMeter1_EXTI_CHANNEL	 EXTI_CHANNEL6
#define FlowMeter2_EXTI_CHANNEL	 EXTI_CHANNEL0


#define SETGPIO_RESET(x,y)	PORT_ClrBit(x, y)
#define SETGPIO_SET(x,y)	PORT_SetBit(x, y)

#define SETGPIO_0(x,y)		PORT_ClrBit(x, y)
#define SETGPIO_1(x,y)		PORT_SetBit(x, y)

#define GPIO_Output(x,y,z)	SETGPIO_##z(x,y)

#define GPIO_GetState(x,y)	PORT_GetBit(x,y)


/////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************************
//------------------------debug--------------------------------------------------------------
#elif defined(VC)

#include"stdio.h"
#include <process.h>
#include"time.h"

#define	UARTSENDDATA(com,ddata)	printf("%d",ddata);

#endif




#endif
