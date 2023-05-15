//*************************************************************************************************
//  Copyright (c) 	��������Ԫ΢�������޹�˾
//	�ļ�����	:  S_TouchKeyCFG.c
//	����		: 
//	ģ�鹦��	:  ���ؼ������ļ�
// 	�汾		:
// 	���ļ�¼	:
//	ע������	:  �û���Ҫ���õ��ļ���S_TouchKeyCFG.h��
//  ��汾���	: 
//************************************************************************************************
#include "S_TouchKeyCFG.h"
#include "TKDriver.h"
#include "stdio.h"
#include "SC95F8x1xB_C.H"
#include "HeadFiles\SysFunVarDefine.h"

#define ScanTimeCon 3
//*************************************************************************************
//		 �Ĵ�������
//*************************************************************************************
/*PSW*/
sfr 	TK_PSW	    = 	0xD0;							//����״̬��
sbit 	TK_CY		= 	TK_PSW^7;						//��λ  

#if defined(SC95F8x3x) || defined(SC92L853x) || defined(SC95F8x6x) || defined(SC95F8x1xB) 
//sfr	    BTMCON      =   0XFB;   						//��Ƶ��ʱ�����ƼĴ���
#elif defined(SC92F848x) || defined(SC92F859x) 
sfr	    BTMCON      =   0XCE; 
#endif


sfr 	TK_IE1	    = 	0xA9;							//�жϿ��ƼĴ�
/*system*/
//sfr 	PCON	    =   0x87;							//��Դ�������ƼĴ���

sfr		TKCR	=	0xE8;								//TouchKey���ƼĴ���

sfr 	TKTMH	=	0xE7;								//����������ʱ�Ĵ���L
sfr 	TKTML	=	0xE6;								//����������ʱ�Ĵ���L
sfr16   TKTM    =   0xE6;

sfr		TKCNTH	=	0xE5;								//TouchKey������ֵ��7λ
sfr		TKCNTL	=	0xE4;								//TouchKey������ֵ��8λ
sfr16   TKCNT   =   0xE4;

sfr 	TKCFG2	=	0xE3;								//���������ο���ѹ���üĴ���
sfr		TKCFG1	=	0xE2;								//TouchKey���üĴ���2
sfr		TKCFG0	=	0xE1;								//TouchKey���üĴ���1

/*TKCR*/
sbit	ENTKS	=	TKCR^7;								//TouchKey���ص�Դ
sbit	TRIG	=	TKCR^6;								//TouchKey�������أ�д1��Ч������һ��keyɨ������
sbit	TRIF	=	TKCR^5;								//TouchKey�жϱ�־
//===========================================================================
//ȫ�ֱ�������
unsigned	char	xdata		SOCAPI_TouchKeyStatus;	//API�ӿ�״̬��bit7-һ��ɨ����ɱ�־  1:��� 	0��δ���
														//			   bit6-ͨ���������������־ 1:���	 0:δ���
//===============================================================================
//ȫ�ֱ��������������򲻿��޸�
unsigned 	int 	xdata		RawData [SOCAPI_SET_TOUCHKEY_TOTAL];			
unsigned 	int		data		BaseLine[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned    int	 	xdata		FilterData[SOCAPI_SET_TOUCHKEY_TOTAL];												
unsigned	char    xdata		RestAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL]; 			
unsigned	char    xdata		TouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];				
unsigned	char    xdata		NoTouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];  			
unsigned	char	xdata		CurrentChannel[SOCAPI_SET_TOUCHKEY_TOTAL];						     
unsigned    char    xdata 	    LowFingerDataCnt[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned	char    xdata		FloatAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL]; 
unsigned 	char 	xdata 	    BaseLineAdjusttmp[SOCAPI_SET_TOUCHKEY_TOTAL]; 	
int                 xdata 	    DifferAccum[SOCAPI_SET_TOUCHKEY_TOTAL]; 
char	            xdata		SetNoiseThreshold;
unsigned 	char	xdata		ConfirmTouchCnt;
unsigned 	char	xdata		MultipleDealTpye = 0; 

//�Զ������
unsigned 	int 	xdata  	    UpdateBaseLNum; 				// ��������������
unsigned 	int 	xdata  	    MultipleLNum;					// �ఴ�����ż���
bit		WakeUp_Flag = 0;

extern unsigned char gcSleepDelayTime;


//�ⲿ�����ӿ�
extern 	unsigned	char	data		CurrentChannelMax;		//��ǰѡ�е�keysensor�ĸ���
extern  bit  bMultiple;	//�ఴ����־
extern	unsigned 	int     xdata       ScanTime;
	
