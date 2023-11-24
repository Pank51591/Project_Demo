#include "bsp_key_irq.h"

/* KEY 外部中断初始化函数 */
void Key_IRQ_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Open ICU module */
    err = R_ICU_ExternalIrqOpen(&g_external_irq7_ctrl, &g_external_irq7_cfg);
    err = R_ICU_ExternalIrqOpen(&g_external_irq2_ctrl, &g_external_irq2_cfg);
    /* 允许中断 */
    err = R_ICU_ExternalIrqEnable(&g_external_irq7_ctrl);
    err = R_ICU_ExternalIrqEnable(&g_external_irq2_ctrl);
}


/* 按键按下标志 */
volatile bool key1_sw2_press = false;
volatile bool key2_sw3_press = false;

/* 按键中断回调函数 */
void key_external_irq_callback(external_irq_callback_args_t *p_args)
{
    /* 判断中断通道 */
    if (7 == p_args->channel)
    {
        key1_sw2_press = true;   // 按键KEY1_SW2按下
    }
    else if (2 == p_args->channel)
    {
        key2_sw3_press = true;   // 按键KEY2_SW3按下
    }
}
