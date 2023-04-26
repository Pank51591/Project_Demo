////////////////////////////////////////////////////////////////////////////////
/// @file     tim1_interrupt.c
/// @author   AE TEAM
/// @brief    PWM output.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////
// Define to prevent recursive inclusion
#define _TIM1_INTERRUPT_C_
// Files includes

#include "tim1_interrupt.h"
#include "led.h"
#include "LED_RF.h"
#include "key.h"
#include "RF_A7325.h"
#include "089_B19110A.h"
#include "test.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM1_INTERRUPT
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM1_Exported_Functions
/// @{


extern u32 SystemCoreClock;
extern volatile unsigned int  giCheckIWDGTimeCount;
extern uint16_t giKeyAddDelay_Count;
extern uint8_t TimeAdd_sta;
extern volatile unsigned char gc10msCount;

uint8_t gcOneMsCount;
uint8_t TestFlag;
uint16_t giIWDGStandTime;


////////////////////////////////////////////////////////////////////////////////
/// @brief  Tim1 Base initialization configuration
/// @note
/// @param  psc: Clock frequency division value.  ��ʱ�ӷ�Ƶֵ��
/// @param  arr: Preloading value.  ��Ԥ����ֵ��
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1, ENABLE);   //ʱ�Ӻ͸�λ����ʹ��

    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);        //����Ĭ��ֵ���TIM�йؽṹ��ĳ�Ա
	
    TIM_TimeBaseStruct.TIM_Period = arr;         // ���ü��������С��ÿ�� arr �����Ͳ���һ�������¼�  ����100��
    TIM_TimeBaseStruct.TIM_Prescaler = psc;      //  24Mhz / 240 = 100Khz   ������10 us
	
    //Setting Clock Segmentation
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;   //ʱ�ӷ�Ƶ
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;          //�ظ�������  �����ֵ������ó� 1,2,3 ������ʱ��ͻ��ӳ���Ӧ�ı�����
	
	  //TIM Upward Counting Mode
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);     //��ʼ��timʱ����Ԫ��Χ�豸

    TIM_ARRPreloadConfig(TIM1, ENABLE);           //���û����ARR�ϵ�tim��Χ�豸Ԥ���ؼĴ�����
	
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);         //���tim�Ĺ����־��
		
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);    //���û����ָ����TIM�ж�Դ��  TIM�����ж�Դ  

    TIM_Cmd(TIM1, ENABLE);    //���û����ָ����TIM��Χ�豸��
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC Configure, Applicable to Cortex M0 or M3 processors.
/// @param  NVIC Channel, Priority or SubPriority.
/// @arg    ch: IRQChannel  �жϵ�ͨ��
/// @arg    pri: Priority, Use only Cortex-M3  ���ȼ�
/// @arg    sub: SubPriority  �����ȼ�
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void NVIC_Configure(u8 ch, u8 pri, u8 sub)   
{
    exNVIC_Init_TypeDef  NVIC_InitStruct;

    NVIC_InitStruct.NVIC_IRQChannel = ch;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = pri;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = sub;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    exNVIC_Init(&NVIC_InitStruct);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  IRQ Handler    ����ʱ���жϵĴ�������  1ms
/// @note   If the program fails, see here.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)   //���TIM�ж��Ƿ��ѷ����� 			
		{
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);    //���tim���жϹ���λ��
			
////////        gcOneMsCount++;
			
				if(IWDGCheck_Flag)
				{
					giCheckIWDGTimeCount++;
				}
				
				/*	gc1MsCount++;*/
					if(Isintest_flag == 0)    //�û�ģʽ
					{
						gc10msCount++;     //�ӵ���10��ʱ����ʾ��ʱΪ10ms
						
						
						
						if(LEDon_Flag)
						{
								led_process();   //LED�Ĵ���	
      							
						}
						
						if((Ptcol_TimeSet != timerconti)&&(Ptcol_TimeSet != 0x00))
						{
						//	gi1sCount++;		
						}
						
						if(KeyAddDelay_flag)
						{
							if(giKeyAddDelay_Count < 2000)
							{
								giKeyAddDelay_Count++;
							}
							
							/* ������ʱ�� ��ʱʱ���ۼ��ٶ� 1s, 1.3s, 1.6s, 1.9s */
							if((giKeyAddDelay_Count == 1000)||(giKeyAddDelay_Count == 1300)\
												||(giKeyAddDelay_Count == 1600)||(giKeyAddDelay_Count == 1900))
							{
								TimeAdd_sta = 2;
							}			
						}
											
						if(RfwaitXams_Flag)	   //�ȴ�Xams
						{
							gcRfXamsCount++;
							if(gcRfXamsCount >= RfwaitXams)
							{
								Clr_RfwaitXams_Flag;
								Set_RfwaitXbms_Flag;		
							}	
						}
						
						if(RfwaitXbms_Flag)	   //�ȴ�Xbms
						{
							gcRfXbmsCount++;
							if(gcRfXbmsCount >= RfwaitXbms)
							{
								Clr_RfwaitXbms_Flag;		
							}	
						}
								
						if(Rfwait500ms_Flag)    //�ȴ�500ms
						{
							giRf500msCount++;
							if(giRf500msCount >= 500)
							{
								Clr_Rfwait500ms_Flag;
								giRf500msCount = 0;		
							}			
						}		
					}
					else      //����ģʽ
					{
						Testled_scan();     //LED����Ĳ���
						
						if(gcTest_state != 7)
						{
							giTestTimeSecCnt++;
							if(giTestTimeSecCnt >= 1000)
							{
								giTestTimeSecCnt = 0;
								giTestTimeMinCnt++;	
							}	
						}
						if(giTestTimeMinCnt >= 180)    //3����
						{
							//_rstc =0xff;        //��λ	
							Clr_Isintest_flag;		//�Լ�ʱ�䳬��3�����˳��Լ�
						}		
						
						
						if(gcTest_state == 2)
						{
							Testled_horseCnt++;	
						}
						else if((gcTest_state == 1)||(gcTest_state == 4))
						{
							Testled_BlinkCnt++;	
						}
						else if(gcTest_state == 5)
						{
							if(gcTestRfXamsCnt <60)
							{
								gcTestRfXamsCnt++;
								if(gcTestRfXamsCnt >= 60)
								{
									gcTestTxRf_flag = 1;
								}				
							}
					
						}
						
					}			
    }
}
/// @}
/// @}
/// @}


