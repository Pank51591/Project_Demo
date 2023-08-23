#include "SC_System.h"

/*****************************************************
*函数名称: SC_Init
*函数功能: MCU初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_Init(void)
{
	SC_GPIO_Init();
	SC_OPTION_Init();
	SC_GPIO_LowOutput();
	SC_TIM0_Init();
	SC_TIM1_Init();
	SC_PWM0_Init();
//	SC_PWM2_Init();
	SC_PWM3_Init();
	SC_INT_Init();
	SC_ADC_Init();
	SC_WDT_Init();
	SC_EXtern_Init();

}

/*****************************************************
*函数名称: SC_OPTION_Init
*函数功能: OPTION配置初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_OPTION_Init(void)
{
	/*OPTION_Init write here*/		
}

/*****************************************************
*函数名称: SC_GPIO_Init
*函数功能: GPIO初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_GPIO_Init(void)
{
	GPIO_Init(GPIO1, GPIO_PIN_4, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_2, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_3, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_5, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_6, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO5, GPIO_PIN_2, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO5, GPIO_PIN_3, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO5, GPIO_PIN_4, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO5, GPIO_PIN_5, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO4, GPIO_PIN_7, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO4, GPIO_PIN_6, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO4, GPIO_PIN_5, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO4, GPIO_PIN_4, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO4, GPIO_PIN_3, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO4, GPIO_PIN_1, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO3, GPIO_PIN_7, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO3, GPIO_PIN_6, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO3, GPIO_PIN_4, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO3, GPIO_PIN_3, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO3, GPIO_PIN_2, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO3, GPIO_PIN_1, GPIO_MODE_IN_PU); /* 面板选择厚度 */
	GPIO_Init(GPIO3, GPIO_PIN_0, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO1, GPIO_PIN_0, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO1, GPIO_PIN_1, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO1, GPIO_PIN_2, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO1, GPIO_PIN_3, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO2, GPIO_PIN_3, GPIO_MODE_OUT_PP);   // P2.3输出
	GPIO_Init(GPIO2, GPIO_PIN_5, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO2, GPIO_PIN_6, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO2, GPIO_PIN_7, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_0, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO0, GPIO_PIN_1, GPIO_MODE_OUT_PP);
	GPIO_Init(GPIO2, GPIO_PIN_3, GPIO_MODE_OUT_PP);
	SC_GPIO_LowOutput();
	/*GPIO_Init write here*/		
}

void SC_GPIO_LowOutput(void)
{
	P02 = 0;
	P03 = 0;
	P05 = 0;
	P06 = 0;
	P52 = 0;
	P53 = 0;
	P54 = 0;
	P55 = 0;
	P47 = 0;
	P46 = 0;
	P45 = 0;
	P44 = 0;
	P43 = 0;
	P41 = 0;
	P36 = 0;
	P34 = 0;
	P33 = 0;
	P32 = 0;
	P30 = 0;
	P10 = 0;
	P11 = 0;
	P12 = 0;
	P13 = 0;
	P14 = 0;
	P25 = 0;
	P26 = 0;
	P27 = 0;
	P00 = 0;
	P01 = 0;
	P23 = 1;
}


/*****************************************************
*函数名称: SC_TIM0_Init
*函数功能: TIMER0初始化函数   （705us中断一次）
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_TIM0_Init(void)
{
	TIM0_TimeBaseInit(TIM0_PRESSEL_FSYS_D12, TIM0_MODE_TIMER);
	TIM0_WorkModeConfig(TIM0_WORK_MODE1, Time_705us, 0);
	TIM0_ITConfig(ENABLE, HIGH);
	TIM0_Cmd(ENABLE);
	/*TIM0_Init write here*/		
}

