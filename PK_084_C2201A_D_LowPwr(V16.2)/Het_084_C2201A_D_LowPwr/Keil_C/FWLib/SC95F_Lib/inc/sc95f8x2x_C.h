/*--------------------------------------------------------------------------
SC95f8x2x_C.H

C Header file for SC95f8x2x microcontroller.
Copyright (c) 2020 Shenzhen SinOne Chip Electronic CO., Ltd.
All rights reserved.
��������Ԫ΢�������޹�˾
�汾��:  V0.1
����:  2020.02.19
--------------------------------------------------------------------------*/
#ifndef _SC95f8x2x_H_
#define _SC95f8x2x_H_

/* ------------------- �ֽڼĴ���-------------------- */
///*CPU*/
sfr 	ACC	   = 0xE0;		//�ۼ�����
sfr 	B	   = 0xF0;		//ͨ�üĴ���B
sfr 	PSW	   = 0xD0;		//����״̬��
sfr 	DPS	   = 0x86;      //����ѡ��Ĵ���
sfr 	DPH1   = 0x85;		//DPH1����ָ���8λ
sfr 	DPL1   = 0x84;      //DPL1����ָ���8λ
sfr 	DPH	   = 0x83;		//DPH����ָ���8λ
sfr 	DPL	   = 0x82;		//DPL����ָ���8λ
sfr 	SP	   = 0x81;		//��ջָ��

/*system*/
sfr		PCON   = 0x87;		//��Դ�������ƼĴ���

/*interrupt*/
sfr		IP2    = 0xBA;      //�ж����ȼ����ƼĴ���2
sfr		IP1    = 0xB9;      //�ж����ȼ����ƼĴ���1
sfr		IP	   = 0xB8;		//�ж�����Ȩ���ƼĴ���
sfr		IE	   = 0xA8;		//�жϿ��ƼĴ���
sfr		IE1    = 0xA9;  	//�жϿ��ƼĴ���1
sfr		IE2    = 0xAA;      //�жϿ��ƼĴ���2

/*PORT*/
sfr 	P5PH    = 0xDA;		//P5��ģʽ���ƼĴ���
sfr	  	P5CON	= 0xD9;		//P5��ģʽ���ƼĴ���
sfr   	P5	    = 0xD8;		//P5�����ݼĴ���
sfr 	P2PH    = 0xA2;		//P2��ģʽ���ƼĴ���
sfr	  	P2CON	= 0xA1;		//P2��ģʽ���ƼĴ���
sfr   	P2	    = 0xA0;		//P2�����ݼĴ���
sfr   	P1PH    = 0x92;		//P1��ģʽ���ƼĴ���
sfr	  	P1CON   = 0x91;		//P1��ģʽ���ƼĴ���
sfr   	P1	    = 0x90;		//P1�����ݼĴ���
sfr	  	P0PH    = 0x9B;		//P0��ģʽ���ƼĴ���
sfr	 	P0CON   = 0x9A;		//P0��ģʽ���ƼĴ���
sfr 	P0	    = 0x80;		//P0�����ݼĴ���
sfr 	IOHCON0 = 0x96;		//IOH0���üĴ���
sfr 	IOHCON1 = 0x97;		//IOH1���üĴ���

/*TIMER*/
sfr 	TMCON   = 0x8E;		//��ʱ��Ƶ�ʿ��ƼĴ���
sfr 	TH1	    = 0x8D;		//��ʱ��1��8λ
sfr 	TH0	    = 0x8C;		//��ʱ��0��8λ
sfr 	TL1	    = 0x8B;		//��ʱ��1��8λ
sfr 	TL0	    = 0x8A;		//��ʱ��0��8λ
sfr 	TMOD	= 0x89;		//��ʱ������ģʽ�Ĵ���
sfr 	TCON	= 0x88;		//��ʱ�����ƼĴ���
sfr   	TXCON   = 0xC8;   //��ʱ��2/3/4���ƼĴ���
sfr   	TXMOD   = 0xC9;   //��ʱ��2/3/4����/��׽��8λ
sfr   	RCAPXL  = 0xCA;   //��ʱ��2/3/4����/��׽��8λ
sfr   	RCAPXH  = 0xCB;   //��ʱ��2/3/4����/��׽��8λ
sfr   	TLX     = 0xCC;   //��ʱ��2/3/4��8λ
sfr   	THX     = 0xCD;   //��ʱ��2/3/4��8λ
sfr   	TXINX   = 0xCE;   //��ʱ�����ƼĴ���ָ��

/*ADC*/
sfr	  ADCCFG0 = 0xAB;	//ADC�������üĴ���0
sfr	  ADCCFG1 = 0xAC;	//ADC�������üĴ���1
sfr	  ADCCFG2 = 0xB5;	//ADC�������üĴ���2
sfr   ADCCON  = 0xAD;   //ADC���ƼĴ���
sfr   ADCVL	  = 0xAE;	//ADC ����Ĵ���
sfr   ADCVH	  = 0xAF;	//ADC ����Ĵ���

/*PWM*/
sfr 	PWMCFG = 0xD1;		//PWM���üĴ���
sfr 	PWMCON0	= 0xD2;		//PWM���üĴ���
sfr 	PWMCON1	= 0xD3;		//PWM���ƼĴ���
sfr 	PWMPDL	= 0xD4;		//PWM�������üĴ�����8λ
sfr 	PWMPDH	= 0xD5;		//PWM�������üĴ�����8λ
sfr 	PWMDFR	= 0xD6;		//PWM0�������üĴ���
sfr 	PWMFLT	= 0xD7;		//PWM���ϼ�����üĴ���

//
///*WatchDog*/
sfr	  BTMCON  = 0xFB;   //��Ƶ��ʱ�����ƼĴ���
sfr 	WDTCON	= 0xCF;		//WDT���ƼĴ���

sfr   OTCON   = 0X8F;	//������ƼĴ���

/*INT*/
sfr   INT0F   = 0xB4; 	//INT0 �½����жϿ��ƼĴ���
sfr   INT0R   = 0xBB; 	//INT0 �Ͻ����жϿ��ƼĴ���
sfr   INT1F   = 0xBC; 	//INT2 �½����жϿ��ƼĴ���
sfr   INT1R   = 0xBD; 	//INT2 �Ͻ����жϿ��ƼĴ���
sfr   INT2F   = 0xBE; 	//INT2 �½����жϿ��ƼĴ���
sfr   INT2R   = 0xBF; 	//INT2 �Ͻ����жϿ��ƼĴ���

/*IAP */
sfr   IAPCTL	= 0xF6;		//IAP���ƼĴ���
sfr   IAPDAT	= 0xF5;		//IAP���ݼĴ���
sfr   IAPADE  = 0xF4;     //IAP��չ��ַ�Ĵ���
sfr   IAPADH	= 0xF3;		//IAPд���ַ��λ�Ĵ���
sfr   IAPADL	= 0xF2;		//IAPд���ַ��8λ�Ĵ���
sfr   IAPKEY	= 0xF1;		//IAP�����Ĵ���

/*UART*/
sfr   SCON    = 0x98;   //���ڿ��ƼĴ���
sfr   SBUF    = 0x99;  	//�������ݻ���Ĵ���


/*USCI0*/
sfr   US0CON0  = 0x95;   //SPI0���ƼĴ���0
sfr   US0CON1  = 0x9D;   //SPI0���ƼĴ���1
sfr   US0CON2  = 0x9E;   //SP10���ƼĴ���2
sfr   US0CON3  = 0x9F;  //SPI0���ݼĴ���
sfr   US0CON4  = 0xB6;   //EGT��չ����ʱ��Ĵ���
sfr   US0CON5  = 0xB7;  //SCSTA0 SC״̬�Ĵ���

/*USCI1*/
sfr   US1CON0  = 0xA4;   //SPI1���ƼĴ���0
sfr   US1CON1  = 0xA5;   //SPI1���ƼĴ���1
sfr   US1CON2  = 0xA6;   //SPI1���ƼĴ���2
sfr   US1CON3  = 0xA7;  //SPI1���ݼĴ���

/*USCI2*/
sfr   US2CON0  = 0xC4;   //SPI2���ƼĴ���0
sfr   US2CON1  = 0xC5;   //SPI2���ƼĴ���1
sfr   US2CON2  = 0xC6;   //SPI2���ƼĴ���2
sfr   US2CON3  = 0xC7;   //SPI2���ݼĴ���

sfr   OPINX   = 0xFE;
sfr   OPREG   = 0xFF;
sfr   EXADH   = 0xF7;

/*�˳�����*/
sfr   EXA0    = 0xE9;   //��չ�ۼ���0
sfr   EXA1    = 0xEA;   //��չ�ۼ���1
sfr   EXA2    = 0xEB;   //��չ�ۼ���2
sfr   EXA3    = 0xEC;   //��չ�ۼ���3
sfr   EXBL    = 0xED;   //��չB�Ĵ���0
sfr   EXBH    = 0xEE;   //��չB�Ĵ���1
sfr   OPERCON = 0xEF;   //������ƼĴ���

/*CRC*/
sfr   CRCINX = 0xFC;	  //Check Sum����Ĵ�����λ
sfr   CRCREG = 0xFD;	  //Check Sum����Ĵ�����λ

