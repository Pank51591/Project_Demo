//************************************************************
// �ļ�����	:	typedef.h
// ����		:	
// ����������:2010-06-08
// �汾		:	V1.0
// ���ļ�¼	:	
//*************************************************************

#ifndef DATA_TYPE_C_HEADER
#define DATA_TYPE_C_HEADER

typedef unsigned char	bool; 		// ����������λ������
typedef unsigned char	BOOL; 		// ����������λ������
typedef unsigned char	uchar;		// �ַ�����
typedef unsigned char 	INT8U; 		// �޷���8λ���ͱ���  
typedef 				 char 	INT8S; 		// �з���8λ���ͱ���
typedef unsigned short 	uint; 		// �޷���16λ���ͱ���  
typedef unsigned short 	INT16U; 	// �޷���16λ���ͱ��� 
typedef signed short 	INT16S; 	// �з���16λ���ͱ���
typedef unsigned int 	INT32U; 	// �޷���32λ���ͱ���
typedef signed int	 	INT32S; 	// �з���32λ���ͱ��� 
typedef float 			FP32; 		// �����ȸ�����(32λ����) 
typedef double 			FP64; 		// ˫���ȸ�����(64λ����)


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
typedef INT8U	HWND;//��������
typedef INT32U	WPARAM;//
//*************************************************************************
//-------------------- ADC typedef --------------------------------------------------



//*************************************************************************
//-------------------- ADC typedef --------------------------------------------------
typedef INT16U ADCVAL;	//ADCת��ֵ����
typedef INT32U ADCDATA; //ADC�ɼ�����

//*************************************************************************
//--------------------PWM typedef ---------------------------------------------------
typedef INT8U PWMDC;//ռ�ձ�����
typedef INT8U PWMFREG;//Ƶ������

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


typedef struct 	 //8 8λ����
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
