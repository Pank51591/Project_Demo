#include"config.h"
#include"VoltageADC.h"

#if 1

#define VOLT_ADC_REF	3.3// 3.3 参考电压
#define VOLT_ADC_R		10000//10k分压电阻

// R15=1.2M,R22=300k

	
INT32U i32ConversionData[4];// 0为水泵1,1为水泵2检测，2为电池，3为按键
//volatile uint32_t g_u32AdcIntFlag=1;


void GetADCData(void);


void VoltageADCHandle(void)
{
	//static INT32U icount=0;
	//INT32U val;


	
	GetADCData();


}





void GetADCData(void)
{
	#if 0
	/* Power on ADC module */
	ADC_POWER_ON(ADC);
	
	/* Set the ADC operation mode as single, input mode as single-end and enable the analog input channel 2 */
	ADC_Open(ADC, ADC_ADCR_DIFFEN_SINGLE_END, ADC_ADCR_ADMD_SINGLE_CYCLE, 0x17);// 0x71

	/* clear the A/D interrupt flag for safe */
	ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);

	/* Enable the ADC interrupt */
	ADC_EnableInt(ADC, ADC_ADF_INT);
	NVIC_EnableIRQ(ADC_IRQn);

	/* Reset the ADC interrupt indicator and Start A/D conversion */
	//g_u32AdcIntFlag = 0;
	ADC_START_CONV(ADC);
	
#endif
#if 0
	/* Wait ADC interrupt (g_u32AdcIntFlag will be set at IRQ_Handler function)*/
	while(g_u32AdcIntFlag == 0);

	/* Disable the ADC interrupt */
	ADC_DisableInt(ADC, ADC_ADF_INT);

	/* Get the conversion result of the ADC channel 2 */
	i32ConversionData[2] = ADC_GET_CONVERSION_DATA(ADC, 4);

    ADC_STOP_CONV(ADC);
#endif    
}







/*---------------------------------------------------------------------------------------------------------*/
/* ADC interrupt handler                                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
void ADC_IRQHandler(void)
{
    //g_u32AdcIntFlag = 1;
//    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT); /* clear the A/D conversion flag */
#if 0
    /* Disable the ADC interrupt */
	ADC_DisableInt(ADC, ADC_ADF_INT);

	/* Get the conversion result of the ADC channel 2 */
	i32ConversionData[3] = ADC_GET_CONVERSION_DATA(ADC, 0);
	i32ConversionData[2] = ADC_GET_CONVERSION_DATA(ADC, 2);
	i32ConversionData[0] = ADC_GET_CONVERSION_DATA(ADC, 1);
	i32ConversionData[1] = ADC_GET_CONVERSION_DATA(ADC, 4);
	ADC_STOP_CONV(ADC);
#endif	
}



#endif


