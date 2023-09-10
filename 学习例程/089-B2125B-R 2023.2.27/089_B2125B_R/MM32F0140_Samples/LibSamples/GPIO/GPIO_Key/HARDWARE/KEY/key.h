////////////////////////////////////////////////////////////////////////////////
/// @file    key.h
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
#ifndef __KEY_H
#define __KEY_H

// Files includes
#include <string.h>

#include "mm32_device.h"



#include "hal_conf.h"


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
#ifdef _KEY_C_
#define GLOBAL







#else
#define GLOBAL extern







#endif





#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{


/**********     按键扫描    *************/
#define KEYSW1				0x0001
#define KEYSW2				0x0002
#define KEYSW3				0x0004
#define KEYSW4				0x0008    //定时按键
#define KEYSW5				0x0010
#define KEYSW6				0x0020
#define KEYSW7				0x0040
#define KEYSW8				0x0080
#define KEYSW9				0x0100
#define KEYSW10				0x0200
#define KEYSW11				0x0400
#define KEYSW12				0x0800
#define KEYcom1				0x0030    //组合按键取暖和换气

#define KEYSW10_3s   	0x1000
#define KEYSW11_3s    0x2000
#define KEYSW11_10s   0x4000
#define KEYSW2_3s    	0x8000
#define KEYSW8_3s		  0x8400



extern unsigned int KeyCheck(void);
extern void TimeSave_func(void);
extern void Set_All_OutPut(void);
extern void Set_PA5_OutPut(void);
extern void Set_PA7_OutPut(void);
extern void Set_PB0_OutPut(void);
extern void Set_PB1_OutPut(void);

extern void Key_Process(void);



/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
