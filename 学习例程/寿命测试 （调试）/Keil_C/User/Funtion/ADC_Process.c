#include "SC_System.h"
 void SC_ADC_EXIRChange(uint8_t ADC_CHANNEL9_NUM);
 void SC_ADC_BatChange(uint8_t ADC_CHANNEL1_NUM);
 void SC_ADC1_Multichannal();
 void SC_ADC9_Multichannal();

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

extern uint32_t gllIRAdcSumValue;
extern uint16_t giIRADCValue;
extern uint8_t gcIRADCCount;
extern uint16_t gcCookingTimes;
extern unsigned char Readbuff[12];
extern uint8_t RadioFREQ[10];

extern void Write_EEPROM(void);

extern volatile uint8_t gcADCDelayTime;
uint32_t gllBatAdcSumValue = 0;
uint16_t giBatValue = 0;
uint8_t gcBatAdcCount = 0;
uint16_t giADCValue = 0;
uint8_t gcBatLowCount = 0;

void Delay_Time(uint16_t Count)
{
    uint16_t i = 0;
    for (i = 0; i < Count; i++)
    {
        //        asm("NOP");
    }
}

void ADC_ExtIR_Check(void)    /* 上电检查 */
{
    uint8_t i = 0;
    Set_ExternalIR_Send1;
	  Delay1ms(); 
		Delay1ms(); 
	  Delay1ms(); 
	  Delay1ms(); 
	  Delay1ms();
	  Delay1ms(); 
		Delay1ms(); 
	  Delay1ms(); 
	  Delay1ms(); 
	  Delay1ms();	
    SC_ADC_EXIRChange(4);   /* 上电默认是第九通道启动，直接转换即可 */
	
		if ((giIRADCValue > EXTIR_ADC_MIN_VALUE)&&(giIRADCValue < EXTIR_ADC_MAX_VALUE))
		{
			Set_ExtIRFlag;
		}
		else
		{
			Clr_ExtIRFlag;
		}
		/*
    if (giIRADCValue >= EXTIR_ADC_VALUE)
    {
        Clr_ExtIRFlag;
    }
    else
    {
        Set_ExtIRFlag;
    }*/
    Clr_ExternalIR_Send;
		
    Set_BAT_EN; /* 打开电池检测的三极管管脚 */
    SC_ADC1_Multichannal();
    SC_ADC_BatChange(4);
    Clr_ExternalIR_Send;
}

void ADC_Process(void)
{
	  Set_BAT_EN; /* 打开电池检测的三极管管脚 */
	
    SC_ADC1_Multichannal();/* 先切换通道再转化 */
    SC_ADC_BatChange(16);/*切换转换出值 */
	
		if (BatLowWarrnEnFlag)
		{
			if (giBatValue < VOL_LOW_VALUE)
			{
				gcBatLowCount ++;
				if (gcBatLowCount >= 200)
				{
						gcBatLowCount = 0;
						Set_BatLowWarrnFlag;
					  Set_ToEEPROMFlag;      //设置低电压存储
					
					if(ToEEPROMFlag)         //如果发生低电压报警，就存储
					{		
							Clr_ToEEPROMFlag;
							Clr_BatLowWarrnEnFlag;      //禁止低电压检测 （保证这段程序只在低电压的时候跑一次）
						  gcCookingTimes = 124;  
						
							RadioFREQ[0] =  gcCookingTimes / 1000;          
							RadioFREQ[1] =  gcCookingTimes / 100 % 10; 
							RadioFREQ[2] =  gcCookingTimes / 10 % 10;				
							RadioFREQ[3] =  gcCookingTimes % 10;	
							RadioFREQ[4] =  0x01;
									
							Write_EEPROM();	
					}
				}
				
				
				
			}
			else
			{
				gcBatLowCount = 0;
			}
		}
}
/* -----ADC转换函数------- */
/* ===ADC_CHANNEL_NUM是转换次数============= */
void SC_ADC_EXIRChange(uint8_t ADC_CHANNEL9_NUM)
{
    uint8_t i;
    gllIRAdcSumValue = 0;
    giADCValue = 0;
    for (i = 0; i < ADC_CHANNEL9_NUM; i++)
    {
        ADCCON |= 0x40; //开始ADC转换
        while (!(ADCCON & 0x20));
        //等待标志位（不同的型号该寄存器的标志位不同，需要该，下一句同样）
        ADCCON &= 0xDF; //清标志位
        giADCValue = (ADCVH << 4) + (ADCVL >> 4);
        gllIRAdcSumValue += giADCValue;
    }
    giIRADCValue = gllIRAdcSumValue / ADC_CHANNEL9_NUM; //返回数值
}

void SC_ADC_BatChange(uint8_t ADC_CHANNEL1_NUM)
{
    uint8_t i;
    giADCValue=0;//
    gllBatAdcSumValue=0;
    for (i = 0; i < ADC_CHANNEL1_NUM; i++)
    {
        ADCCON |= 0x40; //开始ADC转换
        while (!(ADCCON & 0x20));
        //等待标志位（不同的型号该寄存器的标志位不同，需要该，下一句同样）
        ADCCON &= 0xDF; //清标志位
        giADCValue = (ADCVH << 4) + (ADCVL >> 4);
        gllBatAdcSumValue += giADCValue;
    }
    giBatValue = gllBatAdcSumValue / ADC_CHANNEL1_NUM; //返回数值
    /* >16次  gllBatAdcSumValue是否要清零*/
}


/* -------ADC双通道轮流切换---------- */
void SC_ADC1_Multichannal()
{
    ADC_Cmd(ENABLE);
    ADC_ChannelConfig(ADC_CHANNEL_1, ENABLE); /* 切换AIN 1 */
    /* 转换出BAT_VOL值 */
}

void SC_ADC9_Multichannal()
{
    ADC_Cmd(ENABLE);
    ADC_ChannelConfig(ADC_CHANNEL_9, ENABLE); /*切换AIN 9 */
    /* 转换出值IR值 */
}