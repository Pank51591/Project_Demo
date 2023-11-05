#include"config.h"
#include"appADC.h"



#define ADC_DISABLED	0xFF



APPADC gAppadc[ADC_CH_NUM];


void AppADCInit(void)
{
	gAppadc[0].en = 1;
	gAppadc[0].channel = ADC_CHANNEL_4;
	gAppadc[0].average = 0;
	gAppadc[0].proc = GetNTCTemp;

	gAppadc[1].en = 1;
	gAppadc[1].channel = ADC_CHANNEL_1;
	gAppadc[1].average = 0;
	gAppadc[1].proc = GetnetTDS;//原水和纯水换了位置

	gAppadc[2].en =1;
	gAppadc[2].channel = ADC_CHANNEL_3;
	gAppadc[2].average = 0;
	gAppadc[2].proc = GetrawTDS;//原水和纯水换了位置	
	
	gAppadc[3].en =1;
	gAppadc[3].channel = ADC_CHANNEL_2;
	gAppadc[3].average = 0;
	gAppadc[3].proc = GetLeakADC;

	gAppadc[4].en =1;
	gAppadc[4].channel = ADC_CHANNEL_0;
	gAppadc[4].average = 0;
	gAppadc[4].proc = GetPumpADC;

	gAppadc[5].en =1;
	gAppadc[5].channel = ADC_CHANNEL_5;
	gAppadc[5].average = 0;
	gAppadc[5].proc = GetNTCTemp2;	

}

INT8U AppADCSetProc(ADCITEM id,ADCPROC proc)
{
	if(id>=ADC_CH_NUM)
	{
		return 0;
	}
	gAppadc[id].proc = proc;

	return 1;
}


FP32 GetVoltageValue(FP32 vdd,ADCVAL adval)
{
	FP32 ftemp;

	ftemp = (vdd*adval)/4096;

	return ftemp;
}

void AppADCStart(INT8U ch)
{
	gAppadc[ch].en = 1;
}

void AppADCStop(INT8U ch)
{
	gAppadc[ch].en = 0;
}


//冒泡排序
void bubble_sort(unsigned short a[], int n)   
{
    int i,j,temp;    
    
    for (j=0;j<n-1;j++)     
    {                           
        for (i=0;i<n-1-j;i++)
        {
            if(a[i]>a[i+1]) 
            {
                temp=a[i];     
                a[i]=a[i+1];    
                a[i+1]=temp;
            }
        }
    }    
}

INT16U MA(INT16U *pbuf,INT8U len)
{
	INT32U temp=0;
	
	bubble_sort(pbuf,len);

	//去掉前面最小3个，后面最大3个，中间10个取平均值
	for(int i=3;i<len-3;i++)
	{
		temp += pbuf[i];
	}

	return temp/(len-6);
}


INT8U GetChannalADCVal(INT8U ch,INT16U *val)
{
	static INT8U rawstep=0,netstep=0;
	
	switch(ch)
	{
	case ADC_CH_TDS_temp:
		*val = GetADCValues();
		break;
	case ADC_CH_TDS_raw:
		if(rawstep==0)
		{
			rawstep=1;
			Set_rawTDS_Out_Forward();

			return 0;
		}
		else 
		{	
			rawstep=0;
			Set_rawTDS_Out_Reverse();
			delayus(800);
			*val = GetADCValues();
			Set_rawTDS_Out_Close();			
		}
		break;
	case ADC_CH_TDS_net:
		if(netstep==0)
		{
			netstep=1;
			Set_netTDS_Out_Forward();

			return 0;
		}
		else 
		{	
			netstep=0;
			Set_netTDS_Out_Reverse();
			delayus(800);
			*val = GetADCValues();
			Set_netTDS_Out_Close();			
		}	
		break;
	case ADC_CH_leak:                                                                                          
		*val = GetADCValues();
		break;
	case ADC_CH_pumpA:
		*val = GetADCValues();
		break;
	case ADC_CH_TDS_temp2:
		*val = GetADCValues();
		break;		
	}

	return 1;
}


void MonitorAppADC(void)
{
	INT8U ch;
	INT16U val;

	
	for(ch=0;ch<ADC_CH_NUM;ch++)
	{
		if(gAppadc[ch].en)
		{
			ADC_Start(gAppadc[ch].channel);	

			if(GetChannalADCVal(ch,&val))
			{
				gAppadc[ch].adBuff[gAppadc[ch].collectcount] = val;
				gAppadc[ch].collectcount++;

				if(gAppadc[ch].collectcount>=MA_NUM)
				{
					gAppadc[ch].average = MA(gAppadc[ch].adBuff,MA_NUM);
					gAppadc[ch].proc(gAppadc[ch].average);
				
					gAppadc[ch].collectcount = 0;
				}
			}	
		}
	}
}

