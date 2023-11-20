#include "bsp_spi_flash.h"


static volatile bool g_transfer_complete = false;

void spi_flash_callback(spi_callback_args_t *p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        g_transfer_complete = true;
    }
}


void SPI_Flash_Init(void)
{
    spi_cs(1);
    R_SPI_Open(g_spi0_flash.p_ctrl, g_spi0_flash.p_cfg);
    R_BSP_SoftwareDelay(10u, BSP_DELAY_UNITS_MILLISECONDS);
}

/**
 * @brief  使用SPI发送一个字节的数据
 * @param  byte：要发送的数据
 */
void SPI_Flash_SendByte(uint8_t byte, bool spi_continue)
{
		g_transfer_complete = false;
	
    uint8_t data[2];
    data[0] = byte;

    spi_cs(0);
    R_SPI_Write(g_spi0_flash.p_ctrl, &data[0], 1, SPI_BIT_WIDTH_8_BITS); //写入一个字节的数据
    while (false == g_transfer_complete)	//判断是否传输数据完成
    {
        ;
    }
    if (spi_continue == true)spi_cs(1);

    else spi_cs(0);
}

/**
 * @brief  使用SPI发送一个字节的数据
 * @retval 返回接收到的数据
 */
void SPI_Flash_ReadByte(uint8_t *byte, uint32_t len, bool spi_continue)
{
		g_transfer_complete = false;
	
    spi_cs(0);
    R_SPI_Read(g_spi0_flash.p_ctrl, byte, len, SPI_BIT_WIDTH_8_BITS);//接收len个字节的数据
    while (false == g_transfer_complete)	//判断是否传输数据完成
    {
        ;
    }
    if (spi_continue == true)spi_cs(1);
    else spi_cs(0);
}

/**
 * @brief  向FLASH发送 写使能 命令
 * @param  none
 * @retval none
 */
void SPI_Flash_WriteEnable(void)
{
    SPI_Flash_SendByte(WriteEnable, 1);
}

/**
* @brief  等待flash数据写入完成
* @param  无
*/
void SPI_Flash_WaitForWriteEnd(void)
{
    uint8_t FLASH_Status = 0;


    /* 发送 读状态寄存器 命令 */
    SPI_Flash_SendByte(ReadStatusReg, 0);

    /* 若FLASH忙碌，则等待 */
    do
    {
        /* 读取FLASH芯片的状态寄存器 */
        SPI_Flash_ReadByte(&FLASH_Status, 1, 0);
        //printf("Read FLASH_Status = %d\r\n",FLASH_Status);

        //FLASH_Status = 1;
    }
    while ((FLASH_Status & WIP_Flag) == (uint8_t)1);        /* 正在写入标志 */

    spi_cs(1);
}

/**
* @brief  擦除FLASH扇区 4096个字节
* @param  SectorAddr：要擦除的扇区地址
* @retval 无
*/
void SPI_Flash_SectorErase(uint32_t adress)
{
    unsigned char data[6] = {};

    data[0] =  SectorErase;     //erase_command
    data[1] = (uint8_t)(adress >> 16);
    data[2] = (uint8_t)(adress >> 8);
    data[3] = (uint8_t)(adress);

    /* 发送FLASH写使能命令 */
    SPI_Flash_WriteEnable();
    SPI_Flash_WaitForWriteEnd();



    spi_cs(0);
    /* 发送扇区擦除指令*/
    R_SPI_Write(g_spi0_flash.p_ctrl, &data[0], 4, SPI_BIT_WIDTH_8_BITS);
    R_BSP_SoftwareDelay(30, BSP_DELAY_UNITS_MICROSECONDS);
    spi_cs(1);


    SPI_Flash_WaitForWriteEnd();
}



/**
* @brief  读取FLASH ID
* @param  无
* @retval FLASH ID
*/
uint32_t SPI_Flash_ReadID(void)
{
    unsigned char data[6] = {};
    uint32_t back;
    data[0] = JedecDeviceID;

    SPI_Flash_SendByte(data[0], 0);      //false: close the spi  true: go go go
    SPI_Flash_ReadByte(&data[0], 3, 1);

    /*把数据组合起来，作为函数的返回值*/
    back = (data[0] << 16) | (data[1] << 8) | (data[2]);

    return back;
}

