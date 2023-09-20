#ifndef SYSTEM_H
#define SYSTEM_H

#include"typedef.h"


#define OS_START()	//TR0 = 1;


#define DATE_ENABLE 0//日期使能 

#define min(s) (s*60000)//分钟
#define sec(s) (s*1000)//秒钟
#define msc(s) (s)//毫秒

typedef enum
{
	VK_NULL,
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	VK_MENU,
	VK_OK,
	VK_EXIT,

	VK_ONOFF,
	
	VK_REST,
	VK_SELECT,
	VK_REST_FLUSH,

	VK_FLUSH,//冲洗
	
	VK_NUM
}
VKEY;



typedef enum systimer
{
	SYS_TIMER_WINTIMEOUT,//界面超时退出
	
	SYS_TIMER_FLUSHTIME,//自动清洗定时 
	
	SYS_TIMER_powerdownsave,//掉电保存

	SYS_TIMER_BACKLIGHT,//背光灯

	SYS_TIMER_POWERON_DISP,//

	SYS_TIMER_FACTORYMODE,//

	SYS_TIMER_WATERCOUNT,

	SYS_TIMERPUMP,//水泵
	
	SYS_TIMER_TDS_net,//
	SYS_TIMER_TDS_raw,
	SYS_TIMER_TDS_temp,

	SYS_TIMER_FCT,

	SYS_TIMER_wifinetwork,

	SYS_TIMER_Backflow,

	SYS_TIMER_Beep,
	
	SYS_TIMER_FREEID,
	SYS_TIMER_NUM = SYS_TIMER_FREEID
}
SYS_TIMER_ITEM;



enum _TIMERMODE
{
	TIME_ONESHOT=0,//运行一次
	TIME_PERIODIC=1,//无限循环
	TIME_DELAY//延时
};


typedef enum
{
	WM_NONE,//无信息
	
	WM_CREATE,//操作系统第一个处理的消息
	WM_USERINTT,//用户数据初始化
	WM_USERSTARTPROC,
	WM_LOGO,//显示logo

	WM_PREVPAGE,//上一个页面
	WM_NEXTPAGE,//下一个页面
	WM_PAGESWITCH,//切换页面

	WM_UPPER,//上层消息
	
	WM_KEYDOWN,//按键按下
	WM_KEYUP,//按键放开
	WM_KEYLONG,//长按
	WM_KEYCONTINUE,//连按
	WM_KEYDOUBLE,//双击
	WM_KEYCLICK_3,//3击
	WM_KEYCLICK_6,//6击
	WM_KEYLONGUP,//长按松开

	WM_POWERLOW,//电压过低
	WM_ALARM,//报警
	
	WM_COMMAND,//控件消息
	WM_SERIALTXD,//串口发送数据
	WM_SERIALRXD,//串口接收到数据
	WM_ADC,
	WM_ADCCONTROL,
	WM_TIMER,//定时器
	WM_DISPLAY,//显示 
	WM_MODEFYDISPLAY,

	WM_SENDSWER,//发送软件版本

	WM_TIMERAPP,

	WM_NUM
}
SYS_MESSAGE_TYPE;

#pragma pack(1)
typedef struct   
{
	//void (*TimerFunc)(INT8U data1);//回调函数
	//void (*TimerFunc)(void);//回调函数
	TIMERPROC TimerFunc;//回调函数
	INT32U	nElapse;//nElapse最多8192ms 
	INT32U	nElapseBuff;//nElapse最多8192ms 
	INT8U	Flag:1;//定时到时标志
	INT8U	State:1;//状态,ENABLE,DISABLE
	INT8U	MonitorFlag:1;//监控状态
	INT8U	Mode:5;//方式，一次多次还是延时
	INT8U	IDEvent;//nIDEvent，ID
	INT8U	hwnd;//
}
IDATA SYSTIMER;



typedef struct 
{
	HWND	hwnd;//消息ID号16个
	INT8U	message;//消息16个
	WPARAM	wParam;//附加信息
}
MSG,*pMSG;



//消息队列
typedef struct
{
	MSG		*pSend;//发送消息地址
	MSG		*pGet;//获取消息
	MSG		msg[SYS_QUEUE_NUM];
	MSG		HGPriority;//最高优先级

	INT8U	iSend;//发送消息下标
	INT8U	iGet;//获取消息下标
}
 MSGQUEUE;



////////////////////////////////////////////////////////////////////////
typedef struct
{
#if DATE_ENABLE	
	INT16U Year:12;
	INT16U Month:4;
	INT8U Day;
#endif
	INT16U Milliseconds:10;//毫秒
	INT16U Second:6;
	INT8U Hour:5;
	INT8U Week:3;
	INT8U Minute:6;
	INT8U Format:2;//
}
SYSTEMTIME;

#pragma pack()


extern SYSTEMTIME sSystemTime;
extern MSGQUEUE	MsgQueue;//消息队列


//Timer
extern void Timer0(void);
extern BOOL SetTimer(HWND hwnd,INT8U nIDEvent,INT32U nElapse,TIMERPROC TimerProc);
extern BOOL TimeSetEvent(INT8U nIDEvent,INT32U nElapse,TIMERPROC lpTimeProc,BOOL fuEvent);
extern BOOL SetDelayTimer(INT8U nIDEvent,INT32U nElapse);
extern BOOL KillTimer(HWND hwnd,INT8U IDEvent);
extern BOOL GetTimerFlag(INT8U IDEvent);
extern BOOL TimerPause(HWND hwnd,INT8U IDEvent);
extern BOOL TimerStart(HWND hwnd,INT8U IDEvent);
//MSG
extern void SYSInit(void);
extern BOOL GetMessage(MSG *msg,HWND hwnd);
extern BOOL SendMessage(HWND hWnd,INT8U Msg, WPARAM wParam);
extern BOOL SendHGPriotityMessage(HWND hWnd,INT8U Msg, WPARAM wParam);
extern INT8U GetMessageNum(void);
extern void DefOSProc(MSG *msg);

extern void MonitorTimer(void);
extern void MonitorMessage(void);

//SystemTime
extern void GetSystemTime(SYSTEMTIME *time);
extern void SetSystemTime(SYSTEMTIME *time);
extern void SyStemTimeTask(void)REENTRANT;

//other
extern void GetSoftVersion(char *ver);
extern void GetMCUInfor(char *ver);





#endif

