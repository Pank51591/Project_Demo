#ifndef M0FLASH_H
#define M0FLASH_H




#define FLASH_BEGIN_ADDR 0x1D400 //0x0001f000ul //FLASHÊ×µØÖ·





void FlashWrite(INT32U addr,INT8U *pbuff,INT16U len);

void FlashRead(INT32U addr,INT8U *pbuff,INT16U len);








#endif

