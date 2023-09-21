/*
 * The Clear BSD License
 * Copyright (c) 2015 - 2016, Mindmotion Semiconductor, Inc.
 * Copyright 2016 - 2017 Mindmotion
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "usb_host_config.h"
#include "usb_host.h"
//#include "fsl_device_registers.h"
//#include "host_msd_command.h"
#include "host_msd_fatfs.h"
#include "fsl_common.h"
#include "HAL_device.h"
#include "app.h"
//#include "board.h"
#include "HAL_gpio.h"
#include "HAL_rcc.h"
#include "HAL_uart.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief host callback function.
 *
 * device attach/detach callback function.
 *
 * @param deviceHandle        device handle.
 * @param configurationHandle attached device's configuration descriptor information.
 * @param eventCode           callback event code, please reference to enumeration host_event_t.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_NotSupported         The application don't support the configuration.
 */
static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode);

/*!
 * @brief application initialization.
 */

extern void USB_HostClockInit(void);
extern void USB_HostIsrEnable(void);
extern void USB_HostTaskFn(void* param);
void BOARD_InitHardware(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief USB host msd command instance global variable */
usb_host_handle g_HostHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/
void OTG_FS_IRQHandler(void)
{
    USB_HostKhciIsrFunction(g_HostHandle);
}

/*主机时钟*/
void USB_HostClockInit(void)
{ 
    /* Select USBCLK source */
    //  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
    RCC->CFGR &= ~(0x3 << 22);
    RCC->CFGR |= (0x1 << 22);

    RCC->AHB2ENR |= (1<<7);
    /* Enable USB clock */
//    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div2); //RCC->AHB2ENR |= 0x1 << 7;
}

void USB_HostIsrEnable(void)
{
    uint8_t irqNumber;
    uint8_t usbHOSTKhciIrq = USB_FS_IRQn;
    irqNumber = usbHOSTKhciIrq;

    NVIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ((IRQn_Type)irqNumber);
}


/*********************************************************
***函数名：
***函数功能：
***参数：
***返回值：
**********************************************************/
void USB_HostTaskFn(void* param)
{
    USB_HostKhciTaskFunction(param);
}

/*!
 * @brief USB isr function.
 */
/*********************************************************
***函数名：
***函数功能：
***参数：
***返回值：
**********************************************************/
static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode)
{
    usb_status_t status = kStatus_USB_Success;
    switch (eventCode) {
        case kUSB_HostEventAttach:
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            break;

        case kUSB_HostEventNotSupported:
            usb_echo("device not supported.\r\n");
            break;

        case kUSB_HostEventEnumerationDone:
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            break;

        case kUSB_HostEventDetach:
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            break;

        default:
            break;
    }
    return status;
}


void USB_HostApplicationInit(void)
{
    usb_status_t status = kStatus_USB_Success;

    USB_HostClockInit();

    status = USB_HostInit(CONTROLLER_ID, &g_HostHandle, USB_HostEvent);      //枚举，回调函数
    if (status != kStatus_USB_Success) {
        return;
    }
		
    USB_HostIsrEnable();

}

