#include "./ap3216c/ap3216c.h"
#include "bsp_SysTick.h"  
#include "stm32f10x.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include <string.h>


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  /**/
  float ALS;
  uint16_t PS;
  uint16_t IR;
  uint8_t IntStatus;
  
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
 
  
  printf(" 芯片初始化中.....\n");
  /* 初始化 光照传感器 */
  ap3216c_init();

  while(1)    
  {
    IntStatus = ap3216c_get_IntStatus();    // 先读状态位，读ADC数据位会清除状态位（默认设置）
    ALS = ap3216c_read_ambient_light();
    PS = ap3216c_read_ps_data();
    IR = ap3216c_read_ir_data();

    printf("\n光照强度是：%.2fLux\n红外强度是：%d\n", ALS, IR);

    if (PS == 55555)    // IR 太强 PS 数据无效
      printf("IR 太强 PS 数据无效\n");
    else
    {
      printf("接近距离是：%d\n", PS & 0x3FF);
    }
    
    if (AP_INT_Read() == 0)
      printf("有中断产生\n");
    
    if ((PS >> 15) & 1)
      printf("物体接近\n");
    else
      printf("物体远离\n");
    
    if (IntStatus & 0x1)
      printf("ALS 产生中断\n");
    
    if (IntStatus >> 1 & 0x1)
      printf("PS 产生中断\n");
    
    SysTick_Delay_Ms(400);
  }
}


/*********************************************END OF FILE**********************/