extern 	bit  GetIsNeedUpdateBaseline(void);
extern  void SetNeedUpdateBaseline(void);
extern  unsigned long int SensorKeyFlag(void);
extern  void MultipleDeal(unsigned char CycleCnt);
extern  void FilterDataDeal(unsigned char i);
extern  void TouchKey_Service(void);
void  TKSleepMode(void);
extern void ADC_Process(void);

/***************���ɿ����***************/
#define		SOCAPI_SET_CS_FUNCTION						1		//0:��ʾ������CS����,1: ��ʾ����CS����,Ĭ��0
#define		SOCAPI_INHIBITION_ZONE					    8		//��������%�����÷�Χ5-10��Ĭ��7,����7*10��%=70% ����ˮʱ�Ӵ�ò���,�Խ�������С
#define		SOCAPI_MAX_KEY_MUTIPLE						300		//���ٴθ��Ÿ��»��ߣ�Ĭ��300*5=1500
#define		SOCAPI_MAX_KEY_NUM_INVALID					3		//ǿ�Ƹ��»��߰������Ƹ�����Ĭ��3
/****************************************/

#define	  	AppType			     			0
#define	  	IsDoubleKey			 			1
#define	  	AirSeparationDistance	 	    2
#define   	CONFIRMTOUCHCNT        	        3
#define   	INIT_AUTO_UPDATE_TIME	 	    4
#define   	SET_KEY_CONTI_TIME     	        5  
#define   	SET_SYNC_UPDATE 		 		6
#define   	SET_UPDATE_SPEED 		 		7	
#define   	AUTO_UPDATE_TIME	     	    8
#define	  	FilteredKValue		 			9
#define	  	SET_ANTIJAM		     			10
#define	  	BAUD		             		11
#define	  	DwellTime		         		12
#define   	SaveTime					      13
#define   	NOISE                  	16

#define   	SET_TOUCH_FREQ		 			0
#define	  	SET_RESOLUTION		 			1
#define   	SET_GAIN_CFG			 		2
#define   	SCANTIME				 		3
#define   	SET_ICHA				 		4
#define   	FINGER_THRESHOLD_H	 		    6
#define   	FINGER_THRESHOLD_L	 		    7

//**********************************************************************************	
// 								�͹�������							  //
//**********************************************************************************

#define     TK_LowPowerMode                

#ifdef  TK_LowPowerMode

#define		BTM_TIMEBASE_15600US     0X00		//��Ƶʱ���ж�ʱ��Ϊ15.6MS
#define		BTM_TIMEBASE_31300US     0X01		//��Ƶʱ���ж�ʱ��Ϊ31.3MS
#define		BTM_TIMEBASE_62500US     0X02		//��Ƶʱ���ж�ʱ��Ϊ62.5MS
#define		BTM_TIMEBASE_125MS  	   0X03		//��Ƶʱ���ж�ʱ��Ϊ125MS
#define		BTM_TIMEBASE_250MS       0X04		//��Ƶʱ���ж�ʱ��Ϊ250MS
#define		BTM_TIMEBASE_500MS       0X05		//��Ƶʱ���ж�ʱ��Ϊ500MS
#define		BTM_TIMEBASE_1S          0X06		//��Ƶʱ���ж�ʱ��Ϊ1S
#define		BTM_TIMEBASE_2S          0X07		//��Ƶʱ���ж�ʱ��Ϊ2S
#define		BTM_TIMEBASE_4S          0X08		//��Ƶʱ���ж�ʱ��Ϊ4S

#include <intrins.h>

#define      WakeUpKeyNum                      WakeUpKeyNum_Set                    //�͹���ģʽ��ɨ�谴������     
#define      WakeUpKeyChannel                  WakeUpKeyChannel_Set                //�͹�����ɨ�谴���Ķ�Ӧͨ��
#define      TK_SeepTimervSetting              TK_SeepTimervSetting_Set            //�͹����°���֮���ɨ����
#define      TK_WakeUpConfirmTouchCnt          TK_WakeUpConfirmTouchCnt_Set 	   //�͹�����ȷ�ϰ�������

#if	TK_SeepTimervSetting == BTM_TIMEBASE_4S							//�͹����»��߸��¼������
	#define  BaselineUpdateCnt  1										
#elif	TK_SeepTimervSetting == BTM_TIMEBASE_2S							
	#define  BaselineUpdateCnt  3
