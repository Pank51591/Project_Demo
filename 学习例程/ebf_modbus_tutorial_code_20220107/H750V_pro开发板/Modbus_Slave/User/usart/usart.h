/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//���Ŷ���
/***********************usart*****************************/
#define DEBUG_USART                             USART2
#define DEBUG_USART_CLK_ENABLE()                __USART2_CLK_ENABLE();

#define RCC_PERIPHCLK_UARTx                     RCC_PERIPHCLK_USART2
#define RCC_UARTxCLKSOURCE_SYSCLK               RCC_USART2CLKSOURCE_SYSCLK
#define __HAL_RCC_USARTx_CLK_DISABLE 						__HAL_RCC_USART2_CLK_DISABLE();

#define DEBUG_USART_RX_GPIO_PORT                GPIOD
#define DEBUG_USART_RX_GPIO_CLK_ENABLE()        __GPIOD_CLK_ENABLE()
#define DEBUG_USART_RX_PIN                      GPIO_PIN_6
#define DEBUG_USART_RX_AF                       GPIO_AF7_USART2

#define DEBUG_USART_TX_GPIO_PORT                GPIOD
#define DEBUG_USART_TX_GPIO_CLK_ENABLE()        __GPIOD_CLK_ENABLE()
#define DEBUG_USART_TX_PIN                      GPIO_PIN_5
#define DEBUG_USART_TX_AF                       GPIO_AF7_USART2

#define DEBUG_USART_IRQHandler                  USART2_IRQHandler
#define DEBUG_USART_IRQ                 		    USART2_IRQn

#define MB_MASTER_USARTx												2 			//ʹ�ô���2
#define MB_MASTER_USART_BAUDRATE								115200	//������
#define MB_MASTER_USART_PARITY									UART_PARITY_NONE

/*********************usart end***************************************/
/***********************485*****************************/

/* �����Ҫʹ�ô���ת485 ��򿪴˺� */
//#define MODBUS_MASTER_USE_CONTROL_PIN		

#define MODBUS_MASTER_GPIO_PORT									GPIOD
#define MODBUS_MASTER_GPIO_PIN                  GPIO_PIN_4
#define MODBUS_MASTER_GPIO_PIN_HIGH							GPIO_PIN_SET
#define MODBUS_MASTER_GPIO_PIN_LOW							GPIO_PIN_RESET
#define MODBUS_MASTER_GPIO_CLK_ENABLE()         __GPIOD_CLK_ENABLE()

/***********************485 end*************************************/


extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void MX_USART2_UART_Init(uint8_t ucPORT, uint32_t ulBaudRate, uint8_t eParity);
extern void usart_send_string( uint8_t *s);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
