#include "hal_data.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER


/* IOPORT模块头文件 （自己写库——构建库函数雏形） */
#include "ioport/ra_ioport.h"


/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */

    /* 调用取消写保护函数 */
    IOPORT_PinAccessEnable();


    /* 使用 IOPORT 初始化结构体和调用初始化函数来配置PFS寄存器 */
    IOPORT_Init_t led_io_init;
    led_io_init.Port = IO_PORT_04;
    led_io_init.Pin = IO_PIN_03;
    led_io_init.Mode = IO_MODE_GPIO;    //普通GPIO模式，而不是复用功能模式或其他的
    led_io_init.Dir = IO_DIR_OUTPUT;
    led_io_init.OType = IO_OTYPE_PP;
    led_io_init.Drive = 0x00;           //<* 注：RA2L1 没有输出驱动能力选项 *>
    led_io_init.Level = IO_LEVEL_HIGH;  //输出高电平（LED熄灭）
    //LED_IO_Init.Pull = IO_NO_PULL; //端口方向处于输出模式下是用不了上拉的，所以这个属性没意义
    IOPORT_Init(&led_io_init); //调用初始化函数，进行 LED1 引脚初始化

    led_io_init.Pin = IO_PIN_04; //更换引脚号
    IOPORT_Init(&led_io_init); //结构体其他属性不变，再次调用初始化函数，进行 LED2 引脚初始化

    led_io_init.Pin = IO_PIN_05; //更换引脚号
    IOPORT_Init(&led_io_init); //结构体其他属性不变，再次调用初始化函数，进行 LED3 引脚初始化


    /** 此时3个LED灯的引脚默认输出的是高电平，所以3个LED灯都会默认不亮
     *  我们先打开所有LED灯，然后在 while 循环里让 LED1 闪烁：每秒钟翻转一次状态
     */
    IOPORT_PinWrite(IO_PORT_04, IO_PIN_03, IO_LEVEL_LOW); //点亮LED1
    IOPORT_PinWrite(IO_PORT_04, IO_PIN_04, IO_LEVEL_LOW); //点亮LED2
    IOPORT_PinWrite(IO_PORT_04, IO_PIN_05, IO_LEVEL_LOW); //点亮LED3

    while(1)
    {
        /* 使用库函数 IOPORT_PinToggle 翻转 LED1 引脚电平 */
        IOPORT_PinToggle(IO_PORT_04, IO_PIN_03);
        /* 使用延时函数进行延时：此处延时 1000 毫秒 */
        R_BSP_SoftwareDelay(1000, BSP_DELAY_UNITS_MILLISECONDS);
    }


    //这后面的代码无需理会
#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, g_ioport.p_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
#endif