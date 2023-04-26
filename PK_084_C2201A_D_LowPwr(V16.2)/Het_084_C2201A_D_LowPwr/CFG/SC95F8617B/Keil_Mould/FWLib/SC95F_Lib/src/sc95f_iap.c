//************************************************************
//  Copyright (c) ��������Ԫ΢�������޹�˾
//	�ļ�����: 		sc95f_iap.h
//	����:					��ԪӦ���Ŷ�
//	ģ�鹦��: 		BTM�̼��⺯��H�ļ�
//  ����������: 2022��3��23��
// 	�汾: 				V1.10003
//  ˵��: 
//*************************************************************
#include "sc95f_iap.h"

#if defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)
#include "IAP_Option_EW.h"
#endif

/**************************************************
*��������:void IAP_DeInit(void)
*��������:IAP��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void IAP_DeInit(void)
{
  IAPKEY = 0X00;
  IAPADL = 0X00;
  IAPADH = 0X00;
  IAPADE = 0X00;
  IAPDAT = 0X00;
  IAPCTL = 0X00;
}

#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)
/**************************************************
*��������:void PhysicsAddrToMCUAddr(unsigned long *IAP_IapAddr)
*��������:�߼���ַתMCU��ַ 
*��ڲ���:
unsigned long*:IAP_IapAddr:��ַ
*���ڲ���:void 
**************************************************/
void PhysicsAddrToMCUAddr(unsigned long *IAP_IapAddr)
{
  if (*IAP_IapAddr >= 0x10000) //�������64K����Ҫ����Bank�Ĵ���ָ��Ŀ���ַ
  {
    if (*IAP_IapAddr < 0x18000)
    {
      ROMBNK = (ROMBNK & 0xCF) | 0x20;
      *IAP_IapAddr = (*IAP_IapAddr - 0x8000);
    }
    else if (*IAP_IapAddr < 0x20000)
    {

      ROMBNK = (ROMBNK & 0xCF) | 0x30;
      *IAP_IapAddr = (*IAP_IapAddr - 0x10000);
    }
  }
  else
  {
    ROMBNK = (ROMBNK & 0xCF) | 0x10;
  }
}

/**************************************************
*��������:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������
*���ڲ���:
uint8_t:�������ֽ�����
**************************************************/
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType)
{
  uint8_t tmpbyte;
  BitStatus tmpbit;
  uint8_t tmpROMBNK;
  uint8_t tmpIAPADE;

  tmpbit = (BitStatus)EA;
  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;

  if (tmpbit != RESET)
  {
    disableInterrupts();
  }

  PhysicsAddrToMCUAddr(&Address);
  IAPADE = IAP_MemType;
  tmpbyte = *((uint8_t code *)Address);

  ROMBNK = tmpROMBNK;
  IAPADE = tmpIAPADE;

  if (tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpbyte;
}

#if defined(SC95F8x3x) || defined(SC95F7x3x)
/**************************************************
*��������:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:void
**************************************************/
void IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                     uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;
  uint8_t tmpROMBNK;
  uint8_t tmpIAPADE;

	/* UID��������д���� */
	if((IAP_MemType == IAP_MEMTYPE_UID))
		return;
	
  tmpbit = (BitStatus)EA;
  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;
  if (tmpbit != RESET)
  {
    disableInterrupts();
  }

  PhysicsAddrToMCUAddr(&Address);
  IAPADE = IAP_MemType;
  IAPDAT = Data;
  IAPADH = (unsigned char)(Address >> 8);
  IAPADL = (unsigned char)(Address);

  IAPKEY = WriteTimeLimit;
  IAPCTL = 0x10;
  IAPCTL |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();

  ROMBNK = tmpROMBNK;
  IAPADE = tmpIAPADE;
  EA = tmpbit;
}

