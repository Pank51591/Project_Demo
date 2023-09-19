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
  * 实验平台:野火 STM32F767 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f7xx.h"
#include "main.h"
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
  * @brief  System Clock 配置
  *         system Clock 配置如下 : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  无
  * @retval 无
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* 使能HSE，配置HSE为PLL的时钟源，配置PLL的各种分频因子M N P Q 
	 * PLLCLK = HSE/M*N/P = 25M / 25 *432 / 2 = 216M
	 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* 激活 OverDrive 模式以达到216M频率  */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* 选择PLLCLK作为SYSCLK，并配置 HCLK, PCLK1 and PCLK2 的时钟分频因子 
	 * SYSCLK = PLLCLK     = 216M
	 * HCLK   = SYSCLK / 1 = 216M
	 * PCLK2  = SYSCLK / 2 = 108M
	 * PCLK1  = SYSCLK / 4 = 54M
	 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
	/* 在HAL_RCC_ClockConfig函数里面同时初始化好了系统定时器systick，配置为1ms中断一次 */
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}

/*********************************************END OF FILE**********************/

