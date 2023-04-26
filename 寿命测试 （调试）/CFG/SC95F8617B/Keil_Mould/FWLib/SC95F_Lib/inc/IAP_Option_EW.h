//************************************************************
//  Copyright (c) ��������Ԫ΢�������޹�˾
//	�ļ�����	: IAP_Option_EW.h
//	����		:
//	ģ�鹦��	: IAP�̼��⺯��ͷ�ļ�
//	�ֲ������б�:
//  ����������: 2022/1/6
// 	�汾		: V1.0
//  ˵��        �����ļ���������SC95FXX6Xϵ��оƬ
//*************************************************************


#ifndef _IAP_OPTION_EW_H_
#define	_IAP_OPTION_EW_H_


#define APROM 	0X00
#define UID		0X01
#define	EEPROM	0X02
#define	LDROM	0X03


/**************************************************
*�������ƣ�void IAP_ProgramByteOption(unsigned int Add,unsigned char Data,unsigned char Iapade)
*�������ܣ���Byteд��
*��ڲ�����Add ����Ҫ�����ĵ�ַ(0X00~0XFFFF��mcu�߼���ַ��������64K��Ҫ����DATABNK,����FLASH�����ַ�����MCU�߼���ַ������)��
*          Data��Ҫд���Byte
*          Iapade:�������� APROMΪ00��EEPROMΪ02
*���ڲ�����void
**************************************************/
void IAP_ProgramByteOption(unsigned int Add,unsigned char Data,unsigned char Iapade);

/**************************************************
*�������ƣ�void IAP_SectorEraseOption(unsigned int Add,unsigned char Iapade)
*�������ܣ���������
*��ڲ�����Add ����Ҫ�����ĵ�ַ(0X00~0XFFFF��mcu�߼���ַ��������64K��Ҫ����DATABNK,����FLASH�����ַ�����MCU�߼���ַ������)��
*          Iapade:�������� APROMΪ00��EEPROMΪ02
*���ڲ�����void
**************************************************/
void IAP_SectorEraseOption(unsigned int Add,unsigned char Iapade);

#endif