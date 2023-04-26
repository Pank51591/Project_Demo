#ifndef __LED_RF_H__
#define __LED_RF_H__


typedef struct
{
	unsigned char gcAirVol;
	unsigned char gcAirDir;	
	unsigned char gcAirkind;	
	unsigned char gcTimeSet;	
}stMode_info;


extern stMode_info  stWarm_Stro;
extern stMode_info  stWarm_Weak;
extern stMode_info  stChAir_Stro;
extern stMode_info  stChAir_Weak;
extern stMode_info  stCold_dry;
extern stMode_info  stHot_dry;
extern stMode_info  stDegerming;

extern volatile unsigned char TxPtcol_Wifi;
extern volatile unsigned char TxPtcol_voice;
extern volatile unsigned char gcledscan_row;
extern volatile unsigned char gcRfSendCount;



#define  RfwaitXams   60
#define  RfwaitXbms   180


#define   LED_WarmHouse     0x01
#define   LED_Lamp          0x02
#define   LED_Nightlamp     0x04
#define   LED_AirStrong     0x08
#define   LED_HotDry        0x10
#define   LED_Degerming     0x20    //ณýพ๚ตฦนโ
#define   LED_AirWeak       0x40
#define   LED_ColdDry       0x80
#define   LED_AirChange     0x100


extern void RF_Process(void);
extern void Time_convert(void);
extern void Time_calc(void);
extern void StandBy_func(void);
extern void StandBy_init(void);
extern void PowerOn_init(void);
extern void led_process(void);


#endif

