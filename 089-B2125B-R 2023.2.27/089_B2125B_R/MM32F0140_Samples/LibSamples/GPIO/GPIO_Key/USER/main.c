////////////////////////////////////////////////////////////////////////////////
/// @file    main.c
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
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
#define _MAIN_C_

// Files includes
#include "main.h"
#include "key.h"
#include "led.h"
#include "test.h"
#include "delay.h"
#include "LED_RF.h"
#include "tim1_interrupt.h"
#include "089_B19110A.h"
#include "RF_A7325.h"
 
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{



////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is main entrance.
/// @param  None.
/// @retval  0.
////////////////////////////////////////////////////////////////////////////////

u32 ID[5];
struct Flag_Struct MyFlag;

extern uint8_t gcOneMsCount;

volatile unsigned char gc10msCount;
volatile unsigned char gc1MsCount;
volatile unsigned char gcTimeVal_sec;   //��ʱʱ��  ��

volatile unsigned char gcRfXamsCount;
volatile unsigned char gcRfXbmsCount;

volatile unsigned char gcIDcode1;
volatile unsigned char gcIDcode2;
volatile unsigned char gcIDcode3;
volatile unsigned char gcIDcode4;

volatile unsigned char gcPtcolBuff[11]; 
volatile unsigned char gcTxBuff[17];

volatile unsigned int giRf500msCount;
volatile unsigned int gcLamp1sCount;
volatile unsigned int giSleepTime;
volatile unsigned int giTempval;
volatile unsigned int giTimeVal;       //��ʱʱ��  ����
volatile unsigned int gi1sCount;

volatile unsigned int giTempKeyVal;


/*volatile unsigned char gcEEPROM_Init_flag;*/

volatile unsigned int  ID_data1;
volatile unsigned int  ID_data2;
volatile unsigned int  giCheckIWDGTimeCount;
volatile unsigned char giCheckIWDGCount; 
uint32_t gllIWDGTimeSum;
uint16_t giIWDGTime;

volatile unsigned char gcSleepMode_flag;

extern uint8_t gcKeyCount;
extern volatile unsigned int  giLED_status;
extern volatile unsigned int  giLED_Tempstatus;


void Sleep_Process(void);
void GPIO_Input (void);
static u32 gData = 0x00000044;      //0x12345679;   //��̬��ȫ�ֱ���
static volatile FLASH_Status gFlashStatus = FLASH_COMPLETE;
uint32_t G32ReadData;
extern void SystemInit (void);
extern  void DELAY_xUs(u32 count);

#define BANK1_WRITE_START_ADDR  ((u32)0x0800F800)      //ָ����Flashд���ַ

#define  Stack_Check1  ((u32)0x20000130)
#define  Stack_Check2  ((u32)0x20000134)
#define  Stack_Check3  ((u32)0x20000138)

/* ��ȡFLASH ID */
void GetChipdata(void)
{
    u8 i;
    for (i = 0; i < 4; i++) {
        ID[i] = *((vu8*)(0x0800F800u + i));      //��Flash�����ֵ��һλһλ�Ķ�����
    }
} 

/*  */
u8 FLASH_Program(void)
{
    // Porgram FLASH Bank1
    // Unlock the Flash Bank1 Program Erase controller
    FLASH_Unlock();

    // Clear All pending flags
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);       //�������Ĺ����־��

    FLASH_ErasePage(BANK1_WRITE_START_ADDR);   //����ָ���ĵ�����ҳ

    FLASH_ClearFlag(FLASH_FLAG_EOP);    //����������ı�־

    gFlashStatus = FLASH_ProgramWord(BANK1_WRITE_START_ADDR, gData);    //��ָ����ַд��һ����   ������ֵ�������������״̬ ��

    FLASH_ClearFlag(FLASH_FLAG_EOP);

    FLASH_Lock();
		
		G32ReadData = (*(__IO u32*) BANK1_WRITE_START_ADDR);
	
    if((*(__IO u32*) BANK1_WRITE_START_ADDR) != gData) {    //�ж�д��������Ƿ���ȷ
        return 1;
    }
    return 0;     //����ֵΪ0����ʾ�ɹ�
}

