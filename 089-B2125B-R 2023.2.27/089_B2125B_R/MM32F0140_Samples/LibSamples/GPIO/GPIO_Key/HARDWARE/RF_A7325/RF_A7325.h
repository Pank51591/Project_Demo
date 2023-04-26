#ifndef __RF_A7325_H__
#define __RF_A7325_H__

#include <string.h>
#include "mm32_device.h"
#include "hal_conf.h"


#define Uint8		unsigned char 

#define Set_SCS			GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define Clr_SCS			GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define Set_SCK			GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define Clr_SCK			GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define Set_SDIO		GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define Clr_SDIO		GPIO_ResetBits(GPIOA,GPIO_Pin_0)

#define Read_SDIO		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)   //读取指定GPIO端口引脚的输入数据


#define _nop()       


//#define SCS         _pa6        //spi SCS
//#define SCK         _pa7        //spi SCK
//#define SDIO        _pb3        //spi SDIO
//#define Set_SDIO_In		_pbc3 = 1	//SDIO 为输入
//#define Set_SDIO_Out	_pbc3 = 0  //设置SDIO为输出
 
//#define GIO1        _pb4        //GIO1
 

extern void Reset(void);
extern void WriteID(void);
extern void WriteReg(Uint8 addr, Uint8 dataByte);
extern Uint8 ReadReg(Uint8 addr);
extern void ByteSend(Uint8 src);
extern Uint8 ByteRead(void);
extern void Send4Bit(Uint8 src);
extern void SetCH_A7325(Uint8 ch);
extern void SetCH_A7105(Uint8 ch);
extern void initRF_M(void);
extern void WriteFIFO(void);
extern void StrobeCmd(Uint8 cmd);
extern void RxPacket(void);
extern void SelVCOBand(Uint8 vb1, Uint8 vb2);
extern void A7325_Cal(void);
extern void A7325_Config_M(void);
extern void A7325_CHGroupCal(Uint8 ch);
extern void Err_State(void);
extern Uint8 A7325_RCO_Calibration(void);
extern void A7325_Enable_WOT(void);
extern void A7325_Disable_WOT(void);
extern void A7325_Init(void);
extern void A7325TX_Process(void);
extern void A7325_Sleep(void);
extern void A7325_ExitSleep(void);
extern void  DirectMode_init(void);

#endif   




