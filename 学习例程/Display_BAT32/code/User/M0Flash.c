#include"config.h"
#include"M0Flash.h"
#include"sim_eeprom.h"


void FlashWrite(INT32U addr,INT8U *pbuff,INT16U len)
{
	FLASH_SIM_WriteEE((u16*)pbuff, (u32)(BASED_FLASH_SECTOR_ADDRESS+addr), len);
}




void FlashRead(INT32U addr,INT8U *pbuff,INT16U len)
{
    u32 pAddr;

    addr += BASED_FLASH_SECTOR_ADDRESS;
    
    pAddr = FLASH_SIM_WriteLocate((u32)(addr), len);
    //u16* pAddr   = FLASH_SIM_Locate((u32)(BASED_FLASH_SECTOR_ADDRESS), len);

    if (pAddr == 0) {
        return;
    }
    else if (pAddr == addr) {
        pAddr = (addr + 0x0800 - len);
    }
    else {
        pAddr -= len;
    }
    memcpy(pbuff, (s8*)pAddr, len);
}