/*****************************************************
*函数名称: SC_TIM1_Init
*函数功能: TIMER1初始化函数    （1ms中断一次）
*入口参数：void
*出口参数：void
*****************************************************/
void SC_TIM1_Init(void)
{
	TIM1_TimeBaseInit(TIM1_PRESSEL_FSYS_D12, TIM1_MODE_TIMER);
	TIM1_WorkModeConfig(TIM1_WORK_MODE1, Time_1ms);
	TIM1_ITConfig(ENABLE, HIGH);
	TIM1_Cmd(ENABLE);
	/*TIM1_Init write here*/	
}



/*****************************************************
*函数名称: SC_PWM0_Init
*函数功能: PWM0初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM0_Init(void)
{
	/*PWM0独立模式*/ PWM_Init(PWM0_PRESSEL_FHRC_D8, 111);
	/*PWM05 独立模式*/ PWM_IndependentModeConfigEX(PWM05, 0, PWM_OUTPUTSTATE_ENABLE);
	/*PWM07 独立模式*/ PWM_IndependentModeConfigEX(PWM07, 0, PWM_OUTPUTSTATE_ENABLE);
	/*PWM0*/ PWM_Aligned_Mode_Select(PWM0_Edge_Aligned_Mode);
	/*PWM0*/ PWM_FaultDetectionConfigEX(PWM0_Type, DISABLE);
	/*PWM0*/ PWM_FaultDetectionModeConfigEX(PWM0_Type, PWM0_Immediate_Mode, PWM0_FaultDetectionVoltage_Low, PWM0_WaveFilteringTime_0us);
	/*PWM0中断使能*/ PWM_ITConfigEX(PWM0_Type, DISABLE, LOW);
	/*PWM0开关*/ PWM_CmdEX(PWM0_Type, ENABLE);
	/*PWM0_Init write here*/	
}



/*****************************************************
*函数名称: SC_PWM2_Init
*函数功能: PWM1初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM2_Init(void)
{
	PWM_Init(PWM2_PRESSEL_FHRC_D1, PWM_1KPressel);				  /*PWM2初始化*/
	PWM_IndependentModeConfigEX(PWM20, 31999, PWM_OUTPUTSTATE_ENABLE); /*PWM20 独立模式*/
	PWM_ITConfigEX(PWM2_Type, DISABLE, LOW);					  /*PWM2中断使能*/
	PWM_CmdEX(PWM2_Type, ENABLE);
	/*PWM2_Init write here*/	
}

/*****************************************************
*函数名称: SC_PWM3_Init
*函数功能: PWM1初始化函数    蜂鸣器
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_PWM3_Init(void)
{
	PWM_Init(PWM3_PRESSEL_FHRC_D1, PWM_4KPressel);			   /*PWM3初始化*/
	PWM_IndependentModeConfigEX(PWM30, 0, PWM_OUTPUTSTATE_ENABLE); /*PWM30 独立模式*/
	PWM_ITConfigEX(PWM3_Type, DISABLE, LOW);				   /*PWM3中断使能*/
	PWM_CmdEX(PWM3_Type, ENABLE);							   /*PWM3开关*/
	/*PWM3_Init write here*/	
}

void SC_PWM3_Init_2Khz(void)
{
	PWM_Init(PWM3_PRESSEL_FHRC_D1, PWM_2KPressel);			   /*PWM3初始化*/
	PWM_IndependentModeConfigEX(PWM30, 0, PWM_OUTPUTSTATE_ENABLE); /*PWM30 独立模式*/
	PWM_ITConfigEX(PWM3_Type, DISABLE, LOW);				   /*PWM3中断使能*/
	PWM_CmdEX(PWM3_Type, ENABLE);							   /*PWM3开关*/
}

