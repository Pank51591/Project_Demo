////////////////////////////////////////////////////////////////////////////////
/// @file    main.c
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
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
#define _MAIN_C_

// Files includes

#include "key.h"
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "sys.h"

#include "usb_host_config.h"
#include "usb.h"
#include "usb_host.h"
//#include "host_msd_command.h"
#include "host_msd_fatfs.h"
#include "boot.h"
#include "LCD19264F.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{
uint32_t Boot_state = 0;

uint16_t DFU_state;
typedef void (*pFunction)(void);

pFunction Jump_To_Application;
u32 JumpAddress;

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{

extern usb_host_handle g_HostHandle;
extern usb_host_msd_fatfs_instance_t g_MsdFatfsInstance;
void USB_HostApplicationInit(void);
void USB_HostTaskFn(void *param);
u32 asd = 0;
////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is main entrance.
/// @param  None.
/// @retval  0.
////////////////////////////////////////////////////////////////////////////////
void USB_DeviceApplicationInit(void);
#if defined(__CC_ARM) || defined(__GNUC__)
int main(void)
#else
void main(void)
#endif
{

	/*
	must check and set the value as below in startup_mm32f327x_keil.s
	Stack_Size      EQU     0x00001800
	Heap_Size       EQU     0x00000C00

	BootJumpFlag          0x08007C00       // Jump flag
	WRITE_BUFF_SIZE       0x400
	BOOT_HEAD             0x4D4D3332

	*/

	//RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
	//VBUS_CTR_Init();														   // !!! important VBUS Open  PC13 output low Active Power OutPut for MB039
	CONSOLE_Init(115200);													   // !!! important Set UART Out to IP UART8(Tx PE1,Rx PE0) in MB039 UART3
	DELAY_Init();
	if(*((__IO u8*)(0x08008002)) == 0x01)
	{
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		FLASH_ErasePage(0x08008000);
		FLASH_ClearFlag(FLASH_FLAG_EOP);
		FLASH_ProgramHalfWord(0x08008000,0x01);
		FLASH_ProgramHalfWord(0x08008002,0x00);
		FLASH_ClearFlag(FLASH_FLAG_EOP);
		FLASH_Lock();

		__disable_irq();
		

		/* Test if user code is programmed starting from address "ApplicationAddress" */

		if (((*(__IO uint32_t *)ApplicationAddress) & 0x2FFE0000) == 0x20000000) //检查栈顶地址是否合法
		{
			/* Jump to user application */
			JumpAddress = *(__IO uint32_t *)(ApplicationAddress + 4);
			Jump_To_Application = (pFunction)JumpAddress;

			/* Initialize user application's Stack Pointer */
			__set_MSP(*(__IO uint32_t *)ApplicationAddress);

			// Jump to APP
			Jump_To_Application();
		}
	}
	DELAY_Ms(500);	
	USB_HostApplicationInit();
	DELAY_Ms(500);
	while (1)
	{
		if(asd >= 300)
		{
			if(*(__IO u8*)0x08008000 == 0x01 || *(__IO u8*)0x08008000 == 0xff)
			{
				USB_HostMsdTask(&g_MsdFatfsInstance,1);
				FLASH_Unlock();
				FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
				FLASH_ErasePage(0x08008000);
				FLASH_ClearFlag(FLASH_FLAG_EOP);
				FLASH_ProgramHalfWord(0x08008000,0x01);
				FLASH_ProgramHalfWord(0x08008002,0x01);
				FLASH_ClearFlag(FLASH_FLAG_EOP);
				FLASH_Lock();

				NVIC_SystemReset(); //
			}
			else
			{
				NVIC_SystemReset(); //
			}
		}
		else
		{
			USB_HostTaskFn(g_HostHandle);
			USB_HostMsdTask(&g_MsdFatfsInstance,0);
			DELAY_Ms(10);
		}
	}
}

/// @}

/// @}

/// @}
