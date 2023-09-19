/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   GPIO���--ʹ�ù̼������LED��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
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

/* ���Թ��ܲ��� */
#define MB_SAMPLE_TEST_SLAVE_ADDR						1			//�ӻ��豸��ַ

void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/
/* ��ɢ������� */
extern UCHAR    ucSDiscInBuf[S_DISCRETE_INPUT_NDISCRETES/8]  ;
/* ��Ȧ */
extern UCHAR    ucSCoilBuf[S_COIL_NCOILS/8];
/* ����Ĵ��� */
extern USHORT   usSRegInBuf[S_REG_INPUT_NREGS];
/* ���ּĴ��� */
extern USHORT   usSRegHoldBuf[S_REG_HOLDING_NREGS];
static void SystemClock_Config(void);
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* HAL���ʼ�� */
  HAL_Init();  

  /* ϵͳʱ�ӳ�ʼ�� */
  SystemClock_Config();	

  /* �ܽ�ʱ�ӳ�ʼ�� */
  MX_GPIO_Init();
	
	/* ��ʱ��4��ʼ�� */
  MX_TIM4_Init();
	
	/* ����2��ʼ����portserial.c�� */
	
	/* Modbus��ʼ�� */
	eMBInit( MB_RTU, MB_SAMPLE_TEST_SLAVE_ADDR, MB_MASTER_USARTx, MB_MASTER_USART_BAUDRATE, MB_PAR_NONE);
	
	/* ����Mdobus */
	eMBEnable();

  while (1)
  {
		/* ���±��ּĴ���ֵ */
		usSRegHoldBuf[0] =  HAL_GetTick() & 0xff;		           //��ȡʱ��� ���1��8λ
		usSRegHoldBuf[1] = (HAL_GetTick() & 0xff00) >> 8;      //��ȡʱ��� ���9��16λ
		usSRegHoldBuf[2] = (HAL_GetTick() & 0xff0000) >> 16 ;  //��ȡʱ��� ���17��24λ
		usSRegHoldBuf[3] = (HAL_GetTick() & 0xff000000) >> 24; //��ȡʱ��� ���25��32λ
		
		/* ��������Ĵ���ֵ */
		usSRegInBuf[0] =  HAL_GetTick() & 0xff;		             //��ȡʱ��� ���1��8λ
		usSRegInBuf[1] = (HAL_GetTick() & 0xff00) >> 8;        //��ȡʱ��� ���9��16λ
		usSRegInBuf[2] = (HAL_GetTick() & 0xff0000) >> 16 ;    //��ȡʱ��� ���17��24λ
		usSRegInBuf[3] = (HAL_GetTick() & 0xff000000) >> 24;   //��ȡʱ��� ���25��32λ
		
		/* ������Ȧ */
		ucSCoilBuf[0] =  HAL_GetTick() & 0xff;		             //��ȡʱ��� ���1��8λ
		ucSCoilBuf[1] = (HAL_GetTick() & 0xff00) >> 8;         //��ȡʱ��� ���9��16λ
		ucSCoilBuf[2] = (HAL_GetTick() & 0xff0000) >> 16 ;     //��ȡʱ��� ���17��24λ
		ucSCoilBuf[3] = (HAL_GetTick() & 0xff000000) >> 24;    //��ȡʱ��� ���25��32λ
		
		/* ��ɢ������� */
		ucSDiscInBuf[0] =  HAL_GetTick() & 0xff;		           //��ȡʱ��� ���1��8λ
		ucSDiscInBuf[1] = (HAL_GetTick() & 0xff00) >> 8;       //��ȡʱ��� ���9��16λ
		
		/* ���Բ�����ʱ�������ʱʱ�����������timeout */
		HAL_Delay(200);		
		
		/*�ӻ���ѯ*/
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
