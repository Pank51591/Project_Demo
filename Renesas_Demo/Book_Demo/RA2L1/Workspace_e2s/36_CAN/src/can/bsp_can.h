#ifndef __BSP_CAN_H
#define	__BSP_CAN_H
#include "hal_data.h"
#include "stdio.h"


// CAN模块的调试信息输出控制
#define CAN_DEBUG                    1
#if (1 == CAN_DEBUG)
  #define CAN_MSG_PRINTF(format, ...)  printf("[CAN Operation] "format"\r\n", ##__VA_ARGS__)
#else
  #define CAN_MSG_PRINTF(format, ...)
#endif


#define WAIT_TIME                       (5000U)            //wait time value
#define CAN_DESTINATION_MAILBOX_3       (3U)               //destination mail box number
#define CAN_MAILBOX_NUMBER_0            (0U)               //mail box number
#define CAN_FRAME_TRANSMIT_DATA_BYTES   (8U)               //data length


void CAN_Init(void);
void CAN_Operation(void);

#endif
