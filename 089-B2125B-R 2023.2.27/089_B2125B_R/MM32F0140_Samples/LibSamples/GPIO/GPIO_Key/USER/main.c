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
volatile unsigned char gcTimeVal_sec;   //定时时间  秒

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
volatile unsigned int giTimeVal;       //定时时间  分钟
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
static u32 gData = 0x00000044;      //0x12345679;   //静态的全局变量
static volatile FLASH_Status gFlashStatus = FLASH_COMPLETE;
uint32_t G32ReadData;
extern void SystemInit (void);
extern  void DELAY_xUs(u32 count);

#define BANK1_WRITE_START_ADDR  ((u32)0x0800F800)      //指定的Flash写入地址

#define  Stack_Check1  ((u32)0x20000130)
#define  Stack_Check2  ((u32)0x20000134)
#define  Stack_Check3  ((u32)0x20000138)

/* 获取FLASH ID */
void GetChipdata(void)
{
    u8 i;
    for (i = 0; i < 4; i++) {
        ID[i] = *((vu8*)(0x0800F800u + i));      //将Flash里面的值，一位一位的读出来
    }
} 

/*  */
u8 FLASH_Program(void)
{
    // Porgram FLASH Bank1
    // Unlock the Flash Bank1 Program Erase controller
    FLASH_Unlock();

    // Clear All pending flags
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);       //清除闪存的挂起标志。

    FLASH_ErasePage(BANK1_WRITE_START_ADDR);   //擦除指定的的闪存页

    FLASH_ClearFlag(FLASH_FLAG_EOP);    //清除闪存挂起的标志

    gFlashStatus = FLASH_ProgramWord(BANK1_WRITE_START_ADDR, gData);    //在指定地址写入一个字   （返回值是闪存操作结束状态 ）

    FLASH_ClearFlag(FLASH_FLAG_EOP);

    FLASH_Lock();
		
		G32ReadData = (*(__IO u32*) BANK1_WRITE_START_ADDR);
	
    if((*(__IO u32*) BANK1_WRITE_START_ADDR) != gData) {    //判断写入的数据是否正确
        return 1;
    }
    return 0;     //返回值为0，表示成功
}

/*
/// @brief  External interrupt 0, clears interrupt flag after entering.
/// @note   None.
/// @param  None.
/// @retval None.
*/
void EXTI4_15_IRQHandler(void)
{
    EXTI_ClearFlag(EXTI_Line6 | EXTI_Line8 | EXTI_Line10);   //清除中断标志
  	Clr_WdtWakeUp_Flag;
	  Set_KeyWakeUp_Flag;
}

/* NVIC配置 */
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


/* 按键的中断配置 */
static void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    //PA6 PA8 PA10 use EXTI line 0
	
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6|EXTI_PinSource8|EXTI_PinSource10);
    EXTI_StructInit(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = (EXTI_Line6 | EXTI_Line8 | EXTI_Line10);
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;         //中断模式 （而非“事件”）
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;     //下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;     //Specifies the new state of the selected EXTI lines.
    EXTI_Init(&EXTI_InitStruct);
}

/* 按键的关中断配置 */
static void DisEXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    //PA6 PA8 PA10 use EXTI line 0
	
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6|EXTI_PinSource8|EXTI_PinSource10);
    EXTI_StructInit(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = (EXTI_Line6 | EXTI_Line8 | EXTI_Line10);
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;         //中断模式 （而非“事件”）
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;     //下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = DISABLE;     //Specifies the new state of the selected EXTI lines.
    EXTI_Init(&EXTI_InitStruct);
}

/*外部中断事件 IO口配置*/
static void EXTI_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_10;       //PA6 PA8 PA10
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                               //set as Pull up input 上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**********************
/// @brief  External interrupt wake-up standby initialization   （外部中断唤醒初始化）
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
	
		Set_All_OutPut();      //将PA5 PA7 PB0 PB1 置低
}

/* 关闭中断唤醒初始化 */
void WKUP_STOP_DisInit(void)
{
		DisEXTI_NVIC_Init();
		DisEXTI_Config();
	
	  Set_All_OutPut();      //将PA5 PA7 PB0 PB1 置低
		
}

/* 延时 */
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

