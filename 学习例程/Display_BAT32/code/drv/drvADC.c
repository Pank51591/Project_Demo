#include"config.h"
#include"drvADC.h"


////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize LED GPIO pin
/// @note   if use jtag/swd interface GPIO PIN as LED, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC1SingleChannelInit(void)
{
 
}




void ADCUseChannel(INT8U adc_channel)
{
	//ADCxChannelEnable(ADC1, adc_channel);
	//ADC1->CHSR = (1 << adc_channel);
}



//触发AD转换
void ADCTriggerConvertion(void)
{
    //Register ADST bit enable, software start conversion
    //ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

static adc_channel_t ADCChannel;

ADCVAL GetADCValues(void)	
{	
	unsigned short int TEMP_data =0,te[5];

	TEMP_data = ADC_Converse(ADCChannel,1,te);

	return TEMP_data;
}


void ADC_Start(adc_channel_t channel)
{
	ADCChannel = channel;
	//ADC_Start1(channel);
}

#if 0

//AD转换中断
void ADC1_COMP_IRQHandler(void)
{

    //if(ADC_GetFlagStatus(ADC1, ADC_IT_AWD) != RESET) 
    {
        ;//ADCFlag = 1;
    }

    //ADC_ClearFlag(ADC1, ADC_IT_AWD);
}
#endif

