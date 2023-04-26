#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files
#include "SC_it.h"
#include "..\Drivers\SCDriver_List.h"
#include "HeadFiles\SysFunVarDefine.h"

#include "IapOperation.h"
 
#include "stdlib.h"
#include "SC_System.h"

 unsigned char Readbuff[12]={0,0,0,0,0,0,0,0,0,0,0};
 unsigned char gcRFWorkChennel;
 unsigned int  giRandVlaue1;
 unsigned char gcRandValue;	
 uint8_t RadioFREQ[10];

 
/**************************************************
*函数名称：unsigned char IAP_Read(unsigned long Add,unsigned char ADER)
*函数功能：单Byte读取
*入口参数：Add ：需要擦除的地址(0X00~0X1FFFF（FLASH物理地址）
*         Data：要写入的Byte，ADER:操作对象 APROM为00，EEPROM为02
*出口参数：void
**************************************************/
unsigned char IAP_Read(unsigned long Add,unsigned char Iapade)
{
	unsigned char xdata IAP_IapData;
	unsigned char code *point = 0;
	//保存IAPADE、EA
	unsigned char tempADER = IAPADE;
	unsigned char tempEA = EA;

	EA = 0; //关闭中断

	IAPADE = Iapade;  
	IAP_IapData = *(point+Add);
    
    //恢复IAPADE、EA，避免MOVC位置出错
	IAPADE = tempADER;    
	EA = tempEA;
	return IAP_IapData;
	
}


/**************************************************
*函数名称：void IAP_Write_NByte(unsigned long Add,unsigned char ADER)
*函数功能：写N个Byte
*入口参数：Sadd 写入的起始地址,Eadd 写入的结束地址，ADER:操作对象 APROM为00，EEPROM为02
*出口参数：void
**************************************************/
void IAP_Write_NByte(unsigned long Sadd,unsigned long Eadd, unsigned char TBuff[],unsigned char Iapade)
{
	unsigned char i = 0;
	
	for(; Sadd < Eadd; Sadd ++)
	{
		
		IAP_ProgramByteOption(Sadd,TBuff[i], Iapade);
		
		i++;
		
	}

}

/**************************************************
*函数名称：void IAP_Write_NByte(unsigned long Add,unsigned char ADER)
*函数功能：写N个Byte
*入口参数：Sadd 读取的起始地址,Eadd 读取的结束地址，ADER:操作对象 APROM为00，EEPROM为02
*出口参数：void
**************************************************/
void IAP_Read_NByte(unsigned long Sadd,unsigned long Eadd,unsigned char Iapade)
{
  
	unsigned char i = 0;
	
	for(; Sadd < Eadd; Sadd ++)
	{
		 Readbuff[i]=IAP_Read(Sadd,Iapade);

		  i++;
	}
 
}

void SR_EEPROM_Init(void)
{

	IAP_Read_NByte(0,10,EEPROM);   			 // 18
	
	if (Readbuff[0] != 0x55)     //首地址写55
	{
	  Readbuff[0] = 0x55;
		Readbuff[1] = 0;
		Readbuff[2] = 0;	
		
		Readbuff[3] = 0;
		
		Readbuff[4] = 0;
		Readbuff[5] = 0;
		

		IAP_SectorEraseOption(0x0,EEPROM);
		
	  IAP_Write_NByte(0,10,Readbuff,EEPROM);		      //写数据

		RadioFREQ[0] = 0;
		RadioFREQ[1] = 0;
		RadioFREQ[2] = 0;
		RadioFREQ[3] = 0;
		RadioFREQ[4] = 0;
		RadioFREQ[5] = 0;
		
	}
	else
	{

		RadioFREQ[0] = Readbuff[1];
	
		RadioFREQ[1] = Readbuff[2];	
		
		RadioFREQ[2] = Readbuff[3];
		
		RadioFREQ[3] = Readbuff[4];
		
		RadioFREQ[4] = Readbuff[5];
		
		RadioFREQ[5] = Readbuff[6];
	}
}

void Write_EEPROM(void)
{
		IAP_SectorEraseOption(0x0,EEPROM);
	
		Readbuff[0] = 0x55;
		Readbuff[1] = RadioFREQ[0];
		Readbuff[2] = RadioFREQ[1];
		Readbuff[3] = RadioFREQ[2];
		Readbuff[4] = RadioFREQ[3];
	  Readbuff[5] = RadioFREQ[4];
	  Readbuff[6] = RadioFREQ[5];
	
		IAP_Write_NByte(0,10,Readbuff,EEPROM);
	
}


