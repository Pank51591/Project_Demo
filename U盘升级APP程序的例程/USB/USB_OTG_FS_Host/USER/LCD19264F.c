#include "LCD19264F.h"

void HAL_GPIO_WritePin(GPIO_TypeDef* gpio, u16 pin,GPIO_PinState PinState)
{
	if(!PinState)
		GPIO_ResetBits(gpio,pin);
	else
		GPIO_SetBits(gpio,pin);
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* gpio,u16 pin)
{
	return (GPIO_PinState)GPIO_ReadInputDataBit(gpio,pin);
}

void LCM_Data(uint8_t wr_data) 
{
	int status = 0x01;
	#ifdef C51
	DB0_19264F=wr_data&0x01;
	DB1_19264F=wr_data&0x02;
	DB2_19264F=wr_data&0x04;
	DB3_19264F=wr_data&0x08;

	DB4_19264F=wr_data&0x10;
	DB5_19264F=wr_data&0x20;
	DB6_19264F=wr_data&0x40;
	DB7_19264F=wr_data&0x80;	 
	#else
	int i;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:
				if(wr_data & (status << i))
					DB0_ON;
				else
					DB0_OFF;
				break;
			case 1:
				if(wr_data & (status << i))
					DB1_ON;
				else
					DB1_OFF;
				break;
			case 2:
				if(wr_data & (status << i))
					DB2_ON;
				else
					DB2_OFF;
				break;
			case 3:
				if(wr_data & (status << i))
					DB3_ON;
				else
					DB3_OFF;
				break;
			case 4:
				if(wr_data & (status << i))
					DB4_ON;
				else
					DB4_OFF;
				break;
			case 5:
				if(wr_data & (status << i))
					DB5_ON;
				else
					DB5_OFF;
				break;
			case 6:
				if(wr_data & (status << i))
					DB6_ON;
				else
					DB6_OFF;
				break;
			case 7:
				if(wr_data & (status << i))
					DB7_ON;
				else
					DB7_OFF;
				break;
			default:
				break;
		}
	}
	#endif
}


void Lcm_Wr_Data(uchar wrdata,uint8_t enable) //写数据
{
	Lcm_Rd_Status();
	#ifdef C51
	RS=1;
	RW=0;
	#else
	RS_ON;
	RW_OFF;
	#endif
	LCM_Data(wrdata); 
	
	if(!enable)
	{
		CLK1_ON;
		Lcm_Delay();
		CLK1_OFF;
	}
	else
	{
		CLK2_ON;
		Lcm_Delay();
		CLK2_OFF;
	}		
}

void Lcm_Wr_Command(uchar wrcommand,uint8_t enable) //写指令
{
	Lcm_Rd_Status();
	#ifdef C51
	RS=0;
	RW=0;
	#else
	RS_OFF;
	RW_OFF;
	#endif
	LCM_Data(wrcommand); 
	
	if(!enable)
	{
		CLK1_ON;
		Lcm_Delay();
		CLK1_OFF;
	}
	else
	{
		CLK2_ON;
		Lcm_Delay();
		CLK2_OFF;
	}	
}


#if 1


void Lcm_Rd_Status(void) //读忙状态
{

   uchar temp;
   uchar i=10;//根据mcu的频率要进行测试，不然显示会紊乱8
   #ifdef C51
   DB7_19264F=1;
   #else
   DB7_ON;
   #endif
   while(1)
   {
   		#ifdef C51
	   RS=0;
	   RW =1;
	   #else
	   RS_OFF;
	   RW_ON;
	   #endif

	   CLK1_ON;
	   CLK2_ON;
	   if(GPIO_ReadInputDataBit(DB7_GPIO_Port,DB7_Pin))
		   temp=0x80;
	   else
		   temp=0; 
   
	   CLK1_OFF;
	   CLK2_OFF;
	   if((temp&0x80)==0) 
	   break;					//判断忙标志是否为0
	   
	   if(!(i--))break;
   } 
}

#else
void Lcm_Rd_Status(bit enable) //读忙状态
{
	while(1)
	{
		RS=0;
		RW=1;
		Lcm_Data=0xFF;
		if(!enable)
		{
			E1=0;		
			Lcm_Delay();
			E1=1;
			if((Lcm_Data&0x80)==0)
			break;

		
		}
		else
		{
			E2=0;		
			Lcm_Delay();
			E2=1;
			if((Lcm_Data&0x80)==0)
			break;	
		}	
	}
}

#endif


