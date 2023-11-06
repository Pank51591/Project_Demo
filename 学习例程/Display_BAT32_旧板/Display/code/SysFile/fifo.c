#include"config.h"
#include"fifo.h"
#include"typedef.h"
#include"string.h"



#define fifo_max_size SERIAL_BUFF_NUM


 
typedef struct
{
	INT8U frame_data[fifo_max_size];
	INT16U fornt;
	INT16U tail;
	INT16U frame_size;
}Queue;

Queue fifo_queue;




BOOL uartsendflag=0;//发送完成标志
INT8U uartgettimer=0;//接收完成标志


BOOL systimer10msflag;// 这个参数要在中断中10ms置位一次
BOOL systimer1msflag;// 这个参数要在中断中1ms置位一次






/************************fifo********************************/
void fifo_init(void)
{
	fifo_queue.fornt = 0;
	fifo_queue.tail = 0;
	fifo_queue.frame_size = 0;
}

INT8U fifo_is_full(void)
{
	if((fifo_queue.frame_size >= fifo_max_size))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

INT8U fifo_empty(void)
{
	if(fifo_queue.frame_size == 0)
	return 1;
	else
	return 0;
}

void fifo_clean_all(void)
{
	fifo_queue.fornt = 0;
	fifo_queue.tail = 0;
	fifo_queue.frame_size = 0;
}

INT32U fifo_get_size(void)
{
	return fifo_queue.frame_size;
}

INT8U fifo_append_one(INT8U frame_data)
{	
	//if(frame_data==0)
	{
	//	return 0;
	}
	if(fifo_is_full())return 0;
	fifo_queue.frame_data[fifo_queue.tail] = frame_data;
	fifo_queue.tail++;
	fifo_queue.tail %= fifo_max_size;
	fifo_queue.frame_size++;
	return 1;
}



INT32U fifo_read_strings(INT8U *Pdata, INT32U pdata_len)
{
	INT32U i;
	INT32U num = (fifo_queue.frame_size > pdata_len ? pdata_len:fifo_queue.frame_size);
	INT32U j = fifo_queue.fornt;
	
	for(i=0;i<num;i++)
	{
		Pdata[i] = fifo_queue.frame_data[j];
		j++;
		j %= fifo_max_size;
	}
	Pdata[i]=0;
	return num;
}

INT32U fifo_pop(INT32U pdata_len)
{
	if(fifo_queue.frame_size<pdata_len)
	{
		pdata_len=fifo_queue.frame_size;
	}
	fifo_queue.fornt += pdata_len;
	fifo_queue.fornt %= fifo_max_size;
	fifo_queue.frame_size -= pdata_len;
	
  	return pdata_len;
}



//===========================================================================

INT8U GetCmdLen(INT8U *p,INT32U len)
{
	INT16U i;

	for(i=2;i<len;i++)
	{
		if(p[i]==0x0D&&p[i+1]==0x0A)
		{
			return i;
		}
	}

	return 0;
}



INT8U GetCMD(INT8U *p,INT8U len)
{

	return TRUE;
}



//在主函数中调用此函数
INT16U Uart_data_handle(INT8U *buff)
{ 
	INT16U len=0;	
	
	len = fifo_get_size();
	
	if(len<3)
		return 0;
	
	fifo_read_strings(buff,len);

	
	fifo_pop(len);

	return len;
}


