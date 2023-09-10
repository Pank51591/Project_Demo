/********************金逸晨**************************
******************GMT130 模块 1.3寸   7PIN SPI TFT FOR AT89S52/STC12*************
*****AT89S52驱动**************************
*********ST7789 控制器,本模块第七针BLK为0时，背光关闭，可以不接
由于本模块CS直接接地，默认片选，在所有操作中不应该随意操作SCK 以避免引起错误命令
为顺利完成初始化，在RESET 之前应先将SCK操作为1，以便顺利识别时序中的START，随后每次SCK=1,将完成一位数据发送！！

***** P20----3  SCK   ,  P21----4  SDA   ,  P22----5   RES
	  P23-----6   DC   , P24-----7  BLK   ,  
***** BY:GU 
*********ST7789V2

从左往右，从上往下    240*240  16bit 5 6 5 RGB 模式  高位模式

********************************************************/
#include "reg51.h"

#define set_0   0x01
#define set_1   0x02
#define set_2   0x04
#define set_3   0x08    
#define set_4   0x10
#define set_5   0x20
#define set_6   0x40
#define set_7   0x80

#define clr_0   0xFE
#define clr_1   0xFD
#define clr_2   0xFB
#define clr_3   0xF7    
#define clr_4   0xEF
#define clr_5   0xDF
#define clr_6   0xBF
#define clr_7   0x7F
/**********SPI引脚分配，连接oled屏，更具实际情况修改*********/

#define SPI_SCK_0  P2 &=clr_0        //P2_0      
#define SPI_SCK_1  P2|=set_0       
#define SPI_SDA_0  P2&=clr_1        //P2_1        
#define SPI_SDA_1  P2|=set_1
#define SPI_RST_0  P2&=clr_2        //P2_2        
#define SPI_RST_1  P2|=set_2
#define SPI_DC_0  P2&=clr_3           //P2_3
#define SPI_DC_1  P2|=set_3
#define SPI_BLK_0  P2&=clr_4          //P2_4
#define SPI_BLK_1  P2|=set_4

#define     RED          0XF800	  //红色
#define     GREEN        0X07E0	  //绿色
#define     BLUE         0X001F	  //蓝色
#define     WHITE        0XFFFF	  //白色

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 320
#define TFT_COLUMN_OFFSET 0
#define PIC_NUM 28800			//图片数据大小

code unsigned char chines_word[][32]=       //
{
{0x00,0x00,0xE4,0x3F,0x28,0x20,0x28,0x25,0x81,0x08,0x42,0x10,0x02,0x02,0x08,0x02,
0xE8,0x3F,0x04,0x02,0x07,0x07,0x84,0x0A,0x44,0x12,0x34,0x62,0x04,0x02,0x00,0x02},/*"深",0*/
{0x88,0x20,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xBF,0x24,0x88,0x24,0x88,0x24,
0x88,0x24,0x88,0x24,0x88,0x24,0xB8,0x24,0x87,0x24,0x42,0x24,0x40,0x20,0x20,0x20},/*"圳",1*/
{0x80,0x00,0x80,0x00,0x40,0x01,0x20,0x02,0x10,0x04,0x08,0x08,0xF4,0x17,0x83,0x60,
0x80,0x00,0xFC,0x1F,0x80,0x00,0x88,0x08,0x90,0x08,0x90,0x04,0xFF,0x7F,0x00,0x00},/*"金",2*/
{0x80,0x00,0x82,0x00,0x84,0x0F,0x44,0x08,0x20,0x04,0xF0,0x3F,0x27,0x22,0x24,0x22,
0xE4,0x3F,0x04,0x05,0x84,0x0C,0x84,0x54,0x44,0x44,0x24,0x78,0x0A,0x00,0xF1,0x7F},/*"逸",3*/
{0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x00,0x00,0xFC,0x3F,0x04,0x00,
0xF4,0x1F,0x04,0x00,0xFC,0x7F,0x94,0x10,0x14,0x09,0x12,0x06,0x52,0x18,0x31,0x60},/*"晨",4*/
{0x80,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,
0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,0x84,0x50,0x80,0x40,0x80,0x40,0x00,0x7F},/*"电",5*/
{0x00,0x00,0xFE,0x1F,0x00,0x08,0x00,0x04,0x00,0x02,0x80,0x01,0x80,0x00,0xFF,0x7F,
0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00},/*"子",6*/
{0x00,0x00,0xE4,0x1F,0x48,0x10,0x48,0x10,0x41,0x10,0x82,0x08,0x92,0x08,0x90,0x08,
0x08,0x05,0x08,0x05,0x07,0x02,0x04,0x02,0x04,0x05,0x84,0x08,0x44,0x10,0x30,0x60},/*"汉",7*/
{0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x01,0x20,0xF8,0x07,0x00,0x02,0x00,0x01,
0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00},/*"字",8*/
{0x00,0x01,0x04,0x02,0xE8,0x3F,0x28,0x20,0x01,0x00,0xC2,0x1F,0x02,0x02,0xC8,0x1F,
0x48,0x12,0xC4,0x1F,0x47,0x12,0xC4,0x1F,0x04,0x00,0x84,0x08,0x44,0x10,0x20,0x20},/*"演",9*/
{0x00,0x00,0xFC,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x7F,0x80,0x00,
0x80,0x00,0x88,0x08,0x88,0x10,0x84,0x20,0x82,0x40,0x81,0x40,0xA0,0x00,0x40,0x00},/*"示",10*/


};

