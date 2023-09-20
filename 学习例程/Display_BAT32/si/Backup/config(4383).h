#ifndef CONFIG_H
#define CONFIG_H

//**************************************************************************************
//----------------ѡ����--------------------------------------------------------------------
//#define MAIN_Fosc		22118400L	//������ʱ��
//#define MAIN_Fosc		12000000L	//������ʱ��
#define MAIN_Fosc		11059200L	//������ʱ��
//#define MAIN_Fosc		 5529600L	//������ʱ��
//#define MAIN_Fosc		24000000L	//������ʱ��

#define FOSC	MAIN_Fosc


//**************************************************************************************
//---------------����汾��--------------------------------------------------------------
#define SOFT_NUM		"V1.00"
#define SOFT_VERSION	"20201127"
#define SOFT_DATE		"2021.06.03"
//**************************************************************************************
//---------------ѡ��Ƭ������-----------------------------------------------------------

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
//--------------ϵͳ��������---------------------------------------------------------------

#define SYS_QUEUE_NUM	5//ϵͳ��Ϣ���� ��Ϣ����

#define SERIAL_BUFF_NUM	100//2048



//*****************************************************************************************
//--------------ƽ̨ģ������---------------------------------------------------------------

//#define HZ2G//HZ2G HW4G

//**************************************************************************************
//--------------ϵͳ�ļ�����---------------------------------------------------------------

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
//-------------- IO�� ����----------------------------------------------------------------------


//**************************************************************************************
//--------------ѡ����ģ��ͷ------------------------------------------------------------
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
//#pragma message("------����ģʽ-------") 
#define printf	printf
#else
//#pragma message("------����ģʽ-------")


#define printf /\
/printf
#endif


//**************************************************************************************



#endif



