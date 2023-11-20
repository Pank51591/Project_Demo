#ifndef __BSP_INTERNAL_FLASH_H
#define	__BSP_INTERNAL_FLASH_H
#include "hal_data.h"
#include "stdio.h"


// FLASH模块的调试信息输出控制
#define CODE_FLASH_PRINTF_ENABLE            1
#if (1 == CODE_FLASH_PRINTF_ENABLE)
  #define CODE_FLASH_PRINTF(format, ...)    printf("[Code FLASH Operation] "format"\r\n", ##__VA_ARGS__)
#else
  #define CODE_FLASH_PRINTF(format, ...)
#endif

#define DATA_FLASH_PRINTF_ENABLE            1
#if (1 == DATA_FLASH_PRINTF_ENABLE)
  #define DATA_FLASH_PRINTF(format, ...)    printf("[Data FLASH Operation] "format"\r\n", ##__VA_ARGS__)
#else
  #define DATA_FLASH_PRINTF(format, ...)
#endif


/* Code Flash */
#define FLASH_CF_BLOCK0             (0x00000000)        /*   2 KB: 0x00000000 - 0x000007FF */
#define FLASH_CF_BLOCK_SIZE         ((2) * (1024))
#define FLASH_CF_BLOCK(x)           ((FLASH_CF_BLOCK0) + FLASH_CF_BLOCK_SIZE * (uint32_t)(x))

/* Data Flash */
#define FLASH_DF_BLOCK0             (0x40100000)        /*   1 KB: 0x40100000 - 0x401003FF */
#define FLASH_DF_BLOCK_SIZE         ((1) * (1024))
#define FLASH_DF_BLOCK(x)           ((FLASH_DF_BLOCK0) + FLASH_DF_BLOCK_SIZE * (uint32_t)(x))


/* CODE FLASH 测试 */
#define CODE_FLASH_TEST_BLOCK       FLASH_CF_BLOCK(63)  /* 避免覆盖程序代码数据 */
#define CODE_FLASH_TEST_DATA_SIZE   128                 /* 仅测试128个字节数据 */
/* DATA FLASH 测试 */
#define DATA_FLASH_TEST_BLOCK       FLASH_DF_BLOCK(0)
#define DATA_FLASH_TEST_DATA_SIZE   32                  /* 仅测试32个字节数据 */


void FLASH_LP_Init(void);
void FLASH_LP_CodeFlash_Operation(void);
void FLASH_LP_DataFlash_Operation(void);
void FLASH_LP_DataFlash_BGO_Operation(void);

#endif
