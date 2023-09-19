/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

#include "port.h"
#include "stm32f7xx_hal.h"
#include "usart.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
//static void prvvUARTTxReadyISR( void );
//static void prvvUARTRxISR( void );

/* ----------------------- Start implementation -----------------------------*/

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    /**
     * set 485 mode receive and transmit control IO
     * @note MODBUS_MASTER_RT_CONTROL_PIN_INDEX need be defined by user
     */
	
		/* ʹ��485ʱ��Ҫ��usart.h�д�RT_MODBUS_MASTER_USE_CONTROL_PIN�궨�� */
	#if defined(MODBUS_MASTER_USE_CONTROL_PIN)	
		modbus_master_control_init();
	#endif

	MX_USART2_UART_Init(ucPORT,ulBaudRate,eParity);
	return TRUE;				
}

void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
		if (xRxEnable)															
			{
				/* ����2�����ж�ʹ�� */
				__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);	
				#if defined(MODBUS_MASTER_USE_CONTROL_PIN)	
					/* 485�͵�ƽ���� */
					HAL_GPIO_WritePin(MODBUS_MASTER_GPIO_PORT,MODBUS_MASTER_GPIO_PIN,MODBUS_MASTER_GPIO_PIN_LOW);
				#endif
			}
		else
			{
				/* ����2�����жϹر� */
				__HAL_UART_DISABLE_IT(&huart2,UART_IT_RXNE);
				#if defined(MODBUS_MASTER_USE_CONTROL_PIN)
					/* 485�ߵ�ƽ���� */
					HAL_GPIO_WritePin(MODBUS_MASTER_GPIO_PORT,MODBUS_MASTER_GPIO_PIN,MODBUS_MASTER_GPIO_PIN_HIGH);
				#endif
			}
		if (xTxEnable)
			{
				/* ����2�����ж�ʹ�� */
				__HAL_UART_ENABLE_IT(&huart2,UART_IT_TXE);
				#if defined(MODBUS_MASTER_USE_CONTROL_PIN)
					/* 485�ߵ�ƽ����*/
					HAL_GPIO_WritePin(MODBUS_MASTER_GPIO_PORT,MODBUS_MASTER_GPIO_PIN,MODBUS_MASTER_GPIO_PIN_HIGH);
				#endif
			}
		else
			{
				/* ����2�����жϹر� */
				__HAL_UART_DISABLE_IT(&huart2,UART_IT_TXE);
				#if defined(MODBUS_MASTER_USE_CONTROL_PIN)	
					/* 485�͵�ƽ����*/
					HAL_GPIO_WritePin(MODBUS_MASTER_GPIO_PORT,MODBUS_MASTER_GPIO_PIN,MODBUS_MASTER_GPIO_PIN_LOW);
				#endif
			}	
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
		if(HAL_UART_Transmit (&huart2 ,(uint8_t *)&ucByte,1,0x01) != HAL_OK )	//��ӷ���һλ����
			return FALSE ;
		else
			return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
	if(HAL_UART_Receive (&huart2 ,(uint8_t *)pucByte,1,0x01) != HAL_OK )//��ӽ���һλ����
			return FALSE ;
	else
    return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
//static 
void prvvUARTTxReadyISR( void )		//ɾȥǰ���static�������ڴ����ж�ʹ��
{
    pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
//static 
void prvvUARTRxISR( void )				//ɾȥǰ���static�������ڴ����ж�ʹ��
{
    pxMBFrameCBByteReceived(  );
}