///* ------------------- λ�Ĵ���-------------------- */
/*B*/
/*TKCON*/
/*ACC*/
/*PSW*/
sbit 	CY	= PSW ^
            7;	 //��־λ		0:�ӷ��������λ�޽�λ�����߼����������λ�޽�λʱ		1:�ӷ��������λ�н�λ�����߼����������λ�н�λʱ
sbit 	AC	= PSW ^
            6;	 //��λ������־λ	0:�޽�λ����λ		1:�ӷ�����ʱ��bit3λ�н�λ�������������bit3λ�н�λʱ
sbit 	F0	= PSW ^ 5;	 //�û���־λ
sbit 	RS1	= PSW ^ 4;	 //�����Ĵ�����ѡ��λ
sbit 	RS0	= PSW ^ 3;	 //�����Ĵ�����ѡ��λ
sbit 	OV	= PSW ^ 2;	 //�����־λ
sbit 	F1	= PSW ^ 1;	 //F1��־
sbit 	P	= PSW ^ 0;	 //��ż��־λ		0:ACC��1�ĸ���Ϊż��������0����		1:ACC��1�ĸ���Ϊ����

/*TXCON*/
sbit  TFX   = TXCON ^ 7;
sbit  EXFX	= TXCON ^ 6;
sbit  RCLKX = TXCON ^ 5;
sbit  TCLKX	= TXCON ^ 4;
sbit  EXENX	= TXCON ^ 3;
sbit  TRX	= TXCON ^ 2;
sbit  TX    = TXCON ^ 1;
sbit  CP	= TXCON ^ 0;

/*IP*/
sbit 	IPADC  = IP ^
               6;		//ADC�ж����ȿ���λ	0:�趨 ADC���ж�����Ȩ�� ���͡�		1:�趨 ADC���ж�����Ȩ�� ���ߡ�
sbit	IPT2   = IP ^
               5;		//PWM�ж����ȿ���λ	0:�趨 PWM���ж�����Ȩ�� ���͡�		1:�趨 PWM ���ж�����Ȩ�� ���ߡ�
sbit 	IPUART = IP ^
               4;		//SIF�ж����ȿ���λ	0:�趨 SIF���ж�����Ȩ�� ���͡�		1:�趨 SIF���ж�����Ȩ�� ���ߡ�
sbit 	IPT1   = IP ^
               3;		//Timer1�ж����ȿ���λ	0:�趨 Timer 1���ж�����Ȩ�� ���͡�	1:�趨 Timer 1���ж�����Ȩ�� ���ߡ�
sbit	IPINT1 = IP ^
               2;		//32K Base Timer�ж����ȿ���λ		0:�趨 32K���ж�����Ȩ�� ���͡�		1:�趨 32K���ж�����Ȩ�� ���ߡ�
sbit 	IPT0   = IP ^
               1;		//Timer0�ж����ȿ���λ	0:�趨 Timer 0���ж�����Ȩ�� ���͡�	1:�趨 Timer 0���ж�����Ȩ�� ���ߡ�
sbit	IPINT0 = IP ^ 0;

/*IE*/
sbit 	EA	   = IE ^ 7;		//�ж�ʹ�ܵ��ܿ���	0:�ر����е��ж�	1:�����е��ж�
sbit 	EADC   = IE ^ 6;		//ADC�ж�ʹ�ܿ���	0:�ر�ADC�ж�		1:��ADC�ж�
sbit 	ET2    = IE ^ 5;		//PWM�ж�ʹ�ܿ���	0:�ر�PWM�ж�		1:��PWM�ж�
sbit	EUART  = IE ^ 4;		//UART�ж�ʹ�ܿ���	0:�ر�SIF�ж�		1:��SIF�ж�
sbit 	ET1    = IE ^ 3;		//Timer1�ж�ʹ�ܿ���	0:�ر�TIMER1�ж�	1:��TIMER1�ж�
sbit	EINT1  = IE ^ 2;		//32K Base Timer�ж�ʹ�ܿ���	0:�ر�32K�ж�		1:��32K�ж�
sbit 	ET0	   = IE ^ 1;		//Timer0�ж�ʹ�ܿ���	0:�ر�TIMER0�ж�	1:��TIMER0�ж�
sbit	EINT0  = IE ^ 0;		//TouchKey���ж�ʹ�ܿ���	0:�ر�TouchKey�ж�  1:��TouchKey�ж�

/*TCON*/
sbit 	TF1	   = TCON ^
               7;	//T1����ж������־λ	T1��������������ж�ʱ��Ӳ����TF1��Ϊ��1���������жϣ�CPU��Ӧʱ��Ӳ���塰0����
sbit 	TR1	   = TCON ^ 6;	//��ʱ��T1�����п���λ	0:Timer1��ֹ����		1:Timer1��ʼ����
sbit 	TF0	   = TCON ^
               5;	//T0����ж������־λ	T0��������������ж�ʱ��Ӳ����TF0��Ϊ��1���������жϣ�CPU��Ӧʱ��Ӳ���塰0����
sbit 	TR0	   = TCON ^ 4;	//��ʱ��T0�����п���λ	0:Timer0��ֹ����		1:Timer0��ʼ����
sbit 	Bit_IE1	   = TCON ^ 3;	//INT1��־λ
sbit 	Bit_IE0	   = TCON ^ 1;	//INT0��־λ

/*SCON*/
sbit 	SM0    = SCON ^ 7;
sbit 	SM1	   = SCON ^ 6;
sbit 	SM2	   = SCON ^ 5;
sbit 	REN	   = SCON ^ 4;
sbit 	TB8	   = SCON ^ 3;
sbit 	RB8	   = SCON ^ 2;
sbit 	TI	   = SCON ^ 1;
sbit 	RI	   = SCON ^ 0;

/******************* P0 ******************
*SC95F8525��װδ�����Ĺܽţ���
*SC95F8523��װδ�����Ĺܽţ���
*SC95F8522��װδ�����Ĺܽţ�P06/P07
*SC95F8521��װδ�����Ĺܽ�: P02/P03/P04/P06/P07
******************************************/
sbit 	P07 = P0 ^ 7;
sbit 	P06 = P0 ^ 6;
sbit 	P05	= P0 ^ 5;
sbit 	P04	= P0 ^ 4;
sbit 	P03	= P0 ^ 3;
sbit 	P02	= P0 ^ 2;
sbit 	P01	= P0 ^ 1;
sbit 	P00	= P0 ^ 0;

/******************* P1 ******************
*SC95F8525��װδ�����Ĺܽţ���
*SC95F8523��װδ�����Ĺܽţ���
*SC95F8522��װδ�����Ĺܽţ�P16/P17
*SC95F8521��װδ�����Ĺܽţ�P16/P17
******************************************/
sbit 	P17	= P1 ^ 7;
sbit 	P16	= P1 ^ 6;
sbit 	P15	= P1 ^ 5;
sbit 	P14	= P1 ^ 4;
sbit 	P13	= P1 ^ 3;
sbit 	P12	= P1 ^ 2;
sbit 	P11	= P1 ^ 1;
sbit 	P10	= P1 ^ 0;

/******************* P2 ******************
*SC95F8525��װδ�����Ĺܽţ���
*SC95F8523��װδ�����Ĺܽţ���
*SC95F8522��װδ�����Ĺܽţ�P22/P23
*SC95F8521��װδ�����Ĺܽţ�P22/P23/P27
******************************************/
sbit 	P27	= P2 ^ 7;
sbit 	P26	= P2 ^ 6;
sbit 	P25	= P2 ^ 5;
sbit 	P24	= P2 ^ 4;
sbit 	P23	= P2 ^ 3;
sbit 	P22	= P2 ^ 2;
sbit 	P21	= P2 ^ 1;
sbit 	P20	= P2 ^ 0;

/******************* P5 ******************
*SC95F8525��װδ�����Ĺܽţ���
*SC95F8523��װδ�����Ĺܽţ�P52/P53/P54/P55
*SC95F8522��װδ�����Ĺܽţ�P50/P51/P52/P53/P54/P55
*SC95F8521��װδ�����Ĺܽţ�P50/P51/P52/P53/P54/P55
******************************************/
sbit 	P55	= P5 ^ 5;
sbit 	P54	= P5 ^ 4;
sbit 	P53	= P5 ^ 3;
sbit 	P52	= P5 ^ 2;
sbit 	P51	= P5 ^ 1;
sbit 	P50	= P5 ^ 0;

/****************************************************************************
*ע�⣺��װδ�����Ĺܽţ�������Ϊǿ�������ģʽ
*ICѡ�ͣ��������ʹ�õ�IC�ͺ�,�ڳ�ʼ����IO�ں󣬵������Ӧ��δ�����ܽŵ�IO������;
*****************************************************************************/

#define  SC95F8522_NIO_Init()   {P0CON|=0xC0,P1CON|=0xC0,P2CON|=0x0C,P5CON|=0x03;}  // SC95F8522��δ��������IO������
#define  SC95F8521_NIO_Init()   {P0CON|=0xDC,P1CON|=0xC0,P2CON|=0x8C,P5CON|=0x03;}  // SC95F8521��δ��������IO������
#define  SC95F8520S_NIO_Init()  {P0CON|=0xDF,P1CON|=0xD2,P2CON|=0xEC,P5CON|=0x03;}  // SC95F8520S(10PIN)��δ��������IO������
#define  SC95F8520M_NIO_Init()  {P0CON|=0xFF,P1CON|=0xF2,P2CON|=0xEC,P5CON|=0x03;}  // SC95F8520M(8PIN)��δ��������IO������

#endif