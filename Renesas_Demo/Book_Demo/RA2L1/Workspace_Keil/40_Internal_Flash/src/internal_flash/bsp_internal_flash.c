#include "bsp_internal_flash.h"


void FLASH_LP_Init(void)
{
    /* 打开 Flash_HP */
    fsp_err_t err = R_FLASH_LP_Open(&g_flash_ctrl, &g_flash_cfg);
    /* 处理错误 */
    if (FSP_SUCCESS != err)
    {
        printf("Flash_LP_Open API failed!\r\n");
        printf("Returned Error Code: 0x%x\r\n", err);
        while(1);
    }
}


volatile bool flash_interrupt_called  = false;
flash_event_t flash_event;

/* DATA FLASH 操作完成中断回调 */
void flash_callback(flash_callback_args_t *p_args)
{
    flash_interrupt_called  = true;
    flash_event = p_args->event;
}



/* Code Flash 操作函数 */
void FLASH_LP_CodeFlash_Operation(void)
{
    fsp_err_t err;
    flash_result_t blank_check_result = FLASH_RESULT_BLANK;
    uint8_t write_buffer[CODE_FLASH_TEST_DATA_SIZE] = {0};
    uint8_t read_buffer[CODE_FLASH_TEST_DATA_SIZE] = {0};
    uint8_t index;


    /* 写入测试数据到 write_buffer */
    for (index = 0; index < CODE_FLASH_TEST_DATA_SIZE; index++)
    {
        write_buffer[index] = (uint8_t) ('A' + (index % 26));
    }

    CODE_FLASH_PRINTF("擦除 Code Flash");
    
    /* 禁用中断，以避免P/E过程中产生中断导致操作失败
       注：这里禁用中断后，不能使用串口打印 */
    /* Disable interrupts to prevent vector table access while code flash is in P/E mode. */
    __disable_irq();
    /* Erase 1 block of data flash starting at block 0. */
    err = R_FLASH_LP_Erase(&g_flash_ctrl, CODE_FLASH_TEST_BLOCK, 1);
    /* Enable interrupts after code flash operations are complete. */
    __enable_irq();
    /* Error Handle */
    if (FSP_SUCCESS != err)
    {
        CODE_FLASH_PRINTF("Erase API failed");
        CODE_FLASH_PRINTF("Returned Error Code: 0x%x", err);
        while(1);
    }
    CODE_FLASH_PRINTF("Erase successful");


    /** 空白检查：擦除 Code Flash 完成后，进行空白检查
     *  发送 FACI 命令（Blank Check），对 Code Flash 进行空白检查
     */
    err = R_FLASH_LP_BlankCheck(&g_flash_ctrl, CODE_FLASH_TEST_BLOCK, CODE_FLASH_TEST_DATA_SIZE, &blank_check_result);
    /* Error Handle */
    if (FSP_SUCCESS != err)
    {
        CODE_FLASH_PRINTF("BlankCheck API failed");
        CODE_FLASH_PRINTF("Returned Error Code: 0x%x", err);
        while(1);
    }
    CODE_FLASH_PRINTF("BlankCheck API Successful");

    /* 验证空白检查的结果 */
    if (FLASH_RESULT_BLANK == blank_check_result)
    {
        CODE_FLASH_PRINTF("Flash块是空白的");
    }
    else if (FLASH_RESULT_NOT_BLANK == blank_check_result)
    {
        CODE_FLASH_PRINTF("Flash块不是空白的，不要向其中写入数据");
        while(1);
    }


    /* 写入测试数据到 Code Flash */
    CODE_FLASH_PRINTF("写入 Code Flash: ");
    /* Disable interrupts to prevent vector table access while code flash is in P/E mode. */
    __disable_irq();
    err = R_FLASH_LP_Write(&g_flash_ctrl, (uint32_t)write_buffer, CODE_FLASH_TEST_BLOCK, CODE_FLASH_TEST_DATA_SIZE);
    /* Enable interrupts after code flash operations are complete. */
    __enable_irq();
    /* Error Handle */
    if (FSP_SUCCESS != err)
    {
        CODE_FLASH_PRINTF("Write API failed");
        CODE_FLASH_PRINTF("Returned Error Code: %d", err);
        while(1);
    }
    CODE_FLASH_PRINTF("Writing flash data is successful");


    /* 读取 Code Flash 数据 */
    memcpy(read_buffer, (uint8_t *) CODE_FLASH_TEST_BLOCK, CODE_FLASH_TEST_DATA_SIZE);
    CODE_FLASH_PRINTF("打印 read_buffer 里的%d字节测试数据：", CODE_FLASH_TEST_DATA_SIZE);
    for (index = 0; index < CODE_FLASH_TEST_DATA_SIZE; index++)
    {
        printf("%c ", read_buffer[index]);
    }
    printf("\r\nEnd.\r\n");


    /* 对比 write_buffer 和 read_buffer 数据 */
    if (0 == memcmp(read_buffer, write_buffer, CODE_FLASH_TEST_DATA_SIZE))
    {
        CODE_FLASH_PRINTF("数据对比一致，Code Flash 测试成功\r\n");
    }
    else
    {
        CODE_FLASH_PRINTF("数据对比不一致，Code Flash 测试失败\r\n");
        while(1);
    }
}




