/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        #if __has_include("r_ioport.h")
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [1] = ctsu_write_isr, /* CTSU WRITE (Write request interrupt) */
            [2] = ctsu_read_isr, /* CTSU READ (Measurement data transfer request interrupt) */
            [3] = ctsu_end_isr, /* CTSU END (Measurement end interrupt) */
            [4] = sci_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [5] = sci_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [6] = sci_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [7] = sci_uart_eri_isr, /* SCI0 ERI (Receive error) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_GPT0_COUNTER_OVERFLOW), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_CTSU_WRITE), /* CTSU WRITE (Write request interrupt) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_CTSU_READ), /* CTSU READ (Measurement data transfer request interrupt) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_CTSU_END), /* CTSU END (Measurement end interrupt) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_SCI0_RXI), /* SCI0 RXI (Receive data full) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TXI), /* SCI0 TXI (Transmit data empty) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TEI), /* SCI0 TEI (Transmit end) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_SCI0_ERI), /* SCI0 ERI (Receive error) */
        };
        #elif __has_include("r_ioport_b.h")
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_IRQ_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
            [BSP_PRV_IELS_ENUM(GPT0_COUNTER_OVERFLOW)] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [BSP_PRV_IELS_ENUM(CTSU_WRITE)] = ctsu_write_isr, /* CTSU WRITE (Write request interrupt) */
            [BSP_PRV_IELS_ENUM(CTSU_READ)] = ctsu_read_isr, /* CTSU READ (Measurement data transfer request interrupt) */
            [BSP_PRV_IELS_ENUM(CTSU_END)] = ctsu_end_isr, /* CTSU END (Measurement end interrupt) */
            [BSP_PRV_IELS_ENUM(SCI0_RXI)] = sci_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [BSP_PRV_IELS_ENUM(SCI0_TXI)] = sci_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [BSP_PRV_IELS_ENUM(SCI0_TEI)] = sci_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [BSP_PRV_IELS_ENUM(SCI0_ERI)] = sci_uart_eri_isr, /* SCI0 ERI (Receive error) */
        };
        #endif
        #endif