/*
/// @brief  External interrupt 0, clears interrupt flag after entering.
/// @note   None.
/// @param  None.
/// @retval None.
*/
void EXTI4_15_IRQHandler(void)
{
    EXTI_ClearFlag(EXTI_Line6 | EXTI_Line8 | EXTI_Line10);   //����жϱ�־
  	Clr_WdtWakeUp_Flag;
	  Set_KeyWakeUp_Flag;
}

/* NVIC���� */
static void EXTI_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
	
    //ENABLE  External interrupt
    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_15_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0x02;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

static void DisEXTI_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
	
    //ENABLE  External interrupt
    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_15_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0x02;
    NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStruct);
}


/* �������ж����� */
static void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    //PA6 PA8 PA10 use EXTI line 0
	
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6|EXTI_PinSource8|EXTI_PinSource10);
    EXTI_StructInit(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = (EXTI_Line6 | EXTI_Line8 | EXTI_Line10);
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;         //�ж�ģʽ �����ǡ��¼�����
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;     //�½��ش���
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;     //Specifies the new state of the selected EXTI lines.
    EXTI_Init(&EXTI_InitStruct);
}

/* �����Ĺ��ж����� */
static void DisEXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    //PA6 PA8 PA10 use EXTI line 0
	
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6|EXTI_PinSource8|EXTI_PinSource10);
    EXTI_StructInit(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = (EXTI_Line6 | EXTI_Line8 | EXTI_Line10);
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;         //�ж�ģʽ �����ǡ��¼�����
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;     //�½��ش���
    EXTI_InitStruct.EXTI_LineCmd = DISABLE;     //Specifies the new state of the selected EXTI lines.
    EXTI_Init(&EXTI_InitStruct);
}

/*�ⲿ�ж��¼� IO������*/
static void EXTI_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_10;       //PA6 PA8 PA10
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                               //set as Pull up input ��������
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**********************
/// @brief  External interrupt wake-up standby initialization   ���ⲿ�жϻ��ѳ�ʼ����
/// @note   External Wake-up Pin Selection.
/// @param  None.
/// @retval None.
************************/
void WKUP_STOP_Init(void)
{
    // EXTI  SYSTEM CLOLK ENABLE
    EXTI_NVIC_Init();
    EXTI_Config();
    EXTI_GPIO_Config();	
	
		Set_All_OutPut();      //��PA5 PA7 PB0 PB1 �õ�
}

/* �ر��жϻ��ѳ�ʼ�� */
void WKUP_STOP_DisInit(void)
{
		DisEXTI_NVIC_Init();
		DisEXTI_Config();
	
	  Set_All_OutPut();      //��PA5 PA7 PB0 PB1 �õ�
		
}

