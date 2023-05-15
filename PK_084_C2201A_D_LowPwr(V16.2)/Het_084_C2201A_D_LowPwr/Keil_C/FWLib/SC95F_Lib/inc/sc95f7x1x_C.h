/*--------------------------------------------------------------------------
sc95f7x1x_C.H

C Header file for sc95f7x1x microcontroller.
Copyright (c) 2019 Shenzhen SinOne Microelectronics Co., Ltd.
All rights reserved.
��������Ԫ΢�������޹�˾
�汾��:  V2.0
����:  2019.05.10
--------------------------------------------------------------------------*/
#ifndef _sc95f7x1x_H_
#define _sc95f7x1x_H_

/* ------------------- �ֽڼĴ���-------------------- */
///*CPU*/
sfr   ACC	= 0xE0;		//�ۼ�����
sfr   B     = 0xF0;		//ͨ�üĴ���B
sfr   PSW	= 0xD0;		//����״̬��
sfr   DPS	= 0x86;		//����ָ��Ĵ���
sfr   DPH1	= 0x85;		//DPH1����ָ���8λ
sfr   DPL1	= 0x84;		//DPL1����ָ���8λ
sfr   DPH	= 0x83;		//DPH����ָ���8λ
sfr   DPL	= 0x82;		//DPL����ָ���8λ
sfr   SP	= 0x81;		//��ջָ��


/*system*/
sfr   PCON	= 0x87;		//��Դ�������ƼĴ���

/*interrupt*/
sfr   IP2   = 0XBA;     //�ж����ȼ����ƼĴ���2
sfr   IP1   = 0XB9;     //�ж����ȼ����ƼĴ���1
sfr   IP	= 0xB8;		//�ж�����Ȩ���ƼĴ���
sfr   IE	= 0xA8;		//�жϿ��ƼĴ���
sfr   IE1   = 0XA9;  	//�жϿ��ƼĴ���1
sfr   IE2   = 0XAA;  	//�жϿ��ƼĴ���2

/*PORT*/
sfr   P5PH	  = 0xDA;	//P5��ģʽ���ƼĴ���
sfr	  P5CON	  = 0xD9;	//P5��ģʽ���ƼĴ���
sfr   P5	  = 0xD8;	//P5�����ݼĴ���
sfr   P4PH	  = 0xC2;	//P4��ģʽ���ƼĴ���
sfr	  P4CON	  = 0xC1;	//P4��ģʽ���ƼĴ���
sfr   P4	  = 0xC0;	//P4�����ݼĴ���
sfr   P3PH	  = 0xB2;	//P3��ģʽ���ƼĴ���
sfr	  P3CON	  = 0xB1;	//P3��ģʽ���ƼĴ���
sfr   P3	  = 0xB0;	//P3�����ݼĴ���
sfr   P2PH	  = 0xA2;	//P2��ģʽ���ƼĴ���
sfr	  P2CON	  = 0xA1;	//P2��ģʽ���ƼĴ���
sfr   P2	  = 0xA0;	//P2�����ݼĴ���
sfr   P1PH    = 0x92;	//P1��ģʽ���ƼĴ���
sfr	  P1CON	  = 0x91;	//P1��ģʽ���ƼĴ���
sfr   P1	  = 0x90;	//P1�����ݼĴ���
sfr	  P0PH	  = 0x9B;	//P0��ģʽ���ƼĴ���
sfr	  P0CON	  = 0x9A;	//P0��ģʽ���ƼĴ���
sfr   P0	  = 0x80;	//P0�����ݼĴ���
sfr   IOHCON0 = 0x96;	//IOH0���üĴ���
sfr   IOHCON1 = 0x97;	//IOH1���üĴ���

