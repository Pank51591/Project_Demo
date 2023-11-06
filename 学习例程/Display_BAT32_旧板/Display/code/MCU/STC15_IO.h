#ifndef	STC15_IO_H
#define	STC15_IO_H

//#include"typedef.h"
//**************************************************************************************
//--------------------IO�� Init-------------------------------------------------------------

#define	PULL_UP		0	//����׼˫���
#define	HIGH_Z		1	//��������
#define	OUT_OD		2	//��©���
#define	OUT_PP		3	//�������

#define	GPIO_MODE_PULL_UP(gpio,Pin)	gpio##M1 &= ~(0x01<<Pin),	gpio##M0 &= ~(0x01<<Pin)	//����׼˫���
#define	GPIO_MODE_HIGH_Z(gpio,Pin)	gpio##M1 |=  (0x01<<Pin),	gpio##M0 &= ~(0x01<<Pin)	 //��������
#define	GPIO_MODE_OUT_OD(gpio,Pin)	gpio##M1 |=  (0x01<<Pin),	gpio##M0 |=  (0x01<<Pin)	 //��©���
#define	GPIO_MODE_OUT_PP(gpio,Pin)	gpio##M1 &= ~(0x01<<Pin),	gpio##M0 |=  (0x01<<Pin)	 //�������


#define GPIO_MODE_SET(gpio,Pin,mode)	GPIO_MODE_##mode(gpio,Pin)

#define HIGH 1
#define LOW  0

#define GPIO_OUT_HIGH(gpio,Pin)	GPIO_OUT_1(gpio,Pin)
#define GPIO_OUT_LOW(gpio,Pin)	GPIO_OUT_0(gpio,Pin)
#define GPIO_OUT_1(gpio,Pin)	GPIO |= (0x01<<Pin)
#define GPIO_OUT_0(gpio,Pin)	GPIO &= ~(0x01<<Pin)

#define GPIO_Inilize(gpio,Pin,mode,out)	GPIO_MODE_##mode(gpio,Pin);GPIO_OUT_##out(gpio,Pin)//GPIO ΪGPIO�ڣ�PinΪ�ڼ�PIN��modeΪģʽ��outΪ�������


#define GpioOutPut(gpio,Pin,out)	GPIO_OUT_##out(gpio,Pin)//GPIO�������		

#define GPIOMODE() do{}while(0);

//--------------------IO�ڶ�ȡ---------------------------------------------------------

 
#define GpioGetState(gpio,Pin)     ((BOOL)(gpio&(0X01<<Pin)))//��ȡIO�˿ڵ�״̬  
 

//**************************************************************************************
//--------------------IO��-------------------------------------------------------------

#define	P_PA    P0
#define	P_PB    P1
#define	P_PC    P2
#define	P_PD    P3
#define	P_PE    P4
#define	P_PF    P5
#define	P_PG    P6
#define	P_PH    P7

//*************************************************************************************
//----------------------IO�ڷ�������-------------------------------------------------

#define	P_PAIN		P0M1 = 0xff,	P0M0 = 0	 //����P0��Ϊ��������
#define	P_PAOUT		P0M1 = 0,		P0M0 = 0	//����P0��Ϊ˫�����������

#define	P_PBIN		P1M1 = 0xff,	P1M0 = 0	//����P1��Ϊ��������
#define	P_PBOUT		P1M1 = 0,		P1M0 = 0	//����P1��Ϊ˫�����������
									
#define	P_PCIN		P2M1 = 0xff,	P2M0 = 0	//����P2��Ϊ��������
#define	P_PCOUT		P2M1 = 0,		P2M0 = 0	//����P2��Ϊ˫�����������

#define	P_PDIN		P3M1 = 0xff,	P3M0 = 0	//����PD��Ϊ��������
#define	P_PDOUT		P3M1 = 0,		P3M0 = 0	//����PD��Ϊ˫�����������

#define	P_PEIN		P4M1 = 0xff,	P4M0 = 0	//����PE��Ϊ��������
#define	P_PEOUT		P4M1 = 0,		P4M0 = 0	//����PE��Ϊ˫�����������

#define	P_PFIN		P5M1 = 0xff,	P5M0 = 0	//����PF��Ϊ��������
#define	P_PFOUT		P5M1 = 0,		P5M0 = 0	//����PF��Ϊ˫�����������

