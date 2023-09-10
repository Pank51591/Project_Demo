#include "ir.h"
#include "SC_Init.h"	// MCU initialization header file, including all firmware library header files
#include "SC_it.h"
#include "..\Drivers\SCDriver_list.h"
#include "HeadFiles\SysFunVarDefine.h"
#include "ir.h"
#include "sc95f_usci0.h"

//uint8_t firstbit;
//uint8_t receive_statue;
//extern uint8_t head705flag;
uint32_t receive_buf[1] = {0};
//uint8_t receive_buf[] = {0,0,0};
uint8_t receive_bit;
uint8_t send_buf[] = {0,0,0};
uint8_t send_data[] = {0,0,0};
extern uint8_t start_receiveflag;
extern uint8_t head1080usflag;
extern uint8_t after720usflag;
extern uint8_t itcount;
extern uint8_t sendendflag;


/*********************************************************
***函数名：
***函数功能：IR信号接收
***参数：
***返回值：
**********************************************************/
void ir_receive()
{
	  uint8_t receive_data;

		receive_data = GPIO_ReadPin(GPIO1, GPIO_PIN_6);
	  receive_buf[0] <<= 1;       //先左移一位，空出最低位
	  
	  /*将接收到的IR信号，高位存在缓冲区的高位（顺序没有变）*/
	  if(receive_data)
		{
		    receive_buf[0] |= 0x00000001;
		}
		else
		{
		    receive_buf[0] &= 0xfffffffe;    //最低位为0
		}
//	    temp = receive_buf[0];
//    for(i = 0;i <3 ; i--)
//	  {
//	     x = receive_data;
//			 bufvalue = temp;
//			 bufvalue <<= 1;
//			 receive_data = bufvalue&0x80;
//			if(x)
//			{
//			    bufvalue |= 0x01;		 
//	    }
//			else
//			{
//			    bufvalue &= 0xfe;
//			}
//			receive_buf[i] = bufvalue;
//			temp = receive_buf[i+1];			
//		}
}
	
//uint16_t Send8DataTo9Data(uint8_t SendData)
//{
//	uint16_t giiSend9Data = 0;
//	uint8_t i = 0,j=0;
//		
//	giiSend9Data = SendData;
//	
//	for (i=0;i<8;i++)
//	{
//		if (SendData&0x01)
//		{
//			j++;
//		}
//		SendData = ( SendData>> 1);
//	}
//	
//	if((j%2)==0)
//	{
//		giiSend9Data |=0x100;
//	}
//	
//	return giiSend9Data;
//}


/*********************************************************
***函数名：
***函数功能：红外数据接收
***参数：
***返回值：
**********************************************************/
void ir_receive_pocess()
{
	  uint32_t x,y,z;
	  uint8_t i;
	  uint8_t w,v;
	
		head1080usflag = 0;
		after720usflag = 0;
	
	  if(receive_bit < 24)
		{
		   ir_receive();   //将IR数据存起来
			 receive_bit++;
		}
		else
		{
		    receive_bit = 0;
			  start_receiveflag = 0;
        itcount = 0;      //接收完成，中断次数清零
			  x=y=z=receive_buf[0];    //将接收到的IR信号
				send_buf[0] = (u8)(x & 0xff);    //低8位
				send_buf[1] = (u8)(y >> 8);      //中8位
				send_buf[2] = (u8)(z >> 16);     //高8位
			
			  /*将 低中高位的 3个8位的高低位倒序*/
				for(w=0;w<8;w++)
				{
						for(v=0;v<3;v++)
						{
							 send_data[v] >>= 1;    //空出最高位
							
							 if(send_buf[v] & 0x80)
							 {
									 send_data[v] |= 0x80;
							 }
							 else
							 {
									 send_data[v] &= 0x7f;
							 }
							 send_buf[v] <<= 1;    //将原来的最高位移出去
						}
			
				}
			  
/****************************************(串口发送)*****************************************/				
			 for(i= 0 ; i < 3 ; i++)
			 {	
					USCI0_UART_SendData8(send_data[i]);   
					 while (!sendendflag);
					 sendendflag = 0;
			 }
			 receive_buf[0] = 0;	    //将接收缓冲区清零			 
		}

}