/*TIMER*/
sfr   TMCON	  = 0x8E;   //��ʱ��Ƶ�ʿ��ƼĴ���
sfr   TH1	  = 0x8D;   //��ʱ��1��8λ
sfr   TH0	  = 0x8C;	//��ʱ��0��8λ
sfr   TL1	  = 0x8B;	//��ʱ��1��8λ
sfr   TL0	  = 0x8A;	//��ʱ��0��8λ
sfr   TMOD	  = 0x89;	//��ʱ������ģʽ�Ĵ���
sfr   TCON	  = 0x88;	//��ʱ�����ƼĴ���
sfr   TXCON   = 0xC8;   //��ʱ��2/3/4���ƼĴ���
sfr   TXMOD   = 0xC9; 	//��ʱ��2/3/4����ģʽ�Ĵ���
sfr   RCAPXL  = 0xCA;   //��ʱ��2/3/4����/��׽��8λ
sfr   RCAPXH  = 0xCB;   //��ʱ��2/3/4����/��׽��8λ
sfr   TLX     = 0xCC;   //��ʱ��2/3/4��8λ
sfr   THX     = 0xCD;   //��ʱ��2/3/4��8λ
sfr   TXINX   = 0xCE;   //��ʱ�����ƼĴ���ָ��

/*ADC*/
sfr	  ADCCFG0 = 0xAB;	//ADC�������üĴ���0
sfr	  ADCCFG1 = 0xAC;	//ADC�������üĴ���1
sfr	  ADCCFG2 = 0xB5;	//ADC�������üĴ���2
sfr   ADCCON  = 0XAD;   //ADC���ƼĴ���
sfr   ADCVL	  = 0xAE;	//ADC ����Ĵ���
sfr   ADCVH	  = 0xAF;	//ADC ����Ĵ���

/*PWM*/
sfr   PWMMOD  = 0xD7;	//PWMģʽ���üĴ���
sfr   PWMFLT  = 0xD6;	//PWM���ϼ�����üĴ���
sfr   PWMDFR  = 0xD5;	//PWM�������üĴ���
sfr   PWMCFG  = 0xD4;	//PWM���üĴ���
sfr   PWMCON  = 0xD3;	//PWM���ƼĴ���

///*WatchDog*/
sfr   BTMCON  = 0XFB;   //��Ƶ��ʱ�����ƼĴ���
sfr   WDTCON  = 0xCF;	//WDT���ƼĴ���


/*LCD*/
sfr   OTCON   = 0X8F;	//LCD��ѹ������ƼĴ���
sfr   P0VO    = 0X9C;   //P0��ʾ��������Ĵ���
sfr   P1VO    = 0X94;   //P1��ʾ��������Ĵ���
sfr   P2VO    = 0XA3;   //P2��ʾ��������Ĵ���
sfr   P3VO    = 0XB3;   //P3��ʾ��������Ĵ���

sfr   DDRCON  = 0X93;   //��ʾ�������üĴ���


/*INT*/
sfr   INT0F   = 0XB4; 	//INT0 �½����жϿ��ƼĴ���
sfr   INT0R   = 0XBB; 	//INT0 �Ͻ����жϿ��ƼĴ���
sfr   INT1F   = 0XBC; 	//INT1 �½����жϿ��ƼĴ���
sfr   INT1R   = 0XBD; 	//INT1 �Ͻ����жϿ��ƼĴ���
sfr   INT2F   = 0XBE; 	//INT2 �½����жϿ��ƼĴ���
sfr   INT2R   = 0XBF; 	//INT2 �Ͻ����жϿ��ƼĴ���

/*IAP */
sfr   IAPCTL  = 0xF6;	//IAP���ƼĴ���
sfr   IAPDAT  = 0xF5;	//IAP���ݼĴ���
sfr   IAPADE  = 0xF4;   //IAP��չ��ַ�Ĵ���
sfr   IAPADH  = 0xF3;	//IAPд���ַ��λ�Ĵ���
sfr   IAPADL  = 0xF2;	//IAPд���ַ��8λ�Ĵ���
sfr   IAPKEY  = 0xF1;	//IAP�����Ĵ���

/*UART*/
sfr   SCON    = 0X98;   //���ڿ��ƼĴ���
sfr   SBUF    = 0X99;  	//�������ݻ���Ĵ���

/*USCI0*/
sfr   US0CON0 = 0X95;   //USCI0���ƼĴ���0
sfr   US0CON1 = 0X9D;   //USCI0���ƼĴ���1
sfr   US0CON2 = 0X9E;   //USCI0���ƼĴ���2
sfr   US0CON3 = 0X9F;   //USCI0���ƼĴ���3

