/***********************************************************************************************************************
    @file    tinyusb_host_cdc.c
    @author  FAE Team
    @date    23-Aug-2023
    @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
  **********************************************************************************************************************
    @attention

    <h2><center>&copy; Copyright(c) <2023> <MindMotion></center></h2>

      Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
    following conditions are met:
    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
       the following disclaimer in the documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or
       promote products derived from this software without specific prior written permission.

      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *********************************************************************************************************************/

/* Define to prevent recursive inclusion */
#define _TINYUSB_HOST_CDC_C_

/* Files include */
#include <stdio.h>
#include "tinyusb_host_cdc.h"
#include "usbh.h"
/**
  * @addtogroup MM32F3273_LibSamples
  * @{
  */

/**
  * @addtogroup TinyUSB_Device
  * @{
  */

/**
  * @addtogroup TinyUSB_Host_CDC
  * @{
  */

/* Private typedef ****************************************************************************************************/
void cdc_task(void);
void led_blinking_task(void);

extern void cdc_app_task(void);

/* Private define *****************************************************************************************************/

/* Private macro ******************************************************************************************************/
// from msc_app.c

/* Private variables **************************************************************************************************/
/* Private functions **************************************************************************************************/

void USB_DeviceClockInit(void)
{
    /* Select USBCLK source */
//    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
    
    RCC->CFGR &= ~(0x3 << 22);
    RCC->CFGR |= (0x1 << 22);

    /* Enable USB clock */
    RCC->AHB2ENR |= 0x1 << 7;
}


/*********************************************************
***函数名：
***函数功能：
***参数：
***返回值：
**********************************************************/
void USB_Host_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
    
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource13, GPIO_AF_15);  
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);    
    
    //PC13 USB VBUS_EN
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
    
    USB_DeviceClockInit();
}

/***********************************************************************************************************************
  * @brief
  * @note   none
  * @param  none
  * @retval none
  *********************************************************************************************************************/
void TinyUSB_Host_CDC_Sample(void)
{
  printf("TinyUSB Host CDC Example\r\n");

  USB_Host_Init();
    
  // init host stack on configured roothub port
  tuh_init(BOARD_TUH_RHPORT);

  while (1)
  {
    // tinyusb host task
    tuh_task();

    led_blinking_task();
		
    cdc_app_task();
       
  }
}

//--------------------------------------------------------------------+
// TinyUSB Callbacks
//--------------------------------------------------------------------+

void tuh_mount_cb(uint8_t dev_addr)
{
  // application set-up
  printf("A device with address %d is mounted\r\n", dev_addr);
}

void tuh_umount_cb(uint8_t dev_addr)
{
  // application tear-down
  printf("A device with address %d is unmounted \r\n", dev_addr);
}


//--------------------------------------------------------------------+
// Blinking Task
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  const uint32_t interval_ms = 1000;
  static uint32_t start_ms = 0;

  static bool led_state = false;

  // Blink every interval ms
//  if ( board_millis() - start_ms < interval_ms) return; // not enough time
//  start_ms += interval_ms;

//  board_led_write(led_state);
//  led_state = 1 - led_state; // toggle
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/********************************************** (C) Copyright MindMotion **********************************************/

