#ifndef DRVI2C_H
#define DRVI2C_H
 

void IIC_Init(void);

INT8U I2C_ReadKey(void);

void I2C_SendDisplay(INT8U *pdat,INT8U len);


#endif

