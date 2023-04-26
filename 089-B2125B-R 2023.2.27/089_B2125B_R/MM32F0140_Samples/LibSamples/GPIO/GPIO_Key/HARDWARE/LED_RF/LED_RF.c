#include "LED_RF.h"
#include "key.h"
#include "RF_A7325.h"
#include "089_B19110A.h"

void Time_convert(void);

/*stMode_info  stWarmhouse;*/
stMode_info  stWarm_Stro;
stMode_info  stWarm_Weak;
stMode_info  stChAir_Stro;
stMode_info  stChAir_Weak;
stMode_info  stCold_dry;
stMode_info  stHot_dry;
stMode_info  stDegerming;

volatile unsigned int  giLED_status;
volatile unsigned int  giLED_Tempstatus;
volatile unsigned char gcledscan_row;
volatile unsigned char gcRfSendCount;
volatile unsigned char TxPtcol_Wifi;
volatile unsigned char TxPtcol_voice;
volatile unsigned char gcMainSubPair_Flag;

/*************************************************************************
//					void led_process(void)
//					led亮灭处理程序  （扫描LED灯）
//					1ms调用一次
//					
*************************************************************************/
void led_process(void)
{
	Clr_PB3;
	Clr_PB4;
	Clr_PB5;
	Clr_PB6;
	
	Set_PA4;
	Set_PA9;
	Set_PA11;
	Set_PA12;
	Set_PA15;
	
	switch(gcledscan_row)
	{
		case 0:
		{
			/*_pd1 = 0;*/
			if(Ptcol_TimeSet == timer30min)            //30分     // led1   
			{
				//_pb0 = 0;		
					Clr_PA15;	
			}
 
			if(Ptcol_TimeSet == timerconti)            //定时连续    //led2
			{
				//_pb1 = 0;	
					Clr_PA4;
			}
						
			gcledscan_row = 1;
			//_pc4 = 1;		
		  Set_PB4;
		} 	
		break;
		case 1:
		{
			if(giLED_status & LED_WarmHouse)           //取暖    //led16  
			{
				Clr_PA9;	//_pb5 = 0;		                     
			}
			gcledscan_row = 2;
			Set_PB3;	//_pc4 = 1;			
		}	
		break;
		
		case 2:
		{
			
			if(Ptcol_TimeSet == timer15min)            //15分     // led4   
			{
				Clr_PA15;	//_pb0 = 0;		                    
			}
 
			if(Ptcol_TimeSet == timer6hour)           //6小时    //led5
			{
				Clr_PA4;	//_pb1 = 0;		                   
			}
			
			gcledscan_row = 3;
			Set_PB3;	//_pc5 = 1;						
		}
		break;
		
		case 3:
		{
			if(giLED_status & LED_AirChange)           //换气    //led15  
			{
				 Clr_PA11;	//_pb5 = 0;		                     
			}
			gcledscan_row = 4;
			 Set_PB3;   	//_pc5 = 1;			
		}
		break;
				
		case 4:
		{
 
			if(Ptcol_TimeSet == timer3hour)           //3小时    //led9
			{
			 Clr_PA4;  	 //	_pb1 = 0;		                   
			}
	
			gcledscan_row = 5;
			Set_PB6;  	//_pd2 = 1;			
		}
		break;
		
		case 5:
		{
			if(giLED_status & LED_ColdDry)           //凉干燥    //led17  
			{	
       	  Clr_PA11;			
			}
			
////			if(giLED_status & LED_HotDry)            //热干燥    //led18  
////			{
////			 Clr_PA9;	//	_pb6 = 0;		                     
////			}
			gcledscan_row = 6;
			Set_PB6;	//	_pd2 = 1;			
		}
		break;	

		case 6:
		{
//			if(giLED_status & LED_AirStrong)            //强     // led8   
//			{
//			 Clr_PA15;	//	_pb0 = 0;	
//			}
			
			if(giLED_status & LED_HotDry)            //热干燥    //led18  
			{
			 Clr_PA9;	//	_pb6 = 0;		                     
			}
			gcledscan_row = 7;
			Set_PB6;	  //_pd2 = 1;	
						
		}
		break;
			
		case 7:
		{
			if(Ptcol_TimeSet == timer1hour)            //1小时    //led11
			{
				 Clr_PA4;	//_pb1 = 0;		                   
			}
			gcledscan_row = 8;
			 Set_PB5;	//_pd1 = 1;			
		}
		break;

		case 8:
		{
			
			gcledscan_row = 9;
					
		}
		break;
		
		case 9:
		{	
			;
			gcledscan_row = 10;
			
		}
		break;
	  case 10:
		{	
			;
			gcledscan_row = 11;
			
		}
		break;
		case 11:
		{	
			;
			gcledscan_row = 12;
			
		}
		break;
		case 12:
		{	
			;
			gcledscan_row = 13;
			
		}
		break;
		case 13:
		{	
			;
			gcledscan_row = 14;
			
		}
		break;
		case 14:
		{	
			;
			gcledscan_row = 15;
			
		}
		break;
		case 15:
		{	
			;
			gcledscan_row = 0;
			
		}
		break;
		
					
		default:
		break;		
	}		
}


