#include "ir.h"

//uint8_t firstbit;
//uint8_t receive_statue;
//extern uint8_t head705flag;
uint8_t data_buf[] = {0x00,0x00,0x00};

void ir_receive()
{
	  uint8_t receive_data;
	  uint8_t x,y;
		receive_data = GPIO_ReadPin(GPIO1, GPIO_PIN_6);
		if(receive_data)
		{
			data_buf[0] |= 0x01;
		}
		else
		{
			data_buf[0] &= 0xfe;
		}
		for(x =0 ; x<=2 ;i++)
		{
			for(i = 0 ; i<=7; i++)
			{
				data_buf[x] << 1;
			}	
		}
		INT1_ITConfig(ENABLE,LOW);	
}