#define	P_PGIN		P6M1 = 0xff,	P6M0 = 0	//����PG��Ϊ��������
#define	P_PGOUT		P6M1 = 0,		P6M0 = 0	//����PG��Ϊ˫�����������

#define	P_PHIN		P7M1 = 0xff,	P7M0 = 0	//����PH��Ϊ��������
#define	P_PHOUT		P7M1 = 0,		P7M0 = 0	//����PH��Ϊ˫�����������

#define	P_PAIN_BIT(x)	P0M1 |= (0x01<<x),	P0M0 &= ~(0x01<<x) //����PA�ڵĵ�XλΪ����
#define	P_PAOUT_BIT(x)	P0M1 &= ~(0x01<<x),	P0M0 &= ~(0x01<<x)  //����PA�ڵĵ�XλΪ���	

#define	P_PBIN_BIT(x)	P1M1 |= (0x01<<x),	P1M0 &= ~(0x01<<x) //����PB�ڵĵ�XλΪ����
#define	P_PBOUT_BIT(x)	P1M1 &= ~(0x01<<x),	P1M0 &= ~(0x01<<x)  //����PB�ڵĵ�XλΪ���

#define	P_PCIN_BIT(x)	P2M1 |= (0x01<<x),	P2M0 &= ~(0x01<<x) //����PC�ڵĵ�XλΪ����
#define	P_PCOUT_BIT(x)	P2M1 &= ~(0x01<<x),	P2M0 &= ~(0x01<<x)  //����PC�ڵĵ�XλΪ���

#define	P_PDIN_BIT(x)	P3M1 |= (0x01<<x),	P3M0 &= ~(0x01<<x) //����PD�ڵĵ�XλΪ����
#define	P_PDOUT_BIT(x)	P3M1 &= ~(0x01<<x),	P3M0 &= ~(0x01<<x)  //����PD�ڵĵ�XλΪ���

#define	P_PEIN_BIT(x)	P4M1 |= (0x01<<x),	P4M0 &= ~(0x01<<x) //����PE�ڵĵ�XλΪ����
#define	P_PEOUT_BIT(x)	P4M1 &= ~(0x01<<x),	P4M0 &= ~(0x01<<x)  //����PE�ڵĵ�XλΪ���

#define	P_PFIN_BIT(x)	P5M1 |= (0x01<<x),	P5M0 &= ~(0x01<<x) //����PF�ڵĵ�XλΪ����
#define	P_PFOUT_BIT(x)	P5M1 &= ~(0x01<<x),	P5M0 &= ~(0x01<<x)  //����PF�ڵĵ�XλΪ���

#define	P_PGIN_BIT(x)	P6M1 |= (0x01<<x),	P6M0 &= ~(0x01<<x) //����PG�ڵĵ�XλΪ����
#define	P_PGOUT_BIT(x)	P6M1 &= ~(0x01<<x),	P6M0 &= ~(0x01<<x)  //����PG�ڵĵ�XλΪ���

#define	P_PHIN_BIT(x)	P7M1 |= (0x01<<x),	P7M0 &= ~(0x01<<x) //����PH�ڵĵ�XλΪ����
#define	P_PHOUT_BIT(x)	P7M1 &= ~(0x01<<x),	P7M0 &= ~(0x01<<x)  //����PH�ڵĵ�XλΪ���

//***************************************************************************************
//---------------------IO��������������-----------------------------------------------
 
#define	P_PAUP          //P0 = 0xff	//����PA��Ϊ��������
#define	P_PADOWN        //P0 = 0x00	//����PA��Ϊ��������

#define	P_PBUP          //P1 = 0xff	//����PB��Ϊ��������
#define	P_PBDOWN        //P1 = 0x00	//����PB��Ϊ��������

#define	P_PCUP          //P2 = 0xff	//����PC��Ϊ��������
#define	P_PCDOWN        //P2 = 0x00	//����PC��Ϊ��������

#define	P_PDUP          //P3 = 0xff	//����PD��Ϊ��������
#define	P_PDDOWN        //P3 = 0x00	//����PD��Ϊ��������

#define	P_PEUP          //P4 = 0xff	//����PE��Ϊ��������
#define	P_PEDOWN        //P4 = 0x00	//����PE��Ϊ��������

#define	P_PAUP_BIT(x)	//P0 |= (0x01<<x)	  //����PA�ڵĵ�xλΪ��������
#define	P_PADOWN_BIT(x)	//P0 &= ~(0x01<<x)  //����PA�ڵĵ�xλΪ��������

#define	P_PBUP_BIT(x)	//P1 |= (0x01<<x)   //����PB�ڵĵ�xλΪ��������
#define	P_PBDOWN_BIT(x)	//P1 &= ~(0x01<<x)  //����PB�ڵĵ�xλΪ��������

#define	P_PCUP_BIT(x)	//P2 |= (0x01<<x)	  //����PC�ڵĵ�xλΪ��������
#define	P_PCDOWN_BIT(x)	//P2 &= ~(0x01<<x)  //����PC�ڵĵ�xλΪ��������

#define	P_PDUP_BIT(x)	//P3 |= (0x01<<x)	  //����PD�ڵĵ�xλΪ��������
#define	P_PDDOWN_BIT(x)	//P3 &= ~(0x01<<x)  //����PD�ڵĵ�xλΪ��������

#define	P_PEUP_BIT(x)	//P4 |= (0x01<<x)	  //����PE�ڵĵ�xλΪ��������
#define	P_PEDOWN_BIT(x)	//P4 &= ~(0x01<<x)  //����PE�ڵĵ�xλΪ��������

//***************************************************************************************
//---------------------IO�����⣬��©����---------------------------------------------

#define	P_PAPUSH_BIT(x)	P0M1 &= ~(0x01<<x),	P0M0 |= (0x01<<x)  //����P�ڵ�xλΪ������� ǿ����
#define	P_PAOPEN_BIT(x)	P0M1 |= (0x01<<x),	P0M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PBPUSH_BIT(x)	P1M1 &= ~(0x01<<x),	P1M0 |= (0x01<<x)  //����P�ڵ�xλΪ������� ǿ����
#define	P_PBOPEN_BIT(x)	P1M1 |= (0x01<<x),	P1M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PCPUSH_BIT(x)	P2M1 &= ~(0x01<<x),	P2M0 |= (0x01<<x)  //����P�ڵ�xλΪ������� ǿ����
#define	P_PCOPEN_BIT(x)	P2M1 |= (0x01<<x),	P2M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PDPUSH_BIT(x)	P3M1 &= ~(0x01<<x),	P3M0 |= (0x01<<x)  //����P�ڵ�xλΪ������� ǿ����
#define	P_PDOPEN_BIT(x)	P3M1 |= (0x01<<x),	P3M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PEPUSH_BIT(x)	P4M1 &= ~(0x01<<x),	P4M0 |= (0x01<<x)	 //����P�ڵ�xλΪ������� ǿ����
#define	P_PEOPEN_BIT(x)	P4M1 |= (0x01<<x),	P4M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PFPUSH_BIT(x)	P5M1 &= ~(0x01<<x),	P5M0 |= (0x01<<x)	 //����P�ڵ�xλΪ������� ǿ����
#define	P_PFOPEN_BIT(x)	P5M1 |= (0x01<<x),	P5M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PGPUSH_BIT(x)	P6M1 &= ~(0x01<<x),	P6M0 |= (0x01<<x)	 //����P�ڵ�xλΪ������� ǿ����
#define	P_PGOPEN_BIT(x)	P6M1 |= (0x01<<x),	P6M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PHPUSH_BIT(x)	P7M1 &= ~(0x01<<x),	P7M0 |= (0x01<<x)	 //����P�ڵ�xλΪ������� ǿ����
#define	P_PHOPEN_BIT(x)	P7M1 |= (0x01<<x),	P7M0 |= (0x01<<x) //����P�ڵ�xλΪ��©���

//*************************************************************************************
//---------------------IO�������ƽ����---------------------------------------------

#define	P_PAHIGH    P0 = 0xff      //PA������ߵ�ƽ
#define	P_PALOW     P0 = 0x00      //PA������͵�ƽ

#define	P_PBHIGH    P1 = 0xff	   //PB������ߵ�ƽ
#define	P_PBLOW     P1 = 0x00	   //PB������͵�ƽ

#define	P_PCHIGH    P2 = 0xff	   //PC������ߵ�ƽ
#define	P_PCLOW	    P2 = 0x00	   //PC������͵�ƽ

