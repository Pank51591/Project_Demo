#ifndef __lcd_h__
#define __lcd_h__

#include "stm32f10x.h"

#define     RED          0XF800	  //红色
#define     GREEN        0X07E0	  //绿色
#define     BLUE         0X001F	  //蓝色
#define     WHITE        0XFFFF	  //白色

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 240
#define TFT_COLUMN_OFFSET 0

#define PIC_NUM 28800


#define LCD_GPIO_SCK_PORT    	  GPIOB			              /* GPIO端口 */
#define LCD_GPIO_SCK_CLK 	      RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_GPIO_SCK_PIN		    GPIO_Pin_5			        

#define LCD_GPIO_SDA_PORT    	  GPIOB			              /* GPIO端口 */
#define LCD_GPIO_SDA_CLK 	      RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_GPIO_SDA_PIN		    GPIO_Pin_6	

#define LCD_GPIO_RST_PORT    	  GPIOB			              /* GPIO端口 */
#define LCD_GPIO_RST_CLK 	      RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_GPIO_RST_PIN		    GPIO_Pin_7	

#define LCD_GPIO_DC_PORT    	  GPIOB			              /* GPIO端口 */
#define LCD_GPIO_DC_CLK 	      RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_GPIO_DC_PIN		      GPIO_Pin_8	

#define LCD_GPIO_BLK_PORT    	  GPIOB			              /* GPIO端口 */
#define LCD_GPIO_BLK_CLK 	      RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LCD_GPIO_BLK_PIN		    GPIO_Pin_9	


#define SPI_SCK_0   GPIO_ResetBits(LCD_GPIO_SCK_PORT,LCD_GPIO_SCK_PIN);       //置位
#define SPI_SCK_1   GPIO_SetBits(LCD_GPIO_SCK_PORT,LCD_GPIO_SCK_PIN);         // 设置sck接口到PB5   清零
#define SPI_SDA_0   GPIO_ResetBits(LCD_GPIO_SDA_PORT,LCD_GPIO_SDA_PIN);       // 设置SDA接口到PB6
#define SPI_SDA_1   GPIO_SetBits(LCD_GPIO_SDA_PORT,LCD_GPIO_SDA_PIN);
#define SPI_RST_0   GPIO_ResetBits(LCD_GPIO_RST_PORT,LCD_GPIO_RST_PIN);      // 设置RST接口到PB7
#define SPI_RST_1   GPIO_SetBits(LCD_GPIO_RST_PORT,LCD_GPIO_RST_PIN);
#define SPI_DC_0    GPIO_ResetBits(LCD_GPIO_DC_PORT,LCD_GPIO_DC_PIN);        // 设置DC接口到PB8
#define SPI_DC_1    GPIO_SetBits(LCD_GPIO_DC_PORT,LCD_GPIO_DC_PIN);
#define SPI_BLK_0   GPIO_ResetBits(LCD_GPIO_BLK_PORT,LCD_GPIO_BLK_PIN);      // 设置/WR 或CS接口到PB10
#define SPI_BLK_1   GPIO_SetBits(LCD_GPIO_BLK_PORT,LCD_GPIO_BLK_PIN);



void LCD_GPIO_Init (void);

void TFT_full(unsigned int color);
void SPI_SendByte(unsigned  char byte);
void TFT_SEND_CMD(unsigned char o_command);
void TFT_SEND_DATA(unsigned  char o_data);
void TFT_clear(void);
void display_char16_16(unsigned int x,unsigned int y,unsigned long color,unsigned char word_serial_number);
void Picture_Display(const unsigned char *ptr_pic);
void TFT_init(void);
void Delay_us(unsigned int _us_time);
void Delay_ms(unsigned int _ms_time);

#endif