/* 独立看门狗中断初始化 */
void Iwdg_Irq_ON(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
	#if (1)   //这段控制是否产生看门狗中断
    EXTI_InitTypeDef EXTI_InitStruct;

    EXTI_DeInit();          //将EXTI寄存器反初始化为其默认重置值
    EXTI_StructInit(&EXTI_InitStruct);         //用重置值填充每个init_struct成员
    EXTI_InitStruct.EXTI_Line = EXTI_Line24;   //窗口看门狗的中断线必须是 EXTI24
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;         //中断模式
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;      //上升沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;    //指定选定EXTI行的新状态
    EXTI_Init(&EXTI_InitStruct);
    EXTI_ClearITPendingBit(EXTI_Line24);      //清除EXTI的中断线挂起位
   #endif
    NVIC_InitStruct.NVIC_IRQChannel = WWDG_IWDG_IRQn;     //嵌套向量中断控制器的中断通道选择
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/* 窗口看门狗中断函数 */
void WWDG_IRQHandler(void)
{
		//    EXTI_ClearITPendingBit(EXTI_Line24);        //清除EXTI的中断线挂起位
		//    IWDG_WriteAccessCmd(0x5555);     //往KR寄存器写入5555，解除保护   （启用或禁用对IWDG_PR和IWDG_RLR寄存器的写入访问） 软件写入 0x5555 表示解除保护，可以访问其他配置寄存器（IWDG_PR、IWDG_RLR、IWDG_CR，IWDG_IGEN）
		//    IWDG->CR |= 0x02;                //控制寄存器 （IRQ_CLR 写1，清除中断；  IRQ_SEL 写0，溢出后产生复位）
		//    IWDG->KR = 0xAAAA;               //喂狗操作
	
	  EXTI->PR = EXTI_Line24;            //EXTI_ClearITPendingBit(EXTI_Line24); //清除EXTI的中断线挂起位
	
	  //    IWDG_WriteAccessCmd(0x5555);         //往KR寄存器写入5555，解除保护   （启用或禁用对IWDG_PR和IWDG_RLR寄存器的写入访问） 软件写入 0x5555 表示解除保护，可以访问其他配置寄存器（IWDG_PR、IWDG_RLR、IWDG_CR，IWDG_IGEN）
    IWDG->CR |= 0x02;                    //控制寄存器 （IRQ_CLR 写1，清除中断；  IRQ_SEL 写0，溢出后产生复位）
    IWDG->KR = 0xAAAA;                   //喂狗操作
	   
	  while(IWDG->SR & IWDG_SR_UPDATE){};   //检查看门狗重载值是否更新 

//	  // deley
//    int cnt = 40;

//    while (cnt--)
//    {
//        __NOP();  // Do nothing
//        __NOP();
//        __NOP();
//        __NOP();
//    } 
		
	  /***预防栈溢出***/
	   if((*(__IO u32*) Stack_Check1 != 0x00) || (*(__IO u32*) Stack_Check2 != 0x00) || (*(__IO u32*) Stack_Check3 != 0x00) )
		{
			NVIC_SystemReset();       //复位
		}
	
		if((IWDGCheck_Flag == 0)&&(IWDGCheckEnd_Flag==0))        // 校准看门狗定时器时间为1秒
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
				giIWDGTime = (gllIWDGTimeSum >> 1);      // 除2
				gllIWDGTimeSum = 0;
				gllIWDGTimeSum = (1000*2500/giIWDGTime);				
				Write_Iwdg_ON(IWDG_Prescaler_16,gllIWDGTimeSum);      // 校正WDG看门狗的时间，确保每1s中断一次。
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
					Time_calc();     //倒计时函数	
				}
				gc10msCount = 10;	    //立即休眠
		    //giSleepTime = MAX_SLEEP_VALUE;		  	//100  当等于100就立即进入休眠
			}
			
			else
			{
				giTestTimeMinCnt++;
				if(giTestTimeMinCnt >= 180)    //3分钟
				{
					//_rstc =0xff;        //复位	
					Clr_Isintest_flag;		//自检时间超过3分钟退出自检
				}		
			}
		
		Set_WdtWakeUp_Flag;         //设置看门狗唤醒的标志
}

/*********** 独立看门狗写入（定时产生中断）*********/
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

    PVU_CheckStatus();                  //检查预分频器值是否已更新。
    IWDG_WriteAccessCmd(0x5555);        // 解除保护
    IWDG_SetPrescaler(IWDG_Prescaler);  // PR寄存器  设置预分频寄存器的值
    RVU_CheckStatus();                  //检查计数释放值是否已更新。
    IWDG_WriteAccessCmd(0x5555);        
    IWDG_SetReload(Reload & 0xfff);     // RLR 配置看门狗计数器的重载值
    IVU_CheckStatus();                  //检查计数中断值值是否已更新。
    IWDG_WriteAccessCmd(0x5555);
  	IWDG->IGEN = 0x50;							    // IGEN IWDG的中断生成值
    IWDG_ReloadCounter();             //使用重新加载寄存器中定义的值重新加载IWDG计数器  (喂狗函数)
    IWDG_WriteAccessCmd(0x5555);                          
	
    IWDG->CR |= 1;									    //CR 控制寄存器
    IWDG_Enable();                      //启用IWDG（禁用对IWDG_PR和IWDG_RLR寄存器的写入访问）。
}

/******GPIO初始化********/
void Init_GPIO(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	
	  /*将全部引脚设置成下拉输入（除PA13，PA14）,有利于降低功耗*/
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
		
	  // LED灯扫描端口配置
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;    //通用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		//按键输入扫描端口配置	
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;       //上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStruct);
		
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
		
	  // RF_A7325端口配置
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStruct);	

}

