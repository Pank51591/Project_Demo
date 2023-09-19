/****************************************
 * 文件名  ：main.c
 * 描述    ：按接收指令把采集的数据通过CAN总线发送给主机         
 * 实验平台：MINI STM32开发板 基于STM32F103VET6
 * 库版本  ：ST3.0.0
**********************************************************************************/

#include "stm32f10x.h"
#include "can.h" 
#include "adc.h"       

#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_12)

extern __IO u16 ADC_ConvertedValue;
extern u16  After_filter[M];  
extern u8 FABIAO;
// 软件延时
void Delay(unsigned long time)
{unsigned long i,j;
  
	for(j=0; j<time; j++)
	{
	   for(i=0;i<12000;i++);
	}
}

int main(void)
{ 
  u32 AD_value1=0;
  u32 AD_value2=0;
  u32 AD_value3=0;
  u32 AD_value4=0;
  FABIAO=0;	       
  SystemInit();	/* 配置系统时钟为72M */  
  ADC1_Init(); /* 初始化ADC1 */
  CAN_GPIO_Config();//CAN管脚初始化
  CAN_NVIC_Configuration(); //CAN中断初始化   
  CAN_INIT();//CA初始化N模块  

  while (1)
  {
       Delay(100); // 100MS间隔时间
	   filter();
	   AD_value1  = 3300000/4096*After_filter[0]/1000;
	   AD_value2  = 3300000/4096*After_filter[1]/1000;
	   AD_value3  = 3300000/4096*After_filter[2]/1000;
	   AD_value4  = 3300000/4096*After_filter[3]/1000;
	   if(FABIAO==0xff)
	   {can_tx(AD_value1,AD_value2,AD_value3,AD_value4);
	    FABIAO=0x00;
	   }	   
	   LED1_TOGGLE;

	    
       
  }
}