/**************************************************
*��������:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
*��������:IAP��������
*��ڲ���:
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint32_t:IAP_SectorEraseAddress:IAP��������Ŀ���ַ
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
  uint8_t tmpbit;
  uint8_t tmpROMBNK;
  uint8_t tmpIAPADE;
	
	/* UID�������������������� */
	if((IAP_MemType == IAP_MEMTYPE_UID))
		return;

  tmpbit = (BitStatus)EA;
  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;

  if (tmpbit != RESET)
  {
    disableInterrupts();
  }

  PhysicsAddrToMCUAddr(&IAP_SectorEraseAddress);

  IAPADE = IAP_MemType;
  IAPADH = (uint8_t)(IAP_SectorEraseAddress >> 8); //����IAPĿ���ַ��λֵ
  IAPADL = (uint8_t)IAP_SectorEraseAddress;        //����IAPĿ���ַ��λֵ
  IAPKEY = WriteTimeLimit;
  IAPCTL = 0x20;
  IAPCTL |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();

  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;
  if (tmpbit != RESET)
  {
    enableInterrupts();
  }
}

#elif defined (SC95F8x6x) || defined (SC95F7x6x)

/**************************************************
*��������:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:void
**************************************************/
void IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                     uint8_t WriteTimeLimit)
{
	WriteTimeLimit = 0x00;	//�������95ϵ���ͺ�����Ч
  PhysicsAddrToMCUAddr(&Address);
  IAP_ProgramByteOption(Address,Data,IAP_MemType);
}

/**************************************************
*��������:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
*��������:IAP��������
*��ڲ���:
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint32_t:IAP_SectorEraseAddress:IAP��������Ŀ���ַ
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
	WriteTimeLimit = 0x00;	//���ͺ������Ч
  PhysicsAddrToMCUAddr(&IAP_SectorEraseAddress);
  IAP_SectorEraseOption(IAP_SectorEraseAddress,IAP_MemType);
}

#endif

#else
/**************************************************
*��������:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��UID��
*���ڲ���:
uint8_t:�������ֽ�����
**************************************************/
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType)
{
  uint8_t tmpbyte;
  BitStatus tmpbit;
  tmpbit = (BitStatus)EA;

  if (tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;
  tmpbyte = *((uint8_t code *)Address);
  IAPADE = IAP_MEMTYPE_ROM;

  if (tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpbyte;
}

#if defined (SC95F8x1xB) || defined (SC95F7x1xB)
/**************************************************
*��������:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:void
**************************************************/
void IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                     uint8_t WriteTimeLimit)
{
	WriteTimeLimit = 0x00;	//���ͺ������Ч
  IAP_ProgramByteOption(Address,Data,IAP_MemType);
}

/**************************************************
*��������:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
*��������:IAP��������
*��ڲ���:
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint32_t:IAP_SectorEraseAddress:IAP��������Ŀ���ַ
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
	WriteTimeLimit = 0x00;	//���ͺ������Ч
  IAP_SectorEraseOption(IAP_SectorEraseAddress,IAP_MemType);
}
#else
/**************************************************
*��������:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint16_t IAP_SectorEraseAddress)
*��������:IAP��������
*��ڲ���:
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint32_t:IAP_SectorEraseAddress:IAP��������Ŀ���ַ
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
	/* UID�������������������� */
	if((IAP_MemType == IAP_MEMTYPE_UID))
		return;
	
  IAPADE = IAP_MemType;
  IAPADH = (uint8_t)(IAP_SectorEraseAddress >> 8); //����IAPĿ���ַ��λֵ
  IAPADL = (uint8_t)IAP_SectorEraseAddress;        //����IAPĿ���ַ��λֵ
  IAPKEY = WriteTimeLimit;
  IAPCTL = 0x20;
  IAPCTL |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  IAPADE = IAP_MEMTYPE_ROM;
}

/**************************************************
*��������:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                     uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;
	/* UID��������д���� */
	if((IAP_MemType == IAP_MEMTYPE_UID))
		return;

  tmpbit = (BitStatus)EA;
  if (tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;
  IAPDAT = Data;
  IAPADH = (uint8_t)(Address >> 8);
  IAPADL = (uint8_t)Address;
  IAPKEY = WriteTimeLimit;
  IAPCTL = 0x10;
  IAPCTL |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  IAPADE = IAP_MEMTYPE_ROM;

  if (tmpbit != RESET)
  {
    enableInterrupts();
  }
}
#endif

#endif

/**************************************************
*��������:void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
*��������:MCU�����λ��������������ã�����ѡ��ΪAPROM/LDROM
*��ڲ���:
IAP_BTLDType_Ty	peDef:IAP_BTLDType:��λ�����������
*���ڲ���:void
**************************************************/
void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
{
  IAPCTL = (IAPCTL & 0xFB) | IAP_BTLDType;
}

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/