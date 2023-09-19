/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   Modbus�ӻ�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

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