/*************************************************************************
//					void StandBy_init(void)
//					待机长按3s后各模式设定值初始化
//					
*************************************************************************/
void StandBy_init(void)
{
/*	unsigned char i;*/

	stWarm_Stro.gcAirDir = fixed90;
	stWarm_Stro.gcAirVol = strong;
	stWarm_Stro.gcAirkind = focus;
	stWarm_Stro.gcTimeSet = timer15min; //0x03;

		
//	stWarm_Weak.gcAirDir = fixed90;
//	stWarm_Weak.gcAirVol = weak;
//	stWarm_Weak.gcAirkind = spread;
//	stWarm_Weak.gcTimeSet = timer15min; //0x03;

	stChAir_Stro.gcAirDir = noneset;
	stChAir_Stro.gcAirVol = strong;
	stChAir_Stro.gcAirkind = noneset;
	stChAir_Stro.gcTimeSet = timer15min;  //0x03;

//	stChAir_Weak.gcAirDir = noneset;
//	stChAir_Weak.gcAirVol = weak;
//	stChAir_Weak.gcAirkind = noneset;
//	stChAir_Weak.gcTimeSet = timer15min;  //0x03;

	stCold_dry.gcAirDir = automat;
	stCold_dry.gcAirVol = strong;
	stCold_dry.gcAirkind = focus;
	stCold_dry.gcTimeSet = timer15min;  //0x03;

	stHot_dry.gcAirDir = automat;
	stHot_dry.gcAirVol = strong;
	stHot_dry.gcAirkind = focus;
	stHot_dry.gcTimeSet = timer15min;  //0x03;
	
//	stDegerming.gcAirDir = automat;
//	stDegerming.gcAirVol = weak;
//	stDegerming.gcAirkind = spread;      //扩散
//	stDegerming.gcTimeSet = timer3hour;  //0x10;
	
/*	gcPtcolBuff[0] = standby;*/
//	for(i = 1;i < 10;i++)
//	{
//		gcPtcolBuff[i] = noneset;	
//	}
//	gcPtcolBuff[4] = 0x00;

//	if(Ptcol_RunMode == degerming)    //除菌
//	{
//		Ptcol_AirVol = stDegerming.gcAirVol;
//		Ptcol_AirDir = stDegerming.gcAirDir;
//		Ptcol_Airkind = stDegerming.gcAirkind;
//		Ptcol_TimeSet = stDegerming.gcTimeSet;			
//	}
    if(Ptcol_RunMode == changeair)   //换气
	{	
		
//		if(Ptcol_AirVol == weak)	
//		{
//			Ptcol_AirDir = stChAir_Weak.gcAirDir;
//			Ptcol_Airkind = stChAir_Weak.gcAirkind;
//			Ptcol_TimeSet = stChAir_Weak.gcTimeSet;
//		}
//		else
//		{
//			Ptcol_AirDir = stChAir_Stro.gcAirDir;
//			Ptcol_Airkind = stChAir_Stro.gcAirkind;
//			Ptcol_TimeSet = stChAir_Stro.gcTimeSet;				
//		}	
      Ptcol_AirVol = stChAir_Stro.gcAirVol;		
			Ptcol_AirDir = stChAir_Stro.gcAirDir;
			Ptcol_Airkind = stChAir_Stro.gcAirkind;
			Ptcol_TimeSet = stChAir_Stro.gcTimeSet;	
		
					
	}
	else if(Ptcol_RunMode == warmhouse)	  //暖房
	{		
//		if(Ptcol_AirVol == weak)	
//		{
//			Ptcol_AirDir = stWarm_Weak.gcAirDir;
//			Ptcol_Airkind = stWarm_Weak.gcAirkind;
//			Ptcol_TimeSet = stWarm_Weak.gcTimeSet;
//		}
//		else
//		{
//			Ptcol_AirDir = stWarm_Stro.gcAirDir;
//			Ptcol_Airkind = stWarm_Stro.gcAirkind;
//			Ptcol_TimeSet = stWarm_Stro.gcTimeSet;				
//		}
		  Ptcol_AirVol = stWarm_Stro.gcAirVol;
			Ptcol_AirDir = stWarm_Stro.gcAirDir;
			Ptcol_Airkind = stWarm_Stro.gcAirkind;
			Ptcol_TimeSet = stWarm_Stro.gcTimeSet;
	}
	else if(Ptcol_RunMode == cold_dry)		//凉干燥
	{
		Ptcol_AirVol = stCold_dry.gcAirVol;
		Ptcol_AirDir = stCold_dry.gcAirDir;
		Ptcol_Airkind = stCold_dry.gcAirkind;
		Ptcol_TimeSet = stCold_dry.gcTimeSet;		
	}
	else if(Ptcol_RunMode == hot_dry)     //热干燥
	{
		Ptcol_AirVol = stHot_dry.gcAirVol;
		Ptcol_AirDir = stHot_dry.gcAirDir;
		Ptcol_Airkind = stHot_dry.gcAirkind;
		Ptcol_TimeSet = stHot_dry.gcTimeSet;		
	}
		
	
	Time_convert();	
	gi1sCount = 0;	

}

