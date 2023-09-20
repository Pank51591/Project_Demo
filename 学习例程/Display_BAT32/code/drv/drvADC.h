#ifndef DRV_ADC
#define DRV_ADC











void ADC1SingleChannelInit(void);

ADCVAL GetADCValues(void);	//channel = 0~7
void ADCTriggerConvertion(void);
void ADCUseChannel(INT8U channel);
void ADC_Start(adc_channel_t channel);



#endif

