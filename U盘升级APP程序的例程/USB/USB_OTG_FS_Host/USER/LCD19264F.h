#ifndef __LCD19264_H
#define __LCD19264_H
#include "mm32_device.h"
#include "hal_conf.h"
typedef enum
{
	GPIO_PIN_RESET = 0u,
	GPIO_PIN_SET,
}GPIO_PinState;

//IO口定义
#define DB0_Pin GPIO_Pin_0
#define DB0_GPIO_Port GPIOE
#define DB1_Pin GPIO_Pin_1
#define DB1_GPIO_Port GPIOE
#define DB2_Pin GPIO_Pin_2
#define DB2_GPIO_Port GPIOE
#define DB3_Pin GPIO_Pin_3
#define DB3_GPIO_Port GPIOE
#define DB4_Pin GPIO_Pin_4
#define DB4_GPIO_Port GPIOE
#define DB5_Pin GPIO_Pin_5
#define DB5_GPIO_Port GPIOE
#define DB6_Pin GPIO_Pin_6
#define DB6_GPIO_Port GPIOE
#define DB7_Pin GPIO_Pin_7
#define DB7_GPIO_Port GPIOE
#define BACK_CTL_Pin GPIO_Pin_12
#define BACK_CTL_GPIO_Port GPIOE

#define E2_Pin GPIO_Pin_13
#define E2_GPIO_Port GPIOB
#define E1_Pin GPIO_Pin_14
#define E1_GPIO_Port GPIOB
#define R_W_Pin GPIO_Pin_15
#define R_W_GPIO_Port GPIOB

#define RS_Pin GPIO_Pin_10
#define RS_GPIO_Port GPIOD
#define RST_Pin GPIO_Pin_11
#define RST_GPIO_Port GPIOD

//LCD19264F液晶显示屏
#define BACK_LIGHT_ON	HAL_GPIO_WritePin(BACK_CTL_GPIO_Port,BACK_CTL_Pin,GPIO_PIN_SET)
#define BACK_LIGHT_OFF	HAL_GPIO_WritePin(BACK_CTL_GPIO_Port,BACK_CTL_Pin,GPIO_PIN_RESET)
#define RST_ON			HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,GPIO_PIN_SET)
#define RST_OFF			HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin,GPIO_PIN_RESET)
#define RS_ON			HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_SET)
#define RS_OFF			HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_RESET)
#define RW_ON			HAL_GPIO_WritePin(R_W_GPIO_Port,R_W_Pin,GPIO_PIN_SET)
#define RW_OFF			HAL_GPIO_WritePin(R_W_GPIO_Port,R_W_Pin,GPIO_PIN_RESET)
#define DB0_ON			HAL_GPIO_WritePin(DB0_GPIO_Port,DB0_Pin,GPIO_PIN_SET)
#define DB0_OFF			HAL_GPIO_WritePin(DB0_GPIO_Port,DB0_Pin,GPIO_PIN_RESET)
#define DB1_ON			HAL_GPIO_WritePin(DB1_GPIO_Port,DB1_Pin,GPIO_PIN_SET)
#define DB1_OFF			HAL_GPIO_WritePin(DB1_GPIO_Port,DB1_Pin,GPIO_PIN_RESET)
#define DB2_ON			HAL_GPIO_WritePin(DB2_GPIO_Port,DB2_Pin,GPIO_PIN_SET)
#define DB2_OFF			HAL_GPIO_WritePin(DB2_GPIO_Port,DB2_Pin,GPIO_PIN_RESET)
#define DB3_ON			HAL_GPIO_WritePin(DB3_GPIO_Port,DB3_Pin,GPIO_PIN_SET)
#define DB3_OFF			HAL_GPIO_WritePin(DB3_GPIO_Port,DB3_Pin,GPIO_PIN_RESET)
#define DB4_ON			HAL_GPIO_WritePin(DB4_GPIO_Port,DB4_Pin,GPIO_PIN_SET)
#define DB4_OFF			HAL_GPIO_WritePin(DB4_GPIO_Port,DB4_Pin,GPIO_PIN_RESET)
#define DB5_ON			HAL_GPIO_WritePin(DB5_GPIO_Port,DB5_Pin,GPIO_PIN_SET)
#define DB5_OFF			HAL_GPIO_WritePin(DB5_GPIO_Port,DB5_Pin,GPIO_PIN_RESET)
#define DB6_ON			HAL_GPIO_WritePin(DB6_GPIO_Port,DB6_Pin,GPIO_PIN_SET)
#define DB6_OFF			HAL_GPIO_WritePin(DB6_GPIO_Port,DB6_Pin,GPIO_PIN_RESET)
#define DB7_ON			HAL_GPIO_WritePin(DB7_GPIO_Port,DB7_Pin,GPIO_PIN_SET)
#define DB7_OFF			HAL_GPIO_WritePin(DB7_GPIO_Port,DB7_Pin,GPIO_PIN_RESET)
#define CLK1_ON			HAL_GPIO_WritePin(E1_GPIO_Port,E1_Pin,GPIO_PIN_SET)
#define CLK1_OFF		HAL_GPIO_WritePin(E1_GPIO_Port,E1_Pin,GPIO_PIN_RESET)
#define CLK2_ON			HAL_GPIO_WritePin(E2_GPIO_Port,E2_Pin,GPIO_PIN_SET)
#define CLK2_OFF		HAL_GPIO_WritePin(E2_GPIO_Port,E2_Pin,GPIO_PIN_RESET)

void HAL_GPIO_WritePin(GPIO_TypeDef* gpio, u16 pin,uint8_t PinState);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* gpio,u16 pin);

#if 1//佳显测试架
#if 0
sbit RST=P2^6;
sbit RS=P2^5; 
sbit RW=P2^4;
sbit E1=P1^0;
sbit E2=P1^1;
sbit PSB_19264F=P1^2;
sbit DB0_19264F=P1^3;
sbit DB1_19264F=P1^4;
sbit DB2_19264F=P1^5;
sbit DB3_19264F=P1^6;
sbit DB4_19264F=P1^7;
sbit DB5_19264F=P2^3;
sbit DB6_19264F=P2^2;
sbit DB7_19264F=P2^0;
#else
#endif

#else

sbit RS=P2^6; //串口时为CS
sbit RW=P2^5; //串口为SID
sbit E1=P2^4; //串口为时钟SCLK
sbit E2=P2^2; //串口为时钟SCLK

sbit RST=P2^0;

#define Lcm_Data P1

#endif


#define uchar unsigned char 
#define uint unsigned int 

#define ENABLE_UP_SCREEN	0  //上半屏使能
#define ENABLE_DOWN_SCREEN	1  //下半屏使能


void Lcm_Wr_Data(uchar wrdata,uint8_t enable); //写数据
void Lcm_Wr_Command(uchar wrcommand,uint8_t enable); //写指令
void Lcm_Rd_Status(void);//读忙状态
void Lcm_Init(uint8_t enable);//液晶初始化
void Lcm_GotoXY(uchar pos_X,uchar pos_y);
void Lcm_Disp_Onechar(uchar onechar,uint8_t enable);//显示单个字符
void Lcm_Disp_String(uchar *string,uint8_t enable);//显示字符串
void Wr_Gdram(uchar pos_x,uchar pos_y,uint length,uchar width,uchar *table,uint8_t enable);
void Clean_Gdram(uint8_t enable);//清除GDRAM
void Wr_Cgram(uchar addr,uchar *table,uint8_t enable);
void Disp_Cgram(uchar addr_data,uint8_t enable);
void Delay_1ms(uint x);//1ms延时
void Lcm_Delay(void);
#endif
