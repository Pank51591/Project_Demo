//************************************************************
//  Copyright (c)   
//	FileName	  : SC_it.c
//	Function	  : Interrupt Service Routine
//  Instructions  :  
//  Date          : 2022/03/03
// 	Version		  : V1.0002
//*************************************************************
/********************Includes************************************************************************/
#include "SC_it.h"
#include "..\Drivers\SCDriver_list.h"
#include "HeadFiles\SC_itExtern.h"
/**************************************Generated by EasyCodeCube*************************************/

/*************************************.Generated by EasyCodeCube.************************************/

void INT0Interrupt()		interrupt 0				
{
    TCON &= 0XFD;//Clear interrupt flag bit
	/*INT0_it write here begin*/
    /*INT0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*INT0Interrupt Flag Clear begin*/
    /*INT0Interrupt Flag Clear end*/
}
void Timer0Interrupt()		interrupt 1			   
{
    /*TIM0_it write here begin*/
    /*TIM0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer0Interrupt Flag Clear begin*/
    /*Timer0Interrupt Flag Clear end*/		
}
void INT1Interrupt()		interrupt 2		
{
    TCON &= 0XF7;//Clear interrupt flag bit
	/*INT1_it write here begin*/
    /*INT1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*INT1Interrupt Flag Clear begin*/
    /*INT1Interrupt Flag Clear end*/					
}
void Timer1Interrupt()		interrupt 3		
{
    /*TIM1_it write here begin*/
    /*TIM1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer1Interrupt Flag Clear begin*/
    /*Timer1Interrupt Flag Clear end*/		
}
#if defined (SC92F742x) || defined (SC92F7490)
void SSI0Interrupt()		interrupt 4		
{
	/*SSI0_it write here begin*/
    /*SSI0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*SSI0Interrupt Flag Clear begin*/
    /*SSI0Interrupt Flag Clear end*/		
}
#else
void UART0Interrupt()		interrupt 4		
{
    /*UART0_it write here begin*/
    /*UART0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*UART0Interrupt Flag Clear begin*/
    /*UART0Interrupt Flag Clear end*/		
}
#endif
void Timer2Interrupt()		interrupt 5		
{
    /*TIM2_it write here begin*/
    /*TIM2_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer2Interrupt Flag Clear begin*/
    /*Timer2Interrupt Flag Clear end*/		
}
void ADCInterrupt()			interrupt 6		
{
    /*ADC_it write here begin*/
    /*ADC_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*ADCInterrupt Flag Clear begin*/
    /*ADCInterrupt Flag Clear end*/		
}
#if defined (SC92F854x) || defined (SC92F754x) ||defined  (SC92F844xB) || defined (SC92F744xB)||defined  (SC92F84Ax_2) || defined (SC92F74Ax_2)|| defined (SC92F846xB) \
|| defined (SC92F746xB) || defined (SC92F836xB) || defined (SC92F736xB) || defined (SC92F8003)||defined  (SC92F84Ax) || defined (SC92F74Ax) || defined  (SC92F83Ax) \
|| defined (SC92F73Ax) || defined (SC92F7003) || defined (SC92F740x) || defined (SC92FWxx) || defined (SC93F743x) || defined (SC93F833x) || defined (SC93F843x)\
|| defined (SC92F848x) || defined (SC92F748x)|| defined (SC92F859x) || defined (SC92F759x)
void SSIInterrupt()			interrupt 7		
{
    /*SSI_it write here begin*/
    /*SSI_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*SSIInterrupt Flag Clear begin*/
    /*SSIInterrupt Flag Clear end*/		
}
#elif defined (SC92F742x) || defined (SC92F7490)
void SSI1Interrupt()		interrupt 7		
{
	/*SSI1_it write here begin*/
    /*SSI1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*SSI1Interrupt Flag Clear begin*/
    /*SSI1Interrupt Flag Clear end*/		
}
#else 
void USCI0Interrupt()			interrupt 7		
{
	/*USCI0_it write here begin*/
    /*USCI0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI0Interrupt Flag Clear begin*/
    /*USCI0Interrupt Flag Clear end*/		
}
#endif
void PWMInterrupt()			interrupt 8
{
    /*PWM_it write here begin*/
    /*PWM_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*PWMInterrupt Flag Clear begin*/
    /*PWMInterrupt Flag Clear end*/		
}
#if !defined (TK_USE_BTM)
void BTMInterrupt()			interrupt 9
{
	/*BTM_it write here begin*/
    /*BTM_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*BTMInterrupt Flag Clear begin*/
    /*BTMInterrupt Flag Clear end*/		
}
#endif
void INT2Interrupt()		interrupt 10
{	
	/*INT2_it write here begin*/
    /*INT2_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*INT2Interrupt Flag Clear begin*/
    /*INT2Interrupt Flag Clear end*/		
}
void ACMPInterrupt()		interrupt 12
{
	/*ACMP_it write here begin*/
    /*ACMP_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*ACMPInterrupt Flag Clear begin*/
    /*ACMPInterrupt Flag Clear end*/		
}
void Timer3Interrupt()		interrupt 13
{
	/*Timer3_it write here begin*/
    /*Timer3_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer3Interrupt Flag Clear begin*/
    /*Timer3Interrupt Flag Clear end*/		
}
void Timer4Interrupt()		interrupt 14
{
	/*Timer4_it write here begin*/
    /*Timer4_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer4Interrupt Flag Clear begin*/
    /*Timer4Interrupt Flag Clear end*/		
}
void USCI1Interrupt()		interrupt 15		
{	
	/*USCI1_it write here begin*/
    /*USCI1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI1Interrupt Flag Clear begin*/
    /*USCI1Interrupt Flag Clear end*/		
}
void USCI2Interrupt()		interrupt 16		
{	
	/*USCI2_it write here begin*/
    /*USCI2_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI2Interrupt Flag Clear begin*/
    /*USCI2Interrupt Flag Clear end*/		
}
void USCI3Interrupt()		interrupt 17		
{
	/*USCI3_it write here begin*/
    /*USCI3_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI3Interrupt Flag Clear begin*/
    /*USCI3Interrupt Flag Clear end*/		
}
void USCI4Interrupt()		interrupt 18		
{
    /*USCI4_it write here begin*/
    /*USCI4_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI4Interrupt Flag Clear begin*/
    /*USCI4Interrupt Flag Clear end*/		
}
void USCI5Interrupt()		interrupt 19		
{
    /*USCI5_it write here begin*/	
    /*USCI5_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI5Interrupt Flag Clear begin*/
    /*USCI5Interrupt Flag Clear end*/		
}
void LPDInterrupt()		interrupt 22		
{
    /*LPD_it write here begin*/
    /*LPD_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*LPDInterrupt Flag Clear begin*/
    /*LPDInterrupt Flag Clear end*/		
}