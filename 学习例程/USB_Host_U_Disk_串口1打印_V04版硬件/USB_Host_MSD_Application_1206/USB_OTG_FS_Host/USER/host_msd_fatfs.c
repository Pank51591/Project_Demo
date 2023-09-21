/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016, 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "usb_host_config.h"
#include "usb_host.h"
#include "usb_host_msd.h"
#include "host_msd_fatfs.h"
#include "ff.h"
#include "diskio.h"
//#include "fsl_device_registers.h"
#include "app.h"
#include "hal_flash.h"


#define WRITE_BUFF_SIZE  1024
#define BootJumpFlag 0x08007C00       //Jump flag

#define BOOT_HEAD 0x4D4D3332



uint8_t Temp_read_buff[WRITE_BUFF_SIZE] = {0};
uint32_t Calculation_checksum = 0;
uint32_t Packet_Total_lenth = 0;
uint16_t Updatepacketsize = 0;
uint32_t Remaining_size = 0;
uint16_t Temp_count = 0;
uint16_t Loop_count = 0;

uint32_t Version_buff[3];  //Head  Checksum  Version
 
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if MSD_FATFS_THROUGHPUT_TEST_ENABLE
#include "fsl_device_registers.h"
#define THROUGHPUT_BUFFER_SIZE (64 * 1024) /* throughput test buffer */
#define MCU_CORE_CLOCK         (120000000) /* mcu core clock, user need to configure it. */
#endif                                     /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief host msd control transfer callback.
 *
 * This function is used as callback function for control transfer .
 *
 * @param param      the host msd fatfs instance pointer.
 * @param data       data buffer pointer.
 * @param dataLength data length.
 * @status           transfer result status.
 */
void USB_HostMsdControlCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status);

/*!
 * @brief msd fatfs test code execute done.
 */
static void USB_HostMsdFatfsTestDone(void);

#if ((defined MSD_FATFS_THROUGHPUT_TEST_ENABLE) && (MSD_FATFS_THROUGHPUT_TEST_ENABLE))
/*!
 * @brief host msd fatfs throughput test.
 *
 * @param msdFatfsInstance   the host fatfs instance pointer.
 */
static void USB_HostMsdFatfsThroughputTest(usb_host_msd_fatfs_instance_t *msdFatfsInstance);

#else

/*!
 * @brief display file information.
 */
static void USB_HostMsdFatfsDisplayFileInfo(FILINFO *fileInfo);

/*!
 * @brief list files and sub-directory in one directory, the function don't check all sub-directories recursively.
 */
static FRESULT USB_HostMsdFatfsListDirectory(const TCHAR *path);

/*!
 * @brief forward function pointer for fatfs f_forward function.
 *
 * @param data_ptr   forward data pointer.
 * @param dataLength data length.
 */
#if _USE_FORWARD && _FS_TINY
static uint32_t USB_HostMsdFatfsForward(const uint8_t *data_ptr, uint32_t dataLength);
#endif

/*!
 * @brief host msd fatfs test.
 *
 * This function implements msd fatfs test.
 *
 * @param msdFatfsInstance   the host fatfs instance pointer.
 */
//static void USB_HostMsdFatfsTest(usb_host_msd_fatfs_instance_t *msdFatfsInstance);

static void USB_HostMsdFatfsUserReadWrite(usb_host_msd_fatfs_instance_t *msdFatfsInstance); //mm32
    
#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
extern usb_status_t USB_HostTestModeInit(usb_device_handle deviceHandle);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief msd class handle array for fatfs */
extern usb_host_class_handle g_UsbFatfsClassHandle;

usb_host_msd_fatfs_instance_t g_MsdFatfsInstance; /* global msd fatfs instance */
static FATFS fatfs;
/* control transfer on-going state. It should set to 1 when start control transfer, it is set to 0 in the callback */
volatile uint8_t controlIng;
/* control transfer callback status */
volatile usb_status_t controlStatus;

#if MSD_FATFS_THROUGHPUT_TEST_ENABLE
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
static uint32_t testThroughputBuffer[THROUGHPUT_BUFFER_SIZE / 4]; /* the buffer for throughput test */
uint32_t testSizeArray[] = {20 * 1024, 20 * 1024};                /* test time and test size (uint: K)*/
#else
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
static uint8_t testBuffer[(FF_MAX_SS > 256) ? FF_MAX_SS : 256]; /* normal test buffer */
#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */

