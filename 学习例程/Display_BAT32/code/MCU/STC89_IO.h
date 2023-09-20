#ifndef	STC89_IO_H
#define	STC89_IO_H

#include"typedef.h"
//**************************************************************************************
//--------------------IO口-------------------------------------------------------------

#define	P_PA    P0
#define	P_PB    P1
#define	P_PC    P2
#define	P_PD    P3
#define	P_PE    P4

//*************************************************************************************
//----------------------IO口方向设置-------------------------------------------------

#define	P_PAIN		P0 = 0x00	//设置P0口为输入
#define	P_PAOUT		P0 = 0xff	//设置P0口为输出

#define	P_PBIN		P1 = 0x00	//设置P1口为输入
#define	P_PBOUT		P1 = 0xff	//设置P1口为输出

#define	P_PCIN		P2 = 0x00	//设置P2口为输入
#define	P_PCOUT		P2 = 0xff	//设置P2口为输出

#define	P_PDIN		P3 = 0x00	//设置PD口为输入
#define	P_PDOUT		P3 = 0xff	//设置PD口为输出

#define	P_PEIN		P4 = 0x00	//设置PE口为输入
#define	P_PEOUT		P4 = 0xff	//设置PE口为输出

#define	P_PAIN_BIT(x)	P0 &= ~(0x01<<x) //设置PA口的第X位为输入
#define	P_PAOUT_BIT(x)	P0 |= (0x01<<x)  //设置PA口的第X位为输出	

#define	P_PBIN_BIT(x)	P1 &= ~(0x01<<x) //设置PA口的第X位为输入
#define	P_PBOUT_BIT(x)	P1 |= (0x01<<x)  //设置PA口的第X位为输出

#define	P_PCIN_BIT(x)	P2 &= ~(0x01<<x) //设置PA口的第X位为输入
#define	P_PCOUT_BIT(x)	P2 |= (0x01<<x)  //设置PA口的第X位为输出

#define	P_PDIN_BIT(x)	P3 &= ~(0x01<<x) //设置PA口的第X位为输入
#define	P_PDOUT_BIT(x)	P3 |= (0x01<<x)  //设置PA口的第X位为输出

#define	P_PEIN_BIT(x)	P4 &= ~(0x01<<x) //设置PA口的第X位为输入
#define	P_PEOUT_BIT(x)	P4 |= (0x01<<x)  //设置PA口的第X位为输出

//***************************************************************************************
//---------------------IO口上拉电阻设置-----------------------------------------------
 
#define	P_PAUP          P0 = 0xff	//设置PA口为电阻上拉
#define	P_PADOWN        P0 = 0x00	//设置PA口为电阻下拉

#define	P_PBUP          P1 = 0xff	//设置PB口为电阻上拉
#define	P_PBDOWN        P1 = 0x00	//设置PB口为电阻下拉

#define	P_PCUP          P2 = 0xff	//设置PC口为电阻上拉
#define	P_PCDOWN        P2 = 0x00	//设置PC口为电阻下拉

#define	P_PDUP          P3 = 0xff	//设置PD口为电阻上拉
#define	P_PDDOWN        P3 = 0x00	//设置PD口为电阻下拉

#define	P_PEUP          P4 = 0xff	//设置PE口为电阻上拉
#define	P_PEDOWN        P4 = 0x00	//设置PE口为电阻下拉

#define	P_PAUP_BIT(x)	P0 |= (0x01<<x)	  //设置PA口的第x位为电阻上拉
#define	P_PADOWN_BIT(x)	P0 &= ~(0x01<<x)  //设置PA口的第x位为电阻下拉

#define	P_PBUP_BIT(x)	P1 |= (0x01<<x)   //设置PB口的第x位为电阻上拉
#define	P_PBDOWN_BIT(x)	P1 &= ~(0x01<<x)  //设置PB口的第x位为电阻下拉

#define	P_PCUP_BIT(x)	P2 |= (0x01<<x)	  //设置PC口的第x位为电阻上拉
#define	P_PCDOWN_BIT(x)	P2 &= ~(0x01<<x)  //设置PC口的第x位为电阻下拉

#define	P_PDUP_BIT(x)	P3 |= (0x01<<x)	  //设置PD口的第x位为电阻上拉
#define	P_PDDOWN_BIT(x)	P3 &= ~(0x01<<x)  //设置PD口的第x位为电阻下拉

