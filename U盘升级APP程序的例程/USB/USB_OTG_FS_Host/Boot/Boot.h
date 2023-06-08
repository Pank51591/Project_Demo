#ifndef __BOOT_H_
#define __BOOT_H_

#include "usb_host_config.h"
#include "usb.h"
#include "usb_host.h"
//#include "host_msd_command.h"
#include "host_msd_fatfs.h"

#define APP_SIZE 460                  // 460K flash
#define ApplicationAddress 0x08009000 // APP Address
#define BootJumpFlag 0x08008002       // Jump flag

#define WRITE_BUFF_SIZE 0x400

#define BOOT_HEAD 0x01

uint32_t Boot_read_state(void);

uint32_t *Flash_Read(uint32_t SectorAddress, uint32_t DataLength);
uint8_t *verify_Read(uint32_t SectorAddress, uint32_t DataLength);
void Bootloader_Erase_APP(uint16_t size, uint32_t address);
void FLASH_Writeonepacket(uint32_t addr, uint8_t *p, uint16_t Byte_Num);
void Verify_firmware_data(void);

#endif

/***************************end of file****************************************************/
