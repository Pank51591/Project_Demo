/****************************************
 * 文件名  ：main.c
 * 描述    ：通过虚拟串口，采集板子上的电压值，显示到串口调试软件或超级终端上。         
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

u8 comm = 0;
u8 ah,al;
u16 ad;	
u32 adzhi = 0;

u16 time = 0;

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
}

/*******************************************************************************
	函数名：ADC_Configuration
	输  入:
	输  出:
	功能说明：配置ADC, PC0
*/
static void ADC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	volatile u16 ADCConvertedValue;

    /* 使能 ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOB, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);              //72M/6=12,ADC最大时间不能超过14M

	
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB端口
  GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);	 // 关闭所有LED

	/* 配置PC0为模拟输入(ADC Channel10) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 配置ADC1, 不用DMA, 用软件自己触发 */
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		 //ADC1工作模式:独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		 //单次转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	  //转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	 //ADC1数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	   //顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);		   //根据ADC_InitStruct中指定的参数，初始化外设ADC1的寄存器

	/* ADC1 regular channel10 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);	//ADC1,ADC通道10,规则采样顺序值为1,采样时间为239.5周期

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);		  //使能ADC1

	/* Enable ADC1 reset calibaration register */
	ADC_ResetCalibration(ADC1);						//重置ADC1的校准寄存器
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));		//获取ADC1重置校准寄存器的状态,设置状态则等待

	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);					//开始ADC1的校准状态
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));		//等待校准完成

	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能ADC1的软件转换启动功能
}

/*************************************************
函数: void Timer2_Configuration(void)
功能: TIM2 配置
参数: 无
返回: 无
定时计算：(1 /(72 / (72 - 1 + 1))) * 1000 us = 1000us
**************************************************/
void Timer2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=1000;	//自动重装载寄存器周期的值(计数值) 
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);	//时钟预分频数 72M/72      
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);	// 清除溢出中断标志 
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);	// 开启时钟    
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	//先关闭等待使用                          //开启时钟 
}

/*******************************************************************************
* Function Name   : NVIC_Configuration
* Description        : Configures NVIC and Vector Table base location.
* Input                    : None
* Output                 : None
* Return                 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  

  NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*************************************************
函数: void TIM2_IRQHandler(void)
功能: TIM2中断处理函数
参数: 无
返回: 无
说明：390.5us中断1次
**************************************************/
void TIM2_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
   {      
      TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	 //清除中断标志
      time++;
   }
}


void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
}
int main(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_Configuration();
  ADC_Configuration();
  NVIC_Configuration();
  Timer2_Configuration();
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB端口
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();  
  GPIO_SetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13 | GPIO_Pin_14);	 // 关闭所有LED

  while (1)
  {
    u8 s1,s2,s3,s4=0;
         if(time==500) //500毫秒采集一次
		 { 
		  time=0; 		 
	      ADC_SoftwareStartConvCmd(ADC1, ENABLE);	        //软件启动ADC转换
	      while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));   //等待转换结束
	      ad=ADC_GetConversionValue(ADC1);
		  adzhi = 3300000/4096*ad/1000;		        //读取ADC值  
		  s1=(adzhi/1000);
          s2=(adzhi/100%10);
          s3=(adzhi%100/10);
          s4=(adzhi%10);
		  s1=s1+0x30;
		  s2=s2+0x30;
		  s3=s3+0x30;
		  s4=s4+0x30; 		                    
          USART_To_USB_Send_Data('V');
		  USART_To_USB_Send_Data('o');
		  USART_To_USB_Send_Data('l');
		  USART_To_USB_Send_Data('t');
		  USART_To_USB_Send_Data('a');
		  USART_To_USB_Send_Data('g');
		  USART_To_USB_Send_Data('e');
		  USART_To_USB_Send_Data(':');
		  USART_To_USB_Send_Data(s1);
		  USART_To_USB_Send_Data(s2);
		  USART_To_USB_Send_Data(s3);
		  USART_To_USB_Send_Data(s4);
		  USART_To_USB_Send_Data('m');
		  USART_To_USB_Send_Data('V');
		  USART_To_USB_Send_Data('\n');	
		  
          }      
       		  
  }
}