#elif	TK_SeepTimervSetting == BTM_TIMEBASE_1S							
	#define  BaselineUpdateCnt  6
#elif	TK_SeepTimervSetting == BTM_TIMEBASE_500MS					
	#define  BaselineUpdateCnt  12
#elif TK_SeepTimervSetting == BTM_TIMEBASE_250MS					 
	#define  BaselineUpdateCnt  24
#elif TK_SeepTimervSetting == BTM_TIMEBASE_125MS
	#define  BaselineUpdateCnt  48
#elif TK_SeepTimervSetting == BTM_TIMEBASE_62500US
	#define  BaselineUpdateCnt  96
#elif TK_SeepTimervSetting == BTM_TIMEBASE_31300US
	#define  BaselineUpdateCnt  192
#elif TK_SeepTimervSetting == BTM_TIMEBASE_15600US
	#define  BaselineUpdateCnt  384									
#endif

bit  LowPowerScan_Flag = 0;                                         //�͹���ɨ���־
bit  SingleKeyFastScan_Flag = 0;                                    //����������ɨ���־
bit  BTM_WakeUpFlag =0;												//BTM���ѱ�־λ
bit  Touch_WakeUpFlag=0;											//�������ѱ�־λ

unsigned    char    xdata       WakeUpKey_List[WakeUpKeyNum];
unsigned 	char 	xdata  	    WakeUpThenScanCount = 0; 
unsigned 	int		WakeUpNum;										  //���Ѵ�������--���ڵ͹����¸��»���
unsigned 	char 	data WakeUpKeyValue;						//==WakeUpKey_List[WakeUpKey_Index]
unsigned 	int  	ScanTimeTemp0;									//==ScanTime

//**********************************************************************************	
// 								���ѡ������							  //
//**********************************************************************************

//unsigned char  Sensitivity_4mmValue[1][8]={0x03,0x2e,0x04,0x0a,0x21,0x05,0x00,0x9c,};  //4MM �ֻ����� 01
//unsigned char  Sensitivity_4mmValue[1][8]={0x03,0x2e,0x04,0x08,0x22,0x06,0x00,0xad,};  //4MM �ֻ����� 02
//unsigned char  Sensitivity_8mmValue[1][8]={0x03,0x2e,0x04,0x1a,0x22,0x05,0x00,0x98,}; // 8mm ΢������
//unsigned char  Sensitivity_4mmValue[1][8]={0x03,0x2e,0x04,0x0e,0x22,0x05,0x01,0x5f,};  //4MM �ֻ����� 0628
//unsigned char  Sensitivity_8mmValue[1][8]={0x03,0x2e,0x04,0x10,0x22,0x05,0x00,0xc7,};  // 8mm ΢������
//unsigned char  Sensitivity_4mmValue[1][8]={0x03,0x32,0x04,0x08,0x23,0x05,0x01,0x2c,};       //12c = 300


unsigned char  Sensitivity_4mmValue[1][8]={0x03,0x32,0x04,0x08,0x23,0x05,0x00,0xc6,};       //c6 = 198
unsigned char  Sensitivity_8mmValue[1][8]={0x03,0x2e,0x04,0x10,0x22,0x05,0x00,0x8d,};       // 8mm ΢������7c

extern void Time_Process(void);
extern void SleepLED_Process(void);
extern void WakeAutoSleep(void);

void Set_Cfg()
{	
	unsigned char i;
		if(P31==0)       //����
		{
			for(i=0;i<8;i++)
			{
				TKChannelCfg[0][i]=Sensitivity_4mmValue[0][i];
			}			
		}
		else
		{
			for(i=0;i<8;i++)
			{
				TKChannelCfg[0][i]=Sensitivity_8mmValue[0][i];
			}					
		}
}


//**********************************************************************************

/**************************************************
*�������ƣ�void BtmInit(void) 
*�������ܣ�
*��ڲ�����void 
*���ڲ�����void
**************************************************/
void BTM_Init(void)
{
    BTMCON = BTMCON & 0XF0 | TK_SeepTimervSetting;
    BTMCON |= 0X80;
	  TK_IE1 |= 0X04;
}

/**************************************************
*�������ƣ�void BtmInit(void) interrupt	0
*�������ܣ�Btm�жϷ�����
*��ڲ�����void 
*���ڲ�����void
**************************************************/
void BtmInit(void) interrupt	9
{
   BTM_WakeUpFlag = 1;

}
#endif

