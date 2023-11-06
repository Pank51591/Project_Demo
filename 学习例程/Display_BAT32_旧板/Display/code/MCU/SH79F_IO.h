#ifndef	SH79FXX_H
#define	SH79FXX_H

//********************************************************************************************************
//--------------------IO口-------------------------------------------------------------------------------

#define	P_PA    P0
#define	P_PB    P1
#define	P_PC    P2
#define	P_PD    P3
#define	P_PE    P4

//**********************************************************************************************************
//----------------------IO口方向设置----------------------------------------------------------------------


#define	P_PAIN      P0CR = 0x00	//设置P0口为输入
#define	P_PAOUT     P0CR = 0xff	//设置P0口为输出

#define	P_PBIN      P1CR = 0x00	//设置P1口为输入
#define	P_PBOUT     P1CR = 0xff	//设置P1口为输出

#define	P_PCIN      P2CR = 0x00	//设置P2口为输入
#define	P_PCOUT     P2CR = 0xff	//设置P2口为输出

#define	P_PDIN      P3CR = 0x00	//设置P3口为输入
#define	P_PDOUT     P3CR = 0xff	//设置P3口为输出

#define	P_PEIN      P4CR = 0x00	//设置P4口为输入
#define	P_PEOUT     P4CR = 0xff	//设置P4口为输出

#define	P_PAIN_BIT(x)   P0CR &= ~(0x01<<x)	//设置P0口的第X位为输入
#define	P_PAOUT_BIT(x)  P0CR |= (0x01<<x)	//设置P0口的第X位为输出	

#define	P_PBIN_BIT(x)   P1CR &= ~(0x01<<x)	//设置P0口的第X位为输入
#define	P_PBOUT_BIT(x)	P1CR |= (0x01<<x)	//设置P0口的第X位为输出

#define	P_PCIN_BIT(x)   P2CR &= ~(0x01<<x)	//设置P0口的第X位为输入
#define	P_PCOUT_BIT(x)  P2CR |= (0x01<<x)	//设置P0口的第X位为输出

#define	P_PDIN_BIT(x)   P3CR &= ~(0x01<<x)	//设置P0口的第X位为输入
#define	P_PDOUT_BIT(x)  P3CR |= (0x01<<x)	//设置P0口的第X位为输出

#define	P_PEIN_BIT(x)   P4CR &= ~(0x01<<x)	//设置P0口的第X位为输入
#define	P_PEOUT_BIT(x)  P4CR |= (0x01<<x)	//设置P0口的第X位为输出

//*********************************************************************************************************
//---------------------IO口上拉电阻设置-----------------------------------------------------------------

#define	P_PAUP          P0P_PCR = 0xff	//设置P0口为电阻上拉
#define	P_PADOWN        P0P_PCR = 0x00	//设置P0口为电阻下拉

#define	P_PBUP          P1P_PCR = 0xff	//设置P1口为电阻上拉
#define	P_PBDOWN        P1P_PCR = 0x00	//设置P1口为电阻下拉

#define	P_PCUP          P2P_PCR = 0xff	//设置P2口为电阻上拉
#define	P_PCDOWN        P2P_PCR = 0x00	//设置P2口为电阻下拉

#define	P_PDUP          P3P_PCR = 0xff	//设置P3口为电阻上拉
#define	P_PDDOWN        P3P_PCR = 0x00	//设置P3口为电阻下拉

#define	P_PEUP          P4P_PCR = 0xff	//设置P4口为电阻上拉
#define	P_PEDOWN        P4P_PCR = 0x00	//设置P4口为电阻下拉

#define	P_PAUP_BIT(x)   P0P_PCR |= (0x01<<x)    //设置P0口的第x位为电阻上拉
#define	P_PADOWN_BIT(x) P0P_PCR &= ~(0x01<<x)   //设置P0口的第x位为电阻下拉

#define	P_PBUP_BIT(x)   P1P_PCR |= (0x01<<x)    //设置P1口的第x位为电阻上拉
#define	P_PBDOWN_BIT(x) P1P_PCR &= ~(0x01<<x)   //设置P1口的第x位为电阻下拉

#define	P_PCUP_BIT(x)   P2P_PCR |= (0x01<<x)    //设置P2口的第x位为电阻上拉
#define	P_PCDOWN_BIT(x) P2P_PCR &= ~(0x01<<x)   //设置P2口的第x位为电阻下拉

#define	P_PDUP_BIT(x)   P3P_PCR |= (0x01<<x)    //设置P3口的第x位为电阻上拉
#define	P_PDDOWN_BIT(x) P3P_PCR &= ~(0x01<<x)   //设置P3口的第x位为电阻下拉