/*************************************************************************
//					void PowerOn_init(void)
//					上电后各模式设定值初始化
//					
*************************************************************************/
void PowerOn_init(void)
{
	unsigned char i;

	stWarm_Stro.gcAirDir = fixed90;
	stWarm_Stro.gcAirVol = strong;
	stWarm_Stro.gcAirkind = focus;
	stWarm_Stro.gcTimeSet = timer15min;   

	stChAir_Stro.gcAirDir = noneset;
	stChAir_Stro.gcAirVol = strong;
	stChAir_Stro.gcAirkind = noneset;
	stChAir_Stro.gcTimeSet = timer15min;

	stCold_dry.gcAirDir = automat;
	stCold_dry.gcAirVol = strong;
	stCold_dry.gcAirkind = focus;
	stCold_dry.gcTimeSet = timer15min; 

	stHot_dry.gcAirDir = automat;
	stHot_dry.gcAirVol = strong;
	stHot_dry.gcAirkind = focus;
	stHot_dry.gcTimeSet = timer15min;
	
	gcPtcolBuff[0] = standby;
	
	for(i = 1;i < 10;i++)
	{
		gcPtcolBuff[i] = noneset;	
	}
	gcPtcolBuff[4] = 0x00;	
	
	giLED_status = 0;
	
}

/*************************************************************************
//					void StandBy_func(void)
//					待机短按处理函数					
*************************************************************************/
void StandBy_func(void)
{
	unsigned char i;
	
	Ptcol_RunMode = standby;   //进入待机模式

	for(i = 1;i < 10;i++)
	{
		gcPtcolBuff[i] = noneset;   //无设定
	}
	gcPtcolBuff[4] = 0x00;	
	giLED_status = 0;	
}