/********************写DGRAM***********************
pos_x为X坐标，每进1位右移16个点,从0开始
pos_y为Y坐标，每进1位下移1个点,从0开始
****************************************************/
void Wr_Gdram(uchar pos_x,uchar pos_y,uint length,uchar width,uchar *table,uint8_t enable)
{	 
	uchar i,j;
	Lcm_Wr_Command(0x34,enable);//选择扩充指令	
	Lcm_Wr_Command(0x36,enable);	
	for(j=pos_y;j<pos_y+width;j++)
	{	
		Lcm_Wr_Command(0x80+j,enable);  //Y总坐标,即第几行
		Lcm_Wr_Command(0x80+pos_x,enable);//X坐标，16个点进1
		for(i=0;i<length/8;i++)//
			Lcm_Wr_Data(*table++,enable);
	}		
	Lcm_Wr_Command(0x30,enable);//返回基本指令
}


//清除GDRAM
void Clean_Gdram(uint8_t enable)
{    
	uchar i,j;
	Lcm_Wr_Command(0x34,enable);	
    for(j=0;j<32;j++)
    {
       Lcm_Wr_Command(0x80+j,enable);
	   Lcm_Wr_Command(0x80,enable);
       for(i=0;i<32;i++)//
       		Lcm_Wr_Data(0x00,enable);
    }
	Lcm_Wr_Command(0x36,enable);		
	Lcm_Wr_Command(0x30,enable);	
}


/***************************************************
	自定义字符写入CGRAM
	总共有4个自定义字符
	写入地址				   0x40   0x50   0x60   0x70
	对应的读出地址为    0x00   0x02   0x04   0x06
****************************************************/
void Wr_Cgram(uchar addr,uchar *table,uint8_t enable)
{     
      uchar i;
	  Lcm_Wr_Command(addr,enable);  	//设定CGRAM地址	  
      for(i=0;i<32;i++)
		  Lcm_Wr_Data(*table++,enable); 
}


//选定坐标
void Lcm_GotoXY(uchar pos_X,uchar pos_y)
{ 
	uchar addr;
	if((pos_X>11)||(pos_y>1))
		return;
	
	if(pos_y==0)
		addr=0x80+pos_X;
	else if(pos_y==1)
		addr=0x90+pos_X; 
	Lcm_Wr_Command(addr,ENABLE_UP_SCREEN);//设定DDRAM地址
	Lcm_Wr_Command(addr,ENABLE_DOWN_SCREEN);//设定DDRAM地址
}


void Lcm_Disp_Onechar(uchar onechar,uint8_t enable)//显示单个字符
{
	Lcm_Wr_Data(onechar,enable);	
}


void Disp_Cgram(uchar addr_data,uint8_t enable)//显示自定义的字符
{
	Lcm_Wr_Data(0x00,enable);
    Lcm_Wr_Data(addr_data,enable);	
}


void Lcm_Disp_String(uchar *string,uint8_t enable)//显示字符串
{ 
	while (*string != '\0')
		Lcm_Wr_Data(*string++,enable);
}


void Lcm_Init(uint8_t enable)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOE,ENABLE);
	GPIO_StructInit(&GPIO_InitStruct);

	//GPIOB.13,14,15
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_13);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_14);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_15);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	//GPIOD.10,11
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_10);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_11);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStruct);

	//GPIOE.0,1,2,3,4,5,6,7,12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource2,GPIO_AF_2);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource3,GPIO_AF_3);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource4,GPIO_AF_4);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_5);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_6);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_7);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_12);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE,&GPIO_InitStruct);

	
	Delay_1ms(50);
	
	//RST=1;
	//RST_ON;
	Delay_1ms(10);
	//RST=0;
	//RST_OFF;
	Delay_1ms(10);
	//RST=1;
	//RST_ON;

	Lcm_Wr_Command(0x30,enable);
	Delay_1ms(5);
	Lcm_Wr_Command(0x30,enable); 
	Delay_1ms(5);
	Lcm_Wr_Command(0x0c,enable); //开显示及光标设置
	Delay_1ms(5);
	Lcm_Wr_Command(0x01,enable); //显示清屏
	Delay_1ms(10);
	Lcm_Wr_Command(0x06,enable); //显示光标移动设置
	Delay_1ms(5);
}


void Delay_1ms(uint x)//1ms延时
{
	unsigned char j;
	while(x--)
	{
		for(j=0;j<125;j++)
		{;}
	}
}


void Lcm_Delay(void)
{	
	#ifdef C51
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	#else
	Delay_1ms(1);
	#endif
}