/* 在睡眠模式前*/
void GPIO_Input(void)
{
	 GPIO_InitTypeDef  GPIO_InitStruct;
   RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	 RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	
	 //在睡眠状态下，将某些引脚设置成输入
	 GPIO_StructInit(&GPIO_InitStruct);
   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0; 
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;    //上拉输入
   GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	 GPIO_StructInit(&GPIO_InitStruct);
   GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5;
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;    //下拉输入
   GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	  // LED灯
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
		Init_GPIO();																			// GPIO初始化
	
	  NVIC_Configure(TIM1_BRK_UP_TRG_COM_IRQn, 1, 1);   // 1ms定时   中断通道：TIM1断开、更新、触发和换向中断。
	  TIM1_Init(100 - 1, 24000000 / 100000 - 1);    		// 1ms定时
	

		Iwdg_Irq_ON();																		//看门狗定时器初始化
	  Write_Iwdg_ON(IWDG_Prescaler_16,2500);						//看门狗定时器定时时间设置为1秒

		A7325_Init();
			
		Is_IntoTest();                  //判断是否进入测试模式

		GetChipdata();									//读取指定地址FLASH数据
	
		gcIDcode1 =ID[0];               //FLASH ID
		gcIDcode2 =ID[1];
		gcIDcode3 =ID[2];
		gcIDcode4 =ID[3];	
		
		gcSleepMode_flag = 0;        //睡眠模式清零

		PowerOn_init();	             //上电后各模式设定值初始化

		Clr_LEDon_Flag;              //LED不显示
	
		//FLASH_Program();
		
		Ptcol_light = noneset;		
		TxPtcol_Wifi = noneset;
		TxPtcol_voice = noneset;


	while(1)
	{
		
		#if 1
		if(Isintest_flag == 1)    //进入测试模式
		{
			Test_func();  			
		}
		else     //进入用户模式
		{
			if(gc10msCount >= 10)
			{
				gc10msCount = 0;			
				if(gcSleepMode_flag == 0)     //非睡眠模式
				{				
					giTempval = KeyCheck();	    //按键扫描函数返回的值	
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
				if(giTempval)       //值不等于0，就执行
				{
					giTempKeyVal = giTempval;	
				}
				if((RfwaitXams_Flag == 0) && (RfwaitXbms_Flag == 0))       //等待时间满时，这两个标志位就会被清0
				{
					Key_Process();     //按键值处理				
				}	
			}
			
	    /* 当所有的条件都满足时，RF就会发送一次信号 */  
			if (RfSendEnable_Flag && (RfwaitXams_Flag == 0) && (RfwaitXbms_Flag == 0) && (Rfwait500ms_Flag == 0))
	        {					
						RF_Process(); 		// 刷新发送按键值
	        }
		}
		
		#endif	
	}
}

/************************************
//					void Sleep_Process(void)
//					睡眠处理函数
//					在按键之后1秒进入睡眠
//					运行周期：10ms
***************************************/
void Sleep_Process(void)
{
	giSleepTime++;
	if ((giSleepTime >= MAX_SLEEP_VALUE)	&& (IWDGCheckEnd_Flag))
	{
		giSleepTime = 0;
 		A7325_Sleep();     //RF进入睡眠
		
		RCC_SYSCLKConfig(RCC_HSI);    //睡眠之前开启HSI
		
		GPIO_Input();      //将没有用到的引脚设置成输入
	
		
		Clr_LEDon_Flag;
		giLED_status = 0;   //LED状态   	
    gcKeyCount = 0;
		gcSleepMode_flag = 1;  //睡眠模式置起
		
		
		Clr_PB3;
		Clr_PB4;
		Clr_PB5;
		Clr_PB6;
		
		Set_PA4;
		Set_PA9;
		Set_PA11;
		Set_PA12;
		Set_PA15;
		
		
		WKUP_STOP_Init();        //（外部中断唤醒初始化）
		Clr_WdtWakeUp_Flag;
		Clr_KeyWakeUp_Flag;
			 
	for(;;)
	{
//		 RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN, ENABLE);         //使能
		 PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);      //进入停止模式
		
//     IWDG_WriteAccessCmd(0x5555);     //往KR寄存器写入5555，解除保护
//     IWDG->CR |= 0x02;           //控制寄存器 （IRQ_CLR 写1，清除中断；IRQ_SEL 写0，溢出后产生复位）
//     IWDG->KR = 0xAAAA;          //喂狗操作
		
		 if(KeyWakeUp_Flag)          //如果是按键唤醒的标志，那么跳出循环
		 {
			  Clr_WdtWakeUp_Flag;
			  Clr_KeyWakeUp_Flag;
				break;
		 }
	}
	
		SystemInit();	    //设置系统  （此功能只能在重置后使用）
		
		WKUP_STOP_DisInit();
		Init_GPIO();    //唤醒之后从这一步开始执行
	
//	Clr_TESTIO;

		A7325_ExitSleep();		   //唤醒后，退出睡眠		
		Clr_WdtWakeUp_Flag;		
		gcSleepMode_flag = 0;    //睡眠模式清零

	}
}

void HardFault_Handler(void)
{
	NVIC_SystemReset();
}

