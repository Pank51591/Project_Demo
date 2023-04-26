#include  "test.h"
#include  "key.h"
#include  "RF_A7325.h"
#include "089_B19110A.h"


volatile unsigned char  gcTest_state;
volatile unsigned char  gcTestKeyState;
volatile unsigned char  gcTestKeyCount;

volatile unsigned char  TestKeyReturn_Flag;
#define  Set_TestKeyReturn_Flag    TestKeyReturn_Flag=1
#define  Clr_TestKeyReturn_Flag    TestKeyReturn_Flag=0

volatile unsigned char gcTestledscan_row;
volatile unsigned int Testled_BlinkCnt;	

volatile unsigned char Testled_horseSta;    /* �����ѭ��״̬ */
volatile unsigned int Testled_horseCnt;	    /* ��������Ƽ�ʱ */

volatile unsigned int  giTestKeyValue;
volatile unsigned int  giTestTempKeyValue = 0;

volatile unsigned int  giLEDValue;

volatile unsigned char gcTestRfXamsCnt;      /* ����RF���ݷ���ʱ���� 60ms */
volatile unsigned char gcTestTxRf_flag;      /* RF���ͱ�־ */  

volatile unsigned int giTestTimeSecCnt;   /* ����ģʽ��ʱ */
volatile unsigned int giTestTimeMinCnt;   /* ����ģʽ��ʱ */

volatile unsigned int  giKeyDownBit;

extern volatile unsigned char gcTxBuff[17];



const unsigned char gcTestTxBuff[17]=
{
	0xff,	
	0xff,
	0xff,
	0xff,
	warmhouse,    /* warmhouse */
	strong,     /* ���� */
	fixed90,    /* ���� */
	focus,      /* ���� */
	timer15min,
	0x00,
	0x0f,
	noneset,
	noneset,
	noneset,
	ModRB20V1,
	noneset,
	0x00,
};


typedef  struct
{
	unsigned int  b0:1;
	unsigned int  b1:1;	
	unsigned int  b2:1;
	unsigned int  b3:1;		
	unsigned int  b4:1;
	unsigned int  b5:1;	
	unsigned int  b6:1;
	unsigned int  b7:1;
	unsigned int  b8:1;
	unsigned int  b9:1;	
	unsigned int  b10:1;
	unsigned int  b11:1;		
	unsigned int  b12:1;
	unsigned int  b13:1;	
	unsigned int  b14:1;
	unsigned int  b15:1;				
}u16_field;  



typedef  union
{
	unsigned int  word;
	u16_field     Ebit;

}stType_word;

stType_word  stLEDValue; 

#define  LEDAll     stLEDValue.word        //���еĵ�
#define  LED1       stLEDValue.Ebit.b0
#define  LED2       stLEDValue.Ebit.b1
#define  LED4       stLEDValue.Ebit.b2
#define  LED5       stLEDValue.Ebit.b3
#define  LED9       stLEDValue.Ebit.b4
#define  LED11      stLEDValue.Ebit.b5
#define  LED15      stLEDValue.Ebit.b6
#define  LED16      stLEDValue.Ebit.b7
#define  LED17      stLEDValue.Ebit.b8
#define  LED18      stLEDValue.Ebit.b9


#define   F_on    1

unsigned int TestKeyCheck(void);
void TestGet_KeyValue(void);
void Testled_scan(void);
void Testled_horse(void);
void KeytoLed(void);

/*************************************************************************
//					void Is_IntoTest(void)
//					�жϽ������ģʽ
//					
*************************************************************************/
void  Is_IntoTest(void)
{
	unsigned  char i,temp = 0;
	
	Clr_Isintest_flag;
	
	//Set_PA5_Out;
	//Set_PC2_In;
	//Set_PC1_In;
	//Set_PC0_In;
	
	//_pa5 = 0;
	
	Set_PA5_OutPut();
	
	
	if( (ReadKEY_PA6 == 0) || (ReadKEY_PA8 == 0) || (ReadKEY_PA10 == 0) )  //������һ����������
	{
			return ;
	}
	
		

	Set_PB1_OutPut();
	if( (ReadKEY_PA6 == 0) || (ReadKEY_PA8 == 0) || (ReadKEY_PA10 == 0) )
	{
			return ;
	}
	
	
	Set_PB0_OutPut();
	
	if( (ReadKEY_PA6 == 0) || (ReadKEY_PA8 == 0) || (ReadKEY_PA10 == 0) )
	{
			return ;
	}		
	
	Set_PA7_OutPut();
	
	
	if (ReadKEY_PA10 == 0)
	{
		return;
	}
	
	if ((ReadKEY_PA6 == 0)&&(ReadKEY_PA8 == 0))      //��ʱ��ȡůͬʱ���£��������ģʽ
	{
		Set_Isintest_flag;   //�������ģʽ��־
		gcTest_state = 0;

		giTestTimeSecCnt = 0;
		giTestTimeMinCnt = 0;
		
		for(i = 0;i < 16;i++)	
		{
			gcTxBuff[i] = gcTestTxBuff[i];
			temp += gcTxBuff[i];	
		}
		gcTxBuff[16] = temp;	
	}	
}