/**
* @brief  读取FLASH 设备ID
* @param  无
* @retval FLASH ID
*/
uint32_t SPI_Flash_ReadDeviceID(void)
{


    unsigned char data[6] = {};
    uint32_t back;
    data[0] = DeviceID;
    data[1] = 0xff;

    SPI_Flash_SendByte(data[0], 0);      //false: close the spi  true: go go go
    SPI_Flash_SendByte(data[1], 0);      //false: close the spi  true: go go go
    SPI_Flash_SendByte(data[1], 0);      //false: close the spi  true: go go go
    SPI_Flash_SendByte(data[1], 0);      //false: close the spi  true: go go go
    SPI_Flash_ReadByte(&data[0], 3, 1);

    /*把数据组合起来，作为函数的返回值*/
    back = (data[0] << 16) | (data[1] << 8) | (data[2]);

    return back;
}


/**
* @brief  对FLASH按页写入数据，调用本函数写入数据前需要先擦除扇区
* @param  pBuffer，要写入数据的指针
* @param WriteAddr，写入地址
* @param  NumByteToWrite，写入数据长度，必须小于等于页大小
* @retval 无
*/
void SPI_Flash_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{

    /* 发送FLASH写使能命令 */
    SPI_Flash_WriteEnable();

    /* 写页写指令*/
    SPI_Flash_SendByte(PageProgram, 0);
    /*发送写地址的高位*/
    SPI_Flash_SendByte((WriteAddr & 0xFF0000) >> 16, 0);
    /*发送写地址的中位*/
    SPI_Flash_SendByte((WriteAddr & 0xFF00) >> 8, 0);
    /*发送写地址的低位*/
    SPI_Flash_SendByte(WriteAddr & 0xFF, 0);

    if (NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
        printf("SPI_FLASH_PageWrite too large! \r\n");
    }

    //R_QSPI_Write(&Flash_ctrl, pBuffer, WriteAddr, NumByteToWrite);

    /* 写入数据*/
    while (NumByteToWrite--)
    {
        /* 发送当前要写入的字节数据 */
        SPI_Flash_SendByte(*pBuffer, 0);
        /* 指向下一字节数据 */
        pBuffer++;
    }

    spi_cs(1);

    SPI_Flash_WaitForWriteEnd();
}


/**
 * @brief  对FLASH写入数据，调用本函数写入数据前需要先擦除扇区
 * @param  pBuffer，要写入数据的指针
 * @param  WriteAddr，写入地址
 * @param  NumByteToWrite，写入数据长度
 * @retval 无
 */
void SPI_Flash_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    /*mod运算求余，若writeAddr是SPI_FLASH_PageSize整数倍，运算结果Addr值为0*/
    Addr = WriteAddr % SPI_FLASH_PageSize;

    /*差count个数据值，刚好可以对齐到页地址*/
    count = SPI_FLASH_PageSize - Addr;
    /*计算出要写多少整数页*/
    NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
    /*mod运算求余，计算出剩余不满一页的字节数*/
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    /* Addr=0,则WriteAddr 刚好按页对齐 aligned  */
    if (Addr == 0)
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            SPI_Flash_PageWrite(pBuffer, WriteAddr, NumByteToWrite);

        }
        else     /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*先把整数页都写了*/
            while (NumOfPage--)
            {
                SPI_Flash_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);

                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            /*若有多余的不满一页的数据，把它写完*/
            SPI_Flash_PageWrite(pBuffer, WriteAddr, NumOfSingle);

        }
    }

    /* 若地址与 SPI_FLASH_PageSize 不对齐  */
    else
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            /*当前页剩余的count个位置比NumOfSingle小，一页写不完*/
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                /*先写满当前页*/
                SPI_Flash_PageWrite(pBuffer, WriteAddr, count);


                WriteAddr +=  count;
                pBuffer += count;
                /*再写剩余的数据*/
                SPI_Flash_PageWrite(pBuffer, WriteAddr, temp);

            }
            else     /*当前页剩余的count个位置能写完NumOfSingle个数据*/
            {
                SPI_Flash_PageWrite(pBuffer, WriteAddr, NumByteToWrite);

            }

        }
        else     /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*地址不对齐多出的count分开处理，不加入这个运算*/
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            /* 先写完count个数据，为的是让下一次要写的地址对齐 */
            SPI_Flash_PageWrite(pBuffer, WriteAddr, count);

            /* 接下来就重复地址对齐的情况 */
            WriteAddr +=  count;
            pBuffer += count;

            /*把整数页都写了*/
            while (NumOfPage--)
            {
                SPI_Flash_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);

                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            /*若有多余的不满一页的数据，把它写完*/
            if (NumOfSingle != 0)
            {
                SPI_Flash_PageWrite(pBuffer, WriteAddr, NumOfSingle);

            }
        }
    }
}




