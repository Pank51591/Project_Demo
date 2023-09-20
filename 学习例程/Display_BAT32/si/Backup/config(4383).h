#ifndef CONFIG_H
#define CONFIG_H

//**************************************************************************************
//----------------选择晶振--------------------------------------------------------------------
//#define MAIN_Fosc		22118400L	//定义主时钟
//#define MAIN_Fosc		12000000L	//定义主时钟
#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟

#define FOSC	MAIN_Fosc


//**************************************************************************************
//---------------软件版本号--------------------------------------------------------------
#define SOFT_NUM		"V1.00"
#define SOFT_VERSION	"20201127"
#define SOFT_DATE		"2021.06.03"
//**************************************************************************************
//---------------选择单片机类型-----------------------------------------------------------

//#include"STC89.h"
//#include"STC15Fxxxx.H"
//#include"ARM_IO.h"
//#include"STC12LE5A60S2.h"
//#include "ht32.h"
//#include "mm32_device.h"
//#include "hal_conf.h"
#include "BAT32G135.h"
#include "userdefine.h"

#define	BAT32G137//MM32F013X//STC   STM32   STM8  VC  M0

//**************************************************************************************
//--------------系统参数配置---------------------------------------------------------------

#define SYS_QUEUE_NUM	5//系统消息队列 消息个数

#define SERIAL_BUFF_NUM	100//2048



//*****************************************************************************************
//--------------平台模块设置---------------------------------------------------------------

//#define HZ2G//HZ2G HW4G

//**************************************************************************************
//--------------系统文件配置---------------------------------------------------------------

#include"typedef.h"
#include"MCU.h"
#include"sys_clock.h"
#include"ioinit.h"


#include"system.h"
#include"window.h"
#include"task.h"

#include"delay.h"

#include <stdlib.h>
//#include"cJSON.h"

//**************************************************************************************
//-------------- IO口 设置----------------------------------------------------------------------


//**************************************************************************************
//--------------选择功能模块头------------------------------------------------------------
#include"string.h"
//#include"drvI2C.h"
#include"drvLCD1602.h"

#include"keyscan.h"

#include"AppUart.h"
#include"appsystem.h"
#include"fifo.h"

//#include "drvFZH119.h"
//#include"drvTDS.h"
//#include"drvADC.h"
//#include"drvValve.h"
#include"modbus.h"
//#include"drvLeak.h"
//#include"appADC.h"
//#include"FactoryMode.h"
//#include"faucet.h"
//#include"Wifi.h"
//#include"Waterflow.h"
#include"DisplayBoard.h"


#include"Windesktop.h"
//#include"winFilterSet.h"
#include"WinOreration.h"
#include"WinService.h"
#include"WinData.h"
#include"WinLEDLevel.h"


#include"savedata.h"

//#include"VoltageADC.h"
#include"FCT.h"

//**************************************************************************************
//-------------------------------------------------------------------------------------------

 
//**************************************************************************************
//-----------------debug set -----------------------------------------------------------

#define 	DEBUG				0
#define		UART_DEBUG			1


#if UART_DEBUG

#include"stdarg.h"
#include<stdio.h>

#define uart_printf uart_printf1

#else
#include<stdio.h>

#define Uartprintf /\
/ Uartprintf

//#define UartSendString /\
/// UartSendString

#define UartDisInfo /\
/ UartDisInfo

#endif



#if DEBUG
//#pragma message("------调试模式-------") 
#define printf	printf
#else
//#pragma message("------正常模式-------")


#define printf /\
/printf
#endif


//**************************************************************************************



#endif



