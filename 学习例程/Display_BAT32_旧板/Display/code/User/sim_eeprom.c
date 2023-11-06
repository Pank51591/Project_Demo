
#include "config.h"
#include "sim_eeprom.h"
#include "flash.h"
#include "BAT32G135.h"


#define FLASH_PAGE_SIZE 512


void FLASH_ErasePage(uint32_t Address)
{
	EraseSector(Address);
}



/***********************************************************************************************************************
* Function Name: WriteFlash
* Description  : This function for Write Flash.
* Arguments    : addr -- flash addr
			   : buf -- data buf
			   : length -- data length
* Return Value : NONE
***********************************************************************************************************************/
unsigned char mWriteFlash(uint32_t addr,uint8_t *buf,uint8_t length)
{
    //unsigned short i;
	//unsigned char status = 0;
    
	/*
    while(length&0x03)
    {
        buf[length++] = 0xff;
    }
    for(i = 0;i < (length/4);i++)
    {
			status = FLASH_ProgramWordData(addr+i*4,*(u32 *)(buf + i*4));
       if(status != FLASH_COMPLETE)
				 return status;
    } 
	*/
	//status = (unsigned char)ProgramPage(addr, length, buf);
	//return 		status;
	return (unsigned char)ProgramPage(addr, length, buf);
}
/***********************************************************************************************************************
* Function Name: ReadFlash
* Description  : This function for Read Flash.
* Arguments    : addr -- flash addr
			   : buf -- data buf
			   : length -- data length
* Return Value : NONE
***********************************************************************************************************************/
void mReadFlash(uint32_t addr,uint8_t *buf,uint8_t length)
{
    unsigned short i;
    
    for(i = 0;i < length;i++)
    {
        *buf++ = *(unsigned char *)(addr+i);
    }
}

static unsigned char UserDataCrcCheck(unsigned char* data, int len)
{
	int i;
	unsigned char crc=0;
	if(data == 0 || len == 0)  // null
		return 0;
	crc = *data;
	for(i=1; i<len-1; i++)
		crc = (crc-1)-*(data+i);
	//if(type)
		return crc;

}





//-------------------------------------------------------------------------------


unsigned char FlashDataRead(uint8_t* buf,unsigned int *D_Block,unsigned char DataBlockSize,unsigned int Addr,unsigned char Pagemunber)
{
	unsigned int blk,data;
	unsigned char getdata[DataBlockSize],i;  //  C99+ , C98 will get error

	if(DataBlockSize>=65)////  be careful DataBlockSize , over ram size
		while(1);// stop for 
	
	for(blk=0; blk<DataBlockSize; blk++)
		*(buf+blk) = 0;	
	for(blk=0; blk<(FLASH_PAGE_SIZE*Pagemunber)/DataBlockSize; blk++)
	{
		
		mReadFlash(Addr+blk*DataBlockSize, (uint8_t*)&data, 4);
		if(0xFFFFFFFF == data)
			break;
	}
	if(blk)
	{
		*D_Block = blk - 1;
		mReadFlash(Addr+(*D_Block)*DataBlockSize, (uint8_t*)&getdata, DataBlockSize);

		if( UserDataCrcCheck(getdata, DataBlockSize) == *(getdata + DataBlockSize - 1))
		{	
			for(blk=0; blk<DataBlockSize; blk++)
				*(buf+blk) = *(getdata+blk);
			(*D_Block)++;
			if((*D_Block) >= (FLASH_PAGE_SIZE*Pagemunber)/(DataBlockSize))
			{
				(*D_Block) = 0;
				for(i=0;i<Pagemunber;i++)
				{
					FLASH_ErasePage(Addr+FLASH_PAGE_SIZE*i);
				}
				 
			}
			return 0; // return opration ok 
		}
		else
		{
			
			(*D_Block) = 0;
			for(i=0;i<Pagemunber;i++)
			{
				FLASH_ErasePage(Addr+FLASH_PAGE_SIZE*i);
			}
			return 1;  // return error
		}
			
	}
	else
	{
		return 1;  // return error
	}
	
	
}


///----
// data    |data pointer
// D_Block |global value , for save index of address
// DataBlockSize | the size of *data buff
// Addr | flash start address
// Pagemunber | how many pages for *data
unsigned char FlashDataSave(uint8_t* data,unsigned int *D_Block,unsigned char DataBlockSize,unsigned int Addr,unsigned char Pagemunber)
{
	//FLASH_OptionByte op;
  unsigned char tdata[DataBlockSize],blk,i;
	
	if(DataBlockSize>=65)////  be careful DataBlockSize , over ram size
		while(1);
	
	for(blk=0; blk<DataBlockSize; blk++)
		*(tdata+blk) = *(data+blk);
	

  tdata[DataBlockSize-1] = UserDataCrcCheck(tdata, DataBlockSize);

	if((*D_Block) >= FLASH_PAGE_SIZE*Pagemunber/DataBlockSize - 1)  //
	{
		(*D_Block) = 0;
		for(i=0;i<Pagemunber;i++)
		{
			FLASH_ErasePage(Addr+FLASH_PAGE_SIZE*i);
		}				
	}

	 i = mWriteFlash(Addr+(*D_Block)*DataBlockSize, tdata, DataBlockSize);
	(*D_Block)++;
	return i;


}


//------------------------------------------------------------------------------





