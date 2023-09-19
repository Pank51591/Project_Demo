/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   Һ����������ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "stm32f10x.h"
#include "bsp_lcd.h"
#include "palette.h"
#include "joypad.h"
#include "bsp_led.h"   
#include "bsp_SysTick.h"
#include "bsp_usart1.h"
#include "bsp_fsmc_sram.h"
#include "ff.h"
#include "VS1053.h"
#include "nes_main.h"	
#include "TouchPad.h"
#include "malloc.h"	
#include "bsp_key.h" 

#define FILE_NAME_LEN 			100	
#define MAX_FILE_NUM				15
#define _DF1S								0x81

static FATFS fs;
static char path[100]="0:";
static uint8_t  file_num = 0;	
static uint8_t sel_index;
static unsigned char filelist[MAX_FILE_NUM][FILE_NAME_LEN]={0};
static unsigned char showlist[MAX_FILE_NUM][FILE_NAME_LEN/2]={0};
//Ƶ������
//PLL,��Ƶ��
void system_clock_set(u8 PLL)
{
	unsigned char temp=0;   
	//��λ������������
	RCC->APB1RSTR = 0x00000000;//��λ����			 
	RCC->APB2RSTR = 0x00000000; 
	  
	RCC->AHBENR = 0x00000014;  //˯��ģʽ�����SRAMʱ��ʹ��.�����ر�.	  
	RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //�ر������ж�		 
	SCB->VTOR = 0x08000000;//����NVIC��������ƫ�ƼĴ���
	
 	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
	while(!(RCC->CR>>17));//�ȴ��ⲿʱ�Ӿ���
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;				  //����2����λ����Ϊ�Ǵ�2��ʼ�ģ�����0����2��
	RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	FLASH->ACR|=0x32;	  //FLASH 2����ʱ����
	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//�ȴ�PLL����
	RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��	 
	while(temp!=0x02)     //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}  

static FRESULT scan_files (char* path) 
{ 
	FRESULT res;
	FILINFO fno; 
	DIR dir; 
	int i=0; 
	char *fn; 
	char file_name[FILE_NAME_LEN];	
	
	#if _USE_LFN 
	static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
	fno.lfname = lfn; 
	fno.lfsize = sizeof(lfn); 
	#endif 	
	res = f_opendir(&dir, path);
	if (res == FR_OK) 
	{ 
		i = strlen(path); 
		while(1)
		{ 
			res = f_readdir(&dir, &fno); 
			if (res != FR_OK || fno.fname[0] == 0) break; 
			#if _USE_LFN 
			fn = *fno.lfname ? fno.lfname : fno.fname; 
			#else 
			fn = fno.fname; 
			#endif 
			if (*fn == '.') continue;	
			if (fno.fattrib & AM_DIR) 
			{ 
				sprintf(&path[i], "/%s", fn); 							
				res = scan_files(path);											
				if (res != FR_OK) 
					break; 																	
				path[i] = 0; 
			} 
			else 
			{ 
				//printf("%s/%s\r\n", path, fn);
				if(strstr(fn,".nes")||strstr(fn,".NES"))
				{
					if (strlen(path)+strlen(fn)<FILE_NAME_LEN)
					{
						sprintf(file_name, "%s/%s", path, fn);						
						memcpy(filelist[file_num],file_name,strlen(file_name));	
						memcpy(showlist[file_num],fn,strlen(fn));						
						file_num++;
						if(file_num>=20)break;
					}
				}//if(strstr(fn,".nes")||strstr(fn,".NES"))
			 }//else
		 } //while
	} 
	return res; 
}

static void LCD_showindex(uint8_t index)
{
	ILI9341_Clear(10,10,20,300,macBLACK);
	ILI9341_DrawCircle(20,index*20,5,macYELLOW,1);
}
void LCD_showlist(void)
{
	uint8_t i=0;
	//ILI9341_Clear(10,10,220,300,macBLACK);
	LCD_showindex(sel_index);
	for(i=0;i<file_num;++i)
	{
		ILI9341_DispString_EN_CH(30,i*20+12,showlist[i],macBLACK,macBLUE);
	}
}

void LCD_selectindex(void)
{
	uint8_t joykey=0;
	while(1)
	{
		joykey=JOYPAD_Read();
		switch(joykey)
		{
			case 0x20://"��"
				sel_index++;
				if(sel_index>file_num)
					sel_index=1;
				LCD_showindex(sel_index);
				break;
		  case 0x10://"��"
				sel_index--;
				if(sel_index==0)
					sel_index=file_num;
				LCD_showindex(sel_index);
				break;
			case 0x04://"ѡ��"
			case 0x08://"��ʼ"
					return ;
				break;
			default:
				break;
		}
		joykey=0;
		Delay_ms(500);
	}
}

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main ( void )
{	
	system_clock_set(16);//128M
	//EXSRAM ��ʼ��
	FSMC_SRAM_Init();
	//LCD ��ʼ��
	LCD_Init();  
	//JOYSTICK ��ʼ��
	JOYPAD_Init();
	//LED ��ʼ��
	LED_GPIO_Config();
	//KEY ��ʼ��
	Key_GPIO_Config();
	//mount EXFlash FatFS
  f_mount(&fs,"0:",1);	

	//USART1 ��ʼ��	
	USARTx_Config();
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿSRAM�ڴ�� 
	//SYSTick��ʼ��
	SysTick_Init();
	//VS1053 ��ʼ��	
	VS_Init();
	//��Һ������
	LCD_BK_EN;
	
	file_num = 0;
	sel_index=1;
//	printf("NES Game Play\n");
	scan_files(path);
	//printf("NES file namber:%d\n",file_num);
		
	while (file_num)
  {	
		LCD_showlist();
		LCD_selectindex();
		ILI9341_Clear(0,0,240,320,macBLACK);
		nes_load(filelist[sel_index-1]);
		ILI9341_Clear(0,0,240,320,macBLACK);
//		nes_load("0:/SuperMarie.nes");
  }
	ILI9341_Clear(0,0,240,320,macBLACK);
	ILI9341_DispString_EN_CH(60,10,"�޷��ҵ�NES��Ϸ�ļ�",macBLACK,macBLUE);
	while(1);
}



/* ------------------------------------------end of file---------------------------------------- */

