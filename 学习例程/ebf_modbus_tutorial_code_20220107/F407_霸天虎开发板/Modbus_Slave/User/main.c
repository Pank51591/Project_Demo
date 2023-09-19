/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   GPIO输出--使用固件库点亮LED灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "stm32f4xx.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/

#include "mb.h"
#include "mbport.h"
#include "user_mb_app.h"

/* 测试功能参数 */
#define MB_SAMPLE_TEST_SLAVE_ADDR						1			//从机设备地址

void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/
/* 离散输入变量 */
extern UCHAR    ucSDiscInBuf[S_DISCRETE_INPUT_NDISCRETES/8]  ;
/* 线圈 */
extern UCHAR    ucSCoilBuf[S_COIL_NCOILS/8];
/* 输入寄存器 */
extern USHORT   usSRegInBuf[S_REG_INPUT_NREGS];
/* 保持寄存器 */
extern USHORT   usSRegHoldBuf[S_REG_HOLDING_NREGS];
static void SystemClock_Config(void);
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* HAL库初始化 */
  HAL_Init();  

  /* 系统时钟初始化 */
  SystemClock_Config();	

  /* 管脚时钟初始化 */
  MX_GPIO_Init();
	
	/* 定时器4初始化 */
  MX_TIM4_Init();
	
	/* 串口2初始化在portserial.c中 */
	
	/* Modbus初始化 */
	eMBInit( MB_RTU, MB_SAMPLE_TEST_SLAVE_ADDR, MB_MASTER_USARTx, MB_MASTER_USART_BAUDRATE, MB_PAR_NONE);
	
	/* 启动Mdobus */
	eMBEnable();

  while (1)
  {
		/* 更新保持寄存器值 */
		usSRegHoldBuf[0] =  HAL_GetTick() & 0xff;		           //获取时间戳 提出1至8位
		usSRegHoldBuf[1] = (HAL_GetTick() & 0xff00) >> 8;      //获取时间戳 提出9至16位
		usSRegHoldBuf[2] = (HAL_GetTick() & 0xff0000) >> 16 ;  //获取时间戳 提出17至24位
		usSRegHoldBuf[3] = (HAL_GetTick() & 0xff000000) >> 24; //获取时间戳 提出25至32位
		
		/* 更新输入寄存器值 */
		usSRegInBuf[0] =  HAL_GetTick() & 0xff;		             //获取时间戳 提出1至8位
		usSRegInBuf[1] = (HAL_GetTick() & 0xff00) >> 8;        //获取时间戳 提出9至16位
		usSRegInBuf[2] = (HAL_GetTick() & 0xff0000) >> 16 ;    //获取时间戳 提出17至24位
		usSRegInBuf[3] = (HAL_GetTick() & 0xff000000) >> 24;   //获取时间戳 提出25至32位
		
		/* 更新线圈 */
		ucSCoilBuf[0] =  HAL_GetTick() & 0xff;		             //获取时间戳 提出1至8位
		ucSCoilBuf[1] = (HAL_GetTick() & 0xff00) >> 8;         //获取时间戳 提出9至16位
		ucSCoilBuf[2] = (HAL_GetTick() & 0xff0000) >> 16 ;     //获取时间戳 提出17至24位
		ucSCoilBuf[3] = (HAL_GetTick() & 0xff000000) >> 24;    //获取时间戳 提出25至32位
		
		/* 离散输入变量 */
		ucSDiscInBuf[0] =  HAL_GetTick() & 0xff;		           //获取时间戳 提出1至8位
		ucSDiscInBuf[1] = (HAL_GetTick() & 0xff00) >> 8;       //获取时间戳 提出9至16位
		
		/* 可以不用延时，如果延时时间过长主机会timeout */
		HAL_Delay(200);		
		
		/*从机轮询*/
		( void )eMBPoll(  );
    
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 25
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1) {};
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    while(1) {};
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
