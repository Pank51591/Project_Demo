#include "hal_data.h"
#include "led/bsp_led.h"
#include "key/bsp_key.h"
#include "eeprom/i2c_ee.h"
#include "debug_uart/bsp_debug_uart.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER


void hal_entry(void)
{

    I2C_EE_Init();
    Debug_UART4_Init();

    printf("欢迎使用野火启明2L1开发板\n");
    printf("这是一个I2C外设(AT24C02)读写测试例程\n");
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_SECONDS);

    while (1)
    {
        I2C_EE_Writedrase();
        if (I2C_Test() == 1)
        {
            LED3_ON;
        }
        else
        {
            LED1_ON;
        }

        while (1);
    }

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
        R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable()
{

}
#endif
