#ifndef WINDOW_H
#define WINDOW_H

#define HWND_ITEM_NUM 3


//处理项
enum _HANDLE_ITEM
{
	HWND_NULL,
	HWND_DESKTOP,

	HWND_Oreration,
	HWND_Service,
	HWND_Data,
	HWND_LEDLevel,
	HWND_TypeSize,

	HWND_FCT,
	HWND_INVALID,
	
	HWND_MAX=HWND_INVALID
};



typedef struct
{
	INT8U item;
	INT8U focus;
}
POINT,*LPPOINT;




typedef  BOOL (*KEYHAND)(INT8U key);
typedef  BOOL (*WINPROC)(MSG *msg);
typedef void (*WININIT)(void);

typedef struct _WINHAND XDATA WINHAND;


#pragma pack(1)

struct _WINHAND
{
	//WINHAND *head;
	//WINHAND *next;
	WINPROC WinProc;
	WININIT Init;
	INT8U id;
	INT8U item;//选项
	INT8U focus;//光标
};
#pragma pack()

HWND CreatePage(WINHAND *win);
BOOL SetFocus(HWND hwnd);
HWND GetFocus(void);
BOOL SetCursorPos(INT8U item,INT8U focus);
BOOL GetCursorPos(LPPOINT point);
HWND GetActiveWindow(void);
HWND GetParent(void);

void WinInit(void);
BOOL WinPreviousPage(void);
BOOL WinSwichToNextPage(void);
BOOL WinPageSwitch(HWND hwnd);


void WndProc(MSG *msg);

void DefWindowProc(MSG *msg);


#endif