/*************************************************************************
//					void RF_Process(void)
//					发送标志置高，进行发送处理
//					刷新发送按键值
*************************************************************************/
void RF_Process(void)
{
	unsigned char temp=0,i;

	if(gcMainSubPair_Flag == 0)        //主功能发信
	{
		WriteReg(0x24,0x17);          //恢复发射功率设定值	 A7325_TXTEST_REG	
		
		if(Ptcol_TimeSet == timerconti)    //连续运行
		{
			Ptcol_HourRem = 0x0D;
			Ptcol_MinRem = 0x0; 			
		}
		else if(Ptcol_TimeSet == 0x00)
		{
			Ptcol_HourRem = 0x0;
			Ptcol_MinRem = 0x0; 			
		}
		else
		{
			gcTimeVal_sec = 0;
			gi1sCount = 0;
			Ptcol_HourRem = giTimeVal/60;
			Ptcol_MinRem = 	giTimeVal%60;
			
//			giTimeVal -= giTimeVal%60;
//			gi1sCount = 0;
//			Ptcol_HourRem = giTimeVal/3600;
//	
//			Ptcol_MinRem = 	(giTimeVal-Ptcol_HourRem*3600)/60;
			
		}
		
		gcTxBuff[0] = gcIDcode1;     //FLASH ID
		gcTxBuff[1] = gcIDcode2;
		gcTxBuff[2] = gcIDcode3;
		gcTxBuff[3] = gcIDcode4;
		
		/*运行设定 有12个*/
		gcTxBuff[4] = Ptcol_RunMode;
		gcTxBuff[5] = Ptcol_AirVol;
		gcTxBuff[6] = Ptcol_AirDir;
		gcTxBuff[7] = Ptcol_Airkind;	
		gcTxBuff[8] = Ptcol_TimeSet;
		gcTxBuff[9] = Ptcol_HourRem;
		gcTxBuff[10] = Ptcol_MinRem;
		gcTxBuff[11] = noneset;		
		gcTxBuff[12] = noneset;
		gcTxBuff[13] = noneset;
		gcTxBuff[14] = ModRB20V1;
		gcTxBuff[15] = noneset;
		
		for(i = 0;i < 16;i++)	
		{
			temp += gcTxBuff[i];	
		}
		gcTxBuff[16] = temp;
 
	}
	else if(gcMainSubPair_Flag == 1)     //辅助功能发信
	{
		WriteReg(0x24,0x17);          //恢复发射功率设定值	 A7325_TXTEST_REG
		gcTxBuff[0] = gcIDcode1;
		gcTxBuff[1] = gcIDcode2;
		gcTxBuff[2] = gcIDcode3;
		gcTxBuff[3] = gcIDcode4;
		gcTxBuff[4] = noneset;
		gcTxBuff[5] = noneset;
		gcTxBuff[6] = noneset;
		gcTxBuff[7] = noneset;		
		gcTxBuff[8] = noneset;
		gcTxBuff[9] = noneset;
		gcTxBuff[10] = noneset;
		gcTxBuff[11] = Ptcol_light;		
		gcTxBuff[12] = TxPtcol_Wifi;
		gcTxBuff[13] = TxPtcol_voice;
		gcTxBuff[14] = ModRB20V1;
		gcTxBuff[15] = noneset;
		
		for(i = 0;i < 16;i++)	
		{
			temp += gcTxBuff[i];	
		}
		gcTxBuff[16] = temp;		

	}
	else if(gcMainSubPair_Flag == 2)   //配对
	{
		WriteReg(0x24,0x00);       //降低发射功率设定值	 A7325_TXTEST_REG
				
		gcTxBuff[0] = 0xF0;
		gcTxBuff[1] = 0xF0;
		gcTxBuff[2] = 0xF0;
		gcTxBuff[3] = 0xF0;		
		gcTxBuff[4] = gcIDcode1;
		gcTxBuff[5] = gcIDcode2;
		gcTxBuff[6] = gcIDcode3;
		gcTxBuff[7] = gcIDcode4;
		gcTxBuff[8] = 0x00;		
		gcTxBuff[9] = 0x00;
		gcTxBuff[10] = 0x00;
		gcTxBuff[11] = 0x00;
		gcTxBuff[12] = 0x00;
		gcTxBuff[13] = 0x00;
		gcTxBuff[14] = ModRB20V1;
		gcTxBuff[15] = 0x00;
		
		for(i = 0;i < 8;i++)	
		{
			temp += gcTxBuff[i];	
		}
		temp += ModRB20V1;
		gcTxBuff[16] = temp;

	}
	else if(gcMainSubPair_Flag == 3)   //风种风向
	{		
		WriteReg(0x24,0x17);       //恢复发射功率设定值	 A7325_TXTEST_REG  TX测试寄存器
		gcTxBuff[0] = gcIDcode1;
		gcTxBuff[1] = gcIDcode2;
		gcTxBuff[2] = gcIDcode3;
		gcTxBuff[3] = gcIDcode4;
		
		gcTxBuff[4] = Ptcol_RunMode;
		gcTxBuff[5] = Ptcol_AirVol;
		gcTxBuff[6] = Ptcol_AirDir;
		gcTxBuff[7] = Ptcol_Airkind;	
		gcTxBuff[8] = noneset;
		gcTxBuff[9] = noneset;
		gcTxBuff[10] = noneset;
		gcTxBuff[11] = noneset;		
		gcTxBuff[12] = noneset;
		gcTxBuff[13] = noneset;
		gcTxBuff[14] = ModRB20V1;
		gcTxBuff[15] = noneset;
		
		for(i = 0;i < 16;i++)	
		{
			temp += gcTxBuff[i];	
		}
		gcTxBuff[16] = temp;	

	}
	
	A7325TX_Process();    //由A7325发送数据
	
	gcRfSendCount++;      //发送次数计数，发送完两次后就不会再发
	if (gcRfSendCount >= 2)
	{
		gcRfSendCount = 0;
		
	  Set_RfwaitXbms_Flag;
	  gcRfXbmsCount = 0;			
	    	    
		Ptcol_light = noneset;		
		TxPtcol_Wifi = noneset;
		TxPtcol_voice = noneset;

		Clr_RfSendEnable_Flag;     
	}
	else
	{
		Set_RfwaitXams_Flag;
	  gcRfXamsCount = 0;		
	}	
			
}
/*************************************************************************
//					void Time_convert(void)
//					将设定时间转换为剩余时间
//					
************************************************************************/
void Time_convert(void)
{
	switch(Ptcol_TimeSet)   	//gcPtcolBuff[4]      //这个值由定时按键来设定
	{
		case timer15min:
		{
			giTimeVal = 15;	
		}
		break;
		case timer30min:
		{
			giTimeVal = 30;
		}
		break;		
		case timer1hour:
		{
			giTimeVal = 60;
		}
		break;				
		case timer3hour:
		{
			giTimeVal = 180;
		}
		break;			
		case timer6hour:
		{
			giTimeVal = 360;
		}
		break;							
		
		case timerconti:
		{
			giTimeVal = 500;
		}
		break;				
	}
	
}

