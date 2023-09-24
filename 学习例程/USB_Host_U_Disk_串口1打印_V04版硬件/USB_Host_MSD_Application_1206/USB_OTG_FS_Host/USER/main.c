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

#define FLASH_VTOR_OFFSET 0x8000

unsigned char tempbuff[] = {1,2,3,4,5,6};

extern usb_host_handle g_HostHandle;
extern usb_host_msd_fatfs_instance_t g_MsdFatfsInstance;
void USB_HostApplicationInit(void);
void USB_HostTaskFn(void* param);
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

Application address 0x08008000

BOOT_HEAD 0x4D4D3332
    
The upgrade file name must be "Update.bin"
    
*/

//	  SCB->VTOR = FLASH_BASE | FLASH_VTOR_OFFSET; /* Vector Table Relocation in Internal FLASH.*/
//	
//    __enable_irq ();
	

    //SystemReInit(SYSTEMCLK_HSE_96MHz);
	
	
	  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
		
		LED_Init();
    
    VBUS_CTR_Init();    // !!! important VBUS Open  PC13 output low Active Power OutPut for MB039    
    
//		CONSOLE_Init(115200);  		// !!! important Set UART Out to IP UART8(Tx PE1,Rx PE0) in MB039 UART3   
    
		UART1_Init(115200);    //与电机驱动板通信
			
		usb_echo("...... Start Application USB OTG_FS for U-DISK Demo ......\r\n");             //printf("system initial success\r\n"); 
    
		usb_echo("\r\n%s %s\r\n", __DATE__, __TIME__);    
		
    USB_HostApplicationInit(); 
	
    while (1) 
    {
        USB_HostTaskFn(g_HostHandle);
			
        USB_HostMsdTask(&g_MsdFatfsInstance);
			
    }
		
}


/// @}

/// @}

/// @}
