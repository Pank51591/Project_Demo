////////////////////////////////////////////////////////////////////////////////
/// @file    key.c
/// @author  AE TEAM
/// @brief   key intput.
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
#define _KEY_C_

// Files includes
#include "key.h"
#include "delay.h"
#include "led.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY_Exported_Functions
/// @{



////////////////////////////////////////////////////////////////////////////////
/// @brief  Keyboard Scanning
/// @note   None.
/// @param  None.
/// @retval Keyboard value.
////////////////////////////////////////////////////////////////////////////////
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;
    if(mode)
        key_up = 1;
    if(key_up && ((KEY1 == KEY1_DOWN_VALUE) || (KEY2 == KEY2_DOWN_VALUE) || \
                  (KEY3 == KEY3_DOWN_VALUE) || (KEY4 == KEY4_DOWN_VALUE))) {
        DELAY_Ms(10);
        key_up = 0;
        if(KEY1 == KEY1_DOWN_VALUE)
            return KEY1_PRES;
        else if(KEY2 == KEY2_DOWN_VALUE)
            return KEY2_PRES;
        else if(KEY3 == KEY3_DOWN_VALUE)
            return KEY3_PRES;
        else if(KEY4 == KEY4_DOWN_VALUE)
            return KEY4_PRES;
    }
    else if((KEY1 != KEY1_DOWN_VALUE) && (KEY3 != KEY3_DOWN_VALUE) && \
            (KEY4 != KEY4_DOWN_VALUE) && (KEY2 != KEY2_DOWN_VALUE))
        key_up = 1;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize KEY GPIO pin
/// @note   if use jtag/swd interface GPIO PIN as KEY, need to be careful, can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA | RCC_AHBENR_GPIOB | RCC_AHBENR_GPIOC, ENABLE);
#if defined(MINIBOARD)
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = KEY1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = KEY2_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(KEY2_GPIO_Port, &GPIO_InitStruct);
#endif
#if defined(EMINIBOARD)
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = KEY1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = KEY2_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY2_GPIO_Port, &GPIO_InitStruct);
#endif
    GPIO_InitStruct.GPIO_Pin  = KEY3_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY3_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = KEY4_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY4_GPIO_Port, &GPIO_InitStruct);
    GPIO_PinAFConfig(KEY1_GPIO_Port, KEY1_PIN_SOURCE, GPIO_AF_15);
    GPIO_PinAFConfig(KEY2_GPIO_Port, KEY2_PIN_SOURCE, GPIO_AF_15);
    GPIO_PinAFConfig(KEY3_GPIO_Port, KEY3_PIN_SOURCE, GPIO_AF_15);
    GPIO_PinAFConfig(KEY4_GPIO_Port, KEY4_PIN_SOURCE, GPIO_AF_15);
}


/// @}


/// @}

/// @}

