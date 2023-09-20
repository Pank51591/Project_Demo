////////////////////////////////////////////////////////////////////////////////
/// @file    sim_eeprom.h
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////


// Define to prevent recursive inclusion
#ifndef __SIM_EEPROM_H
#define __SIM_EEPROM_H

// Files includes
#include <string.h>

//#include "mm32_device.h"
//#include "hal_conf.h"


#define USERSTATUSADDR  (0x00500000+512)// bat32g137
#define USERSTATUSBLOCKSIZE (64)//(32)
#define USEPAGES (1)  // use 1 page total, max is 2   the first page can not be used,so we can use page 2 and 3 in 3 pages


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Example_Layer
/// @brief MM32 Example Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_RESOURCE
/// @brief MM32 Examples resource modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Constants
/// @{

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Enumeration
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief XXXX enumerate definition.
/// @anchor XXXX
////////////////////////////////////////////////////////////////////////////////


/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _SIM_EEPROM_C_
#define GLOBAL







#else
#define GLOBAL extern







#endif





#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{




void FLASH_SIM_EEPROM_Init(void);
s32 EEPROM_Write(u32 addr,u8* ptr, u16 len);
s32 EEPROM_Read(u32 addr,u8* ptr, u16 len);
s32 FLASH_SIM_EEPROM_Test(void);


unsigned char FlashDataRead(uint8_t* buf,unsigned int *D_Block,unsigned char DataBlockSize,unsigned int Addr,unsigned char Pagemunber);
unsigned char FlashDataSave(uint8_t* data,unsigned int *D_Block,unsigned char DataBlockSize,unsigned int Addr,unsigned char Pagemunber);




/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