/* ��ʱ */
void deleyNop(u32 DlyTime)
{
    u32 i, j;
    for(i = 0; i < DlyTime; i++) {
			
        for(j = 0; j < 100; j++) {
            __NOP();      //Do nothing
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
}

/* �������Ź��жϳ�ʼ�� */
void Iwdg_Irq_ON(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
	#if (1)   //��ο����Ƿ�������Ź��ж�
    EXTI_InitTypeDef EXTI_InitStruct;

    EXTI_DeInit();          //��EXTI�Ĵ�������ʼ��Ϊ��Ĭ������ֵ
    EXTI_StructInit(&EXTI_InitStruct);         //������ֵ���ÿ��init_struct��Ա
    EXTI_InitStruct.EXTI_Line = EXTI_Line24;   //���ڿ��Ź����ж��߱����� EXTI24
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;         //�ж�ģʽ
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;      //�����ش���
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;    //ָ��ѡ��EXTI�е���״̬
    EXTI_Init(&EXTI_InitStruct);
    EXTI_ClearITPendingBit(EXTI_Line24);      //���EXTI���ж��߹���λ
   #endif
    NVIC_InitStruct.NVIC_IRQChannel = WWDG_IWDG_IRQn;     //Ƕ�������жϿ��������ж�ͨ��ѡ��
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/* ���ڿ��Ź��жϺ��� */
void WWDG_IRQHandler(void)
{
		//    EXTI_ClearITPendingBit(EXTI_Line24);        //���EXTI���ж��߹���λ
		//    IWDG_WriteAccessCmd(0x5555);     //��KR�Ĵ���д��5555���������   �����û���ö�IWDG_PR��IWDG_RLR�Ĵ�����д����ʣ� ���д�� 0x5555 ��ʾ������������Է����������üĴ�����IWDG_PR��IWDG_RLR��IWDG_CR��IWDG_IGEN��
		//    IWDG->CR |= 0x02;                //���ƼĴ��� ��IRQ_CLR д1������жϣ�  IRQ_SEL д0������������λ��
		//    IWDG->KR = 0xAAAA;               //ι������
	
	  EXTI->PR = EXTI_Line24;            //EXTI_ClearITPendingBit(EXTI_Line24); //���EXTI���ж��߹���λ
	
	  //    IWDG_WriteAccessCmd(0x5555);         //��KR�Ĵ���д��5555���������   �����û���ö�IWDG_PR��IWDG_RLR�Ĵ�����д����ʣ� ���д�� 0x5555 ��ʾ������������Է����������üĴ�����IWDG_PR��IWDG_RLR��IWDG_CR��IWDG_IGEN��
    IWDG->CR |= 0x02;                    //���ƼĴ��� ��IRQ_CLR д1������жϣ�  IRQ_SEL д0������������λ��
    IWDG->KR = 0xAAAA;                   //ι������
	   
	  while(IWDG->SR & IWDG_SR_UPDATE){};   //��鿴�Ź�����ֵ�Ƿ���� 

//	  // deley
//    int cnt = 40;

//    while (cnt--)
//    {
//        __NOP();  // Do nothing
//        __NOP();
//        __NOP();
//        __NOP();
//    } 
		
	  /***Ԥ��ջ���***/
	   if((*(__IO u32*) Stack_Check1 != 0x00) || (*(__IO u32*) Stack_Check2 != 0x00) || (*(__IO u32*) Stack_Check3 != 0x00) )
		{
			NVIC_SystemReset();       //��λ
		}
	
		if((IWDGCheck_Flag == 0)&&(IWDGCheckEnd_Flag==0))        // У׼���Ź���ʱ��ʱ��Ϊ1��
		{
			giCheckIWDGTimeCount = 0;
			Set_IWDGCheck_Flag;
		}
		else if(IWDGCheckEnd_Flag==0)
		{
			giCheckIWDGCount++;
			gllIWDGTimeSum += giCheckIWDGTimeCount;              
			
			if(giCheckIWDGCount >= 2)
			{
				giIWDGTime = (gllIWDGTimeSum >> 1);      // ��2
				gllIWDGTimeSum = 0;
				gllIWDGTimeSum = (1000*2500/giIWDGTime);				
				Write_Iwdg_ON(IWDG_Prescaler_16,gllIWDGTimeSum);      // У��WDG���Ź���ʱ�䣬ȷ��ÿ1s�ж�һ�Ρ�
				Set_IWDGCheckEnd_Flag;
			}
			else
			{
				Clr_IWDGCheck_Flag;
				giCheckIWDGTimeCount = 0;
			}
		}
		
			if(Isintest_flag == 0)
			{
				if((Ptcol_TimeSet != timerconti)&&(Ptcol_TimeSet != 0x00))
				{		
					Time_calc();     //����ʱ����	
				}
				gc10msCount = 10;	    //��������
		    //giSleepTime = MAX_SLEEP_VALUE;		  	//100  ������100��������������
			}
			
			else
			{
				giTestTimeMinCnt++;
				if(giTestTimeMinCnt >= 180)    //3����
				{
					//_rstc =0xff;        //��λ	
					Clr_Isintest_flag;		//�Լ�ʱ�䳬��3�����˳��Լ�
				}		
			}
		
		Set_WdtWakeUp_Flag;         //���ÿ��Ź����ѵı�־
}

/*********** �������Ź�д�루��ʱ�����жϣ�*********/
////////////////////////////////////////////////////////////////////////////////
/// @brief  Set IWDG on
/// @param  IWDG_Prescaler     prescaler value
///         Reload      reload value
/// @retval None
////////////////////////////////////////////////////////////////////////////////
void Write_Iwdg_ON(u16 IWDG_Prescaler, u16 Reload)
{
    RCC_LSICmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

    PVU_CheckStatus();                  //���Ԥ��Ƶ��ֵ�Ƿ��Ѹ��¡�
    IWDG_WriteAccessCmd(0x5555);        // �������
    IWDG_SetPrescaler(IWDG_Prescaler);  // PR�Ĵ���  ����Ԥ��Ƶ�Ĵ�����ֵ
    RVU_CheckStatus();                  //�������ͷ�ֵ�Ƿ��Ѹ��¡�
    IWDG_WriteAccessCmd(0x5555);        
    IWDG_SetReload(Reload & 0xfff);     // RLR ���ÿ��Ź�������������ֵ
    IVU_CheckStatus();                  //�������ж�ֵֵ�Ƿ��Ѹ��¡�
    IWDG_WriteAccessCmd(0x5555);
  	IWDG->IGEN = 0x50;							    // IGEN IWDG���ж�����ֵ
    IWDG_ReloadCounter();             //ʹ�����¼��ؼĴ����ж����ֵ���¼���IWDG������  (ι������)
    IWDG_WriteAccessCmd(0x5555);                          
	
    IWDG->CR |= 1;									    //CR ���ƼĴ���
    IWDG_Enable();                      //����IWDG�����ö�IWDG_PR��IWDG_RLR�Ĵ�����д����ʣ���
}

/******GPIO��ʼ��********/
void Init_GPIO(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	
	  /*��ȫ���������ó��������루��PA13��PA14��,�����ڽ��͹���*/
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_All & (~(GPIO_Pin_13 | GPIO_Pin_14));
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_All ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_All ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitStruct);	
	
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_All ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
		
	  // LED��ɨ��˿�����
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;    //ͨ���������
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		//��������ɨ��˿�����	
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;       //��������
    GPIO_Init(GPIOA, &GPIO_InitStruct);
		
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
		
	  // RF_A7325�˿�����
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
    GPIO_Init(GPIOA, &GPIO_InitStruct);	

}

/* ��˯��ģʽǰ*/
void GPIO_Input(void)
{
	 GPIO_InitTypeDef  GPIO_InitStruct;
   RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	 RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	
	 //��˯��״̬�£���ĳЩ�������ó�����
	 GPIO_StructInit(&GPIO_InitStruct);
   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0; 
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;    //��������
   GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	 GPIO_StructInit(&GPIO_InitStruct);
   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;    //��������
   GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	  // LED��
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
		
}
	
s32 main(void)
{
		Init_GPIO();																			// GPIO��ʼ��
	
	  NVIC_Configure(TIM1_BRK_UP_TRG_COM_IRQn, 1, 1);   // 1ms��ʱ   �ж�ͨ����TIM1�Ͽ������¡������ͻ����жϡ�
	  TIM1_Init(100 - 1, 24000000 / 100000 - 1);    		// 1ms��ʱ
	

		Iwdg_Irq_ON();																		//���Ź���ʱ����ʼ��
	  Write_Iwdg_ON(IWDG_Prescaler_16,2500);						//���Ź���ʱ����ʱʱ������Ϊ1��

		A7325_Init();
			
		Is_IntoTest();                  //�ж��Ƿ�������ģʽ

		GetChipdata();									//��ȡָ����ַFLASH����
	
		gcIDcode1 =ID[0];               //FLASH ID
		gcIDcode2 =ID[1];
		gcIDcode3 =ID[2];
		gcIDcode4 =ID[3];	
		
		gcSleepMode_flag = 0;        //˯��ģʽ����

		PowerOn_init();	             //�ϵ���ģʽ�趨ֵ��ʼ��

		Clr_LEDon_Flag;              //LED����ʾ
	
		//FLASH_Program();
		
		Ptcol_light = noneset;		
		TxPtcol_Wifi = noneset;
		TxPtcol_voice = noneset;


	while(1)
	{
		
		#if 1
		if(Isintest_flag == 1)    //�������ģʽ
		{
			Test_func();  			
		}
		else     //�����û�ģʽ
		{
			if(gc10msCount >= 10)
			{
				gc10msCount = 0;			
				if(gcSleepMode_flag == 0)     //��˯��ģʽ
				{				
					giTempval = KeyCheck();	    //����ɨ�躯�����ص�ֵ	
//          Clr_PB3;
//					Clr_PB5;
//					Clr_PB6;
//					Set_PB4;
//					
//					Clr_PA4;
//					Set_PA15;
//					Set_PA12;
//					Set_PA11;
//					Set_PA9;						
				}		
				Sleep_Process();				    				
				if(giTempval)       //ֵ������0����ִ��
				{
					giTempKeyVal = giTempval;	
				}
				if((RfwaitXams_Flag == 0) && (RfwaitXbms_Flag == 0))       //�ȴ�ʱ����ʱ����������־λ�ͻᱻ��0
				{
					Key_Process();     //����ֵ����				
				}	
			}
			
	    /* �����е�����������ʱ��RF�ͻᷢ��һ���ź� */  
			if (RfSendEnable_Flag && (RfwaitXams_Flag == 0) && (RfwaitXbms_Flag == 0) && (Rfwait500ms_Flag == 0))
	        {					
						RF_Process(); 		// ˢ�·��Ͱ���ֵ
	        }
		}
		
		#endif	
	}
}

/************************************
//					void Sleep_Process(void)
//					˯�ߴ�����
//					�ڰ���֮��1�����˯��
//					�������ڣ�10ms
***************************************/
void Sleep_Process(void)
{
	giSleepTime++;
	if ((giSleepTime >= MAX_SLEEP_VALUE)	&& (IWDGCheckEnd_Flag))
	{
		giSleepTime = 0;
 		A7325_Sleep();     //RF����˯��
		
		RCC_SYSCLKConfig(RCC_HSI);    //˯��֮ǰ����HSI
		
		GPIO_Input();      //��û���õ����������ó�����
	
		
		Clr_LEDon_Flag;
		giLED_status = 0;   //LED״̬   	
    gcKeyCount = 0;
		gcSleepMode_flag = 1;  //˯��ģʽ����
		
		
		Clr_PB3;
		Clr_PB4;
		Clr_PB5;
		Clr_PB6;
		
		Set_PA4;
		Set_PA9;
		Set_PA11;
		Set_PA12;
		Set_PA15;
		
		
		WKUP_STOP_Init();        //���ⲿ�жϻ��ѳ�ʼ����
		Clr_WdtWakeUp_Flag;
		Clr_KeyWakeUp_Flag;
			 
	for(;;)
	{
//		 RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN, ENABLE);         //ʹ��
		 PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);      //����ֹͣģʽ
		
//     IWDG_WriteAccessCmd(0x5555);     //��KR�Ĵ���д��5555���������
//     IWDG->CR |= 0x02;           //���ƼĴ��� ��IRQ_CLR д1������жϣ�IRQ_SEL д0������������λ��
//     IWDG->KR = 0xAAAA;          //ι������
		
		 if(KeyWakeUp_Flag)          //����ǰ������ѵı�־����ô����ѭ��
		 {
			  Clr_WdtWakeUp_Flag;
			  Clr_KeyWakeUp_Flag;
				break;
		 }
	}
	
		SystemInit();	    //����ϵͳ  ���˹���ֻ�������ú�ʹ�ã�
		
		WKUP_STOP_DisInit();
		Init_GPIO();    //����֮�����һ����ʼִ��
	
//	Clr_TESTIO;

		A7325_ExitSleep();		   //���Ѻ��˳�˯��		
		Clr_WdtWakeUp_Flag;		
		gcSleepMode_flag = 0;    //˯��ģʽ����

	}
}

void HardFault_Handler(void)
{
	NVIC_SystemReset();
}

