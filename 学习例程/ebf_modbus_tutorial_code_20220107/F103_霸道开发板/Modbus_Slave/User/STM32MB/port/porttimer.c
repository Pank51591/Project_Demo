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

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
//static void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )		//定时器初始化直接返回TRUE，已经在mian函数初始化过
{
    return TRUE;
}


inline void
vMBPortTimersEnable(  )		//使能定时器中断
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
		__HAL_TIM_CLEAR_IT(&htim4,TIM_IT_UPDATE);
		__HAL_TIM_ENABLE_IT(&htim4,TIM_IT_UPDATE);
		__HAL_TIM_SET_COUNTER(&htim4,0);
		__HAL_TIM_ENABLE(&htim4);
}

inline void
vMBPortTimersDisable(  )	//取消定时器中断
{
    /* Disable any pending timers. */
			__HAL_TIM_DISABLE(&htim4);
			__HAL_TIM_SET_COUNTER(&htim4,0);
			__HAL_TIM_DISABLE_IT(&htim4,TIM_IT_UPDATE);
			__HAL_TIM_CLEAR_IT(&htim4,TIM_IT_UPDATE);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
//static 
void prvvTIMERExpiredISR( void )	//modbus定时器动作，需要在中断内使用
{
    ( void )pxMBPortCBTimerExpired(  );
}