/**
 * @brief  读取FLASH数据
 * @param  pBuffer，存储读出数据的指针
 * @param   ReadAddr，读取地址
 * @param   NumByteToRead，读取数据长度
 * @retval 无
 */
void SPI_Flash_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{

    /* 发送 读 指令 */
    SPI_Flash_SendByte(ReadData, 0);

    /* 发送 读 地址高位 */
    SPI_Flash_SendByte((ReadAddr & 0xFF0000) >> 16, 0);
    /* 发送 读 地址中位 */
    SPI_Flash_SendByte((ReadAddr & 0xFF00) >> 8, 0);
    /* 发送 读 地址低位 */
    SPI_Flash_SendByte(ReadAddr & 0xFF, 0);

    /* 读取数据 */
    while (NumByteToRead--)    /* while there is data to be read */
    {
        /* 读取一个字节*/
        SPI_Flash_ReadByte(pBuffer,1,0);
        /* 指向下一个字节缓冲区 */
        pBuffer++;
    }

    /* 停止信号 FLASH: CS 高电平 */
    spi_cs(1);
}




/**
* @brief  进入掉电模式
* @param  无
*/
void SPI_Flash_PowerDown(void)
{
		/* 发送 掉电 命令 */
		SPI_Flash_SendByte(PowerDown , 1);
}

/**
* @brief  唤醒
* @param  无
*/
void SPI_Flash_WAKEUP(void)
{
  /* 发送 上电 命令 */
  SPI_Flash_SendByte(ReleasePowerDown , 1);
}


uint8_t SPI_FLASH_Test(void)
{
    uint32_t FlashDeviceID;
    uint32_t FlashID = 0;
    unsigned char data[6] = {};
    
    
    /* 获取 Flash Device ID */
//    FlashDeviceID = SPI_FLASH_ReadDeviceID();
    
    
    /* 获取 SPI Flash ID */
    FlashID = SPI_Flash_ReadID();

//    data[0] = JedecDeviceID;
//    R_SPI_Write(g_spi0_flash.p_ctrl, &data[0], 1, SPI_BIT_WIDTH_8_BITS); //写入一个字节的数据
//    while (false == g_transfer_complete);   //判断是否传输数据完成

//    g_transfer_complete = false;
//    R_SPI_Read(g_spi0_flash.p_ctrl, &data[0], 3, SPI_BIT_WIDTH_8_BITS);//接收len个字节的数据
//    while (false == g_transfer_complete);   //判断是否传输数据完成

    /*把数据组合起来 */
//    FlashID = (uint32_t)(data[0] << 16) | (uint32_t)(data[1] << 8) | (uint32_t)(data[2]);

    
    //printf("\r\nFlashID is 0x%X, Manufacturer Device ID is 0x%X\r\n", FlashID, FlashDeviceID);
    
    if ((FlashID == FLASH_ID_W25Q32JV) || (FlashID == FLASH_ID_AT25SF321B))
    {
        //printf("\tFLASH_ID：0x%X", FlashID);
        return 0;
    }

    printf("\tFLASH_ID 错误：0x%X", FlashID);
    return 0;   //读取 ID 错误
}