/* Data Flash 操作函数 */
void FLASH_LP_DataFlash_Operation(void)
{
    fsp_err_t err;
    flash_result_t blank_check_result = FLASH_RESULT_BLANK;
    uint8_t write_buffer[DATA_FLASH_TEST_DATA_SIZE] = {0};
    uint8_t read_buffer[DATA_FLASH_TEST_DATA_SIZE] = {0};
    uint8_t index;

    /* 写入测试数据到 write_buffer */
    for (index = 0; index < DATA_FLASH_TEST_DATA_SIZE; index++)
    {
        write_buffer[index] = (uint8_t) ('A' + (index % 26));
    }

    /* 擦除 Data Flash */
    DATA_FLASH_PRINTF("擦除 Data Flash");
    /* Erase 1 block of data flash starting at block 0. */
    err = R_FLASH_LP_Erase(&g_flash_ctrl, DATA_FLASH_TEST_BLOCK, 1);
    /* Error Handle */
    if (FSP_SUCCESS != err)
    {
        DATA_FLASH_PRINTF("Erase API failed");
        DATA_FLASH_PRINTF("Returned Error Code: %d", err);
        while(1);
    }
    DATA_FLASH_PRINTF("Erase API successful");


    while (!flash_interrupt_called)
    {
        ;
    }
    flash_interrupt_called = false;
    DATA_FLASH_PRINTF("Erase successful");


    /* 空白检查：擦除 Data Flash 完成后，进行空白检查 */
    /* Check if block 0 is erased. */
    err = R_FLASH_LP_BlankCheck(&g_flash_ctrl, DATA_FLASH_TEST_BLOCK, FLASH_DF_BLOCK_SIZE, &blank_check_result);
    /* Error Handle */
    if (FSP_SUCCESS != err)
    {
        DATA_FLASH_PRINTF("BlankCheck API failed");
        DATA_FLASH_PRINTF("Returned Error Code: %d", err);
        while(1);
    }
    DATA_FLASH_PRINTF("BlankCheck API Successful");

    /* 验证空白检查的结果 */
    if (FLASH_RESULT_BLANK == blank_check_result)
    {
        DATA_FLASH_PRINTF("Flash块是空白的");
    }
    else if (FLASH_RESULT_NOT_BLANK == blank_check_result)
    {
        DATA_FLASH_PRINTF("Flash块不是空白的，不要向其中写入数据");
        while(1);
    }

    /* 写入测试数据到 Data Flash */
    DATA_FLASH_PRINTF("写入 Data Flash: ");
    err = R_FLASH_LP_Write(&g_flash_ctrl, (uint32_t)write_buffer, DATA_FLASH_TEST_BLOCK, DATA_FLASH_TEST_DATA_SIZE);
    /* Error Handle */
    if (FSP_SUCCESS != err)
    {
        DATA_FLASH_PRINTF("Write API failed");
        DATA_FLASH_PRINTF("Returned Error Code: %d", err);
        while(1);
    }

    flash_status_t status;
    /* Wait until the current flash operation completes. */
    do
    {
        err = R_FLASH_LP_StatusGet(&g_flash_ctrl, &status);
    } while ((FSP_SUCCESS == err) && (FLASH_STATUS_BUSY == status));

    DATA_FLASH_PRINTF("Writing flash data is successful");


    /* 读取 DATA Flash 数据 */
    memcpy(read_buffer, (uint8_t *) DATA_FLASH_TEST_BLOCK, DATA_FLASH_TEST_DATA_SIZE);
    DATA_FLASH_PRINTF("打印 read_buffer 里的%d字节测试数据：", DATA_FLASH_TEST_DATA_SIZE);
    for (index = 0; index < DATA_FLASH_TEST_DATA_SIZE; index++)
    {
        printf("%c ", read_buffer[index]);
    }
    printf("\r\nEnd.\r\n");


    /* 对比 write_buffer 和 read_buffer 数据 */
    if (0 == memcmp(read_buffer, write_buffer, DATA_FLASH_TEST_DATA_SIZE))
    {
        DATA_FLASH_PRINTF("数据对比一致，Data Flash 测试成功\r\n");
    }
    else
    {
        DATA_FLASH_PRINTF("数据对比不一致，Data Flash 测试失败\r\n");
        while(1);
    }
}