//**********************************************************************************	
// 								  �����ӿڵ��ò���								  //
//**********************************************************************************
/**************************************************
*�������ƣ�unsigned int SetOneKeyPushResetTime(void) 
*�������ܣ�����������ʱ��
*��ڲ�����void
*���ڲ�����unsigned int SOCAPI_SET_KEY_CONTI_TIME
*��ע	 ���������ֵ�����ã� �Ǹ����ж೤ʱ������TouchKeyRestart����
����10ms ����һ�Σ� ��SOCAPI_SET_KEY_CONTI_TIME*10ms������ʱ���˰�����Ч��
**************************************************/
unsigned int SetOneKeyPushResetTime(void)   
{	  
	return  TKCFG[SET_KEY_CONTI_TIME];
}

/**************************************************
*�������ƣ�int  GetBaselineUpdateThreshold(void)
*�������ܣ������ٶ� 
*��ڲ�����void
*���ڲ�����int 
*��ע	 ��
**************************************************/
int  GetBaselineUpdateThreshold(void)
{
	return TKCFG[SET_UPDATE_SPEED]; 
}

/**************************************************
*�������ƣ�unsigned char GetInitAutoUpdateTime(void)
*�������ܣ���ʼ���Զ�У׼����
*��ڲ�����void
*���ڲ�����unsigned  char 
*��ע	 ��
**************************************************/
unsigned char GetInitAutoUpdateTime(void)
{
	return  TKCFG[INIT_AUTO_UPDATE_TIME];
}
/**************************************************
*�������ƣ� char GetCsFunction(void)
*�������ܣ�����CS ����
*��ڲ�����void
*���ڲ�����char SOCAPI_SET_CS_FUNCTION
*��ע	 ��
**************************************************/
char GetCsFunction(void)
{
	return SOCAPI_SET_CS_FUNCTION; 
}
/**************************************************
*�������ƣ�int  GetCurrFingerValue(unsigned char i)
*�������ܣ���ȡ��ǰ��finger ֵ
*��ڲ�����unsigned char
*���ڲ�����int 
*��ע	 ��
**************************************************/
unsigned int   GetCurrFingerValue(unsigned char i)
{ 
	return	TKChannelCfg[i][FINGER_THRESHOLD_H]*256+TKChannelCfg[i][FINGER_THRESHOLD_L] ;
}

/**************************************************
*�������ƣ�unsigned char  GetScanTimeValue(unsigned char i)
*�������ܣ���ȡ��ǰͨ����ɨ��ʱ��
*��ڲ�����unsigned char
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char  GetScanTimeValue(unsigned char i)
{ 
	return TKChannelCfg[i][SCANTIME];
}
/**************************************************
*�������ƣ�unsigned char IsDoubleKeyOrSlideKey(void)
*�������ܣ�����Ƿ��ǵ��ɻ�������˫��
*��ڲ�����void
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char IsDoubleKeyOrSlideKey(void)
{
    return TKCFG[IsDoubleKey];
}
/**************************************************
*�������ƣ�unsigned char  GetBaseLineAdjustValue(unsigned char i)
*�������ܣ���ȡ��ǰͨ���Ļ��ߵ���
j
*��ڲ�����unsigned char
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char  GetBaseLineAdjustValue(unsigned char i)
{	
     return BaseLineAdjusttmp[i]; 
}
/**************************************************
*�������ƣ�unsigned char GetUpConfirmCnt(void)
*�������ܣ���ⰴ���������
*��ڲ�����void
*���ڲ��������ذ�������ȷ�ϴ��� 
*��ע	 ��
**************************************************/
unsigned char GetUpConfirmCnt(void)
{
	return ConfirmTouchCnt>>1;
}
/**************************************************
*�������ƣ�unsigned char GetTKYzCnt(void)
*�������ܣ���ȡ��������ȷ�ϴ���
*��ڲ�����void
*���ڲ������������ƴ��� 
*��ע	 ��
**************************************************/

unsigned char GetTKYzCnt(void)
{
	return (ConfirmTouchCnt/3);
}

