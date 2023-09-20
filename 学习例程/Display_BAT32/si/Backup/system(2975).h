#ifndef SYSTEM_H
#define SYSTEM_H

#include"typedef.h"


#define OS_START()	//TR0 = 1;


#define DATE_ENABLE 0//����ʹ�� 

#define min(s) (s*60000)//����
#define sec(s) (s*1000)//����
#define msc(s) (s)//����

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

	VK_FLUSH,//��ϴ
	
	VK_NUM
}
VKEY;



typedef enum systimer
{
	SYS_TIMER_WINTIMEOUT,//���泬ʱ�˳�
	
	SYS_TIMER_FLUSHTIME,//�Զ���ϴ��ʱ 
	
	SYS_TIMER_powerdownsave,//���籣��

	SYS_TIMER_BACKLIGHT,//�����

	SYS_TIMER_POWERON_DISP,//

	SYS_TIMER_FACTORYMODE,//

	SYS_TIMER_WATERCOUNT,

	SYS_TIMERPUMP,//ˮ��
	
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
	TIME_ONESHOT=0,//����һ��
	TIME_PERIODIC=1,//����ѭ��
	TIME_DELAY//��ʱ
};


typedef enum
{
	WM_NONE,//����Ϣ
	
	WM_CREATE,//����ϵͳ��һ���������Ϣ
	WM_USERINTT,//�û����ݳ�ʼ��
	WM_USERSTARTPROC,
	WM_LOGO,//��ʾlogo

	WM_PREVPAGE,//��һ��ҳ��
	WM_NEXTPAGE,//��һ��ҳ��
	WM_PAGESWITCH,//�л�ҳ��

	WM_UPPER,//�ϲ���Ϣ
	
	WM_KEYDOWN,//��������
	WM_KEYUP,//�����ſ�
	WM_KEYLONG,//����
	WM_KEYCONTINUE,//����
	WM_KEYDOUBLE,//˫��
	WM_KEYCLICK_3,//3��
	WM_KEYCLICK_6,//6��
	WM_KEYLONGUP,//�����ɿ�

	WM_POWERLOW,//��ѹ����
	WM_ALARM,//����
	
	WM_COMMAND,//�ؼ���Ϣ
	WM_SERIALTXD,//���ڷ�������
	WM_SERIALRXD,//���ڽ��յ�����
	WM_ADC,
	WM_ADCCONTROL,
	WM_TIMER,//��ʱ��
	WM_DISPLAY,//��ʾ 
	WM_MODEFYDISPLAY,

	WM_SENDSWER,//��������汾

	WM_TIMERAPP,

	WM_NUM
}
SYS_MESSAGE_TYPE;

#pragma pack(1)
typedef struct   
{
	//void (*TimerFunc)(INT8U data1);//�ص�����
	//void (*TimerFunc)(void);//�ص�����
	TIMERPROC TimerFunc;//�ص�����
	INT32U	nElapse;//nElapse���8192ms 
	INT32U	nElapseBuff;//nElapse���8192ms 
	INT8U	Flag:1;//��ʱ��ʱ��־
	INT8U	State:1;//״̬,ENABLE,DISABLE
	INT8U	MonitorFlag:1;//���״̬
	INT8U	Mode:5;//��ʽ��һ�ζ�λ�����ʱ
	INT8U	IDEvent;//nIDEvent��ID
	INT8U	hwnd;//
}
IDATA SYSTIMER;



typedef struct 
{
	HWND	hwnd;//��ϢID��16��
	INT8U	message;//��Ϣ16��
	WPARAM	wParam;//������Ϣ
}
MSG,*pMSG;



//��Ϣ����
typedef struct
{
	MSG		*pSend;//������Ϣ��ַ
	MSG		*pGet;//��ȡ��Ϣ
	MSG		msg[SYS_QUEUE_NUM];
	MSG		HGPriority;//������ȼ�

	INT8U	iSend;//������Ϣ�±�
	INT8U	iGet;//��ȡ��Ϣ�±�
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
	INT16U Milliseconds:10;//����
	INT16U Second:6;
	INT8U Hour:5;
	INT8U Week:3;
	INT8U Minute:6;
	INT8U Format:2;//
}
SYSTEMTIME;

#pragma pack()


extern SYSTEMTIME sSystemTime;
extern MSGQUEUE	MsgQueue;//��Ϣ����


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

