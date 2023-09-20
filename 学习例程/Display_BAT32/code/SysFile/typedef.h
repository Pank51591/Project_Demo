//************************************************************
// 文件名称	:	typedef.h
// 作者		:	
// 最后更正日期:2010-06-08
// 版本		:	V1.0
// 更改记录	:	
//*************************************************************

#ifndef DATA_TYPE_C_HEADER
#define DATA_TYPE_C_HEADER

typedef unsigned char	bool; 		// 布尔变量（位变量）
typedef unsigned char	BOOL; 		// 布尔变量（位变量）
typedef unsigned char	uchar;		// 字符变量
typedef unsigned char 	INT8U; 		// 无符号8位整型变量  
typedef 				 char 	INT8S; 		// 有符号8位整型变量
typedef unsigned short 	uint; 		// 无符号16位整型变量  
typedef unsigned short 	INT16U; 	// 无符号16位整型变量 
typedef signed short 	INT16S; 	// 有符号16位整型变量
typedef unsigned int 	INT32U; 	// 无符号32位整型变量
typedef signed int	 	INT32S; 	// 有符号32位整型变量 
typedef float 			FP32; 		// 单精度浮点数(32位长度) 
typedef double 			FP64; 		// 双精度浮点数(64位长度)


typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;
typedef 	signed long		s32;

#define	UCHAR	unsigned	char
#define	UINT16	unsigned	int
#define	UINT32	unsigned	double	int

#define DATA  //data
#define IDATA //xdata
#define XDATA //xdata
#define CODE  const
#define CONST const
#define REENTRANT //reentrant 
#define RTDATA //static 
#define INLINE	inline

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

//*************************************************************************
//-------------------- system typedef -------------------------------------
typedef INT8U	HWND;//窗口类句柄
typedef INT32U	WPARAM;//
//*************************************************************************
//-------------------- ADC typedef --------------------------------------------------



//*************************************************************************
//-------------------- ADC typedef --------------------------------------------------
typedef INT16U ADCVAL;	//ADC转换值类型
typedef INT32U ADCDATA; //ADC采集数据

//*************************************************************************
//--------------------PWM typedef ---------------------------------------------------
typedef INT8U PWMDC;//占空比类型
typedef INT8U PWMFREG;//频率类型

//*************************************************************************
//--------------------Timer typedef--------------------------------------------------
typedef void (*TIMERPROC)(void);
typedef void (*UARTPROC)(INT8U *pbuf,INT16U len);

//*************************************************************************

#define 	true		1
#define 	false		0
#define 	enable		1
#define 	disable		0


#define 	TRUE		1
#define 	FALSE		0
#define 	ENABLE		1
#define 	DISABLE		0

#if 0
#define		BIT0	0x01
#define		BIT1	0x02
#define		BIT2	0x04
#define		BIT3	0x08
#define		BIT4	0x10
#define		BIT5	0x20
#define		BIT6	0x40
#define		BIT7	0x80
#endif


typedef struct 	 //8 8位功能
{
	char bit1 :1;
	char bit2 :1;
	char bit3 :1;
	char bit4 :1;
	char bit5 :1;
	char bit6 :1;
	char bit7 :1;
	char bit8 :1;
}
U8BITHAND;

typedef struct
{
	INT32U u32bit;
	INT8U  u8bit;  
}
INT32TO8;




#endif