/*************************************************************************
//					void Is_IntoTest(void)
//					
//					
*************************************************************************/
unsigned int TestKeyCheck(void)
{
	
	Set_All_OutPut();
	
	switch(gcTestKeyState)
	{
		case 0:
		{	
			//			_nop();
			//			_nop();
			
			//if((_pa1 == 0)||(_pa3 == 0)||(_pa4 == 0)) //��һ��Ϊ0����Ϊ�а�������
			if( (ReadKEY_PA6 == 0) || (ReadKEY_PA8 == 0) || (ReadKEY_PA10 == 0) )  //�а�������
			{
				gcTestKeyCount++;
				if (gcTestKeyCount >= 3)
				{
					gcTestKeyCount = 0;
					gcTestKeyState = 1;	
				}
			}
			
		}
		break;
		
		case 1:
		{
			giTestTimeSecCnt = 0;
			giTestTimeMinCnt = 0;
			Set_TestKeyReturn_Flag;
			TestGet_KeyValue();
			gcTestKeyState = 2;
		}
		break;
		
		case 2:
		{
			giTestTimeSecCnt = 0;
			giTestTimeMinCnt = 0;
		  //	if((_pa1 == 1)&&(_pa3 == 1)&&(_pa4 == 1)) //ȫΪ�ߣ���Ϊ��������
			if( (ReadKEY_PA6) && (ReadKEY_PA8) && (ReadKEY_PA10))
			{
				gcTestKeyCount++;
				if (gcTestKeyCount >= 3)
				{
					if(giTestKeyValue == KEYSW3)
					{
						Set_TestKeyReturn_Flag;						
					} 
					gcTestKeyCount = 0;
					gcTestKeyState = 0;	
					
				}				
				
			}
			else
			{
				Set_TestKeyReturn_Flag;
				TestGet_KeyValue();	
			}			
		}
		break;		
				
	}
	
	if (TestKeyReturn_Flag)
	{
		Clr_TestKeyReturn_Flag;
		return giTestKeyValue;

	}
	else
	{
		return 0x0000;	
	}	
	
}
/*************************************************************************
//					void TestGet_KeyValue(void)
//					����ģʽ��ȡ����״̬
//					
*************************************************************************/
void TestGet_KeyValue(void)
{
	giTestKeyValue = 0;	
	
	Set_PA5_OutPut();
	
	//if (_pa4 == 0)
	if (ReadKEY_PA6 == 0) 
	{
		giTestKeyValue |= KEYSW3;        //
	 Clr_TestKeyReturn_Flag;
		//Set_TestKeyReturn_Flag;        //���÷��ر�־
	}
		
	if (ReadKEY_PA10 == 0) 
	{     
		giTestKeyValue |= KEYSW2;      //
	}
	
	if (ReadKEY_PA8 == 0) 
	{
		giTestKeyValue |= KEYSW1;      //
	}
			
	Set_PA7_OutPut();
	
	if (ReadKEY_PA6 == 0) 
	{
		giTestKeyValue |= KEYSW6;       //
	}
	
	if (ReadKEY_PA10 == 0) 
	{   
		giTestKeyValue |= KEYSW5;       //
	}
	
	if (ReadKEY_PA8 == 0) 
	{
		giTestKeyValue |= KEYSW4;        //
	}	


	Set_PB1_OutPut();
	
	if (ReadKEY_PA6 == 0)
	{
		giTestKeyValue |= KEYSW9;        //

	}
	
	if (ReadKEY_PA10 == 0)
	{
		giTestKeyValue |= KEYSW8;        //

	}
	
	if (ReadKEY_PA8 == 0)
	{
		giTestKeyValue |= KEYSW7;        //	
	}
			
	Set_PB0_OutPut();
	
	if (ReadKEY_PA6 == 0)
	{
		giTestKeyValue |= KEYSW12;            //
	}
	
//	if (ReadKEY_PA10 == 0)
//	{
//		giTestKeyValue |= KEYSW11;           //
//	}
	
	if (ReadKEY_PA8 == 0)
	{	
		giTestKeyValue |= KEYSW10;           //
	}
				
}