void SC_PWM3_Init_41Khz(void)
{
	PWM_Init(PWM3_PRESSEL_FHRC_D1, PWM_4_1KPressel);			   /*PWM3初始化*/
	PWM_IndependentModeConfigEX(PWM30, 0, PWM_OUTPUTSTATE_ENABLE); /*PWM30 独立模式*/
	PWM_ITConfigEX(PWM3_Type, DISABLE, LOW);				   /*PWM3中断使能*/
	PWM_CmdEX(PWM3_Type, ENABLE);							   /*PWM3开关*/
}
void SC_PWM3_Init_33Khz(void)
{
	PWM_Init(PWM3_PRESSEL_FHRC_D1, PWM_3_3KPressel);			   /*PWM3初始化*/
	PWM_IndependentModeConfigEX(PWM30, 0, PWM_OUTPUTSTATE_ENABLE); /*PWM30 独立模式*/
	PWM_ITConfigEX(PWM3_Type, DISABLE, LOW);				   /*PWM3中断使能*/
	PWM_CmdEX(PWM3_Type, ENABLE);							   /*PWM3开关*/
}

/*****************************************************
*函数名称: SC_INT_Init
*函数功能: INT初始化函数
*入口参数：void
*出口参数：void
*****************************************************/
void SC_INT_Init(void)
{
	GPIO_Init(GPIO2, GPIO_PIN_0, GPIO_MODE_IN_PU);
	GPIO_Init(GPIO2, GPIO_PIN_1, GPIO_MODE_IN_PU);
	GPIO_Init(GPIO2, GPIO_PIN_2, GPIO_MODE_IN_PU);
	GPIO_Init(GPIO1, GPIO_PIN_6, GPIO_MODE_IN_PU);
	GPIO_Init(GPIO1, GPIO_PIN_7, GPIO_MODE_IN_PU);
	GPIO_Init(GPIO0, GPIO_PIN_4, GPIO_MODE_IN_PU);
	INT2_SetTriggerMode(0x00 | INT20 | INT21 | INT22, INT_TRIGGER_RISE_FALL);
	INT2_ITConfig(ENABLE, LOW);
	INT1_SetTriggerMode(0x00 | INT16 | INT17, INT_TRIGGER_RISE_FALL);
	INT1_ITConfig(ENABLE, LOW);
	INT0_SetTriggerMode(0x00 | INT04, INT_TRIGGER_RISE_FALL);
	INT0_ITConfig(ENABLE, LOW);
	/*INT_Init write here*/
	/*INT_Init write here*/	
}

/*****************************************************
*函数名称: SC_ADC_Init
*函数功能: ADC初始化函数
*入口参数：void
*出口参数：void 
*****************************************************/
void SC_ADC_Init(void)
{
	ADC_Init(ADC_PRESSEL_32CLOCK, ADC_Cycle_Null);
	ADC_EAINConfig(ADC_EAIN_1, ENABLE); /*AIN1口模式设置，设置为ADC口，去除上拉*/
	ADC_EAINConfig(ADC_EAIN_9, ENABLE); /*AIN9口模式设置，设置为ADC口，去除上拉*/
	ADC_ChannelConfig(ADC_CHANNEL_9, ENABLE);/* ADCCON选择通道 */
	ADC_ITConfig(DISABLE, LOW);/* ADCCON|=0X80; */
	ADC_Cmd(ENABLE);/* 先关闭 */
	/*ADC_Init write here*/
}

/*****************************************************
 *函数名称: SC_WDT_Init
 *函数功能: 看门狗初始化函数
 *入口参数：void
 *出口参数：void
 *****************************************************/
void SC_WDT_Init(void)
{
	WDT_Init(WDT_OverflowTime_500MS);
	OPTION_WDT_Cmd(ENABLE);
	/*WDT_Init write here*/
}
/*****************************************************
 *函数名称: SC_EXtern_Init
 *函数功能: 32K晶振初始化函数
 *入口参数：void
 *出口参数：void
 *****************************************************/

void SC_EXtern_Init(void)
{
	OPTION_XTIPLL_Cmd(ENABLE);
}

/* 选择完面板厚度后将管脚设置推挽关闭，达到省电 */
void Clr_IO(void)
{
	Delay1ms();
	GPIO_Init(GPIO3, GPIO_PIN_1, GPIO_MODE_OUT_PP);
	Delay1ms();
	P31 = 0;
}