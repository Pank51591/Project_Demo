/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022, Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#include "tusb.h"
#include "stdio.h"
//#include "bsp/board_api.h"

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+

uint32_t Loop_cnt = 0;
uint8_t tx_count = 0;
uint8_t txbuf[64+1]; // +1 for extra null character
//------------- IMPLEMENTATION -------------//


/*********************************************************
***函数名：
***函数功能：
***参数：
***返回值：
**********************************************************/
void cdc_app_task(void)
{
    
   Loop_cnt++;
   if(Loop_cnt>100000)
   {  
        Loop_cnt = 0;
       
        uint32_t const bufsize = sizeof(txbuf)-1;

        uint32_t count = 0x20;

        memset(txbuf,0x12,sizeof(txbuf));
        txbuf[0] = tx_count;
        tx_count++;
        if ( tuh_cdc_mounted(0) )
        {
            printf("Write data to com...\r\n");
            
            // console --> cdc interfaces
            if (count)
            {
                tuh_cdc_write(0, txbuf, count);
                tuh_cdc_write_flush(0);
            }
        }    
    }

}

uint8_t rxbuf[64+1]; // +1 for extra null character

// Invoked when received new data
void tuh_cdc_rx_cb(uint8_t idx)
{
  uint8_t temp_cnt = 0;
    

  uint32_t const bufsize = sizeof(rxbuf)-1;

  // forward cdc interfaces -> console
  uint32_t count = tuh_cdc_read(idx, rxbuf, bufsize);
    
  printf("tuh_cdc_rx_cb %x -->> ",idx);
    
  printf(" Read data from com = %d -->>",count);
  for(temp_cnt=0;temp_cnt<count;temp_cnt++)
  {
      printf(" %x ",rxbuf[temp_cnt]);
  }
  printf("\r\n");


}


/*********************************************************
***函数名：
***函数功能：
***参数：
***返回值：
**********************************************************/
void tuh_cdc_mount_cb(uint8_t idx)
{
  tuh_itf_info_t itf_info = { 0 };
  tuh_cdc_itf_get_info(idx, &itf_info);

  printf("CDC Interface is mounted: address = %u, itf_num = %u\r\n", itf_info.daddr, itf_info.desc.bInterfaceNumber);

#ifdef CFG_TUH_CDC_LINE_CODING_ON_ENUM
  // CFG_TUH_CDC_LINE_CODING_ON_ENUM must be defined for line coding is set by tinyusb in enumeration
  // otherwise you need to call tuh_cdc_set_line_coding() first
  cdc_line_coding_t line_coding = { 0 };
  if ( tuh_cdc_get_local_line_coding(idx, &line_coding) )
  {
    printf("  Baudrate: %lu, Stop Bits : %u\r\n", line_coding.bit_rate, line_coding.stop_bits);
    printf("  Parity  : %u, Data Width: %u\r\n", line_coding.parity  , line_coding.data_bits);
  }
#endif
}

/*********************************************************
***函数名：
***函数功能：
***参数：
***返回值：
**********************************************************/
void tuh_cdc_umount_cb(uint8_t idx)
{
  tuh_itf_info_t itf_info = { 0 };
  tuh_cdc_itf_get_info(idx, &itf_info);

  printf("CDC Interface is unmounted: address = %u, itf_num = %u\r\n", itf_info.daddr, itf_info.desc.bInterfaceNumber);
}