const unsigned char  *point;
void delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;
  }
}
void Delay_ms(unsigned int _ms_time)
  {
    unsigned int i,j;
    for(i=0;i<_ms_time;i++)
    {
    for(j=0;j<900;j++)
      {;}
    }
  }
/*************SPI配置函数*******************
SCL空闲时低电平，第一个上升沿采样
模拟SPI
******************************************/

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

    SPI_SendByte(o_command);

   
    //SPI_DC_1;
  }
	
  //向液晶屏写一个8位数据
void TFT_SEND_DATA(unsigned  char o_data)
  { 
    SPI_DC_1;

    SPI_SendByte(o_data);

    
   }
void TFT_clear(void)
  {
    unsigned int ROW,column;
  TFT_SEND_CMD(0x2a);     //Column address set
  TFT_SEND_DATA(0x00);    //start column
  TFT_SEND_DATA(0x00); 
  TFT_SEND_DATA(0x00);    //end column
  TFT_SEND_DATA(0xF0);

  TFT_SEND_CMD(0x2b);     //Row address set
  TFT_SEND_DATA(0x00);    //start row
  TFT_SEND_DATA(0x00); 
  TFT_SEND_DATA(0x01);    //end row
  TFT_SEND_DATA(0x40);
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
    
  for(column=0;column<TFT_COLUMN_NUMBER ;column++) //column loop
          {

			TFT_SEND_DATA(color>>8);
			  TFT_SEND_DATA(color);
          }
      }
  }
void TFT_init(void)        
  {
  SPI_SCK_1;			//特别注意！！
	  SPI_BLK_1;
	SPI_RST_0;
	Delay_ms(1000);
	SPI_RST_1;
	Delay_ms(1000);
    TFT_SEND_CMD(0x11); 			//Sleep Out
	Delay_ms(120);               //DELAY120ms 
//-----------------------ST7789V Frame rate setting-----------------//
//************************************************
                TFT_SEND_CMD(0x3A);        //65k mode
                TFT_SEND_DATA(0x05);
                TFT_SEND_CMD(0xC5); 		//VCOM
                TFT_SEND_DATA(0x1A);
                TFT_SEND_CMD(0x36);                 // 屏幕显示方向设置
                TFT_SEND_DATA(0x00);
                //-------------ST7789V Frame rate setting-----------//
                TFT_SEND_CMD(0xb2);		//Porch Setting
                TFT_SEND_DATA(0x05);
                TFT_SEND_DATA(0x05);
                TFT_SEND_DATA(0x00);
                TFT_SEND_DATA(0x33);
                TFT_SEND_DATA(0x33);

                TFT_SEND_CMD(0xb7);			//Gate Control
                TFT_SEND_DATA(0x05);			//12.2v   -10.43v
                //--------------ST7789V Power setting---------------//
                TFT_SEND_CMD(0xBB);//VCOM
                TFT_SEND_DATA(0x3F);

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
TFT_SEND_CMD(0x29); //Display on // 开显示
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
//            data=*ptr_pic++;
//            data=~data;
            TFT_SEND_DATA(*ptr_pic++);
	
			
          }
  }
void IO_init(void)
{
  P2|=0xFF;                         //PC  06,07，03,04,07输出模式
  

}

int main()
{ 
 
  IO_init();
  TFT_init();
  TFT_full(RED);
	Delay_ms(1000);
	TFT_full(GREEN);
	Delay_ms(1000);
	TFT_full(BLUE);
	Delay_ms(1000);
	TFT_clear();
  while(1)
  {
    display_char16_16(104,100,RED,0);
    display_char16_16(120,100,GREEN,1);
    display_char16_16(80,150,BLUE,2);
    display_char16_16(96,150,0XFFFFFF,3);
    display_char16_16(112,150,BLUE,4);
    display_char16_16(138,150,GREEN,5);
    display_char16_16(154,150,RED,6);
    display_char16_16(96,190,BLUE,7);
    display_char16_16(112,190,GREEN,8);
    display_char16_16(138,190,RED,9);
    display_char16_16(154,190,BLUE,10);
    Delay_ms(1000);
    TFT_clear();
                Delay_ms(1000);
  }
}