/*******************************************************************************
 * Code
 ******************************************************************************/

void USB_HostMsdControlCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status)
{
    usb_host_msd_fatfs_instance_t *msdFatfsInstance = (usb_host_msd_fatfs_instance_t *)param;

    if (msdFatfsInstance->runWaitState == kUSB_HostMsdRunWaitSetInterface) /* set interface finish */
    {
        msdFatfsInstance->runWaitState = kUSB_HostMsdRunIdle;
        msdFatfsInstance->runState     = kUSB_HostMsdRunMassStorageTest;
    }
    controlIng    = 0;
    controlStatus = status;
}

static void USB_HostMsdFatfsTestDone(void)
{
    usb_echo("............................test done......................\r\n");
}

#if ((defined MSD_FATFS_THROUGHPUT_TEST_ENABLE) && (MSD_FATFS_THROUGHPUT_TEST_ENABLE))

static void USB_HostMsdFatfsThroughputTest(usb_host_msd_fatfs_instance_t *msdFatfsInstance)
{
    uint64_t totalTime;
    FRESULT fatfsCode;
    FIL file;
    uint32_t resultSize;
    uint32_t testSize;
    uint8_t testIndex;
    char test_file_name[30];

    /* time delay (~100ms) */
    for (resultSize = 0; resultSize < 400000; ++resultSize)
    {
        __NOP();
    }

    usb_echo("............................fatfs test.....................\r\n");
    CoreDebug->DEMCR |= (1 << CoreDebug_DEMCR_TRCENA_Pos);

    for (testSize = 0; testSize < (THROUGHPUT_BUFFER_SIZE / 4); ++testSize)
    {
        testThroughputBuffer[testSize] = testSize;
    }

    sprintf(test_file_name, "%c:", USBDISK + '0');
    fatfsCode = f_mount(&fatfs, test_file_name, 1);
    if (fatfsCode)
    {
        usb_echo("fatfs mount error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }

    sprintf(test_file_name, "%c:/thput.dat", USBDISK + '0');
    usb_echo("throughput test:\r\n");
    for (testIndex = 0; testIndex < (sizeof(testSizeArray) / 4); ++testIndex)
    {
        fatfsCode = f_unlink(test_file_name); /* delete the file if it is existed */
        if ((fatfsCode != FR_OK) && (fatfsCode != FR_NO_FILE))
        {
            USB_HostMsdFatfsTestDone();
            return;
        }

        fatfsCode = f_open(&file, test_file_name, FA_WRITE | FA_READ | FA_CREATE_ALWAYS); /* create one new file */
        if (fatfsCode)
        {
            USB_HostMsdFatfsTestDone();
            return;
        }

        totalTime = 0;
        testSize  = testSizeArray[testIndex] * 1024;
        while (testSize)
        {
            if (msdFatfsInstance->deviceState != kStatus_DEV_Attached)
            {
                USB_HostMsdFatfsTestDone();
                return;
            }
            DWT->CYCCNT = 0;
            DWT->CTRL |= (1 << DWT_CTRL_CYCCNTENA_Pos);
            fatfsCode = f_write(&file, testThroughputBuffer, THROUGHPUT_BUFFER_SIZE, &resultSize);
            if (fatfsCode)
            {
                usb_echo("write error\r\n");
                f_close(&file);
                USB_HostMsdFatfsTestDone();
                return;
            }
            totalTime += DWT->CYCCNT;
            DWT->CTRL &= ~(1 << DWT_CTRL_CYCCNTENA_Pos);
            testSize -= THROUGHPUT_BUFFER_SIZE;
        }
        testSize = testSizeArray[testIndex];
        usb_echo("    write %dKB data the speed is %d KB/s\r\n", testSize,
                 (uint32_t)((uint64_t)testSize * (uint64_t)MCU_CORE_CLOCK / (uint64_t)totalTime));

        fatfsCode = f_lseek(&file, 0);
        if (fatfsCode)
        {
            USB_HostMsdFatfsTestDone();
            return;
        }
        totalTime = 0;
        testSize  = testSizeArray[testIndex] * 1024;
        while (testSize)
        {
            if (msdFatfsInstance->deviceState != kStatus_DEV_Attached)
            {
                USB_HostMsdFatfsTestDone();
                return;
            }
            DWT->CYCCNT = 0;
            DWT->CTRL |= (1 << DWT_CTRL_CYCCNTENA_Pos);
            fatfsCode = f_read(&file, testThroughputBuffer, THROUGHPUT_BUFFER_SIZE, &resultSize);
            if (fatfsCode)
            {
                usb_echo("read error\r\n");
                f_close(&file);
                USB_HostMsdFatfsTestDone();
                return;
            }
            totalTime += DWT->CYCCNT;
            DWT->CTRL &= ~(1 << DWT_CTRL_CYCCNTENA_Pos);
            testSize -= THROUGHPUT_BUFFER_SIZE;
        }
        testSize = testSizeArray[testIndex];
        usb_echo("    read %dKB data the speed is %d KB/s\r\n", testSize,
                 (uint32_t)((uint64_t)testSize * (uint64_t)MCU_CORE_CLOCK / (uint64_t)totalTime));

        fatfsCode = f_close(&file);
        if (fatfsCode)
        {
            USB_HostMsdFatfsTestDone();
            return;
        }
    }

    USB_HostMsdFatfsTestDone();
}

#else

static void USB_HostMsdFatfsDisplayFileInfo(FILINFO *fileInfo)
{
    char *fileName;
#if _USE_LFN
    fileName = (fileInfo->lfname[0] ? fileInfo->lfname : fileInfo->fname;
#else
    fileName = fileInfo->fname;
#endif /* _USE_LFN */
    /* note: if this file/directory don't have one attribute, '_' replace the attribute letter ('R' - readonly, 'H' - hide, 'S' - system) */
    usb_echo("    %s - %c%c%c - %s - %dBytes - %d-%d-%d %d:%d:%d\r\n", (fileInfo->fattrib & AM_DIR) ? "dir" : "fil",
             (fileInfo->fattrib & AM_RDO) ? 'R' : '_',
             (fileInfo->fattrib & AM_HID) ? 'H' : '_',
             (fileInfo->fattrib & AM_SYS) ? 'S' : '_',
             fileName,
             (fileInfo->fsize),
             (uint32_t)((fileInfo->fdate >> 9) + 1980) /* year */,
             (uint32_t)((fileInfo->fdate >> 5) & 0x000Fu) /* month */,
             (uint32_t)(fileInfo->fdate & 0x001Fu) /* day */,
             (uint32_t)((fileInfo->ftime >> 11) & 0x0000001Fu) /* hour */,
             (uint32_t)((fileInfo->ftime >> 5) & 0x0000003Fu) /* minute */,
             (uint32_t)(fileInfo->ftime & 0x0000001Fu) /* second */
             );
}

static FRESULT USB_HostMsdFatfsListDirectory(const TCHAR *path)
{
    FRESULT fatfsCode = FR_OK;
    FILINFO fileInfo;
    DIR dir;
    uint8_t outputLabel = 0;

#if _USE_LFN
    static uint8_t fileNameBuffer[_MAX_LFN];
    fileInfo.lfname = fileNameBuffer;
    fileInfo.lfsize = _MAX_LFN;
#endif /* _USE_LFN */

    fatfsCode = f_opendir(&dir, path);
    if (fatfsCode)
    {
        return fatfsCode;
    }
    while (1)
    {
        fatfsCode = f_readdir(&dir, &fileInfo);
        if ((fatfsCode) || (!fileInfo.fname[0]))
        {
            break;
        }
        outputLabel = 1;
        USB_HostMsdFatfsDisplayFileInfo(&fileInfo);
    }
    if (!outputLabel)
    {
        usb_echo("\r\n");
    }

    return fatfsCode;
}

#if _USE_FORWARD && _FS_TINY
static uint32_t USB_HostMsdFatfsForward(const uint8_t *data, uint32_t dataLength)
{
    uint32_t resultCount = dataLength;

    if (dataLength == 0)
    {
        return 1;
    }
    else
    {
        do
        {
            usb_echo("%c", *data);
            data++;
            resultCount--;
        } while (resultCount);
        return dataLength;
    }
}
#endif

//=============================================================================================
//User Read write File
static void USB_HostMsdFatfsUserReadWrite(usb_host_msd_fatfs_instance_t *msdFatfsInstance)
{
    FRESULT fatfsCode;
    FATFS *fs;
    FIL file;
    FILINFO fileInfo;
    uint32_t freeClusterNumber;
    uint32_t index;
    uint32_t resultSize;
    //char *testString;
    uint8_t driverNumberBuffer[3];

#if _USE_LFN
    static uint8_t fileNameBuffer[_MAX_LFN];
    fileInfo.lfname = fileNameBuffer;
    fileInfo.lfsize = _MAX_LFN;
#endif /* _USE_LFN */

    /* time delay */
    for (freeClusterNumber = 0; freeClusterNumber < 10000; ++freeClusterNumber)
    {
        __nop();//__NOP();
    }

    usb_echo("............................fatfs Start Read Write file.....................\r\n");

    usb_echo("fatfs mount as logiacal driver %d......", USBDISK);
    sprintf((char *)&driverNumberBuffer[0], "%c:", USBDISK + '0');
    fatfsCode = f_mount(&fatfs, (char const *)&driverNumberBuffer[0], 0);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");

#if (FF_FS_RPATH >= 2)
    fatfsCode = f_chdrive((char const *)&driverNumberBuffer[0]);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
#endif

#if FF_USE_MKFS 
    MKFS_PARM formatOptions;
    formatOptions.fmt = FM_SFD | FM_ANY;
    usb_echo("test f_mkfs......");
    fatfsCode = f_mkfs((char const *)&driverNumberBuffer[0], &formatOptions, testBuffer, FF_MAX_SS);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
#endif /* FF_USE_MKFS */

    usb_echo("test f_getfree:\r\n");
    fatfsCode = f_getfree((char const *)&driverNumberBuffer[0], (DWORD *)&freeClusterNumber, &fs);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    
    if (fs->fs_type == FS_FAT12)
    {
        usb_echo("    FAT type = FAT12\r\n");
    }
    else if (fs->fs_type == FS_FAT16)
    {
        usb_echo("    FAT type = FAT16\r\n");
    }
    else
    {
        usb_echo("    FAT type = FAT32\r\n");
    }
    usb_echo("    bytes per cluster = %d; number of clusters=%lu \r\n", fs->csize * 512, fs->n_fatent - 2);
    usb_echo("    The free size: %dKB, the total size:%dKB\r\n", (freeClusterNumber * (fs->csize) / 2),
             ((fs->n_fatent - 2) * (fs->csize) / 2));

    usb_echo("directory operation:\r\n");
    usb_echo("list root directory:\r\n");
    fatfsCode = USB_HostMsdFatfsListDirectory((char const *)&driverNumberBuffer[0]);
    if (fatfsCode)
    {
        USB_HostMsdFatfsTestDone();
        return;
    }
       
    usb_echo("list root directory:\r\n");
    fatfsCode = USB_HostMsdFatfsListDirectory(_T("1:"));
    if (fatfsCode)
    {
        USB_HostMsdFatfsTestDone();
        return;
    }
       

#if (FF_FS_RPATH >= 2)
    usb_echo("get current directory......");
    fatfsCode = f_getcwd((TCHAR *)&testBuffer[0], 256);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("%s\r\n", testBuffer);
    usb_echo("change current directory to \"dir_1\"......");
    fatfsCode = f_chdir(_T("dir_1"));
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("list current directory:\r\n");
    fatfsCode = USB_HostMsdFatfsListDirectory(_T("."));
    if (fatfsCode)
    {
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("get current directory......");
    fatfsCode = f_getcwd((TCHAR *)&testBuffer[0], 256);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("%s\r\n", testBuffer);
    
#endif

    usb_echo("Read file operation:\r\n");

    fatfsCode = f_open(&file, _T("1:/Config.txt"), FA_READ);  //FA_WRITE | FA_READ | FA_CREATE_ALWAYS
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("file exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }
 

    usb_echo("test f_seek......");
    fatfsCode = f_lseek(&file, 0);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    
    usb_echo("test f_read......");
    fatfsCode = f_read(&file, testBuffer, 101, (UINT *)&resultSize);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    testBuffer[resultSize] = 0;
    usb_echo("%s\r\n", testBuffer);


    usb_echo("Read test f_close......");
    fatfsCode = f_close(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");

//---------------------------------------------------    
    usb_echo("Write file operation:\r\n");

    fatfsCode = f_open(&file, _T("1:/Config.txt"), FA_WRITE | FA_READ);  //FA_WRITE | FA_READ 
    
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("file exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }

    usb_echo("test f_seek......");
    fatfsCode = f_lseek(&file, 0x29);
    
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    
    
    usb_echo("test f_write......");
    for (index = 0; index < 58; ++index)
    {
        testBuffer[index] = 'A' + index;
    }
    testBuffer[58] = '\r';
    testBuffer[59] = '\n';
    

    
    fatfsCode      = f_write(&file, testBuffer, 60, (UINT *)&resultSize);
    if ((fatfsCode) || (resultSize != 60))
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    fatfsCode = f_sync(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    

    usb_echo("change \"Config.txt\" timestamp to Compile time");
     
    fileInfo.fdate = ((uint32_t)(2021 - 1980) << 9 | 12 << 5 | 6);   /* 2015.10.1 */  //(__DATE__);  //
    fileInfo.ftime = (uint32_t)(0x09 << 11 | 00 << 5);                         /* 12:30:00 */  //(__TIME__);  //

    fatfsCode      = f_utime(_T("1:/Config.txt"), &fileInfo);
    
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    
   
    //-------------------------------------------------------------
    //IAP  Read Checksum
       
    usb_echo("IAP Read file operation:\r\n");

    fatfsCode = f_open(&file, _T("1:/Update.bin"), FA_READ);  //FA_WRITE | FA_READ 
    
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("file exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }
    
    usb_echo("get file \"Update.bin\" information:\r\n");
    fatfsCode = f_stat(_T("1:/Update.bin"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    USB_HostMsdFatfsDisplayFileInfo(&fileInfo);
      
    Remaining_size = fileInfo.fsize;
    Packet_Total_lenth = fileInfo.fsize;
    
    usb_echo("get file \"Update.bin\" Transmission length = %d \r\n",Packet_Total_lenth);
    
    Loop_count = 0;
    Calculation_checksum = 0;
    
    while(Remaining_size)  //lopp calculation checksum
    {
        
        if( Remaining_size >=  WRITE_BUFF_SIZE)
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
                
        usb_echo("test f_read......");
        fatfsCode = f_read(&file, Temp_read_buff, Updatepacketsize, (UINT *)&resultSize);
        if (fatfsCode)
        {
            usb_echo("error\r\n");
            f_close(&file);
            USB_HostMsdFatfsTestDone();
            return;
        }
        usb_echo("success\r\n");
        

    
        for(Temp_count=0;Temp_count <Updatepacketsize; Temp_count++)
        {
            Calculation_checksum = Calculation_checksum + Temp_read_buff[Temp_count];
        }


        usb_echo("app iap file f_seek......");
        fatfsCode = f_lseek(&file,(Packet_Total_lenth-Remaining_size));
        
        if (fatfsCode)
        {
            usb_echo("error\r\n");
            f_close(&file);
            USB_HostMsdFatfsTestDone();
            return;
        }
        usb_echo("success\r\n"); 
    
    }
    
    usb_echo("file calculation loop count= %d \r\n",Loop_count);
    usb_echo("file Checksum= %08x \r\n",Calculation_checksum); 
    
    Version_buff[0] = (*((__IO u32 *) (BootJumpFlag)));   //0x4D4D3332
    Version_buff[1] = (*((__IO u32 *) (BootJumpFlag+4))); ////Checksum   
    Version_buff[2] = (*((__IO u32 *) (BootJumpFlag+8))); //

    usb_echo("App Boot JumpFlag %08x %08x %08x \r\n",Version_buff[0],Version_buff[1],Version_buff[2]);  

    if( Version_buff[0] == BOOT_HEAD )
    {
       if(Version_buff[1] != Calculation_checksum)
       {
           
        usb_echo("Clear Boot flag\r\n");   
           
        FLASH_Unlock();
        FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        FLASH_ErasePage(BootJumpFlag);
           
        FLASH_Lock();
           
        usb_echo("App Reast to bootloader\r\n");
           
        NVIC_SystemReset(); //   
           
        while(1)
        {
        }            
           
       }           
    }
 
    
#if _USE_FORWARD && _FS_TINY
    usb_echo("test f_forward......");
    fatfsCode = f_forward(&file, USB_HostMsdFatfsForward, 10, &resultSize);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("\r\n");
#endif
       
    usb_echo("end of file test\r\n");

    USB_HostMsdFatfsTestDone();
}

#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */



/*********************************************************
***函数名：
***函数功能：
***参数：
***返回值：
**********************************************************/
void USB_HostMsdTask(void *arg)
{
    usb_status_t status;
    usb_host_msd_fatfs_instance_t *msdFatfsInstance = (usb_host_msd_fatfs_instance_t *)arg;

    if (msdFatfsInstance->deviceState != msdFatfsInstance->prevDeviceState)
    {
        msdFatfsInstance->prevDeviceState = msdFatfsInstance->deviceState;
        switch (msdFatfsInstance->deviceState)
        {
            case kStatus_DEV_Idle:
                break;

            case kStatus_DEV_Attached: /* deivce is attached and numeration is done */
                status                = USB_HostMsdInit(msdFatfsInstance->deviceHandle,
                                         &msdFatfsInstance->classHandle); /* msd class initialization */
                g_UsbFatfsClassHandle = msdFatfsInstance->classHandle;
                if (status != kStatus_USB_Success)
                {
                    usb_echo("usb host msd init fail\r\n");
                    return;
                }
                msdFatfsInstance->runState = kUSB_HostMsdRunSetInterface;
                break;

            case kStatus_DEV_Detached: /* device is detached */
                msdFatfsInstance->deviceState = kStatus_DEV_Idle;
                msdFatfsInstance->runState    = kUSB_HostMsdRunIdle;
                USB_HostMsdDeinit(msdFatfsInstance->deviceHandle,
                                  msdFatfsInstance->classHandle); /* msd class de-initialization */
                msdFatfsInstance->classHandle = NULL;

                usb_echo("mass storage device detached\r\n");
						
//						    printf("中国\r\n");
						
                break;

            default:
                break;
        }
    }

    /* run state */
    switch (msdFatfsInstance->runState)
    {
        case kUSB_HostMsdRunIdle:
            break;

        case kUSB_HostMsdRunSetInterface: /* set msd interface */
            msdFatfsInstance->runState     = kUSB_HostMsdRunIdle;
            msdFatfsInstance->runWaitState = kUSB_HostMsdRunWaitSetInterface;
            status = USB_HostMsdSetInterface(msdFatfsInstance->classHandle, msdFatfsInstance->interfaceHandle, 0,
                                             USB_HostMsdControlCallback, msdFatfsInstance);
            if (status != kStatus_USB_Success)
            {
                usb_echo("set interface fail\r\n");
            }
            break;

        case kUSB_HostMsdRunMassStorageTest: /* set interface succeed */
#if ((defined MSD_FATFS_THROUGHPUT_TEST_ENABLE) && (MSD_FATFS_THROUGHPUT_TEST_ENABLE))
            USB_HostMsdFatfsThroughputTest(msdFatfsInstance); /* test throughput */
#else
//            USB_HostMsdFatfsTest(msdFatfsInstance); /* test msd device */
              USB_HostMsdFatfsUserReadWrite(msdFatfsInstance); //mm32        
#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */
            msdFatfsInstance->runState = kUSB_HostMsdRunIdle;
            break;

        default:
            break;
    }
}

usb_status_t USB_HostMsdEvent(usb_device_handle deviceHandle,
                              usb_host_configuration_handle configurationHandle,
                              uint32_t eventCode)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_configuration_t *configuration;
    uint8_t interfaceIndex;
    usb_host_interface_t *interface;
    uint32_t infoValue;
    uint8_t id;

    switch (eventCode)
    {
        case kUSB_HostEventAttach:
            /* judge whether is configurationHandle supported */
            configuration = (usb_host_configuration_t *)configurationHandle;
            for (interfaceIndex = 0; interfaceIndex < configuration->interfaceCount; ++interfaceIndex)
            {
                interface = &configuration->interfaceList[interfaceIndex];
                id        = interface->interfaceDesc->bInterfaceClass;
                if (id != USB_HOST_MSD_CLASS_CODE)
                {
                    continue;
                }
                id = interface->interfaceDesc->bInterfaceSubClass;
                if ((id != USB_HOST_MSD_SUBCLASS_CODE_UFI) && (id != USB_HOST_MSD_SUBCLASS_CODE_SCSI))
                {
                    continue;
                }
                id = interface->interfaceDesc->bInterfaceProtocol;
                if (id != USB_HOST_MSD_PROTOCOL_BULK)
                {
                    continue;
                }
                else
                {
                    if (g_MsdFatfsInstance.deviceState == kStatus_DEV_Idle)
                    {
                        /* the interface is supported by the application */
                        g_MsdFatfsInstance.deviceHandle    = deviceHandle;
                        g_MsdFatfsInstance.interfaceHandle = interface;
                        g_MsdFatfsInstance.configHandle    = configurationHandle;
                        return kStatus_USB_Success;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            status = kStatus_USB_NotSupported;
            break;

        case kUSB_HostEventNotSupported:
            break;

        case kUSB_HostEventEnumerationDone:
            if (g_MsdFatfsInstance.configHandle == configurationHandle)
            {
                if ((g_MsdFatfsInstance.deviceHandle != NULL) && (g_MsdFatfsInstance.interfaceHandle != NULL))
                {
                    /* the device enumeration is done */
                    if (g_MsdFatfsInstance.deviceState == kStatus_DEV_Idle)
                    {
                        g_MsdFatfsInstance.deviceState = kStatus_DEV_Attached;

                        USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDevicePID, &infoValue);
                        usb_echo("mass storage device attached:pid=0x%x", infoValue);
                        USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceVID, &infoValue);
                        usb_echo("vid=0x%x ", infoValue);
                        USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceAddress, &infoValue);
                        usb_echo("address=%d\r\n", infoValue);
                    }
                    else
                    {
                        usb_echo("not idle msd instance\r\n");
                        status = kStatus_USB_Error;
                    }
                }
            }
            break;

        case kUSB_HostEventDetach:
            if (g_MsdFatfsInstance.configHandle == configurationHandle)
            {
                /* the device is detached */
                g_UsbFatfsClassHandle           = NULL;
                g_MsdFatfsInstance.configHandle = NULL;
                if (g_MsdFatfsInstance.deviceState != kStatus_DEV_Idle)
                {
                    g_MsdFatfsInstance.deviceState = kStatus_DEV_Detached;
                }
            }
            break;

        default:
            break;
    }
    return status;
}


#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
usb_status_t USB_HostTestEvent(usb_device_handle deviceHandle,
                               usb_host_configuration_handle configurationHandle,
                               uint32_t eventCode)
{
    /* process the same supported device that is identified by configurationHandle */
    static usb_host_configuration_handle s_ConfigHandle = NULL;
    static usb_device_handle s_DeviceHandle             = NULL;
    static usb_host_interface_handle s_InterfaceHandle  = NULL;
    usb_status_t status                                 = kStatus_USB_Success;
    usb_host_configuration_t *configuration;
    uint8_t interfaceIndex;
    usb_host_interface_t *interface;
    uint32_t id;

    switch (eventCode)
    {
        case kUSB_HostEventAttach:
            /* judge whether is configurationHandle supported */
            configuration = (usb_host_configuration_t *)configurationHandle;
            for (interfaceIndex = 0; interfaceIndex < configuration->interfaceCount; ++interfaceIndex)
            {
                interface = &configuration->interfaceList[interfaceIndex];
                USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceVID, &id);
                if (id == 0x1a0a) /* certification Vendor ID */
                {
                    usb_echo("cetification test device VID match\r\n");
                    s_DeviceHandle    = deviceHandle;
                    s_InterfaceHandle = interface;
                    s_ConfigHandle    = configurationHandle;
                    return kStatus_USB_Success;
                }
            }
            status = kStatus_USB_NotSupported;
            break;

        case kUSB_HostEventNotSupported:
            usb_echo("Unsupported Device\r\n");
            break;

        case kUSB_HostEventEnumerationDone:
            if (s_ConfigHandle == configurationHandle)
            {
                USB_HostTestModeInit(s_DeviceHandle);
            }
            break;

        case kUSB_HostEventDetach:
            if (s_ConfigHandle == configurationHandle)
            {
                usb_echo("PET test device detach\r\n");
                USB_HostCloseDeviceInterface(s_DeviceHandle, s_InterfaceHandle);
                /* the device is detached */
                s_DeviceHandle    = NULL;
                s_InterfaceHandle = NULL;
                s_ConfigHandle    = NULL;
            }
            break;

        default:
            break;
    }
    return status;
}
#endif
