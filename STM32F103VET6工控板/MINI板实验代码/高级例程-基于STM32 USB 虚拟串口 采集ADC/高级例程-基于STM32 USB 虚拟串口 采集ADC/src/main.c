/****************************************
 * �ļ���  ��main.c
 * ����    ��ͨ�����⴮�ڣ��ɼ������ϵĵ�ѹֵ����ʾ�����ڵ�������򳬼��ն��ϡ�         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * ��汾  ��ST3.2.1  																										  
*********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "stm32f10x_tim.h"
#include "platform_config.h"

u8 comm = 0;
u8 ah,al;
u16 ad;	
u32 adzhi = 0;

u16 time = 0;

/*************************************************
����: void RCC_Configuration(void)
����: ��λ��ʱ�ӿ��� ����
����: ��
����: ��
**************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
  HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
  if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
    FLASH_SetLatency(FLASH_Latency_2);                    //flash��������ʱ
      	
    RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);                //����APB1(PCLK1)��==AHB1/2ʱ��
         
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
    RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
   
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
    while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
    {
    }
  }
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    //����AFIOʱ��

  /* Enable USB_DISCONNECT GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);

  /* Configure USB pull-up pin */
  GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);
}

/*******************************************************************************
	��������ADC_Configuration
	��  ��:
	��  ��:
	����˵��������ADC, PC0
*/
static void ADC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	volatile u16 ADCConvertedValue;

    /* ʹ�� ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOB, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);              //72M/6=12,ADC���ʱ�䲻�ܳ���14M

	
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB�˿�
  GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);	 // �ر�����LED

	/* ����PC0Ϊģ������(ADC Channel10) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ����ADC1, ����DMA, ������Լ����� */
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		 //ADC1����ģʽ:����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			 //��ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		 //����ת��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	  //ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	 //ADC1�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	   //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);		   //����ADC_InitStruct��ָ���Ĳ�������ʼ������ADC1�ļĴ���

	/* ADC1 regular channel10 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);	//ADC1,ADCͨ��10,�������˳��ֵΪ1,����ʱ��Ϊ239.5����

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);		  //ʹ��ADC1

	/* Enable ADC1 reset calibaration register */
	ADC_ResetCalibration(ADC1);						//����ADC1��У׼�Ĵ���
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));		//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�

	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);					//��ʼADC1��У׼״̬
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));		//�ȴ�У׼���

	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ADC1�����ת����������
}

/*************************************************
����: void Timer2_Configuration(void)
����: TIM2 ����
����: ��
����: ��
��ʱ���㣺(1 /(72 / (72 - 1 + 1))) * 1000 us = 1000us
**************************************************/
void Timer2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=1000;	//�Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) 
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);	//ʱ��Ԥ��Ƶ�� 72M/72      
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);	// �������жϱ�־ 
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);	// ����ʱ��    
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	//�ȹرյȴ�ʹ��                          //����ʱ�� 
}

/*******************************************************************************
* Function Name   : NVIC_Configuration
* Description        : Configures NVIC and Vector Table base location.
* Input                    : None
* Output                 : None
* Return                 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  

  NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*************************************************
����: void TIM2_IRQHandler(void)
����: TIM2�жϴ�����
����: ��
����: ��
˵����390.5us�ж�1��
**************************************************/
void TIM2_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
   {      
      TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	 //����жϱ�־
      time++;
   }
}


void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
}
int main(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_Configuration();
  ADC_Configuration();
  NVIC_Configuration();
  Timer2_Configuration();
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB�˿�
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();  
  GPIO_SetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13 | GPIO_Pin_14);	 // �ر�����LED

  while (1)
  {
    u8 s1,s2,s3,s4=0;
         if(time==500) //500����ɼ�һ��
		 { 
		  time=0; 		 
	      ADC_SoftwareStartConvCmd(ADC1, ENABLE);	        //�������ADCת��
	      while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));   //�ȴ�ת������
	      ad=ADC_GetConversionValue(ADC1);
		  adzhi = 3300000/4096*ad/1000;		        //��ȡADCֵ  
		  s1=(adzhi/1000);
          s2=(adzhi/100%10);
          s3=(adzhi%100/10);
          s4=(adzhi%10);
		  s1=s1+0x30;
		  s2=s2+0x30;
		  s3=s3+0x30;
		  s4=s4+0x30; 		                    
          USART_To_USB_Send_Data('V');
		  USART_To_USB_Send_Data('o');
		  USART_To_USB_Send_Data('l');
		  USART_To_USB_Send_Data('t');
		  USART_To_USB_Send_Data('a');
		  USART_To_USB_Send_Data('g');
		  USART_To_USB_Send_Data('e');
		  USART_To_USB_Send_Data(':');
		  USART_To_USB_Send_Data(s1);
		  USART_To_USB_Send_Data(s2);
		  USART_To_USB_Send_Data(s3);
		  USART_To_USB_Send_Data(s4);
		  USART_To_USB_Send_Data('m');
		  USART_To_USB_Send_Data('V');
		  USART_To_USB_Send_Data('\n');	
		  
          }      
       		  
  }
}

