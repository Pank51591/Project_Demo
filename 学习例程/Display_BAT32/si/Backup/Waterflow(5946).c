#include"config.h"
#include"Waterflow.h"

void IRQ01_Handler(void) __attribute__((alias("intp_0_6_interrupt")));
void IRQ26_Handler(void) __attribute__((alias("tma0_interrupt")));


uint32_t 	SysTick1ms;
uint16_t 	SysTick1msD=0;
uint32_t 	SysTick1msC = 0;

FlowMeterTypedef FlowMeter1st = {0};
FlowMeterTypedef FlowMeter2nd = {0};


void intp_0_6_interrupt(void)
{
	volatile uint8_t ifl, ifh;

	ifl = INTC_GetPendingIRQ(INTP0_IRQn);
	ifh = INTC_GetPendingIRQ(INTP6_IRQn);

	if(ifl)
	{
		INTC_ClearPendingIRQ(INTP0_IRQn);

		if((SysTick1msD >= 5)&&(SysTick1msD < 400))
		{
					if(FlowMeter2nd.PulseCnt < 250)
						FlowMeter2nd.PulseCnt ++;
		}
		SysTick1msD = 0;
	}

	if(ifh)
	{
		INTC_ClearPendingIRQ(INTP6_IRQn); 
		if((SysTick1msC >= 5)&&(SysTick1msC < 400))
		{
					if(FlowMeter1st.PulseCnt < 250)
						FlowMeter1st.PulseCnt ++;
		}
		SysTick1msC = 0;
	}
}




static void tma0_interrupt(void)
{
    //INTC_ClearPendingIRQ(TMA_IRQn); /* clear INTTMA interrupt flag */
    R_INT->IF[TMA_IRQn].IFL = 0;
    /* Start user code. Do not edit comment generated here */
    if ((TMA->TACR0 & _20_TMA_UNDERFLOW_OCCUR) != 0U)
    {
        TMA->TACR0 &= (uint8_t)~_20_TMA_UNDERFLOW_OCCUR;
			
			  TMA->TACR0 &= (uint8_t)~_01_TMA_COUNT_START;
				INTC_DisableIRQ(TMA_IRQn);/* disable INTTMA interrupt */


    }
    /* End user code. Do not edit comment generated here */
}







/***********************************************************************************************************************
* Function Name: ExternalInterruptInit
* @brief  INTP0 or INTP6 interrupt entry
* @param  None
* @return None
***********************************************************************************************************************/
void ExternalInterruptInit(void)
{
	PORT_Init(PORT14,PIN0,PULLUP_INPUT);
	INTP_Init(FlowMeter1_EXTI_CHANNEL,INTP_FALLING);
	INTP_Start(FlowMeter1_EXTI_CHANNEL);
	
	
	PORT_Init(PORT13,PIN6,PULLUP_INPUT);
	INTP_Init(FlowMeter2_EXTI_CHANNEL,INTP_FALLING);
	INTP_Start(FlowMeter2_EXTI_CHANNEL);
}






