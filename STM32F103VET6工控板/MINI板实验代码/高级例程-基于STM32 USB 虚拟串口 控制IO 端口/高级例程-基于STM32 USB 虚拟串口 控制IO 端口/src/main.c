/****************************************
 * �ļ���  ��main.c
 * ����    ��ͨ�����⴮�ڣ����ô��ڵ�������򳬼��ն˷��Ϳ�����������ӣ����ư�����LED��         
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


u16 ad;	
u32 adzhi = 0; 
u16 time = 0;
extern u16 count_out;
extern uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];

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

   /* Enable GPIOA, GPIOD and USART1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
}





int main(void)
{
  	

  RCC_Configuration();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
  GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ); //�ر�3��LED
   

  while (1)
  {

   
	if (count_out != 0)	//�ж��������ݽ��յ�
    {  
	  
      
	  if(USB_Rx_Buffer[0]==0x01){GPIO_ResetBits(GPIOB, GPIO_Pin_14 );
	                          USB_Send_string("LED1 ����  \r\n");
							  
							  count_out=0;
							 }	//������յ��������0X01������led1
	  if(USB_Rx_Buffer[0]==0x02){GPIO_ResetBits(GPIOB, GPIO_Pin_12 );
	                          USB_Send_string("LED2 ����\r\n");
							  count_out=0;
							  }	
							  //������յ��������0X02������led2
	  if(USB_Rx_Buffer[0]==0x03){GPIO_ResetBits(GPIOB, GPIO_Pin_13 );
	                          USB_Send_string("LED3 ����\r\n");
							  count_out=0;
							  }	
							  //������յ��������0X03������led3
	  if(USB_Rx_Buffer[0]==0x04){GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 );
	                          USB_Send_string("LED ȫ��\r\n");
							  count_out=0;
							  } //������յ��������0X04��//�ر�3��LED  
    }         
        
      
       		  
  }
}

