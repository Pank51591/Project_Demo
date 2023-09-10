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
***��������
***�������ܣ�IR�źŽ���
***������
***����ֵ��
**********************************************************/
void ir_receive()
{
	  uint8_t receive_data;

		receive_data = GPIO_ReadPin(GPIO1, GPIO_PIN_6);
	  receive_buf[0] <<= 1;       //������һλ���ճ����λ
	  
	  /*�����յ���IR�źţ���λ���ڻ������ĸ�λ��˳��û�б䣩*/
	  if(receive_data)
		{
		    receive_buf[0] |= 0x00000001;
		}
		else
		{
		    receive_buf[0] &= 0xfffffffe;    //���λΪ0
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
***��������
***�������ܣ��������ݽ���
***������
***����ֵ��
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
		   ir_receive();   //��IR���ݴ�����
			 receive_bit++;
		}
		else
		{
		    receive_bit = 0;
			  start_receiveflag = 0;
        itcount = 0;      //������ɣ��жϴ�������
			  x=y=z=receive_buf[0];    //�����յ���IR�ź�
				send_buf[0] = (u8)(x & 0xff);    //��8λ
				send_buf[1] = (u8)(y >> 8);      //��8λ
				send_buf[2] = (u8)(z >> 16);     //��8λ
			
			  /*�� ���и�λ�� 3��8λ�ĸߵ�λ����*/
				for(w=0;w<8;w++)
				{
						for(v=0;v<3;v++)
						{
							 send_data[v] >>= 1;    //�ճ����λ
							
							 if(send_buf[v] & 0x80)
							 {
									 send_data[v] |= 0x80;
							 }
							 else
							 {
									 send_data[v] &= 0x7f;
							 }
							 send_buf[v] <<= 1;    //��ԭ�������λ�Ƴ�ȥ
						}
			
				}
			  
/****************************************(���ڷ���)*****************************************/				
			 for(i= 0 ; i < 3 ; i++)
			 {	
					USCI0_UART_SendData8(send_data[i]);   
					 while (!sendendflag);
					 sendendflag = 0;
			 }
			 receive_buf[0] = 0;	    //�����ջ���������			 
		}

}