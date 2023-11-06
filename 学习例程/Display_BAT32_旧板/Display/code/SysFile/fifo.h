#ifndef FIFO_H
#define FIFO_H

#include"typedef.h"

void fifo_init(void);
INT8U fifo_is_full(void);
INT8U fifo_empty(void);
void fifo_clean_all(void);
INT32U fifo_get_size(void);
INT8U fifo_append_one(INT8U frame_data);
INT32U fifo_read_strings(INT8U *Pdata, INT32U pdata_len);
INT32U fifo_pop(INT32U pdata_len);

INT16U Uart_data_handle(INT8U *buff);


#endif
