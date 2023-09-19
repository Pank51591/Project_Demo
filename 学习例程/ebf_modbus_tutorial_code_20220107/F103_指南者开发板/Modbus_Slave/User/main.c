/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   Modbus从机例程
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
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

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

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
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 2
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 0
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  oscinitstruct.HSEState        = RCC_HSE_ON;
  oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