/*USCI1*/
sfr   US1CON0 = 0XA4;   //USCI1���ƼĴ���0
sfr   US1CON1 = 0XA5;   //USCI1���ƼĴ���1
sfr   US1CON2 = 0XA6;   //USCI1���ƼĴ���2
sfr   US1CON3 = 0XA7;   //USCI1���ƼĴ���3

/*USCI2*/
sfr   US2CON0 = 0XC4;   //USCI2���ƼĴ���0
sfr   US2CON1 = 0XC5;   //USCI2���ƼĴ���1
sfr   US2CON2 = 0XC6;   //USCI2���ƼĴ���2
sfr   US2CON3 = 0XC7;   //USCI2���ƼĴ���3

sfr   OPINX   = 0XFE;
sfr   OPREG   = 0XFF;
sfr   EXADH   = 0XF7;

/*ģ��Ƚ���*/
sfr   CMPCFG  = 0XB6;	//ģ��Ƚ������üĴ���
sfr   CMPCON  = 0XB7;	//ģ��Ƚ������ƼĴ���

/*�˳�����*/
sfr   EXA0    = 0xE9;   //��չ�ۼ���0
sfr   EXA1    = 0xEA;   //��չ�ۼ���1
sfr   EXA2    = 0xEB;   //��չ�ۼ���2
sfr   EXA3    = 0xEC;   //��չ�ۼ���3
sfr   EXBL    = 0xED;   //��չB�Ĵ���0
sfr   EXBH    = 0xEE;   //��չB�Ĵ���1
sfr   OPERCON = 0xEF;   //������ƼĴ���

/* CRCУ�� */
sfr   CRCINX  = 0xFC;
sfr   CRCREG  = 0xFD;

/* ------------------- λ�Ĵ���-------------------- */
/*PSW*/
sbit  CY	  = PSW ^
              7;	//��־λ		0:�ӷ��������λ�޽�λ�����߼����������λ�޽�λʱ		1:�ӷ��������λ�н�λ�����߼����������λ�н�λʱ
sbit  AC	  = PSW ^
              6;	//��λ������־λ	0:�޽�λ����λ		1:�ӷ�����ʱ��bit3λ�н�λ�������������bit3λ�н�λʱ
sbit  F0	  = PSW ^ 5;	//�û���־λ
sbit  RS1	  = PSW ^ 4;	//�����Ĵ�����ѡ��λ
sbit  RS0	  = PSW ^ 3;	//�����Ĵ�����ѡ��λ
sbit  OV	  = PSW ^ 2;	//�����־λ
sbit  F1	  = PSW ^ 1;	//F1��־
sbit  P	      = PSW ^ 0;	//��ż��־λ		0:ACC��1�ĸ���Ϊż��������0����		1:ACC��1�ĸ���Ϊ����

/*TXCON*/
sbit  TFX     = TXCON ^ 7;
sbit  EXFX    = TXCON ^ 6;
sbit  RCLKX   = TXCON ^ 5;
sbit  TCLKX   = TXCON ^ 4;
sbit  EXENX   = TXCON ^ 3;
sbit  TRX	  = TXCON ^ 2;
sbit  TX      = TXCON ^ 1;
sbit  CP      = TXCON ^ 0;

/*IP*/
sbit  IPADC	  = IP ^
                6;	//ADC�ж����ȿ���λ      0:�趨 ADC���ж�����Ȩ�� ���͡�		1:�趨 ADC���ж�����Ȩ�� ���ߡ�
sbit  IPT2	  = IP ^
                5;	//Timer2�ж����ȿ���λ   0:�趨 Timer2���ж�����Ȩ�� ���͡�		1:�趨Timer2���ж�����Ȩ�� ���ߡ�
sbit  IPUART  = IP ^
                4;	//UART�ж����ȿ���λ	   0:�趨UART���ж�����Ȩ�� ���͡�		1:�趨UART���ж�����Ȩ�� ���ߡ�
sbit  IPT1	  = IP ^
                3;	//Timer1�ж����ȿ���λ   0:�趨 Timer 1���ж�����Ȩ�� ���͡�	1:�趨 Timer 1���ж�����Ȩ�� ���ߡ�
sbit  IPINT1  = IP ^
                2;	//INT1�ж����ȿ���λ	   0:�趨INT1�ж�����Ȩ�� ���͡�		    1:�趨INT1���ж�����Ȩ�� ���ߡ�
