/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_sci_uart.h"
#include "r_uart_api.h"
#include "r_ctsu.h"
#include "r_ctsu_api.h"
#include "rm_touch.h"
#include "rm_touch_api.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
/** UART on SCI Instance. */
extern const uart_instance_t g_uart_qe;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart_qe_ctrl;
extern const uart_cfg_t g_uart_qe_cfg;
extern const sci_uart_extended_cfg_t g_uart_qe_cfg_extend;

#ifndef touch_uart_callback
void touch_uart_callback(uart_callback_args_t *p_args);
#endif
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
