/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   GPIO输出--使用固件库点亮LED灯
  ******************************************************************
  * @attention
  *
  * 实验平台:野火 STM32H743 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************
  */  
#include "stm32h7xx.h"
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
  *         system Clock 配置如下: 
	*            System Clock source  = PLL (HSE)
	*            SYSCLK(Hz)           = 400000000 (CPU Clock)
	*            HCLK(Hz)             = 200000000 (AXI and AHBs Clock)
	*            AHB Prescaler        = 2
	*            D1 APB3 Prescaler    = 2 (APB3 Clock  120MHz)
	*            D2 APB1 Prescaler    = 2 (APB1 Clock  120MHz)
	*            D2 APB2 Prescaler    = 2 (APB2 Clock  120MHz)
	*            D3 APB4 Prescaler    = 2 (APB4 Clock  120MHz)
	*            HSE Frequency(Hz)    = 25000000
	*            PLL_M                = 2
	*            PLL_N                = 64
	*            PLL_P                = 2
	*            PLL_Q                = 4
	*            PLL_R                = 2
	*            VDD(V)               = 3.3
	*            Flash Latency(WS)    = 4
  * @param  None
  * @retval None
  */
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** 启用电源配置更新
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** 配置主内稳压器输出电压
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** 初始化CPU、AHB和APB总线时钟
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
		while(1);
  }
  /** 初始化CPU、AHB和APB总线时钟
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
		while(1);
  }
}
/****************************END OF FILE***************************/
