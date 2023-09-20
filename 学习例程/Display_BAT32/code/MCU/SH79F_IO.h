#ifndef	SH79FXX_H
#define	SH79FXX_H

//********************************************************************************************************
//--------------------IO��-------------------------------------------------------------------------------

#define	P_PA    P0
#define	P_PB    P1
#define	P_PC    P2
#define	P_PD    P3
#define	P_PE    P4

//**********************************************************************************************************
//----------------------IO�ڷ�������----------------------------------------------------------------------


#define	P_PAIN      P0CR = 0x00	//����P0��Ϊ����
#define	P_PAOUT     P0CR = 0xff	//����P0��Ϊ���

#define	P_PBIN      P1CR = 0x00	//����P1��Ϊ����
#define	P_PBOUT     P1CR = 0xff	//����P1��Ϊ���

#define	P_PCIN      P2CR = 0x00	//����P2��Ϊ����
#define	P_PCOUT     P2CR = 0xff	//����P2��Ϊ���

#define	P_PDIN      P3CR = 0x00	//����P3��Ϊ����
#define	P_PDOUT     P3CR = 0xff	//����P3��Ϊ���

#define	P_PEIN      P4CR = 0x00	//����P4��Ϊ����
#define	P_PEOUT     P4CR = 0xff	//����P4��Ϊ���

#define	P_PAIN_BIT(x)   P0CR &= ~(0x01<<x)	//����P0�ڵĵ�XλΪ����
#define	P_PAOUT_BIT(x)  P0CR |= (0x01<<x)	//����P0�ڵĵ�XλΪ���	

#define	P_PBIN_BIT(x)   P1CR &= ~(0x01<<x)	//����P0�ڵĵ�XλΪ����
#define	P_PBOUT_BIT(x)	P1CR |= (0x01<<x)	//����P0�ڵĵ�XλΪ���

#define	P_PCIN_BIT(x)   P2CR &= ~(0x01<<x)	//����P0�ڵĵ�XλΪ����
#define	P_PCOUT_BIT(x)  P2CR |= (0x01<<x)	//����P0�ڵĵ�XλΪ���

#define	P_PDIN_BIT(x)   P3CR &= ~(0x01<<x)	//����P0�ڵĵ�XλΪ����
#define	P_PDOUT_BIT(x)  P3CR |= (0x01<<x)	//����P0�ڵĵ�XλΪ���

#define	P_PEIN_BIT(x)   P4CR &= ~(0x01<<x)	//����P0�ڵĵ�XλΪ����
#define	P_PEOUT_BIT(x)  P4CR |= (0x01<<x)	//����P0�ڵĵ�XλΪ���

//*********************************************************************************************************
//---------------------IO��������������-----------------------------------------------------------------

#define	P_PAUP          P0P_PCR = 0xff	//����P0��Ϊ��������
#define	P_PADOWN        P0P_PCR = 0x00	//����P0��Ϊ��������

#define	P_PBUP          P1P_PCR = 0xff	//����P1��Ϊ��������
#define	P_PBDOWN        P1P_PCR = 0x00	//����P1��Ϊ��������

#define	P_PCUP          P2P_PCR = 0xff	//����P2��Ϊ��������
#define	P_PCDOWN        P2P_PCR = 0x00	//����P2��Ϊ��������

#define	P_PDUP          P3P_PCR = 0xff	//����P3��Ϊ��������
#define	P_PDDOWN        P3P_PCR = 0x00	//����P3��Ϊ��������

#define	P_PEUP          P4P_PCR = 0xff	//����P4��Ϊ��������
#define	P_PEDOWN        P4P_PCR = 0x00	//����P4��Ϊ��������

#define	P_PAUP_BIT(x)   P0P_PCR |= (0x01<<x)    //����P0�ڵĵ�xλΪ��������
#define	P_PADOWN_BIT(x) P0P_PCR &= ~(0x01<<x)   //����P0�ڵĵ�xλΪ��������

#define	P_PBUP_BIT(x)   P1P_PCR |= (0x01<<x)    //����P1�ڵĵ�xλΪ��������
#define	P_PBDOWN_BIT(x) P1P_PCR &= ~(0x01<<x)   //����P1�ڵĵ�xλΪ��������

#define	P_PCUP_BIT(x)   P2P_PCR |= (0x01<<x)    //����P2�ڵĵ�xλΪ��������
#define	P_PCDOWN_BIT(x) P2P_PCR &= ~(0x01<<x)   //����P2�ڵĵ�xλΪ��������

#define	P_PDUP_BIT(x)   P3P_PCR |= (0x01<<x)    //����P3�ڵĵ�xλΪ��������
#define	P_PDDOWN_BIT(x) P3P_PCR &= ~(0x01<<x)   //����P3�ڵĵ�xλΪ��������

#define	P_PEUP_BIT(x)   P4P_PCR |= (0x01<<x)    //����P4�ڵĵ�xλΪ��������
#define	P_PEDOWN_BIT(x) P4P_PCR &= ~(0x01<<x)   //����P4�ڵĵ�xλΪ��������

//**************************************************************************************************
//---------------------IO�����⣬��©����--------------------------------------------------------

#define	P_PAPUSH_BIT(x)     P0OS |= (0x01<<x)   //����P�ڵ�xλΪ�������
#define	P_PAOP_PEN_BIT(x)   P0OS &= ~(0x01<<x)  //����P�ڵ�xλΪ��©���

#define	P_PBPUSH_BIT(x)     P1OS |= (0x01<<x)   //����P�ڵ�xλΪ�������
#define	P_PBOP_PEN_BIT(x)   P1OS &= ~(0x01<<x)  //����P�ڵ�xλΪ��©���

#define	P_PCPUSH_BIT(x)     P2OS |= (0x01<<x)   //����P�ڵ�xλΪ�������
#define	P_PCOP_PEN_BIT(x)   P2OS &= ~(0x01<<x)  //����P�ڵ�xλΪ��©���

#define	P_PDPUSH_BIT(x)     P3OS |= (0x01<<x)   //����P�ڵ�xλΪ�������
#define	P_PDOP_PEN_BIT(x)   P3OS &= ~(0x01<<x)  //����P�ڵ�xλΪ��©���

#define	P_PEPUSH_BIT(x)     P4OS |= (0x01<<x)   //����P�ڵ�xλΪ�������
#define	P_PEOP_PEN_BIT(x)   P4OS &= ~(0x01<<x)  //����P�ڵ�xλΪ��©���

//**********************************************************************************************
//---------------------IO�������ƽ����------------------------------------------------------

#define	P_PAHIGH    P0 = 0xff   //P0������ߵ�ƽ
#define	P_PALOW	    P0 = 0x00   //P0������͵�ƽ

#define	P_PBHIGH    P1 = 0xff   //P1������ߵ�ƽ
#define	P_PBLOW	    P1 = 0x00   //P1������͵�ƽ

#define	P_PCHIGH    P2 = 0xff   //P2������ߵ�ƽ
#define	P_PCLOW	    P2 = 0x00   //P2������͵�ƽ

#define	P_PDHIGH    P3 = 0xff   //P3������ߵ�ƽ
#define	P_PDLOW     P3 = 0x00   //P3������͵�ƽ

#define	P_PEHIGH    P4 = 0xff   //P4������ߵ�ƽ
#define	P_PELOW     P4 = 0x00   //P4������͵�ƽ

#define	P_PAHIGH_BIT(x) P0 |= (0x01<<x)     //P0�ĵ�xλ����ߵ�ƽ
#define	P_PALOW_BIT(x)  P0 &= ~(0x01<<x)    //P0�ĵ�Xλ����͵�ƽ

#define	P_PBHIGH_BIT(x) P1 |= (0x01<<x)     //P1�ĵ�xλ����ߵ�ƽ
#define	P_PBLOW_BIT(x)  P1 &= ~(0x01<<x)    //P1�ĵ�Xλ����͵�ƽ

#define	P_PCHIGH_BIT(x) P2 |= (0x01<<x)     //P2�ĵ�xλ����ߵ�ƽ
#define	P_PCLOW_BIT(x)  P2 &= ~(0x01<<x)    //P2�ĵ�Xλ����͵�ƽ

#define	P_PDHIGH_BIT(x) P3 |= (0x01<<x)     //P3�ĵ�xλ����ߵ�ƽ
#define	P_PDLOW_BIT(x)  P3 &= ~(0x01<<x)    //P3�ĵ�Xλ����͵�ƽ

#define	P_PEHIGH_BIT(x) P4 |= (0x01<<x)     //P4�ĵ�xλ����ߵ�ƽ
#define	P_PELOW_BIT(x)  P4 &= ~(0x01<<x)    //P4�ĵ�Xλ����͵�ƽ


//******************************************************************************************
//---------------------IO��������---------------------------------------------------------

//---------------------��ȡIO��״̬-------------------------------------------------------

#define	P_PAREAD   P0
#define	P_PBREAD   P1
#define	P_PCREAD   P2
#define	P_PDREAD   P3
#define	P_PEREAD   P4

//--------------------��ȡIO��λ״̬----------------------------------------------------

#define	P_PAREAD_BIT(X)    (BOOL)(P0&(0X01<<X))
#define	P_PBREAD_BIT(X)    (BOOL)(P1&(0X01<<X))
#define	P_PCREAD_BIT(X)    (BOOL)(P2&(0X01<<X))
#define	P_PDREAD_BIT(X)    (BOOL)(P3&(0X01<<X))
#define	P_PEREAD_BIT(X)    (BOOL)(P4&(0X01<<X))

//****************************************************************************************

#endif











