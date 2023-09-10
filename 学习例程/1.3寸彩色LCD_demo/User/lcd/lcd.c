#include "lcd.h"

const unsigned char  chines_word[ ][32]=   //汉字码
{
0x00,0x00,0xE4,0x3F,0x28,0x20,0x28,0x25,0x81,0x08,0x42,0x10,0x02,0x02,0x08,0x02,
0xE8,0x3F,0x04,0x02,0x07,0x07,0x84,0x0A,0x44,0x12,0x34,0x62,0x04,0x02,0x00,0x02,/*"深",0*/

0x88,0x20,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xBF,0x24,0x88,0x24,0x88,0x24,
0x88,0x24,0x88,0x24,0x88,0x24,0xB8,0x24,0x87,0x24,0x42,0x24,0x40,0x20,0x20,0x20,/*"圳",1*/

0x80,0x00,0x80,0x00,0x40,0x01,0x20,0x02,0x10,0x04,0x08,0x08,0xF4,0x17,0x83,0x60,
0x80,0x00,0xFC,0x1F,0x80,0x00,0x88,0x08,0x90,0x08,0x90,0x04,0xFF,0x7F,0x00,0x00,/*"金",2*/

0x80,0x00,0x82,0x00,0x84,0x0F,0x44,0x08,0x20,0x04,0xF0,0x3F,0x27,0x22,0x24,0x22,
0xE4,0x3F,0x04,0x05,0x84,0x0C,0x84,0x54,0x44,0x44,0x24,0x78,0x0A,0x00,0xF1,0x7F,/*"逸",3*/

0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x00,0x00,0xFC,0x3F,0x04,0x00,
0xF4,0x1F,0x04,0x00,0xFC,0x7F,0x94,0x10,0x14,0x09,0x12,0x06,0x52,0x18,0x31,0x60,/*"晨",4*/

0x80,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,
0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,0x84,0x50,0x80,0x40,0x80,0x40,0x00,0x7F,/*"电",5*/

0x00,0x00,0xFE,0x1F,0x00,0x08,0x00,0x04,0x00,0x02,0x80,0x01,0x80,0x00,0xFF,0x7F,
0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00,/*"子",6*/
};




/*************************************************************
***函数名：
***函数功能：
***输入：
***输出：
**************************************************************/
void LCD_GPIO_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 
  	
	GPIO_InitStructure.GPIO_Pin = (LCD_GPIO_SCK_PIN|LCD_GPIO_SDA_PIN|LCD_GPIO_RST_PIN|LCD_GPIO_DC_PIN|LCD_GPIO_BLK_PIN);	
	
	/*设置GPIO模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	
	/*设置GPIO速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	
	/*调用库函数，初始化控制蜂鸣器的GPIO*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB,LCD_GPIO_SCK_PIN|LCD_GPIO_SDA_PIN|LCD_GPIO_RST_PIN|LCD_GPIO_DC_PIN|LCD_GPIO_BLK_PIN);

}


/**************************SPI模块发送函数************************************************

 *************************************************************************/
void SPI_SendByte(unsigned  char byte)				//向液晶屏写一个8位数据
{
  
  unsigned char counter;
 
  for(counter=0;counter<8;counter++)
  { 
    SPI_SCK_0;		  
    if((byte&0x80)==0)
    {
      SPI_SDA_0;
    }
    else SPI_SDA_1;
    byte=byte<<1;	
    SPI_SCK_1;		
  }		
	SPI_SCK_0;
}


void TFT_SEND_CMD(unsigned char o_command)
{
	SPI_DC_0;
//	SPI_SCK_0;
	SPI_SendByte(o_command);
}


  //向液晶屏写一个8位数据
void TFT_SEND_DATA(unsigned  char o_data)
{ 
	SPI_DC_1;
//	SPI_SCK_0;
	SPI_SendByte(o_data);   
 }

	
