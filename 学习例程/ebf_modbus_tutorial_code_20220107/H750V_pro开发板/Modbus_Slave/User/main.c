/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2022-xx-xx
  * @brief   Modbus����
  ******************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32H750������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************
  */  
#include "stm32h7xx.h"
#include "main.h"
#include "usart.h"
#include "tim.h"

#include "gpio.h"
#include "mb.h"
#include "mbport.h"
#include "user_mb_app.h"

#define MB_SAMPLE_TEST_SLAVE_ADDR						1			//�ӻ��豸��ַ

/* ��ɢ������� */
extern UCHAR    ucSDiscInBuf[S_DISCRETE_INPUT_NDISCRETES/8]  ;
/* ��Ȧ */
extern UCHAR    ucSCoilBuf[S_COIL_NCOILS/8];
/* ����Ĵ��� */
extern USHORT   usSRegInBuf[S_REG_INPUT_NREGS];
/* ���ּĴ��� */
extern USHORT   usSRegHoldBuf[S_REG_HOLDING_NREGS];

int main(void)
{
 	HAL_Init();  
	
	SystemClock_Config();

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
		
		/*�ӻ���ѯ*/
		
		#if defined(MODBUS_MASTER_USE_CONTROL_PIN)			
			HAL_Delay(1);
		#else
      HAL_Delay(2);     	
		#endif
		
		( void )eMBPoll(  );

  }
}

/**
  * @brief  System Clock ����
  *         system Clock ��������: 
	*            System Clock source  = PLL (HSE)
	*            SYSCLK(Hz)           = 480000000 (CPU Clock)
	*            HCLK(Hz)             = 240000000 (AXI and AHBs Clock)
	*            AHB Prescaler        = 2
	*            D1 APB3 Prescaler    = 2 (APB3 Clock  120MHz)
	*            D2 APB1 Prescaler    = 2 (APB1 Clock  120MHz)
	*            D2 APB2 Prescaler    = 2 (APB2 Clock  120MHz)
	*            D3 APB4 Prescaler    = 2 (APB4 Clock  120MHz)
	*            HSE Frequency(Hz)    = 25000000
	*            PLL_M                = 5
	*            PLL_N                = 192
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

  /** ���õ�Դ���ø���
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** ����������ѹ�������ѹ
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** ��ʼ��CPU��AHB��APB����ʱ��
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
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
  /** ��ʼ��CPU��AHB��APB����ʱ��
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
