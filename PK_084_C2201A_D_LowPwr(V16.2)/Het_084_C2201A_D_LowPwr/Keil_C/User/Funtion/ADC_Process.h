#ifndef __ADC_PROCESS_H__
#define __ADC_PROCESS_H__

extern void SC_ADC_EXIRChange(uint8_t ADC_CHANNEL9_NUM);
extern void SC_ADC_BatChange(uint8_t ADC_CHANNEL1_NUM);
extern void SC_ADC1_Multichannal();
extern void SC_ADC9_Multichannal();
extern void ADC_Process(void);
extern void ADC_ExtIR_Check(void);

#endif    