sbit  IPT0	  = IP ^
                1;	//Timer0�ж����ȿ���λ   0:�趨 Timer 0���ж�����Ȩ�� ���͡�	1:�趨 Timer 0���ж�����Ȩ�� ���ߡ�
sbit  IPINT0  = IP ^
                0; //INT0�ж����ȿ���λ	   0:�趨INT0�ж�����Ȩ�� ���͡�		    1:�趨INT0���ж�����Ȩ�� ���ߡ�

/*IE*/
sbit  EA	  = IE ^ 7;	//�ж�ʹ�ܵ��ܿ���	0:�ر����е��ж�	1:�����е��ж�
sbit  EADC    = IE ^ 6;	//ADC�ж�ʹ�ܿ���	    0:�ر�ADC�ж�		1:��ADC�ж�
sbit  ET2     = IE ^ 5;	//Timer2�ж�ʹ�ܿ���	0:�ر�Timer2�ж�    1:��Timer2�ж�
sbit  EUART   = IE ^ 4;	//UART�ж�ʹ�ܿ���	0:�ر�UART�ж�		1:��UART�ж�
sbit  ET1     = IE ^ 3;	//Timer1�ж�ʹ�ܿ���	0:�ر�TIMER1�ж�	1:��TIMER1�ж�
sbit  EINT1   = IE ^ 2;	//INT1�ж�ʹ�ܿ���	0:�ر�INT1�ж�		1:��INT1�ж�
sbit  ET0	  = IE ^ 1;	//Timer0�ж�ʹ�ܿ���	0:�ر�TIMER0�ж�	1:��TIMER0�ж�
sbit  EINT0   = IE ^ 0;	//INT0�ж�ʹ�ܿ���	0:�ر�INT0�ж�      1:��INT0�ж�

/*TCON*/
sbit  TF1	  = TCON ^
              7;	//T1����ж������־λ	T1��������������ж�ʱ��Ӳ����TF1��Ϊ��1���������жϣ�CPU��Ӧʱ��Ӳ���塰0����
sbit  TR1	  = TCON ^ 6;	//��ʱ��T1�����п���λ	0:Timer1��ֹ����		1:Timer1��ʼ����
sbit  TF0	  = TCON ^
              5;	//T0����ж������־λ	T0��������������ж�ʱ��Ӳ����TF0��Ϊ��1���������жϣ�CPU��Ӧʱ��Ӳ���塰0����
sbit  TR0	  = TCON ^ 4;	//��ʱ��T0�����п���λ	0:Timer0��ֹ����		1:Timer0��ʼ����

/*SCON*/
sbit  SM0	  = SCON ^ 7;
sbit  SM1	  = SCON ^ 6;
sbit  SM2	  = SCON ^ 5;
sbit  REN	  = SCON ^ 4;
sbit  TB8	  = SCON ^ 3;
sbit  RB8	  = SCON ^ 2;
sbit  TI	  = SCON ^ 1;
sbit  RI	  = SCON ^ 0;

/******************* P0 ******************
*SC95F8617��װδ�����Ĺܽţ���
*SC95F8616��װδ�����Ĺܽţ���
*SC95F8615��װδ�����Ĺܽţ�P00/P01/P02/P03
*SC95F8613��װδ�����Ĺܽţ�P00/P01/P02/P03
*SC95F8612��װδ�����Ĺܽţ�P00/P01/P02/P03
******************************************/
sbit 	P07	= P0 ^ 7;
sbit 	P06	= P0 ^ 6;
sbit 	P05	= P0 ^ 5;
sbit 	P04	= P0 ^ 4;
sbit 	P03	= P0 ^ 3;
sbit 	P02	= P0 ^ 2;
sbit 	P01	= P0 ^ 1;
sbit 	P00	= P0 ^ 0;

