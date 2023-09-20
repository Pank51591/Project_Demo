#ifndef DRV_LCD1602
#define DRV_LCD1602









void LcdInit(void);	

void LcdWriteStrimg(uchar page,INT8U col,INT8S *str);
void LCDWtireCGRAM(void);



#endif