/*************************************************************************
//					void Testled_scan(void)
//					led���������
//					1ms����һ��
//					
*************************************************************************/
void Testled_scan(void)
{
	
	Clr_PB4;
	Clr_PB3;
	Clr_PB6;
	Clr_PB5;
	
	Set_PA15;
	Set_PA4;
	Set_PA12;
	Set_PA11;
	Set_PA9;
	
	switch(gcTestledscan_row)
	{
		case 0:
		{
			if(LED1 == F_on)                //led1   
			{
				//_pc4 = 1;		     
					Set_PB4;
			}
 
			if(LED4 == F_on)                //led4
			{
				//_pc5 = 1;		 
					Set_PB3;
			}
									
			gcTestledscan_row = 1;
			//_pb0 = 0;			
			Clr_PA15;
		} 	
		break;
		
		case 1:
		{
			gcTestledscan_row = 2;
		}
		break;
		
		case 2:
		{
			if(LED2 == F_on)              //led2   
			{
				//_pc4 = 1;		
					Set_PB4;
			}
 
			if(LED5 == F_on)              //led5
			{
				//_pc5 = 1;	
					Set_PB3;
			}

			if(LED9 == F_on)              //led9   
			{
				//_pd2 = 1;		
					Set_PB6;
			}
 
			if(LED11 == F_on)             //led11
			{
				//_pd1 = 1;		
					Set_PB5;
			}
			gcTestledscan_row = 3;
			//_pb1 = 0;		
				Clr_PA4;
		}	
		break;

		case 3:
		{
			gcTestledscan_row = 4;	
		}
		break;

		case 4:
		{
			gcTestledscan_row = 5;
			
		}
		break;

		case 5:
		{
			gcTestledscan_row = 6;	
			
		}
		break;
		
		case 6:
		{ 
			if(LED15 == F_on)              //led15
			{
				//_pc5 = 1;		
					Set_PB3;
			}

			if(LED17 == F_on)               // led17   
			{
				//_pd2 = 1;		  
					Set_PB6;
			}
 
			gcTestledscan_row = 7;
			//_pb5 = 0;		
				Clr_PA11;
		}
		break;
		
		case 7:
		{
			gcTestledscan_row =8;	
		}
		break; 
		
		case 8:
		{
			if(LED16 == F_on)              // led16   
			{
				//_pd2 = 1;		     
					Set_PB3;
			}
			if(LED18 == F_on)              // led18   
			{
				//_pd2 = 1;		     
					Set_PB6;
			}

			gcTestledscan_row = 9;
			//_pb6 = 0;		
				Clr_PA9;
		}
		break;
		
		case 9:
		{
			gcTestledscan_row = 0;
		}
		break;		
					
		default:
		break;		
	}		
}

/*************************************************************************
//					void Testled_horse(void)
//					����Ƴ���
//					
//					
*************************************************************************/
void Testled_horse(void)
{
	if(Testled_horseCnt >= 300)	     //0.3s ����Ƶ��	
	{
		Testled_horseCnt = 0;
	switch(Testled_horseSta)
		{
			case 0:
				LEDAll = 0;
				LED16 = 1;	
			break;
				
			case 1:
				LEDAll = 0;
				LED18 = 1;	
			break;

			case 2:
				LEDAll = 0;
				LED17 = 1;	
			break;

			case 3:
				LEDAll = 0;
				LED15 = 1;	
			break;

			case 4:
				LEDAll = 0;
				LED2 = 1;	
			break;

			case 5:
				LEDAll = 0;
				LED5 = 1;	
			break;

			case 6:
				LEDAll = 0;
				LED9 = 1;	
			break;

			case 7:
				LEDAll = 0;
				LED11 = 1;	
			break;

			case 8:
				LEDAll = 0;
				LED1 = 1;	
			break;

			case 9:
				LEDAll = 0;
				LED4 = 1;	
			break;
			
		}
		Testled_horseSta++;
		if(Testled_horseSta > 9)
		{
			Testled_horseSta = 0;
		}	
	}
	
	
}