/******************* P1 ******************
*SC95F8617��װδ�����Ĺܽţ���
*SC95F8616��װδ�����Ĺܽţ���
*SC95F8615��װδ�����Ĺܽţ�P14/P15/P16/P17
*SC95F8613��װδ�����Ĺܽţ�P14/P15/P16/P17
*SC95F8612��װδ�����Ĺܽţ�P14/P15/P16/P17
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
*SC95F8617��װδ�����Ĺܽţ���
*SC95F8616��װδ�����Ĺܽţ���
*SC95F8615��װδ�����Ĺܽţ���
*SC95F8613��װδ�����Ĺܽţ���
*SC95F8612��װδ�����Ĺܽţ�P24/P25/P26/P27
******************************************/
sbit 	P27	= P2 ^ 7;
sbit 	P26	= P2 ^ 6;
sbit 	P25	= P2 ^ 5;
sbit 	P24	= P2 ^ 4;
sbit 	P23	= P2 ^ 3;
sbit 	P22	= P2 ^ 2;
sbit 	P21	= P2 ^ 1;
sbit 	P20	= P2 ^ 0;

/******************* P3 ******************
*SC95F8617��װδ�����Ĺܽţ���
*SC95F8616��װδ�����Ĺܽţ���
*SC95F8615��װδ�����Ĺܽţ�P34/P35/P36/P37
*SC95F8613��װδ�����Ĺܽţ�P34/P35/P36/P37
*SC95F8612��װδ�����Ĺܽţ�P3
******************************************/
sbit 	P37	= P3 ^ 7;
sbit 	P36	= P3 ^ 6;
sbit 	P35	= P3 ^ 5;
sbit 	P34	= P3 ^ 4;
sbit 	P33	= P3 ^ 3;
sbit 	P32	= P3 ^ 2;
sbit 	P31	= P3 ^ 1;
sbit 	P30	= P3 ^ 0;

/******************* P4 ******************
*SC95F8617��װδ�����Ĺܽţ���
*SC95F8616��װδ�����Ĺܽţ�P46/P47
*SC95F8615��װδ�����Ĺܽţ�P46/P47
*SC95F8613��װδ�����Ĺܽţ�P46/P47
*SC95F8612��װδ�����Ĺܽţ�P46/P47
******************************************/
sbit 	P47	= P4 ^ 7;
sbit 	P46	= P4 ^ 6;
sbit 	P45	= P4 ^ 5;
sbit 	P44	= P4 ^ 4;
sbit 	P43	= P4 ^ 3;
sbit 	P42	= P4 ^ 2;
sbit 	P41	= P4 ^ 1;
sbit 	P40	= P4 ^ 0;

/******************* P5 ******************
*SC95F8617��װδ�����Ĺܽţ���
*SC95F8616��װδ�����Ĺܽţ�P54/P55
*SC95F8615��װδ�����Ĺܽţ�P54/P55
*SC95F8613��װδ�����Ĺܽţ�P5
*SC95F8612��װδ�����Ĺܽţ�P5
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
*����ѡSC95F7517�����õ��ú궨�塣
*����ѡSC95F7617�����õ��ú궨�塣
*****************************************************************************/                                    
#define  SC95F7516_NIO_Init()   {P4CON|=0xC0,P5CON|=0x30;}                                                 //SC95F7516��δ��������IO������
#define  SC95F7515_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P3CON|=0xF0,P4CON|=0xC0,P5CON|=0x30;}             //SC95F7515��δ��������IO������
#define  SC95F7513_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P3CON|=0xF0,P4CON|=0xC0,P5CON|=0x3F;}             //SC95F7513��δ��������IO������
#define  SC95F7512_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P2CON|=0xF0,P3CON|=0xFF,P4CON|=0xC0,P5CON|=0x3F;} //SC95F7512��δ��������IO������

#define  SC95F7619_NIO_Init()   {P0CON|=0x01,P3CON|=0xFF,P4CON|=0x01,P5CON|=0x3F;}                         //SC95F7619��δ��������IO������
#define  SC95F7616_NIO_Init()   {P4CON|=0xC0,P5CON|=0x30;}                                                 //SC95F7616��δ��������IO������
#define  SC95F7615_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P3CON|=0xF0,P4CON|=0xC0,P5CON|=0x30;}             //SC95F7615��δ��������IO������
#define  SC95F7613_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P3CON|=0xF0,P4CON|=0xC0,P5CON|=0x3F;}             //SC95F7613��δ��������IO������
#define  SC95F7612_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P2CON|=0xF0,P3CON|=0xFF,P4CON|=0xC0,P5CON|=0x3F;} //SC95F7612��δ��������IO������

#endif