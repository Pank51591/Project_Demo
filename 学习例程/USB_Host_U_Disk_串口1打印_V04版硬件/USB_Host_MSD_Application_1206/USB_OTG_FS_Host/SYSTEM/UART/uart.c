////////////////////////////////////////////////////////////////////////////////
/// @file    uart.c
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _UART_C_

// Files includes
#include <stdio.h>
#include "uart.h"
#include "hal_conf.h"


#define RS485_BLDC_IM2_SEND_MODE()	GPIO_SetBits(GPIOB,GPIO_Pin_15);   //PB15=1;
#define RS485_BLDC_IM2_REC_MODE()	  GPIO_ResetBits(GPIOB,GPIO_Pin_15); //PB15=0;



#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE s32 __io_putchar(s32 ch)
#else
#define PUTCHAR_PROTOTYPE s32 fputc(s32 ch, FILE *f)

#endif

#ifdef USE_IAR
PUTCHAR_PROTOTYPE {
    while((UART1->CSR & UART_IT_TXIEN) == 0); //The loop is sent until it is finished
    UART1->TDR = (ch & (u16)0x00FF);
    return ch;
}

#else
void _sys_exit(s32 x)
{
    x = x;
}

//redefine fputcfunction
s32 fputc(s32 ch, FILE* f)
{
		RS485_BLDC_IM2_SEND_MODE();

//	  delay_ms();
	
		while((UART1->CSR & UART_IT_TXIEN) == 0);   //The loop is sent until it is finished
			UART1->TDR = (ch & (u16)0x00FF);
	
//	  delay_ms();
//		RS485_BLDC_IM2_REC_MODE();

	
    return ch;
	
	
	
}

#endif



/*********************************************************
***函数名：
***函数功能：串口
***参数：
***返回值：
**********************************************************/
void CONSOLE_Init(u32 baudrate)
{
    //GPIO port set
    GPIO_InitTypeDef GPIO_InitStruct;
    UART_InitTypeDef UART_InitStruct;
	  //NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1ENR_UART3, ENABLE);   //enableUART3,GPIOAclock
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);  //
    //UART initialset

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_7);     //Tx
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_7);     //Rx

    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.UART_BaudRate = baudrate;
    UART_InitStruct.UART_WordLength = UART_WordLength_8b;
    UART_InitStruct.UART_StopBits = UART_StopBits_1;//one stopbit
    UART_InitStruct.UART_Parity = UART_Parity_No;//none odd-even  verify bit
    UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//No hardware flow control
    UART_InitStruct.UART_Mode = UART_Mode_Rx | UART_Mode_Tx; // receive and sent  mode

    UART_Init(UART3, &UART_InitStruct);          //initial uart 3
    UART_Cmd(UART3, ENABLE);                     //enable uart 3

    //UART3_TX   GPIOB.10
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    //UART3_RX    GPIOB.11
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

}


void UART1_Init(u32 BaudRate)
{
    UART_InitTypeDef UART_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);

//    //UART1 NVIC
//    NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

    //Baud rate
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.BaudRate = BaudRate;
    //The word length is in 8-bit data format.
    UART_InitStructure.WordLength = UART_WordLength_8b;
    UART_InitStructure.StopBits = UART_StopBits_1;
    //No even check bit.
    UART_InitStructure.Parity = UART_Parity_No;
	
    //No hardware data flow control.
    UART_InitStructure.HWFlowControl = UART_HWFlowControl_None;
    UART_InitStructure.Mode = UART_Mode_Rx | UART_Mode_Tx;

    UART_Init(UART1, &UART_InitStructure);
    //UART_ITConfig(UART1, UART_IT_TXIEN|UART_IT_RXIEN, ENABLE);
    UART_Cmd(UART1, ENABLE);

    UART1_GPIO_Init();

}

void UART1_GPIO_Init (void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

    //RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_7);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_7);

    //UART1_TX   GPIOA.9
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //UART1_RX    GPIOA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  //M_485_EN
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void delay_ms (void)
{
	uint8_t  i;
	for(i = 0 ; i < 200; i++)
	{
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
	}
}

//BOOL UartSendICEMachineData(u8 *buff,u8 len)
//{
//	u8 i;

//	RS485_BLDC_IM2_SEND_MODE();
//	
//	for(i=0;i<len;i++)
//	{
//		UART_SendData(UART1, buff[i]);
//		while(!UART_GetFlagStatus(UART1, UART_FLAG_TXEPT));
//	}

//	RS485_BLDC_IM2_REC_MODE();
//	
//	return 1;

//}

