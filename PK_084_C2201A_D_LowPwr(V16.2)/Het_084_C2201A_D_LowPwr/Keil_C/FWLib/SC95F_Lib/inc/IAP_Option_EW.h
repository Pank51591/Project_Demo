//************************************************************
//  Copyright (c) 深圳市赛元微电子有限公司
//	文件名称	: IAP_Option_EW.h
//	作者		:
//	模块功能	: IAP固件库函数头文件
//	局部函数列表:
//  最后更正日期: 2022/1/6
// 	版本		: V1.0
//  说明        ：该文件仅适用于SC95FXX6X系列芯片
//*************************************************************


#ifndef _IAP_OPTION_EW_H_
#define	_IAP_OPTION_EW_H_


#define APROM 	0X00
#define UID		0X01
#define	EEPROM	0X02
#define	LDROM	0X03


/**************************************************
*函数名称：void IAP_ProgramByteOption(unsigned int Add,unsigned char Data,unsigned char Iapade)
*函数功能：单Byte写入
*入口参数：Add ：需要擦除的地址(0X00~0XFFFF（mcu逻辑地址），超过64K需要设置DATABNK,并将FLASH物理地址换算成MCU逻辑地址再填入)，
*          Data：要写入的Byte
*          Iapade:操作对象 APROM为00，EEPROM为02
*出口参数：void
**************************************************/
void IAP_ProgramByteOption(unsigned int Add,unsigned char Data,unsigned char Iapade);

/**************************************************
*函数名称：void IAP_SectorEraseOption(unsigned int Add,unsigned char Iapade)
*函数功能：扇区擦除
*入口参数：Add ：需要擦除的地址(0X00~0XFFFF（mcu逻辑地址），超过64K需要设置DATABNK,并将FLASH物理地址换算成MCU逻辑地址再填入)，
*          Iapade:操作对象 APROM为00，EEPROM为02
*出口参数：void
**************************************************/
void IAP_SectorEraseOption(unsigned int Add,unsigned char Iapade);

#endif