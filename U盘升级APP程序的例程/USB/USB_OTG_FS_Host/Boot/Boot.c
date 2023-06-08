
#include "usb_host_config.h"
#include "usb.h"
#include "usb_host.h"
//#include "host_msd_command.h"
#include "host_msd_fatfs.h"

#include "Boot.h"
#include "sys.h"
#include "string.h"

uint8_t *IAP_readBuff = NULL;
uint16_t Boot_index = 0;
/*************************************************************************************************************************/

/*************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////
/// @brief  uint32_t *Flash_Read(uint32_t SectorAddress, uint32_t DataLength) //
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
uint32_t *Flash_Read(uint32_t SectorAddress, uint32_t DataLength) //
{
	return (uint32_t *)SectorAddress;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  uint8_t *verify_Read(uint32_t SectorAddress, uint32_t DataLength) //
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
uint8_t *verify_Read(uint32_t SectorAddress, uint32_t DataLength) //
{
	return (uint8_t *)SectorAddress;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  uint32_t Boot_read_state(void)
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
uint32_t Boot_read_state(void)
{
	return (*((__IO u32 *)(BootJumpFlag)));
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  void Bootloader_Erase_APP(uint8_t size, uint32_t address)
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void Bootloader_Erase_APP(uint16_t size, uint32_t address)
{
	uint32_t Address;
	uint16_t index, temp;
	temp = size;
	Address = address; // APP flash   0x08008000 -- 0x08080000   480K flash
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	for (index = 0; index < temp; index++)
	{
		FLASH_ErasePage(Address);
		Address = Address + 0x400;
	}
	FLASH_Lock();
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  void FLASH_Writeonepacket(uint32_t addr, uint8_t *p, uint16_t Byte_Num)
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_Writeonepacket(uint32_t addr, uint8_t *p, uint16_t Byte_Num)
{
	uint32_t HalfWord;
	Byte_Num = Byte_Num / 2;

	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	while (Byte_Num--)
	{
		HalfWord = *(p++);
		HalfWord |= *(p++) << 8;
		FLASH_ProgramHalfWord(addr, HalfWord);
		addr += 2;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  void Verify_firmware_data(void)
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////

void Verify_firmware_data(void)
{
	Loop_count = 0;
	Operation_address = ApplicationAddress;
	Calculation_Write_checksum = 0;
	Remaining_size = Packet_Total_lenth;

	while (Remaining_size) // lopp calculation checksum
	{

		if (Remaining_size >= WRITE_BUFF_SIZE)
		{
			Remaining_size = Remaining_size - WRITE_BUFF_SIZE;
			Updatepacketsize = WRITE_BUFF_SIZE;
		}
		else
		{
			Updatepacketsize = Remaining_size;
			Remaining_size = 0;
		}

		Loop_count++;

		//usb_echo("Verify read......");

		IAP_readBuff = verify_Read(Operation_address, Updatepacketsize);
		memcpy(Temp_write_buff, IAP_readBuff, Updatepacketsize);

		for (Boot_index = 0; Boot_index < Updatepacketsize; Boot_index++)
		{
			Calculation_Write_checksum = Temp_write_buff[Boot_index] + Calculation_Write_checksum;
		}

		Operation_address = Operation_address + Updatepacketsize;

		//usb_echo("success\r\n");
	}

	//usb_echo("IAP Verify Checksum= %08x \r\n", Calculation_Write_checksum);

	if (Calculation_Write_checksum == Calculation_Read_checksum)
	{
		/*
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		FLASH_ErasePage(0x08007000);
		FLASH_ClearFlag(FLASH_FLAG_EOP);
		
		Version_buff[0] = BOOT_HEAD;				  ////0x4D4D3332
		Version_buff[1] = 0x02; // Checksum
		Version_buff[2] = 0x03;
		FLASH_ProgramHalfWord(BootJumpFlag,Version_buff[0]);
		FLASH_ProgramHalfWord(BootJumpFlag+2,Version_buff[1]);
		FLASH_ProgramHalfWord(BootJumpFlag+4,Version_buff[2]);
		FLASH_ClearFlag(FLASH_FLAG_EOP);
		FLASH_Lock();
		*/
		/*
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		FLASH_ErasePage(BootJumpFlag);

		Version_buff[0] = BOOT_HEAD;				  ////0x4D4D3332
		Version_buff[1] = 0x02; // Checksum
		Version_buff[2] = 0x03;

		FLASH_ProgramWord(BootJumpFlag, Version_buff[0]);
		FLASH_ProgramWord(BootJumpFlag + 4, Version_buff[1]);
		FLASH_ProgramWord(BootJumpFlag + 8, Version_buff[2]);

		FLASH_Lock();
		*/
		////usb_echo("Upgrade success  %08x %08x %08x\r\n", Version_buff[0], Version_buff[1], Version_buff[2]);

		////usb_echo("Boot Reast\r\n");
		
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		FLASH_ErasePage(0x08008000);
		FLASH_ClearFlag(FLASH_FLAG_EOP);
		FLASH_ProgramHalfWord(0x08008000,0x01);
		FLASH_ProgramHalfWord(0x08008002,0x01);
		FLASH_ClearFlag(FLASH_FLAG_EOP);
		FLASH_Lock();

		NVIC_SystemReset(); //

		while (1)
		{
		}
	}
}

/***************************end of file****************************************************/