#define	P_PDHIGH    P3 = 0xff	   //PD������ߵ�ƽ
#define	P_PDLOW	    P3 = 0x00	   //PD������͵�ƽ

#define	P_PEHIGH    P4 = 0xff      //PE������ߵ�ƽ
#define	P_PELOW	    P4 = 0x00	   //PE������͵�ƽ

#define	P_PFHIGH    P5 = 0xff      //PE������ߵ�ƽ
#define	P_PFLOW	    P5 = 0x00	   //PE������͵�ƽ

#define	P_PGHIGH    P6 = 0xff      //PE������ߵ�ƽ
#define	P_PGLOW	    P6 = 0x00	   //PE������͵�ƽ

#define	P_PHHIGH    P7 = 0xff      //PE������ߵ�ƽ
#define	P_PHLOW	    P7 = 0x00	   //PE������͵�ƽ

#define	P_PAHIGH_BIT(x) P0 |= (0x01<<x)  //PA�ĵ�xλ����ߵ�ƽ
#define	P_PALOW_BIT(x)  P0 &= ~(0x01<<x) //PA�ĵ�Xλ����͵�ƽ

#define	P_PBHIGH_BIT(x) P1 |= (0x01<<x)  //PB�ĵ�xλ����ߵ�ƽ
#define	P_PBLOW_BIT(x)  P1 &= ~(0x01<<x) //PB�ĵ�Xλ����͵�ƽ

#define	P_PCHIGH_BIT(x) P2 |= (0x01<<x)  //PC�ĵ�xλ����ߵ�ƽ
#define	P_PCLOW_BIT(x)  P2 &= ~(0x01<<x) //PC�ĵ�Xλ����͵�ƽ

#define	P_PDHIGH_BIT(x) P3 |= (0x01<<x)  //PD�ĵ�xλ����ߵ�ƽ
#define	P_PDLOW_BIT(x)  P3 &= ~(0x01<<x) //PD�ĵ�Xλ����͵�ƽ

#define	P_PEHIGH_BIT(x) P4 |= (0x01<<x)  //PE�ĵ�xλ����ߵ�ƽ
#define	P_PELOW_BIT(x)  P4 &= ~(0x01<<x) //PE�ĵ�Xλ����͵�ƽ

#define	P_PFHIGH_BIT(x) P5 |= (0x01<<x)  //PF�ĵ�xλ����ߵ�ƽ
#define	P_PFLOW_BIT(x)  P5 &= ~(0x01<<x) //PF�ĵ�Xλ����͵�ƽ

#define	P_PGHIGH_BIT(x) P6 |= (0x01<<x)  //PG�ĵ�xλ����ߵ�ƽ
#define	P_PGLOW_BIT(x)  P6 &= ~(0x01<<x) //PG�ĵ�Xλ����͵�ƽ

#define	P_PHHIGH_BIT(x) P7 |= (0x01<<x)  //PH�ĵ�xλ����ߵ�ƽ
#define	P_PHLOW_BIT(x)  P7 &= ~(0x01<<x) //PH�ĵ�Xλ����͵�ƽ

//************************************************************************************
//---------------------IO��������---------------------------------------------------

//---------------------��ȡIO��״̬-------------------------------------------------

#define	P_PAREAD   P0
#define	P_PBREAD   P1
#define	P_PCREAD   P2
#define	P_PDREAD   P3
#define	P_PEREAD   P4
#define	P_PFREAD   P5
#define	P_PGREAD   P6
#define	P_PHREAD   P7

//--------------------��ȡIO��λ״̬----------------------------------------------

#define	P_PAREAD_BIT(X)    (BOOL)(P0&(0X01<<X))
#define	P_PBREAD_BIT(X)    (BOOL)(P1&(0X01<<X))
#define	P_PCREAD_BIT(X)    (BOOL)(P2&(0X01<<X))
#define	P_PDREAD_BIT(X)    (BOOL)(P3&(0X01<<X))
#define	P_PEREAD_BIT(X)    (BOOL)(P4&(0X01<<X))
#define	P_PFREAD_BIT(X)    (BOOL)(P5&(0X01<<X))
#define	P_PGREAD_BIT(X)    (BOOL)(P6&(0X01<<X))
#define	P_PHREAD_BIT(X)    (BOOL)(P7&(0X01<<X))

//**********************************************************************************

#endif











