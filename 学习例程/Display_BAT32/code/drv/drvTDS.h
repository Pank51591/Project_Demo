#ifndef DRV_TDS
#define DRV_TDS


#define TDS1_1(x)	SETGPIO_##x(PORT7,PIN0)//
#define TDS1_2(x)	SETGPIO_##x(PORT7,PIN1)//

#define TDS2_1(x)	SETGPIO_##x(PORT0,PIN1)//
#define TDS2_2(x)	SETGPIO_##x(PORT0,PIN0)//

	

#define Set_rawTDS_Out_Forward()	TDS2_1(0);TDS2_2(1);	
#define Set_rawTDS_Out_Reverse()	TDS2_1(1);TDS2_2(0);	
#define Set_rawTDS_Out_Close()		TDS2_1(0);TDS2_2(0);	

#define Set_netTDS_Out_Forward()	TDS1_1(0);TDS1_2(1);	
#define Set_netTDS_Out_Reverse()	TDS1_1(1);TDS1_2(0);	
#define Set_netTDS_Out_Close()		TDS1_1(0);TDS1_2(0);




#define TDS_get_29s		29
#define TDS_get_20s		20
#define TDS_get_5s		5	



typedef struct
{
	INT16U raw;//ԭˮTDS	
	INT16U temperature;
	INT16U net;//��ˮTDS
}
ADC_VAL;


extern INT16S gTDSTemp;//TDS�¶�
extern INT16S gTDSTemp2;//TDS�¶�


void GetNTCTemp(INT16U ad);
void GetrawTDS(INT16U ad);
void GetnetTDS(INT16U ad);
INT32U GetNTCResVal(INT16U ad);

void GetNTCTemp2(INT16U ad);


void MonitorTDS(void);
void SetTDSUpdataEN(BOOL en);


#endif

