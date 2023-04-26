#include "SC_System.h"
#include "Burner_Process.h"
#include "Output_Process.h"
#include "Sleep_Process.h"
extern uint8_t gcBurner1OpenCount;       
extern uint8_t gcBurner1CloseCount;       

extern uint8_t gcBurner2OpenCount;        
extern uint8_t gcBurner2CloseCount;       

extern uint8_t gcBurner3OpenCount;        
extern uint8_t gcBurner3CloseCount;      

extern uint8_t gcBurner4OpenCount;         
extern uint8_t gcBurner4CloseCount;        

extern uint8_t gcBurner5OpenCount;        
extern uint8_t gcBurner5CloseCount;        

extern uint8_t gcBurner6OpenCount;         
extern uint8_t gcBurner6CloseCount;        

extern uint8_t gcBurnerStatus;            
extern uint8_t gcBurnerOpenCount;   

extern uint8_t gcKeyStatus;                
extern uint8_t gcKeyCount;                
extern uint8_t gcOneMsCount;               
extern uint32_t gcButton1State;             
extern uint8_t gcKeyValue;                
extern uint16_t giKeySW6LongDownTime;      
extern uint8_t gcBuzzerTime; 
extern uint8_t  gcPowerUpTime;
extern uint16_t giLEDPwmValue;
extern volatile uint16_t giLightDelayOffTime;  // 5minute
extern volatile uint16_t giSpeedDelayOffTime;  // 5minute

sfr		TKCR	=	0xE8;	
//=======================================================================================
//                  void Sleep_Process(void)
//                  Run once in 10ms         
//                  Return value::No
//=======================================================================================
 void Sleep_Process(void)
 {
		Key_Scan();
 }
 
 void Sleep_Clr()//关闭耗电外设
 {
			TKCR &=0x7F;
			Delay1ms();
			Delay1ms();
			OPTION_WDT_Cmd(DISABLE);
			OPTION_XTIPLL_Cmd(DISABLE);
	 	 	PWM_IndependentModeConfigEX(PWM05, 0, PWM_OUTPUTSTATE_DISABLE); /*PWM05 独立模式*/
		//	PWM_IndependentModeConfigEX(PWM07, 0, PWM_OUTPUTSTATE_DISABLE); /*PWM07 独立模式*/
			PWM_IndependentModeConfigEX(PWM20, 0, PWM_OUTPUTSTATE_DISABLE);
			PWM_IndependentModeConfigEX(PWM30, 0, PWM_OUTPUTSTATE_DISABLE);
	 		PWM_CmdEX(PWM0_Type, DISABLE); /*PWM0开关*/
			//PWM_CmdEX(PWM2_Type, DISABLE); /*PWM2开关*/
			PWM_CmdEX(PWM3_Type, DISABLE); /*PWM3开关*/
	 		TIM0_ITConfig(DISABLE, HIGH);
			TIM0_Cmd(DISABLE);
			TIM1_ITConfig(DISABLE, HIGH);
			TIM1_Cmd(DISABLE);
			ADC_EAINConfig(ADC_EAIN_1, DISABLE);
			ADC_EAINConfig(ADC_EAIN_9, DISABLE);
			ADC_ChannelConfig(ADC_CHANNEL_9, DISABLE);
			ADC_Cmd(DISABLE);
			P0CON=0xEF;
			P0PH=~0xEF;
			P1CON=0x3F;
			P1PH=~0X3F;
			P2CON=0xF8;
			P2PH=~0XF8;
			P3CON=0xFF;
			P3PH=0X00;
			P4CON=0xFF;
			P4PH=0X00;
			P5CON =0xFF;
			P5PH=0X00;
			P0=0;
			P1=0;
			P2&=0X08;// P23保持不变
			P3=0;
			P4=0;
			P5=0; 
 }

 
 void Task_Sleep()
 {
	PCON |= 0x02;	//PCON的bit1 STOP位写1，配置MCU进入STOP模式
	_nop_();		//至少需要8个_nop_()
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TKCR |=0x80;
	Delay1ms();
	Delay1ms();
	Delay1ms();
	Delay1ms();
 }
 
