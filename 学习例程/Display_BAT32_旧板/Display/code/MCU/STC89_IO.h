#ifndef	STC89_IO_H
#define	STC89_IO_H

#include"typedef.h"
//**************************************************************************************
//--------------------IO��-------------------------------------------------------------

#define	P_PA    P0
#define	P_PB    P1
#define	P_PC    P2
#define	P_PD    P3
#define	P_PE    P4

//*************************************************************************************
//----------------------IO�ڷ�������-------------------------------------------------

#define	P_PAIN		P0 = 0x00	//����P0��Ϊ����
#define	P_PAOUT		P0 = 0xff	//����P0��Ϊ���

#define	P_PBIN		P1 = 0x00	//����P1��Ϊ����
#define	P_PBOUT		P1 = 0xff	//����P1��Ϊ���

#define	P_PCIN		P2 = 0x00	//����P2��Ϊ����
#define	P_PCOUT		P2 = 0xff	//����P2��Ϊ���

#define	P_PDIN		P3 = 0x00	//����PD��Ϊ����
#define	P_PDOUT		P3 = 0xff	//����PD��Ϊ���

#define	P_PEIN		P4 = 0x00	//����PE��Ϊ����
#define	P_PEOUT		P4 = 0xff	//����PE��Ϊ���

#define	P_PAIN_BIT(x)	P0 &= ~(0x01<<x) //����PA�ڵĵ�XλΪ����
#define	P_PAOUT_BIT(x)	P0 |= (0x01<<x)  //����PA�ڵĵ�XλΪ���	

#define	P_PBIN_BIT(x)	P1 &= ~(0x01<<x) //����PA�ڵĵ�XλΪ����
#define	P_PBOUT_BIT(x)	P1 |= (0x01<<x)  //����PA�ڵĵ�XλΪ���

#define	P_PCIN_BIT(x)	P2 &= ~(0x01<<x) //����PA�ڵĵ�XλΪ����
#define	P_PCOUT_BIT(x)	P2 |= (0x01<<x)  //����PA�ڵĵ�XλΪ���

#define	P_PDIN_BIT(x)	P3 &= ~(0x01<<x) //����PA�ڵĵ�XλΪ����
#define	P_PDOUT_BIT(x)	P3 |= (0x01<<x)  //����PA�ڵĵ�XλΪ���

#define	P_PEIN_BIT(x)	P4 &= ~(0x01<<x) //����PA�ڵĵ�XλΪ����
#define	P_PEOUT_BIT(x)	P4 |= (0x01<<x)  //����PA�ڵĵ�XλΪ���

//***************************************************************************************
//---------------------IO��������������-----------------------------------------------
 
#define	P_PAUP          P0 = 0xff	//����PA��Ϊ��������
#define	P_PADOWN        P0 = 0x00	//����PA��Ϊ��������

#define	P_PBUP          P1 = 0xff	//����PB��Ϊ��������
#define	P_PBDOWN        P1 = 0x00	//����PB��Ϊ��������

#define	P_PCUP          P2 = 0xff	//����PC��Ϊ��������
#define	P_PCDOWN        P2 = 0x00	//����PC��Ϊ��������

#define	P_PDUP          P3 = 0xff	//����PD��Ϊ��������
#define	P_PDDOWN        P3 = 0x00	//����PD��Ϊ��������

#define	P_PEUP          P4 = 0xff	//����PE��Ϊ��������
#define	P_PEDOWN        P4 = 0x00	//����PE��Ϊ��������

#define	P_PAUP_BIT(x)	P0 |= (0x01<<x)	  //����PA�ڵĵ�xλΪ��������
#define	P_PADOWN_BIT(x)	P0 &= ~(0x01<<x)  //����PA�ڵĵ�xλΪ��������

#define	P_PBUP_BIT(x)	P1 |= (0x01<<x)   //����PB�ڵĵ�xλΪ��������
#define	P_PBDOWN_BIT(x)	P1 &= ~(0x01<<x)  //����PB�ڵĵ�xλΪ��������

#define	P_PCUP_BIT(x)	P2 |= (0x01<<x)	  //����PC�ڵĵ�xλΪ��������
#define	P_PCDOWN_BIT(x)	P2 &= ~(0x01<<x)  //����PC�ڵĵ�xλΪ��������

#define	P_PDUP_BIT(x)	P3 |= (0x01<<x)	  //����PD�ڵĵ�xλΪ��������
#define	P_PDDOWN_BIT(x)	P3 &= ~(0x01<<x)  //����PD�ڵĵ�xλΪ��������

#define	P_PEUP_BIT(x)	P4 |= (0x01<<x)	  //����PE�ڵĵ�xλΪ��������
#define	P_PEDOWN_BIT(x)	P4 &= ~(0x01<<x)  //����PE�ڵĵ�xλΪ��������

//***************************************************************************************
//---------------------IO�����⣬��©����---------------------------------------------

#define	P_PAPUSH_BIT(x)	P0 |= (0x01<<x)  //����P�ڵ�xλΪ�������
#define	P_PAOPEN_BIT(x)	P0 &= ~(0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PBPUSH_BIT(x)	P1 |= (0x01<<x)  //����P�ڵ�xλΪ�������
#define	P_PBOPEN_BIT(x)	P1 &= ~(0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PCPUSH_BIT(x)	P2 |= (0x01<<x)  //����P�ڵ�xλΪ�������
#define	P_PCOPEN_BIT(x)	P2 &= ~(0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PDPUSH_BIT(x)	P3 |= (0x01<<x)  //����P�ڵ�xλΪ�������
#define	P_PDOPEN_BIT(x)	P3 &= ~(0x01<<x) //����P�ڵ�xλΪ��©���

#define	P_PEPUSH_BIT(x)	P4 |= (0x01<<x)	 //����P�ڵ�xλΪ�������
#define	P_PEOPEN_BIT(x)	P4 &= ~(0x01<<x) //����P�ڵ�xλΪ��©���

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



//************************************************************************************
//---------------------IO��������---------------------------------------------------

//---------------------��ȡIO��״̬-------------------------------------------------

#define	P_PAREAD   P0
#define	P_PBREAD   P1
#define	P_PCREAD   P2
#define	P_PDREAD   P3
#define	P_PEREAD   P4

//--------------------��ȡIO��λ״̬----------------------------------------------

#define	P_PAREAD_BIT(X)    (BOOL)(P0&(0X01<<X))
#define	P_PBREAD_BIT(X)    (BOOL)(P1&(0X01<<X))
#define	P_PCREAD_BIT(X)    (BOOL)(P2&(0X01<<X))
#define	P_PDREAD_BIT(X)    (BOOL)(P3&(0X01<<X))
#define	P_PEREAD_BIT(X)    (BOOL)(P4&(0X01<<X))

//**********************************************************************************

#endif











