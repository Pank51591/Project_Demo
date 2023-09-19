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
  * ʵ��ƽ̨:Ұ�� STM32F767 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
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
  * @brief  System Clock ����
  *         system Clock �������� : 
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
  * @param  ��
  * @retval ��
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* ʹ��HSE������HSEΪPLL��ʱ��Դ������PLL�ĸ��ַ�Ƶ����M N P Q 
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
  
  /* ���� OverDrive ģʽ�Դﵽ216MƵ��  */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* ѡ��PLLCLK��ΪSYSCLK�������� HCLK, PCLK1 and PCLK2 ��ʱ�ӷ�Ƶ���� 
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
  
	/* ��HAL_RCC_ClockConfig��������ͬʱ��ʼ������ϵͳ��ʱ��systick������Ϊ1ms�ж�һ�� */
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}

/*********************************************END OF FILE**********************/