/*********************************************************************
Function:GetFlowMeterPulse
Brief:
Param:
Return:
Description:
Example:
**********************************************************************/
uint8_t GetFlowMeterPulse(FlowMeterTypedef *FlowMeter)
{
	uint32_t t = SysTick1ms;
	uint32_t t1 = 0;
	
	if(t < FlowMeter->SampleTime)
	{
		t1 = 0xffffffff - FlowMeter->SampleTime + t;
	}
	else
	{
		t1 = t - FlowMeter->SampleTime;
	}
	
	if(t1 >= 1000)              //1s计算一次
	{
		FlowMeter->SampleTime = t;
		FlowMeter->PulsePerSec = FlowMeter->PulseCnt;



		FlowMeter->TotalPulse += FlowMeter->PulsePerSec;
		FlowMeter->PerPulse += FlowMeter->PulsePerSec;
		FlowMeter->PulseCnt = FlowMeter->PulseCnt - FlowMeter->PulsePerSec;     //脉冲计数清零，防止计算这两行的时候遗漏中断来的1个脉冲

		return 1;
	}
	return 0;
}
/*********************************************************************
Function:UpdataFlowMeterWaterVolume
Brief:
Param:
Return:
Description:
Example:		
**********************************************************************/
void UpdataFlowMeterWaterVolume(void)//10ms
{
	static INT16U delaytimes=2000;
	float vol = 0;
	
	if(GetFlowMeterPulse(&FlowMeter1st))		// 	1S
	{
		FlowMeter1st.VolumePerSec = FlowMeter1st.PulsePerSec * C_FlowMeter1st_mLPerPulse;// 1秒的流量，单位mL
		vol = FlowMeter1st.VolumePerSec * 60;
		systemseting.FlowMeterBeforeVelocity = vol;				// 前置流量计的流速，单位mL/min
		
		FlowMeter1st.PerVolume 	+= FlowMeter1st.VolumePerSec;
		FlowMeter1st.TotalVolume += FlowMeter1st.VolumePerSec;
		
		gReg.RawWaterVolume += FlowMeter1st.VolumePerSec;		// 总水量
		systemseting.PerAutoRawUL += FlowMeter1st.VolumePerSec;	// 单次制水量
		
		if(systemseting.PowerOnPumpMakeWater2H >= 7200)
		{
			//systemseting.PPPumpMakeWaterValuemL += FlowMeter1st.VolumePerSec;// PPC 水量寿命  单位mL
		}
		//uart_printf("flow speed=%d",systemseting.FlowMeterBeforeVelocity);
	}
	
	if(GetFlowMeterPulse(&FlowMeter2nd))
	{
		FlowMeter2nd.VolumePerSec = FlowMeter2nd.PulsePerSec * C_FlowMeter2nd_mLPerPulse;
		FlowMeter2nd.PerVolume += FlowMeter2nd.VolumePerSec;
		FlowMeter2nd.TotalVolume += FlowMeter2nd.VolumePerSec;
	}

	if(gReg.WorkState==WORKSTATE_live)
	{
		if(delaytimes)//延时2秒不检测
		{
			delaytimes--;
			return;
		}
		
		if(systemseting.FlowMeterBeforeVelocity==0)//没有流量
		{
			systemseting.WaterFlowError=1;
		}
		else 
		{
			systemseting.WaterFlowError=0;
		}
	}
	else 
	{
		delaytimes=2000;
		systemseting.WaterFlowError=0;
	}
	
}

/*********************************************************************
Function:ResetFlowMeterParam
Brief:
Param:
Return:
Description:
Example:
**********************************************************************/
void ResetFlowMeterParam(void)
{
	FlowMeter1st.PulseCnt= 0;
	FlowMeter1st.Err1Cnt= 0;        //流量计出错计数
	FlowMeter1st.Err2Cnt= 0;        //流量计出错计数
	FlowMeter1st.SensorError= 0;    //流量计故障，无水流时产生脉冲，或有水流时无脉冲
	FlowMeter1st.PulsePerSec= 0;    //每秒脉冲数
	FlowMeter1st.TotalPulse= 0;		//总计脉冲数
	FlowMeter1st.PerPulse= 0;
	FlowMeter1st.SampleTime= 0;
	FlowMeter1st.VolumePerSec= 0;	//每秒流量单位ml
	FlowMeter1st.PerVolume= 0;		//每秒流量单位ml
	FlowMeter1st.TotalVolume= 0;	//每秒流量单位ml

	FlowMeter2nd.PulseCnt= 0;
	FlowMeter2nd.Err1Cnt= 0;        //流量计出错计数
	FlowMeter2nd.Err2Cnt= 0;        //流量计出错计数
	FlowMeter2nd.SensorError= 0;    //流量计故障，无水流时产生脉冲，或有水流时无脉冲
	FlowMeter2nd.PulsePerSec= 0;    //每秒脉冲数
	FlowMeter2nd.TotalPulse= 0;		//总计脉冲数
	FlowMeter2nd.PerPulse= 0;
	FlowMeter2nd.SampleTime= 0;
	FlowMeter2nd.VolumePerSec= 0;	//每秒流量单位ml
	FlowMeter2nd.PerVolume= 0;		//每秒流量单位ml
	FlowMeter2nd.TotalVolume= 0;	//每秒流量单位ml
}