void TFT_clear(void)
{
	unsigned int ROW,column;

	SPI_SCK_1;			//特别注意！！
	SPI_RST_0;
	Delay_ms(1000);
	SPI_RST_1;
	Delay_ms(1000);
	TFT_SEND_CMD(0x2a);     //Column address set
	TFT_SEND_DATA(0x00);    //start column
	TFT_SEND_DATA(0x00); 
	TFT_SEND_DATA(0x00);    //end column
	TFT_SEND_DATA(0xF0);

	TFT_SEND_CMD(0x2b);     //Row address set
	TFT_SEND_DATA(0x00);    //start row
	TFT_SEND_DATA(0x00); 
	TFT_SEND_DATA(0x00);    //end row
	TFT_SEND_DATA(0xF0);
	TFT_SEND_CMD(0x2C);     //Memory write
	
	for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
	{ 

			for(column=0;column<TFT_COLUMN_NUMBER;column++)  //column loop
			{
				TFT_SEND_DATA(0xFF);
				TFT_SEND_DATA(0xFF);
			}
	}
}


void TFT_full(unsigned int color)
{
	unsigned int ROW,column;
	
	SPI_SCK_1;			//特别注意！！
	SPI_RST_0;
	Delay_ms(1000);
	SPI_RST_1;
	Delay_ms(1000);
	
	TFT_SEND_CMD(0x2a);     //Column address set
	TFT_SEND_DATA(0x00);    //start column
	TFT_SEND_DATA(0x00); 
	TFT_SEND_DATA(0x00);    //end column
	TFT_SEND_DATA(0xF0);
	TFT_SEND_CMD(0x2b);     //Row address set
	TFT_SEND_DATA(0x00);    //start row
	TFT_SEND_DATA(0x00); 
	TFT_SEND_DATA(0x00);    //end row
	TFT_SEND_DATA(0xF0);
	TFT_SEND_CMD(0x2C);     //Memory write
	
	
	for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop  240
	{ 

		for(column=0;column<TFT_COLUMN_NUMBER ;column++) //column loop    240
		{
			TFT_SEND_DATA(color>> 8);    //先传高位
			TFT_SEND_DATA(color);       //再传低位
//			TFT_SEND_DATA(0x07);
//			TFT_SEND_DATA(0xE0);
		}
	}
}


void TFT_init(void)				////ST7789V2
{
		SPI_SCK_1;			//特别注意！！
		SPI_RST_0;
		Delay_ms(1000);
		SPI_RST_1;
		Delay_ms(1000);
		TFT_SEND_CMD(0x11); 			//Sleep Out
		Delay_ms(120);            //DELAY120ms 
//-----------------------ST7789V Frame rate setting------------------------//
		TFT_SEND_CMD(0x3A);     //65k mode
		TFT_SEND_DATA(0x05);
	
		TFT_SEND_CMD(0xC5); 		//VCOM 设置工作电压
		TFT_SEND_DATA(0x1A);
		
	  TFT_SEND_CMD(0x36);    // 屏幕显示方向设置
		TFT_SEND_DATA(0x00);
	
		//-------------ST7789V Frame rate setting-----------//
		TFT_SEND_CMD(0xB2);		   //Porch Setting
		TFT_SEND_DATA(0x0C);     //(0x05);
		TFT_SEND_DATA(0x0C);     //(0x05);
		TFT_SEND_DATA(0x00);
		TFT_SEND_DATA(0x33);
		TFT_SEND_DATA(0x33);

		TFT_SEND_CMD(0xB7);			//Gate Control
		TFT_SEND_DATA(0x35);			//12.2v   -10.43v
		
		//--------------ST7789V Power setting---------------//
		TFT_SEND_CMD(0xBB);//VCOM
		TFT_SEND_DATA(0x19);

		TFT_SEND_CMD(0xC0); //Power control
		TFT_SEND_DATA(0x2c);

		TFT_SEND_CMD(0xC2);		//VDV and VRH Command Enable
		TFT_SEND_DATA(0x01);

		TFT_SEND_CMD(0xC3);			//VRH Set
		TFT_SEND_DATA(0x0F);		//4.3+( vcom+vcom offset+vdv)

		TFT_SEND_CMD(0xC4);			//VDV Set
		TFT_SEND_DATA(0x20);				//0v

		TFT_SEND_CMD(0xC6);				//Frame Rate Control in Normal Mode
		TFT_SEND_DATA(0X01);			//111Hz

		TFT_SEND_CMD(0xd0);				//Power Control 1
		TFT_SEND_DATA(0xa4);
		TFT_SEND_DATA(0xa1);

		TFT_SEND_CMD(0xE8);				//Power Control 1
		TFT_SEND_DATA(0x03);

		TFT_SEND_CMD(0xE9);				//Equalize time control
		TFT_SEND_DATA(0x09);
		TFT_SEND_DATA(0x09);
		TFT_SEND_DATA(0x08);
		
		
		//---------------ST7789V gamma setting-------------//
		TFT_SEND_CMD(0xE0); //Set Gamma
		TFT_SEND_DATA(0xD0);
		TFT_SEND_DATA(0x05);
		TFT_SEND_DATA(0x09);
		TFT_SEND_DATA(0x09);
		TFT_SEND_DATA(0x08);
		TFT_SEND_DATA(0x14);
		TFT_SEND_DATA(0x28);
		TFT_SEND_DATA(0x33);
		TFT_SEND_DATA(0x3F);
		TFT_SEND_DATA(0x07);
		TFT_SEND_DATA(0x13);
		TFT_SEND_DATA(0x14);
		TFT_SEND_DATA(0x28);
		TFT_SEND_DATA(0x30);
		 
		TFT_SEND_CMD(0XE1); //Set Gamma
		TFT_SEND_DATA(0xD0);
		TFT_SEND_DATA(0x05);
		TFT_SEND_DATA(0x09);
		TFT_SEND_DATA(0x09);
		TFT_SEND_DATA(0x08);
		TFT_SEND_DATA(0x03);
		TFT_SEND_DATA(0x24);
		TFT_SEND_DATA(0x32);
		TFT_SEND_DATA(0x32);
		TFT_SEND_DATA(0x3B);
		TFT_SEND_DATA(0x14);
		TFT_SEND_DATA(0x13);
		TFT_SEND_DATA(0x28);
		TFT_SEND_DATA(0x2F);

		TFT_SEND_CMD(0x21); 		//反显
		
		TFT_SEND_CMD(0x11); //Exit Sleep // 退出睡眠模式
	  Delay_ms(120); 
	 
		TFT_SEND_CMD(0x29);         //开启显示 

}
	