/*************************************************************************
//					void Time_calc(void)
//					将设定时间倒计时
//					
*************************************************************************/
void Time_calc(void)
{
	gcTimeVal_sec++;       //计时1秒
	
	if(gcTimeVal_sec >= 60)
	{
		gcTimeVal_sec = 0;
		giTimeVal--;	       //定时时间分钟数减1	
	}
				
	if(giTimeVal == 0)
	{
		StandBy_func();       //待机短按处理函数
	}
	else if(giTimeVal <= 15)
	{
		if(Ptcol_TimeSet != timer15min)     //按下定时按键
		{
			Ptcol_TimeSet = timer15min;
			
		}
	}
	else if(giTimeVal <= 30)
	{
		if(Ptcol_TimeSet != timer30min)
		{
			Ptcol_TimeSet = timer30min;
			
		}		
	}
	else if(giTimeVal <= 60)
	{
		if(Ptcol_TimeSet != timer1hour)
		{
			Ptcol_TimeSet = timer1hour;
			
		}		
	}
	else if(giTimeVal <= 180)
	{
		if(Ptcol_TimeSet != timer3hour)
		{
			Ptcol_TimeSet = timer3hour;
			
		}		
	}	
	else if(giTimeVal <= 360)
	{
		if(Ptcol_TimeSet != timer6hour)
		{
			Ptcol_TimeSet = timer6hour;
			
		}		
	}		
			
}

