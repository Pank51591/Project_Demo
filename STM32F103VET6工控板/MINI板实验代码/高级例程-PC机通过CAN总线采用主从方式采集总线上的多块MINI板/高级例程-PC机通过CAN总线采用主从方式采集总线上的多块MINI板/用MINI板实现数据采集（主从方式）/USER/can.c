/****************************************
 * 文件名  ：can.c
 * 描述    ：CAN测试应用函数库。         
 * 实验平台：MINI STM32开发板 基于STM32F103VET6
 * 硬件连接：-----------------
 *          | 				  |
            |  PB8-CAN-RX     |
 *          |  PB9-CAN-TX     |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.0.0  																										  
*********************************************************/
#include "can.h" 
#include "stdio.h"

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
u8 FABIAO;
u8 slaveID=0x22;  //定义板子地址

/* 在中断处理函数中返回 */
__IO uint32_t ret = 0;

volatile TestStatus TestRx;	

/*CAN RX0 中断优先级配置  */
 void CAN_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

  	/* Configure the NVIC Preemption Priority Bits */  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	#ifdef  VECT_TAB_RAM  
	  /* Set the Vector Table base location at 0x20000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
	  /* Set the Vector Table base location at 0x08000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif

	/* enabling interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
}

/*CAN GPIO 和时钟配置 */
 void CAN_GPIO_Config(void)
{
 GPIO_InitTypeDef GPIO_InitStructure; 
  /* 复用功能和GPIOB端口时钟使能*/	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);	                        											 

  /* CAN1 模块时钟使能 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); 

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化LED2端口	用于状态指示
  GPIO_SetBits(GPIOB, GPIO_Pin_12);

  /* Configure CAN pin: RX */	 // PB8
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */   // PB9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
	//#define GPIO_Remap_CAN    GPIO_Remap1_CAN1 本实验没有用到重映射I/O
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
  
}

/*	CAN初始化 */
 void CAN_INIT(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  CanTxMsg TxMessage;  

  /* CAN register init */
  CAN_DeInit(CAN1);	//将外设CAN的全部寄存器重设为缺省值
  CAN_StructInit(&CAN_InitStructure);//把CAN_InitStruct中的每一个参数按缺省值填入

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM=DISABLE;//没有使能时间触发模式
  CAN_InitStructure.CAN_ABOM=DISABLE;//没有使能自动离线管理
  CAN_InitStructure.CAN_AWUM=DISABLE;//没有使能自动唤醒模式
  CAN_InitStructure.CAN_NART=DISABLE;//没有使能非自动重传模式
  CAN_InitStructure.CAN_RFLM=DISABLE;//没有使能接收FIFO锁定模式
  CAN_InitStructure.CAN_TXFP=DISABLE;//没有使能发送FIFO优先级
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;//CAN设置为正常模式
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq; //重新同步跳跃宽度1个时间单位
  CAN_InitStructure.CAN_BS1=CAN_BS1_3tq; //时间段1为3个时间单位
  CAN_InitStructure.CAN_BS2=CAN_BS2_2tq; //时间段2为2个时间单位
  CAN_InitStructure.CAN_Prescaler=60;  //时间单位长度为60	
  CAN_Init(CAN1,&CAN_InitStructure);
                                      //波特率为：72M/2/60(1+3+2)=0.1 即100K

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=1;//指定过滤器为1
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;//指定过滤器为标识符屏蔽位模式
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;//过滤器位宽为32位
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;// 过滤器标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;//	 过滤器标识符的低16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//过滤器屏蔽标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;//	过滤器屏蔽标识符的低16位值
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;// 设定了指向过滤器的FIFO为0
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;// 使能过滤器
  CAN_FilterInit(&CAN_FilterInitStructure);//	按上面的参数初始化过滤器

  /* CAN FIFO0 message pending interrupt enable */ 
 CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE); //使能FIFO0消息挂号中断
 
 }  
/* 发送两个字节的数据*/
void can_tx(u32 Data1,u32 Data2,u32 Data3,u32 Data4)
{ 
  CanTxMsg TxMessage;  

  TxMessage.StdId=slaveID;	//标准标识符为0x00
  TxMessage.ExtId=0x0000; //扩展标识符0x0000
  TxMessage.IDE=CAN_ID_STD;//使用标准标识符
  TxMessage.RTR=CAN_RTR_DATA;//为数据帧
  TxMessage.DLC=8;	//	消息的数据长度为2个字节
  TxMessage.Data[0]=Data1/256; //第一个字节数据
  TxMessage.Data[1]=Data1%256; //第二个字节数据////////// 
  TxMessage.Data[2]=Data2/256; //第一个字节数据
  TxMessage.Data[3]=Data2%256; //第二个字节数据////////// 
  TxMessage.Data[4]=Data3/256; //第一个字节数据
  TxMessage.Data[5]=Data3%256; //第二个字节数据////////// 
  TxMessage.Data[6]=Data4/256; //第一个字节数据
  TxMessage.Data[7]=Data4%256; //第二个字节数据////////// 
  CAN_Transmit(CAN1,&TxMessage); //发送数据
 
 
}
/* USB中断和CAN接收中断服务程序，USB跟CAN公用I/O，这里只用到CAN的中断。 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  
  CanRxMsg RxMessage;

  RxMessage.StdId=0x00;
  RxMessage.ExtId=0x00;
  RxMessage.IDE=0;
  RxMessage.DLC=0;
  RxMessage.FMI=0;
  RxMessage.Data[0]=0x00;
  RxMessage.Data[1]=0x00;    

  CAN_Receive(CAN1,CAN_FIFO0, &RxMessage); //接收FIFO0中的数据  
  if((RxMessage.StdId==slaveID)&&(RxMessage.Data[0]==0x55))   
  {FABIAO=0xff;}
  
  
} 


