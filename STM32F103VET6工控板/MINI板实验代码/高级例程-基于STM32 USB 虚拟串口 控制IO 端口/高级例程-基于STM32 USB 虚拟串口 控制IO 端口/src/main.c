/****************************************
 * 文件名  ：main.c
 * 描述    ：通过虚拟串口，利用串口调试软件或超级终端发送控制命令给板子，控制板子上LED。         
 * 实验平台：MINI STM32开发板 基于STM32F103VET6
 * 库版本  ：ST3.2.1  																										  
*********************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "stm32f10x_tim.h"
#include "platform_config.h"


u16 ad;	
u32 adzhi = 0; 
u16 time = 0;
extern u16 count_out;
extern uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];

/*************************************************
函数: void RCC_Configuration(void)
功能: 复位和时钟控制 配置
参数: 无
返回: 无
**************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;                    //定义外部高速晶体启动状态枚举变量
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_DeInit();                                    //复位RCC外部设备寄存器到默认值
  RCC_HSEConfig(RCC_HSE_ON);                       //打开外部高速晶振
  HSEStartUpStatus = RCC_WaitForHSEStartUp();      //等待外部高速时钟准备好
  if(HSEStartUpStatus == SUCCESS)                  //外部高速时钟已经准别好
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //开启FLASH预读缓冲功能，加速FLASH的读取。所有程序中必须的用法.位置：RCC初始化子函数里面，时钟起振之后
    FLASH_SetLatency(FLASH_Latency_2);                    //flash操作的延时
      	
    RCC_HCLKConfig(RCC_SYSCLK_Div1);               //配置AHB(HCLK)时钟等于==SYSCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);                //配置APB2(PCLK2)钟==AHB时钟
    RCC_PCLK1Config(RCC_HCLK_Div2);                //配置APB1(PCLK1)钟==AHB1/2时钟
         
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //配置PLL时钟 == 外部高速晶体时钟 * 9 = 72MHz
    RCC_PLLCmd(ENABLE);                                   //使能PLL时钟
   
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //等待PLL时钟就绪
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //配置系统时钟 = PLL时钟
    while(RCC_GetSYSCLKSource() != 0x08)                  //检查PLL时钟是否作为系统时钟
    {
    }
  }
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    //允许AFIO时钟

  /* Enable USB_DISCONNECT GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);

  /* Configure USB pull-up pin */
  GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);

   /* Enable GPIOA, GPIOD and USART1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
}





int main(void)
{
  	

  RCC_Configuration();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
  GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ); //关闭3个LED
   

  while (1)
  {

   
	if (count_out != 0)	//判断有无数据接收到
    {  
	  
      
	  if(USB_Rx_Buffer[0]==0x01){GPIO_ResetBits(GPIOB, GPIO_Pin_14 );
	                          USB_Send_string("LED1 点亮  \r\n");
							  
							  count_out=0;
							 }	//如果接收到的输出是0X01，点亮led1
	  if(USB_Rx_Buffer[0]==0x02){GPIO_ResetBits(GPIOB, GPIO_Pin_12 );
	                          USB_Send_string("LED2 点亮\r\n");
							  count_out=0;
							  }	
							  //如果接收到的输出是0X02，点亮led2
	  if(USB_Rx_Buffer[0]==0x03){GPIO_ResetBits(GPIOB, GPIO_Pin_13 );
	                          USB_Send_string("LED3 点亮\r\n");
							  count_out=0;
							  }	
							  //如果接收到的输出是0X03，点亮led3
	  if(USB_Rx_Buffer[0]==0x04){GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 );
	                          USB_Send_string("LED 全灭\r\n");
							  count_out=0;
							  } //如果接收到的输出是0X04，//关闭3个LED  
    }         
        
      
       		  
  }
}

