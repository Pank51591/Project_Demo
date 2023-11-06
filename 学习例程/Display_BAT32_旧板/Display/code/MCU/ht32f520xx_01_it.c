/******************************************************************************
 *文件信息：ht32f520xx_01_it.c
 *版本信息：V4.0
 *制作日期：2017.10.18
 *使用介绍：中断程序处理入口
*******************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "ht32.h"
//#include "systick.h"
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/****************************************************
* Function Name: NMI_Handler
* Description  : Non-maskable interrupts
* Arguments    : None
* Return Value : None
**********************************************************/
void NMI_Handler(void)
{
}

/****************************************************
* Function Name: HardFault_Handler
* Description  : A hardware error occurs
* Arguments    : None
* Return Value : None
**********************************************************/
void HardFault_Handler(void)
{
	while (1);
}

/****************************************************
* Function Name: SVC_Handler
* Description  : SVC abnormal
* Arguments    : None
* Return Value : None
**********************************************************/
void SVC_Handler(void)
{
}

/****************************************************
* Function Name: PendSV_Handler
* Description  : PendSV is an interrupt driver for system-level services
* Arguments    : None
* Return Value : None
**********************************************************/
void PendSV_Handler(void)
{
}

/****************************************************
* Function Name: SysTick_Handler
* Description  : Systick interrupt
* Arguments    : None
* Return Value : None
**********************************************************/
//void SysTick_Handler(void)//系统时钟10ms中断
//{
	
//}
/*********************************************************************************************************//**
* Function Name: EXTI0_1_IRQHandler
* Description  : EXTI line 0-1 interrupt
* Arguments    : None
* Return Value : None
 ************************************************************************************************************/
void EXTI0_1_IRQHandler(void)
{
//  extern vu32 gSPIINT;
 
//    gSPIINT = 1;
//  }
}
/*********************************************************************************************************//**
* Function Name: EXTI4_15_IRQHandler
* Description  : EXTI line 4-15 interrupt
* Arguments    : None
* Return Value : None
 ************************************************************************************************************/
void EXTI4_15_IRQHandler(void)
{
  //if (EXTI_GetEdgeStatus(EXTI_CHANNEL_8, EXTI_EDGE_NEGATIVE) == SET)
 // {
 //   EXTI_ClearEdgeFlag(EXTI_CHANNEL_8);
//	extern char poweroffcheck;
//    poweroffcheck = 1;
		
//		GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_1,RESET);
//		extern void PowerOffProcess(void);
//		PowerOffProcess();
 // }
}

/****************************************************
* Function Name: USART0_IRQHandler
* Description  : Serial port0 to send and receive interrupt processing
* Arguments    : None
* Return Value : None
**********************************************************/
//void USART0_IRQHandler(void)
//{
//}
/***********************************END OF FILE*******************************************/