/**************************************************
*�������ƣ�int GetTKYzThreshold(unsigned char i)
*�������ܣ���ȡ������������
*��ڲ�����unsigned char i
*���ڲ�����������������
*��ע	 ��
**************************************************/
int GetTKYzThreshold(unsigned char i)
{	
	unsigned int SetFingerThresholdtmp; 
	
	SetFingerThresholdtmp = GetCurrFingerValue(i); 
    SetFingerThresholdtmp = SetFingerThresholdtmp*SOCAPI_INHIBITION_ZONE/10;

	return SetFingerThresholdtmp;
}
/**************************************************
*�������ƣ�void CurrentSensorChoose(void)
*�������ܣ���ǰͨ��ѡ��
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void CurrentSensorChoose(void)
{
	unsigned char  	i = 0;
	unsigned char  	Ctk_Channel_mark = 0;
	unsigned char  	WakeUpKey_Channel_mark = 0;
	unsigned long int	CurrentSensorKey = 0 ; 
	
	CurrentSensorKey = SOCAPI_SET_TOUCHKEY_CHANNEL; 
		
	for(i=0;i<31;i++)
	{
		CurrentSensorKey=CurrentSensorKey>>1;
		if(TK_CY)
		{
			CurrentChannel[Ctk_Channel_mark] = i;						//ѡ������ǰ��ͨ��
            #ifdef  TK_LowPowerMode
			if(WakeUpKey_Channel_mark<WakeUpKeyNum)
            {
                if((WakeUpKeyChannel&((unsigned long int)1<<i)))
                {
                    WakeUpKey_List[WakeUpKey_Channel_mark++] = Ctk_Channel_mark;
                }
            }
            #endif
			Ctk_Channel_mark++;
			if(Ctk_Channel_mark >= SOCAPI_SET_TOUCHKEY_TOTAL)
				break;
		}		
	}
	CurrentChannelMax = Ctk_Channel_mark;							//��ǰѡ��İ����� 
}

/**************************************************
*�������ƣ�unsigned char  GetCfgMsg(unsigned char i)
*�������ܣ���ȡTouch KEY ������Ϣ
*��ڲ�����void
*���ڲ�����int 
*��ע	 ��
**************************************************/
unsigned char  GetCfgMsg(unsigned char i)
{
	switch(i)
	{ 
		 case 0:  return TKChannelCfg[0][SET_TOUCH_FREQ];
		 case 1:  return TKChannelCfg[0][SET_RESOLUTION];
		 case 2:  return TKChannelCfg[0][SET_GAIN_CFG];
		 case 3:  return GetBaseLineAdjustValue(0);	//TKChannelCfg[0][SET_GAIN_CFG];
		 case 4:  return TKCFG[SET_ANTIJAM];
		 default:return 0; 	 	
	}
}