void display_char16_16(unsigned int x,unsigned int y,unsigned long color,unsigned char word_serial_number)
{
  unsigned int column;
  unsigned char tm=0,temp=0,xxx=0;

  TFT_SEND_CMD(0x2a);    //Column address set
  TFT_SEND_DATA(x>>8);    //start column
  TFT_SEND_DATA(x);
  x=x+15;
  TFT_SEND_DATA(x>>8);    //end column
  TFT_SEND_DATA(x);

  TFT_SEND_CMD(0x2b);     //Row address set
  TFT_SEND_DATA(y>>8);    //start row
  TFT_SEND_DATA(y); 
  y=y+15;
  TFT_SEND_DATA(y>>8);    //end row
  TFT_SEND_DATA(y);
  TFT_SEND_CMD(0x2C);     //Memory write
    
    
  for(column=0;column<32;column++)  //column loop
	{
		temp=chines_word[  word_serial_number ][xxx];
		for(tm=0;tm<8;tm++)
		{
		if(temp&0x01)
			{
			TFT_SEND_DATA(color>>8);
			TFT_SEND_DATA(color);
			}
		else 
			{
			TFT_SEND_DATA(0XFF);
			TFT_SEND_DATA(0XFF);
			}
			temp>>=1;
		}
	xxx++;
		
	}
}

void Picture_Display(const unsigned char *ptr_pic)
{
  unsigned long  number;
	
	TFT_SEND_CMD(0x2a); 		//Column address set
	TFT_SEND_DATA(0x00); 		//start column
	TFT_SEND_DATA(0x00); 
	TFT_SEND_DATA(0x00);		//end column
	TFT_SEND_DATA(0x77);

	TFT_SEND_CMD(0x2b); 		//Row address set
	TFT_SEND_DATA(0x00); 		//start row
	TFT_SEND_DATA(0x00); 
	TFT_SEND_DATA(0x00);		//end row
	TFT_SEND_DATA(0x78);
	TFT_SEND_CMD(0x2C);			//Memory write
	  
	for(number=0;number<PIC_NUM;number++)	
	{
		//data=*ptr_pic++;
		//data=~data;
		TFT_SEND_DATA(*ptr_pic++);


	}
}




void Delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
		x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
		x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
  }
}


void Delay_ms(unsigned int _ms_time)
{
	unsigned int i,j;
	for(i=0;i<_ms_time;i++)
	{
	for(j=0;j<500;j++)
		{
			;
		}
	}
}
  



