#ifndef APP_ADC
#define APP_ADC


#define MA_NUM			16


typedef enum
{
	ADC_CH_TDS_temp,
	ADC_CH_TDS_raw,
	ADC_CH_TDS_net,
	ADC_CH_leak,//漏水检测
	ADC_CH_pumpA,//水泵电流	

	ADC_CH_TDS_temp2,
	ADC_CH_NUM,
}
ADCITEM;





typedef void (*ADCPROC)(INT16U val);


typedef struct
{
	INT8U en;
	adc_channel_t channel;
	INT8U collectcount;
	INT16U adBuff[MA_NUM];
	INT16U average;
	ADCPROC proc;
}
APPADC;

extern APPADC gAppadc[];

void AppADCInit(void);
void bubble_sort(unsigned short a[], int n);
INT16U MA(INT16U *pbuf,INT8U len);

void MonitorAppADC(void);

void AppADCStart(INT8U ch);
void AppADCStop(INT8U ch);


FP32 GetVoltageValue(FP32 vdd,ADCVAL adval);
INT8U AppADCSetProc(ADCITEM id,ADCPROC proc);



#endif

