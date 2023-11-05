#include"config.h"
#include"delay.h"


//INT16U delaycount=0; 


void delayms( INT32U us ) 
//void delay(INT32U us)
{
	INT32U tm;
	
	tm=5*us;
	
	for(us=0;us<tm;us++)
	{
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;//NOP;NOP;NOP;
		//NOP;NOP;NOP;NOP;NOP;
		WDT_Restart();
	}
	
}







#if 1
void delayus( INT32U us ) 
{
	for(us=us;us>0;us--)
	{
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;NOP;NOP;NOP;
		NOP;NOP;//NOP;NOP;NOP;
		//NOP;NOP;NOP;NOP;NOP;		
	}
}
#endif