/*************************************************************************
//					void KeytoLed(void)
//					
//					
*************************************************************************/
void KeytoLed(void)
{
	switch(giTestTempKeyValue)
	{
		case KEYSW1:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW1;	
		}
		break;
		
		case KEYSW2:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW2;					
		}
		break;			
		
		case KEYSW4:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW4;					
		}
		break;
		
		case KEYSW5:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW5;					
		}
		break;	
			
		case KEYSW6:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW6;					
		}
		break;

		case KEYSW7:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW7;					
		}
		break;
		
		case KEYSW8:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW8;					
		}
		break;	
			
		case KEYSW9:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW9;					
		}
		break;		
		
		case KEYSW10:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW10;					
		}
		break;
		
//		case KEYSW11:                    
//		{
//			LED2 = 1;
//			giKeyDownBit |= KEYSW11;					
//		}
//		break;	
			
		case KEYSW12:                    
		{
			LED2 = 1;
			giKeyDownBit |= KEYSW12;					
		}
		break;

		default:
			LED2 = 0;	
			break;		
	}	
}


/*************************************************************************
//					void Test_func(void)
//					�жϽ������ģʽ
//					
*************************************************************************/
void Test_func(void)
{
	

	switch(gcTest_state)
	{
		case 0:      //���ֺ�����汾
		{
			LED17 = 1;     //������ʾ
			LED5 = 1;      //����汾��ʾ
			
			if(giTestTempKeyValue == KEYSW1)    /* RF�źŲ��� */
			{
				gcTest_state = 7;
				LEDAll = 0;
			}
			else if(giTestTempKeyValue == KEYSW3)   /* FCT���ܲ��� */
			{
				WriteReg(0x24,0x00);      //���ͷ��书���趨ֵ	 A7325_TXTEST_REG 
				gcTest_state = 1;
				LEDAll = 0;
			}
		}
		break;
		
		case 1:          //led ȫ��˸
		{
			if(Testled_BlinkCnt >= 500)
			{
				Testled_BlinkCnt = 0;
				if(LEDAll == 0)
				{
					LEDAll = 0x03ff;	
				}
				else
				{
					LEDAll = 0;
					
				}					
			}
					
			if(giTestTempKeyValue == KEYSW3)
			{
				gcTest_state = 2;
				Testled_horseCnt = 0;
				Testled_BlinkCnt = 0;	

			}
			
		}
		break;		
		
		case 2:           //����ƣ���ⵥ��LED
		{
			Testled_horse();
			
			if(giTestTempKeyValue == KEYSW3)
			{
				gcTest_state = 3;
				Testled_horseCnt = 0;
				LEDAll = 0;
				giKeyDownBit = 0;	

			}			
			
		}
		break;

		case 3:       //��������LED2������ⵥ������
		{
			KeytoLed();
			if((giKeyDownBit == 0x0bfb)&&(gcTestKeyState == 0))    //����ȫ�������� ��������ֵΪffb���Ұ�����ȫ���ɿ���
			{
				gcTest_state = 4;
				LEDAll = 0;					
			}

		}
		break;
		
		case 4:          //LEDȫ��˸
		{
			if(Testled_BlinkCnt >= 500)
			{
				Testled_BlinkCnt = 0;
				if(LEDAll == 0)
				{
					LEDAll = 0xbfff;	
				}
				else
				{
					LEDAll = 0;
				}	
			}
						
			if(giTestTempKeyValue == KEYSW3)
			{
				gcTestTxRf_flag = 1;
				gcTestRfXamsCnt = 0;
				LEDAll = 0;	
				gcTest_state = 5;					
			}
		}
		break;
		
		case 5:      //����RF�ź�
		{
			LED2 = 1;
			
			if(gcTestTxRf_flag)	
			{
				gcTestTxRf_flag = 0;
				A7325TX_Process();	
			}
						
			if(giTestTempKeyValue == KEYSW3)
			{			
	  			gcTest_state = 6;
	  			LEDAll = 0;
			}
			
		}
		break;		
		
		case 6:      //�������
		{
			giSleepTime = MAX_SLEEP_VALUE;
			Sleep_Process();
			
		}
		break;
		
		case 7:             //ѭ�����͵��ز�
		{
			DirectMode_init();
			
			while(1)
			{
				StrobeCmd(0xD0);   //CMD_TX				
			}
		
		}
		break;
		
		default:
		break;				
	}
	
 	giTestTempKeyValue = TestKeyCheck();	
	
		
}