#define	P_PEUP_BIT(x)   P4P_PCR |= (0x01<<x)    //设置P4口的第x位为电阻上拉
#define	P_PEDOWN_BIT(x) P4P_PCR &= ~(0x01<<x)   //设置P4口的第x位为电阻下拉

//**************************************************************************************************
//---------------------IO口推免，开漏设置--------------------------------------------------------

#define	P_PAPUSH_BIT(x)     P0OS |= (0x01<<x)   //设置P口第x位为推免输出
#define	P_PAOP_PEN_BIT(x)   P0OS &= ~(0x01<<x)  //设置P口第x位为开漏输出

#define	P_PBPUSH_BIT(x)     P1OS |= (0x01<<x)   //设置P口第x位为推免输出
#define	P_PBOP_PEN_BIT(x)   P1OS &= ~(0x01<<x)  //设置P口第x位为开漏输出

#define	P_PCPUSH_BIT(x)     P2OS |= (0x01<<x)   //设置P口第x位为推免输出
#define	P_PCOP_PEN_BIT(x)   P2OS &= ~(0x01<<x)  //设置P口第x位为开漏输出

#define	P_PDPUSH_BIT(x)     P3OS |= (0x01<<x)   //设置P口第x位为推免输出
#define	P_PDOP_PEN_BIT(x)   P3OS &= ~(0x01<<x)  //设置P口第x位为开漏输出

#define	P_PEPUSH_BIT(x)     P4OS |= (0x01<<x)   //设置P口第x位为推免输出
#define	P_PEOP_PEN_BIT(x)   P4OS &= ~(0x01<<x)  //设置P口第x位为开漏输出

//**********************************************************************************************
//---------------------IO口输出电平设置------------------------------------------------------

#define	P_PAHIGH    P0 = 0xff   //P0口输出高电平
#define	P_PALOW	    P0 = 0x00   //P0口输出低电平

#define	P_PBHIGH    P1 = 0xff   //P1口输出高电平
#define	P_PBLOW	    P1 = 0x00   //P1口输出低电平

#define	P_PCHIGH    P2 = 0xff   //P2口输出高电平
#define	P_PCLOW	    P2 = 0x00   //P2口输出低电平

#define	P_PDHIGH    P3 = 0xff   //P3口输出高电平
#define	P_PDLOW     P3 = 0x00   //P3口输出低电平

#define	P_PEHIGH    P4 = 0xff   //P4口输出高电平
#define	P_PELOW     P4 = 0x00   //P4口输出低电平

#define	P_PAHIGH_BIT(x) P0 |= (0x01<<x)     //P0的第x位输出高电平
#define	P_PALOW_BIT(x)  P0 &= ~(0x01<<x)    //P0的第X位输出低电平

#define	P_PBHIGH_BIT(x) P1 |= (0x01<<x)     //P1的第x位输出高电平
#define	P_PBLOW_BIT(x)  P1 &= ~(0x01<<x)    //P1的第X位输出低电平

#define	P_PCHIGH_BIT(x) P2 |= (0x01<<x)     //P2的第x位输出高电平
#define	P_PCLOW_BIT(x)  P2 &= ~(0x01<<x)    //P2的第X位输出低电平

#define	P_PDHIGH_BIT(x) P3 |= (0x01<<x)     //P3的第x位输出高电平
#define	P_PDLOW_BIT(x)  P3 &= ~(0x01<<x)    //P3的第X位输出低电平

#define	P_PEHIGH_BIT(x) P4 |= (0x01<<x)     //P4的第x位输出高电平
#define	P_PELOW_BIT(x)  P4 &= ~(0x01<<x)    //P4的第X位输出低电平


//******************************************************************************************
//---------------------IO输入设置---------------------------------------------------------

//---------------------读取IO口状态-------------------------------------------------------

#define	P_PAREAD   P0
#define	P_PBREAD   P1
#define	P_PCREAD   P2
#define	P_PDREAD   P3
#define	P_PEREAD   P4

//--------------------读取IO口位状态----------------------------------------------------

#define	P_PAREAD_BIT(X)    (BOOL)(P0&(0X01<<X))
#define	P_PBREAD_BIT(X)    (BOOL)(P1&(0X01<<X))
#define	P_PCREAD_BIT(X)    (BOOL)(P2&(0X01<<X))
#define	P_PDREAD_BIT(X)    (BOOL)(P3&(0X01<<X))
#define	P_PEREAD_BIT(X)    (BOOL)(P4&(0X01<<X))

//****************************************************************************************

#endif