#define	P_PEUP_BIT(x)	P4 |= (0x01<<x)	  //设置PE口的第x位为电阻上拉
#define	P_PEDOWN_BIT(x)	P4 &= ~(0x01<<x)  //设置PE口的第x位为电阻下拉

//***************************************************************************************
//---------------------IO口推免，开漏设置---------------------------------------------

#define	P_PAPUSH_BIT(x)	P0 |= (0x01<<x)  //设置P口第x位为推免输出
#define	P_PAOPEN_BIT(x)	P0 &= ~(0x01<<x) //设置P口第x位为开漏输出

#define	P_PBPUSH_BIT(x)	P1 |= (0x01<<x)  //设置P口第x位为推免输出
#define	P_PBOPEN_BIT(x)	P1 &= ~(0x01<<x) //设置P口第x位为开漏输出

#define	P_PCPUSH_BIT(x)	P2 |= (0x01<<x)  //设置P口第x位为推免输出
#define	P_PCOPEN_BIT(x)	P2 &= ~(0x01<<x) //设置P口第x位为开漏输出

#define	P_PDPUSH_BIT(x)	P3 |= (0x01<<x)  //设置P口第x位为推免输出
#define	P_PDOPEN_BIT(x)	P3 &= ~(0x01<<x) //设置P口第x位为开漏输出

#define	P_PEPUSH_BIT(x)	P4 |= (0x01<<x)	 //设置P口第x位为推免输出
#define	P_PEOPEN_BIT(x)	P4 &= ~(0x01<<x) //设置P口第x位为开漏输出

//*************************************************************************************
//---------------------IO口输出电平设置---------------------------------------------

#define	P_PAHIGH    P0 = 0xff      //PA口输出高电平
#define	P_PALOW     P0 = 0x00      //PA口输出低电平

#define	P_PBHIGH    P1 = 0xff	   //PB口输出高电平
#define	P_PBLOW     P1 = 0x00	   //PB口输出低电平

#define	P_PCHIGH    P2 = 0xff	   //PC口输出高电平
#define	P_PCLOW	    P2 = 0x00	   //PC口输出低电平

#define	P_PDHIGH    P3 = 0xff	   //PD口输出高电平
#define	P_PDLOW	    P3 = 0x00	   //PD口输出低电平

#define	P_PEHIGH    P4 = 0xff      //PE口输出高电平
#define	P_PELOW	    P4 = 0x00	   //PE口输出低电平

#define	P_PAHIGH_BIT(x) P0 |= (0x01<<x)  //PA的第x位输出高电平
#define	P_PALOW_BIT(x)  P0 &= ~(0x01<<x) //PA的第X位输出低电平

#define	P_PBHIGH_BIT(x) P1 |= (0x01<<x)  //PB的第x位输出高电平
#define	P_PBLOW_BIT(x)  P1 &= ~(0x01<<x) //PB的第X位输出低电平

#define	P_PCHIGH_BIT(x) P2 |= (0x01<<x)  //PC的第x位输出高电平
#define	P_PCLOW_BIT(x)  P2 &= ~(0x01<<x) //PC的第X位输出低电平

#define	P_PDHIGH_BIT(x) P3 |= (0x01<<x)  //PD的第x位输出高电平
#define	P_PDLOW_BIT(x)  P3 &= ~(0x01<<x) //PD的第X位输出低电平

#define	P_PEHIGH_BIT(x) P4 |= (0x01<<x)  //PE的第x位输出高电平
#define	P_PELOW_BIT(x)  P4 &= ~(0x01<<x) //PE的第X位输出低电平



//************************************************************************************
//---------------------IO输入设置---------------------------------------------------

//---------------------读取IO口状态-------------------------------------------------

#define	P_PAREAD   P0
#define	P_PBREAD   P1
#define	P_PCREAD   P2
#define	P_PDREAD   P3
#define	P_PEREAD   P4

//--------------------读取IO口位状态----------------------------------------------

#define	P_PAREAD_BIT(X)    (BOOL)(P0&(0X01<<X))
#define	P_PBREAD_BIT(X)    (BOOL)(P1&(0X01<<X))
#define	P_PCREAD_BIT(X)    (BOOL)(P2&(0X01<<X))
#define	P_PDREAD_BIT(X)    (BOOL)(P3&(0X01<<X))
#define	P_PEREAD_BIT(X)    (BOOL)(P4&(0X01<<X))

//**********************************************************************************

#endif