/**************************************************
*�������ƣ�void CurrentSensorChoose(void)
*�������ܣ���ʼ��TK�Ĵ���
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void TouchKeyCFGInit(void)
{
	unsigned char  	i;
	ConfirmTouchCnt = TKCFG[CONFIRMTOUCHCNT];
	SetNoiseThreshold = TKCFG[NOISE];
	CurrentSensorChoose(); 
	for(i=0;i<CurrentChannelMax;i++)
	{
	  BaseLineAdjusttmp[i] =TKChannelCfg[i][SET_ICHA];;	
	} 
	UpdateBaseLNum = 0;
    #ifdef  TK_LowPowerMode
    BTM_Init();
    #endif 
}

/**************************************************
*�������ƣ�unsigned int TouchKeyScan(void)
*�������ܣ���ⰴ���ӿ�
*��ڲ�����void
*���ڲ���������ͨ���� ���ص���һ��int , ͨ����
*��ע	 ��1,  ���ô��ؿ��⺯��SensorKeyFlag()
		   2,  �����ó�16��ͨ�����ĸ�ͨ���а��£�����bit λ����Ϊ1������Ϊ0
		   3,  ����Ƿ���Ҫ��������baseline:  ����MAX_KEY_RESET_BASELINE ����������ʱ��������baseline
		   4,  ˫�����ߵ�������ʱ�� ʱ�����SetOneKeyPushResetTime()���ʱ����baseline 
**************************************************/
unsigned char OffHandCount = 0;
unsigned int  NumCount = 0;
unsigned long int TouchKeyScan(void)
{
	unsigned char t;
    unsigned char MultipleCnt = 0;//��������
	unsigned long int Keyvalue = 0; 
	unsigned long int KeyData = 0; 	
	int WakeupDiffData = 0; 
	int WakeupSetFingerThresholdtmp;
	

	if(WakeUp_Flag == 0)
	{
		if(GetIsNeedUpdateBaseline() == 0)				//����Ƿ���Ҫ����baseline 
		{
			Keyvalue = SensorKeyFlag();					//Sensor�ж�, �������bMultiple = 1 ��ʾ�м��и���	 //�����������ó���׼��16ͨ��bit λ                     							   
			for(t=0;t<CurrentChannelMax;t++)
			{
				Keyvalue = Keyvalue>>1;
				if(TK_CY)
				{
					KeyData |= ((unsigned long int)0x01 << (CurrentChannel[t]));              
					MultipleCnt++;							
				}
			}                
			if(MultipleCnt >= 2) 	 						//����ఴ������
			{			
				bMultiple = 1;			
				if(MultipleCnt >= SOCAPI_MAX_KEY_NUM_INVALID)
				{
					SetNeedUpdateBaseline(); 				// ��������baseline ,�����ǿ��������ȥ
				}
				else
				{					
					if(IsDoubleKeyOrSlideKey())
					{
						bMultiple = 0;
					} 				 
				}			
			}			
	
			if(bMultiple == 0)								//���밴���ж�
			{		
				if(KeyData != 0x0)					    	//���������ﵽ�೤ʱ���update baseline ,���ּ��
				{			
					UpdateBaseLNum++; 
				}
				else	
				{
					UpdateBaseLNum = 0; 	
				} 
			}	
			else
			{   
			    //���ǻ��߸���		
				MultipleLNum++; 
				KeyData = 0x00;
			}
	
			if(UpdateBaseLNum > SetOneKeyPushResetTime())	//������������ʱ����»���
			{
	 			SetNeedUpdateBaseline(); 
				UpdateBaseLNum = 0;
			}
					
			if(MultipleLNum >SOCAPI_MAX_KEY_MUTIPLE)		//���ż����������������»���
	 		{
				SetNeedUpdateBaseline(); 
				MultipleDealTpye = 1; 
				MultipleLNum = 0;
			}  
		}			
		else
		{
			MultipleDeal(TKCFG[AUTO_UPDATE_TIME]);			//���߸�λ����
		}
	}
	else
	{
        #ifdef  TK_LowPowerMode
		
		if(Touch_WakeUpFlag==1)
		{
			KeyData |= ((unsigned long int)0x01 << (CurrentChannel[WakeUpKeyValue]));

			WakeupDiffData = RawData[WakeUpKeyValue]-BaseLine[WakeUpKeyValue];
			WakeupSetFingerThresholdtmp = GetCurrFingerValue(WakeUpKeyValue);

			if(WakeupDiffData <= (WakeupSetFingerThresholdtmp-((WakeupSetFingerThresholdtmp)>>2)))
			{	
				NumCount=0;
				if(++OffHandCount>5)
				{
					OffHandCount = 0;
					WakeUp_Flag = 0;
					Touch_WakeUpFlag=0;
					KeyData = 0;
				}
				for(t=0;t<CurrentChannelMax;t++)
				{
					FilterDataDeal(t);
					if(!WakeUp_Flag)
					{
						if(WakeUpKeyValue == t)
						continue;
						BaseLine[t] = RawData[t];	
					}
				}
					
			}
			else
			{
				OffHandCount=0;
				if(++NumCount > SetOneKeyPushResetTime())	//������������ʱ����»���
				{
		 			SetNeedUpdateBaseline(); 
					NumCount = 0;
					WakeUp_Flag = 0;
					Touch_WakeUpFlag=0;
					KeyData = 0;
				}		
			}
			
		
		}
		else
		{
			if(++WakeUpThenScanCount>5)
			{
				WakeUpThenScanCount = 0;
				WakeUp_Flag = 0;
			}
			for(t=0;t<CurrentChannelMax;t++)
			{
				FilterDataDeal(t);
				if(!WakeUp_Flag)
				{
					
					BaseLine[t] = RawData[t];	
				}	
			}
			
		}
		
		#endif
	}  
	
	return KeyData;
}

/**************************************************
*�������ƣ�void CTK_ISR(void) interrupt	11
*�������ܣ������жϷ�����
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void CTK_ISR(void) interrupt	11
{
   TouchKey_Service();
}

/**************************************************
*�������ƣ�bit GetLowPowerScanFlag(void)
*�������ܣd��ȡ�͹���ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
bit GetLowPowerScanFlag(void)
{
    #ifdef  TK_LowPowerMode
    return LowPowerScan_Flag;
    #endif
}

/**************************************************
*�������ƣ�void TouchKey_LowPower_Init(unsigned char i)
*�������ܣd�͹��ĳ�ʼ��
*��ڲ�����void
*���ڲ�����void  
**************************************************/
unsigned 	char    xdata 	    BaseLineAdjusttmp_Low[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned 	char 	xdata 	    CurrentChannel_Low[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned 	int 	xdata       ScanTimeTemp_Low[SOCAPI_SET_TOUCHKEY_TOTAL];
int 	data       SetFingerThresholdtmp_Low[SOCAPI_SET_TOUCHKEY_TOTAL];
void TouchKey_LowPower_Init(void)
{
    unsigned char i;
    	
    for(i=0;i<WakeUpKeyNum;i++)
    {
        WakeUpKeyValue = WakeUpKey_List[i];
        ScanTimeTemp_Low[WakeUpKeyValue] = ScanTimeTemp0*TKChannelCfg[WakeUpKeyValue][SCANTIME];
        BaseLineAdjusttmp_Low[WakeUpKeyValue] = BaseLineAdjusttmp[WakeUpKeyValue];//(TKCFG1 & 0X80) | BaseLineAdjusttmp[WakeUpKeyValue];
        CurrentChannel_Low[WakeUpKeyValue] =  0xc0|CurrentChannel[WakeUpKeyValue];

        SetFingerThresholdtmp_Low[WakeUpKeyValue] = TKChannelCfg[WakeUpKeyValue][FINGER_THRESHOLD_H]*256+TKChannelCfg[WakeUpKeyValue][FINGER_THRESHOLD_L];        

        TKCFG0 &= 0XF0;
        TKCFG0 |= TKChannelCfg[0][SET_TOUCH_FREQ];
    }
}

/**************************************************
*�������ƣ�void TouchKey_IntoLowPowerMode(void)
*�������ܣd����͹���ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void TouchKey_IntoLowPowerMode(void)
{
    #ifdef  TK_LowPowerMode
	unsigned char t;
    LowPowerScan_Flag = 1;

	ScanTimeTemp0 = ScanTime >> ScanTimeCon;
    Customer_IntoLowPowerMode_Init();

    TouchKey_LowPower_Init();
   
	for(t=0;t<CurrentChannelMax;t++)
	{
	   TouchCnt[t] = 0;
	}
    #endif
}

#ifdef  TK_LowPowerMode
/**************************************************
*�������ƣ�void TouchKey_QuitLowPowerMode(void)
*�������ܣd�˳��͹���ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void TouchKey_QuitLowPowerMode(void)
{
	 LowPowerScan_Flag = 0;
     WakeUp_Flag = 1;
	 
     TKCR = 0x80|CurrentChannel[0];
	 TKTM = ScanTime*TKChannelCfg[0][SCANTIME]; 
	 TRIG = 1;
	 while(TRIF == 0);  
	 TRIF = 0;
	 TK_IE1 = TK_IE1|0x10;    				//ʹ��TK�ж�
     TRIG = 1; 
     Customer_QuitLowPowerMode_Init();
}


/**************************************************
*�������ƣ�void Lowpower_BaselineUpdate(unsigned char i)
*�������ܣd�͹��Ļ��߸���
*��ڲ�����unsigned char
*���ڲ�����void  
**************************************************/
void Lowpower_BaselineUpdate(unsigned char i)
{
	BaseLine[WakeUpKeyValue] =BaseLine[WakeUpKeyValue]-(BaseLine[WakeUpKeyValue]>>i)+(RawData[WakeUpKeyValue]>>i);
}


/**************************************************
*�������ƣ�void TouchKey_LowPower_Dispose(void)
*�������ܣd�͹���ɨ�����ݴ���
*��ڲ�����void
*���ڲ�����void  
**************************************************/

void TouchKey_LowPower_Dispose(void)
{  
	int data differData; 

	unsigned char data WakeUpKey_Index;

	
	BTM_WakeUpFlag = 0;

	  TRIG = 1;
    PCON = 0x02;	//PCON��bit1 STOPλд1������MCU����STOPģʽ
	  _nop_();		//������Ҫ8��_nop_()
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
	  _nop_();

    TRIG = 1;
    PCON = 0x02;	//PCON��bit1 STOPλд1������MCU����STOPģʽ
	  _nop_();		//������Ҫ8��_nop_()
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
	  _nop_();
	
	for(WakeUpKey_Index=0; WakeUpKey_Index<WakeUpKeyNum; WakeUpKey_Index++)	//ѭ��ɨ�谴��
	{


        WakeUpKeyValue = WakeUpKey_List[WakeUpKey_Index];
		TKCFG1 =  BaseLineAdjusttmp_Low[WakeUpKeyValue]; 
		TKTM = ScanTimeTemp_Low[WakeUpKeyValue];//ScanTimeTemp;
		TKCR = CurrentChannel_Low[WakeUpKeyValue];

        PCON = 0x02;	//PCON��bit1 STOPλд1������MCU����STOPģʽ
    	_nop_();		//������Ҫ8��_nop_()
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    	_nop_();       

        differData = (TKCNT<<ScanTimeCon)-BaseLine[WakeUpKeyValue] ; 
	
		if(differData >= SetFingerThresholdtmp_Low[WakeUpKeyValue])
	    {
			 SingleKeyFastScan_Flag = 1;
			 break;       
	    } 
			
			
			else if(differData > (-(SetFingerThresholdtmp_Low[WakeUpKeyValue]>>2)))
			{
         if(WakeUpNum==WakeUpKey_Index)
          BaseLine[WakeUpKeyValue] += differData>>4;
			 }
			else	
		  {
          BaseLine[WakeUpKeyValue] += differData>>2;
		  }	
			
			
	}


	if(++WakeUpNum>=BaselineUpdateCnt)
	{
		WakeUpNum = 0;
	}
	

}

/**************************************************
*�������ƣ�void SingleKeyFastScan(void)
*�������ܣd����������ɨ��ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void SingleKeyFastScan(void)
{ 
	unsigned char i;
	int differData; 
	int SetFingerThresholdtmp;
	
	SingleKeyFastScan_Flag = 0;
	TK_IE1 = TK_IE1|0x10; //��TK�ж�
	TKCFG1 = (TKCFG1 & 0X80) | BaseLineAdjusttmp[WakeUpKeyValue];
  TKCR = 0x80|CurrentChannel[WakeUpKeyValue]; 
	TKTM = ScanTimeTemp0*TKChannelCfg[WakeUpKeyValue][SCANTIME];
	
	for(i=0;i<TK_WakeUpConfirmTouchCnt;i++)      //
    {        
	
		 TRIG = 1;
		 TKSleepMode();
		 RawData[WakeUpKeyValue] = TKCNT << ScanTimeCon;
		 FilterDataDeal(WakeUpKeyValue);
         differData = RawData[WakeUpKeyValue]-BaseLine[WakeUpKeyValue] ;
		 SetFingerThresholdtmp = GetCurrFingerValue(WakeUpKeyValue);

		 if(differData >= SetFingerThresholdtmp)
         {   
            TouchCnt[WakeUpKeyValue]++;  
         }             
         else
		 {
			break;
		 }
    }
	
    if(TouchCnt[WakeUpKeyValue]>=TK_WakeUpConfirmTouchCnt)
    {    
		 TouchKey_QuitLowPowerMode();       
		 Touch_WakeUpFlag= 1; 
	}
    else
    {
		
        TouchCnt[WakeUpKeyValue] = 0;
		
    }
}


void  TKSleepMode(void)
{   
	
	PCON = 0x02;	//PCON��bit1 STOPλд1������MCU����STOPģʽ
	_nop_();		//������Ҫ8��_nop_()
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
	_nop_();
}
#endif
/**************************************************
*�������ƣ�void LowPower_Touchkey_Scan(void)
*�������ܣd�͹���ģʽTKɨ��
*��ڲ�����void
*���ڲ�����void  
**************************************************/
 

void LowPower_Touchkey_Scan(void)
{      					
    #ifdef  TK_LowPowerMode 
    
    TKCR &= 0x7f;//~0x80;
		PCON = 0x02;	//PCON��bit1 STOPλд1������MCU����STOPģʽ
		_nop_();		//������Ҫ8��_nop_()
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
		_nop_();
		TKCR |= 0x80;	//��TK��Դ

	//���а�������
	if(BTM_WakeUpFlag)
	{

		TouchKey_LowPower_Dispose();  	   //��ⰴ��	
		
		if( SingleKeyFastScan_Flag == 1)
	    {								   
				SingleKeyFastScan();		   //���а�����Ϣ���뵥�������ٶ��ɨ��ȷ�������Ƿ���ʵ�źš�
	    }
	
		// �û�BTM���Ѻ�Ĵ�������
		  Customer_BTM_Dispose();
		  	
			Time_Process();
//			ADC_Process();             //������7.12
			SleepLED_Process();
			WakeAutoSleep();
//			Key_Scan();
			
		//	P31=0; 	;				//��BTM���ѣ��û�������Ҫ����������������
    }
	else
	{
	  //	P31=~P31; 	;				//��BTM���ѣ��û�������Ҫ����������������
		//LowPowerScan_Flag = 0;
		
		TouchKey_QuitLowPowerMode();
		
	}
	#endif    
}