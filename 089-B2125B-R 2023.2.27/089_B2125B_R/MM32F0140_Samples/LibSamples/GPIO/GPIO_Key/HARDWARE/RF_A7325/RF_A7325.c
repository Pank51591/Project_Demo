#include "RF_A7325.h"

//  A7325寄存器的地址宏定义
#define A7325_MODE_REG 			0x00
#define A7325_MODECTRL_REG	    0x01
#define A7325_CALIBRATION_REG 	0x02
#define A7325_FIFO1_REG 		0x03
#define A7325_FIFO2_REG 		0x04
#define A7325_FIFO_REG 			0x05
#define A7325_IDCODE_REG 		0x06
#define A7325_RCOSC1_REG 		0x07
#define A7325_RCOSC2_REG 		0x08
#define A7325_RCOSC3_REG 		0x09
#define A7325_CKO_REG 			0x0A
#define A7325_GPIO1_REG 		0x0B
#define A7325_CLOCK_REG 		0x0C
#define A7325_DATARATE_REG	0x0D
#define A7325_PLL1_REG 			0x0E
#define A7325_PLL2_REG			0x0F
#define A7325_PLL3_REG 			0x10
#define A7325_PLL4_REG			0x11
#define A7325_PLL5_REG 			0x12
#define A7325_CHG1_REG      0x13
#define A7325_CHG2_REG      0x14
#define A7325_TX1_REG  			0x15
#define A7325_TX2_REG  			0x16
#define A7325_DELAY1_REG		0x17
#define A7325_DELAY2_REG		0x18
#define A7325_ADC_REG			  0x19
#define A7325_CODE1_REG			0x1A
#define A7325_CODE2_REG     0x1B
#define A7325_VCOCCAL_REG 	0x1C
#define A7325_VCOCAL1_REG		0x1D
#define A7325_VCOCAL2_REG		0x1E
#define A7325_VCODEVCAL1_REG  	0x1F
#define A7325_VCODEVCAL2_REG 	0x20
#define A7325_VCODEVCAL3_REG	0x21
#define A7325_VCOMODDELAY_REG 	0x22
#define A7325_BATTERY_REG		0x23
#define A7325_TXTEST_REG  	0x24   //TX测试寄存器
#define A7325_CPC_REG  		    0x25
#define A7325_CRYSTALTEST_REG	0x26
#define A7325_PLLTEST_REG  	    0x27
#define A7325_VCOTEST_REG       0x28
#define A7325_CHSELECT_REG      0x29
#define A7325_VRB_REG           0x2A
#define A7325_RTX_REG           0x2B
#define A7325_HWTEST_REG		0x2C
#define A7325_USID				0x3F

//strobe command  （与器件规格书相同）
#define CMD_SLEEP		0x80	//1000,xxxx	SLEEP mode
#define CMD_IDLE		0x90	//1001,xxxx	IDLE mode
#define CMD_STBY		0xA0	//1010,xxxx Standby mode
#define CMD_PLL			0xB0	//1011,xxxx	PLL mode
#define CMD_TX			0xD0	//1101,xxxx	TX mode
#define CMD_TFR			0xE0	//1110,xxxx	TX FIFO reset

extern volatile unsigned char gcTxBuff[17];
//extern volatile unsigned char	PairMode_Flag;
//extern volatile unsigned char gcPairedBuff[17];
const unsigned char  ID_Tab[4]={0xAA,0xBB,0xCC,0xDD};
/*const Uint8  BitCount_Tab[16] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};*/


//const Uint8  PN9_Tab[]=
//{   0xFF,0x83,0xDF,0x17,0x32,0x09,0x4E,0xD1,
//    0xE7,0xCD,0x8A,0x91,0xC6,0xD5,0xC4,0xC4,
//    0xC6,0xD5,0xC4,0xC4
//};  // This table are 64bytes PN9 pseudo random code.

/*7325的配置*/
const Uint8 A7325Config_Master[]=
{
    0x00, //MODE register,         only reset, not use on config
    0x02, //MODE CTRL register,     开启FIFO模式
    0x00, //CALIBRATION register,   vco校准关闭
    0x10, //FIFO1 register,        TX FIFO传送结束地址 
    0x00, //FIFO2 register,        TX FIFO传送起始地址
    0x00, //FIFO register,         for fifo read/write
    0x00, //IDData register,       for idcode
    0x00, //RCOSC1 register,
    0x00, //RCOSC2 register,
    0x00, //RCOSC3 register,
    0x00, //CKO register,
    0x01, //GIO1 register       GIO1开启
    0x1D, //Clock register,     master clock/1；选择内部石英振荡器    
    0x00, //DATARATE register,     // 0x18=20K
    0x00, //PLL1 register,
    0x0E, //PLL2 register,      RFbase 2400.001MHz
    0x96, //PLL3 register,
    0x00, //PLL4 register,
    0x04, //PLL5 register,
    0x3C, //chanel group I,
    0x78, //chanel group II,
    0x56, //TX1 register,
    0x2F, //TX2 register,
    0x1A, //DELAY1 register,
    0x48, //DELAY2 register,
    0xCC, //ADC register,
    0x05, //CODE1 register,             CRC关闭，ID CODE 4 bytes,  preamble 2 bytes
    0x2A, //CODE2 register,             VCO Current  1mA
    0x2C, //VCOCCAL register,
    0xC4, //VCOBC1 register,
    0x80, //VCOBC2 register,
    0x20, //VCO DEV Cal. I register,
    0x0B, //VCO DEV Cal. II register,
    0x80, //VCO DEV Cal. III register,
    0x02, //VCO Mod. delay register,
    0x6E, //BATTERY register,
    0x17, //TXTEST register,
    0xF3, //CPC register,
    0xF5, //CRYSTAL register,
    0xD5, //PLLTEST register,
    0x48, //VCOTEST register,
    0x08, //Channel select,
    0x00, //VRB register,
    0xFF, //RTX register,
    0xB0  //HW test
};
extern  void DELAY_xUs(u32 count);

void Set_SDIO_Out(void)
{
		GPIO_InitTypeDef  GPIO_InitStruct;
	
	  // RF_A7325端口配置
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStruct);		
}

void Set_SDIO_In(void)
{
		GPIO_InitTypeDef  GPIO_InitStruct;
	
	  // RF_A7325端口配置
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;      //上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStruct);		
}

/**********************************************************
* Delay1ms @12MHz
**********************************************************/
void Delay1ms(Uint8 n)
{
    Uint8 i;

    while(n--)
        for(i=0;i<250;i++);
}

/**********************************************************
* Delay100us @12MHz
**********************************************************/
/*void Delay100us(Uint8 n)
{
    Uint8 i;
    while(n--)
        for(i=0;i<23;i++);
}*/

/************************************************************************
**  Reset_RF
************************************************************************/
void Reset(void)
{
    WriteReg(A7325_MODE_REG, 0x00); //reset RF chip
}

/************************************************************************
**  WriteID
************************************************************************/
void WriteID(void)
{
    Uint8 i;
/*    Uint8 d1,d2,d3,d4;*/

    //SCS = 0;
		Clr_SCS;
    ByteSend(A7325_IDCODE_REG);
    for (i=0; i < 4; i++)
        ByteSend(ID_Tab[i]);
   // SCS = 1;
		Set_SCS;
	
		Clr_SCS;
    //SCS=0;
    ByteSend(A7325_IDCODE_REG | 0x40);
	
//    d1=ByteRead();
//    d2=ByteRead();
//    d3=ByteRead();
//    d4=ByteRead();
/*    gitestvalue = ((unsigned int)d1<<24)|((unsigned int)d2<<16)|((unsigned int)d3<<8)|((unsigned int)d4);*/
//    if((d1==0x34)&&(d2==0x75)&&(d3==0xC5)&&(d4==0x2A))
//    {
//
//		    	
//    }
		Set_SCS;
}

/************************************************************************
**  WriteReg  （写配置）
************************************************************************/
void WriteReg(Uint8 addr, Uint8 dataByte)
{
    Uint8 i;

    //SCS = 0;
	  Clr_SCS;   //拉低选中
    addr |= 0x00;     //bit cmd=0,r/w=0  （只取低8位）
    for(i = 0; i < 8; i++)
    {
        if(addr & 0x80)//
				{
           Set_SDIO;//SDIO = 1;
				}
        else
				{
            Clr_SDIO;//SDIO = 0;
				}
        // SCK = 1;
				Set_SCK;
        _nop();
        _nop();
				DELAY_xUs(5);
        // SCK = 0;
				Clr_SCK;
        addr = addr << 1;
    }
				_nop();
    //send data byte
    for(i = 0; i < 8; i++)
    {
        if(dataByte & 0x80)
				{
          Set_SDIO;   //  SDIO = 1;
				}
        else
				{
           Clr_SDIO;  // SDIO = 0;
				}

				Set_SCK;
        _nop();
    	  _nop();   
				DELAY_xUs(5);

				Clr_SCK;
        dataByte = dataByte<< 1;
    }

    //SCS = 1;
		Set_SCS;
}

/************************************************************************
**  ReadReg（读配置）
************************************************************************/
Uint8 ReadReg(Uint8 addr)
{
    Uint8 i;
    Uint8 tmp;
    
		Set_SDIO_Out();
		
		//  SCS = 0;
		Clr_SCS;
    addr |= 0x40;     //bit cmd=0,r/w=1
    for(i = 0; i < 8; i++)
    {

        if(addr & 0x80)
				{
						Set_SDIO;  //SDIO = 1;
				}
        else
				{
            Clr_SDIO;  //SDIO = 0;
				}
        _nop();
				DELAY_xUs(5);
       // SCK = 1;
				Set_SCK;
        _nop();
				DELAY_xUs(5);
       // SCK = 0;
				Clr_SCK;
        addr = addr << 1;
    }

		_nop();
   
		Set_SDIO_In();
    //read data
    for(i = 0; i < 8; i++)
    {
        if(Read_SDIO)
            tmp = (tmp << 1) | 0x01;
        else
            tmp = tmp << 1;

       // SCK = 1;
				Set_SCK;
        _nop();
				DELAY_xUs(5);
        //SCK = 0;
				Clr_SCK;
    }
    //SCS = 1;
    Set_SCS;
    Set_SDIO_Out();
    return tmp;
}

/************************************************************************
**  ByteSend 
************************************************************************/
void ByteSend(Uint8 src)
{
    Uint8 i;

    for(i = 0; i < 8; i++)
    {
        if(src & 0x80)
				{
            //SDIO = 1;
						Set_SDIO;
				}
        else
				{
           // SDIO = 0;
					Clr_SDIO;
				}
        _nop();
				DELAY_xUs(5);      // liu
        //SCK = 1;
				Set_SCK;
        _nop();
				DELAY_xUs(5);
       // SCK = 0;
				Clr_SCK;
        src = src << 1;
    }
}

/************************************************************************
**  ByteRead
************************************************************************/
Uint8 ByteRead(void)
{
    Uint8 i,tmp;

    //SDIO = 1;   //sdio pull high
    Set_SDIO_In();  //设置为 SDIO为输入
    for(i = 0; i < 8; i++)
    {
        if(Read_SDIO)
            tmp = (tmp << 1) | 0x01;
        else
            tmp = tmp << 1;

        // SCK = 1;
				Set_SCK;
        _nop();
				DELAY_xUs(5);
        // SCK = 0;
				
				Clr_SCK;
				DELAY_xUs(5);
    }  
    Set_SDIO_Out();	//恢复SDIO为输出
    return tmp;
}

/************************************************************************
**  Send4Bit
************************************************************************/
void Send4Bit(Uint8 src)
{
    Uint8 i;

    for(i = 0; i < 4; i++)
    {
        if(src & 0x80)
				{
          // SDIO = 1;
					Set_SDIO;
				}
        else
				{
          // SDIO = 0;
					Clr_SDIO;
				}
        _nop();
				DELAY_xUs(5);
        //SCK = 1;
			  Set_SCK;
        _nop();
        //SCK = 0;
				DELAY_xUs(5);
				Clr_SCK;
        src = src << 1;
    }
}

/*********************************************************************
** SetCH_A7325
*********************************************************************/
void SetCH_A7325(Uint8 ch)
{
    WriteReg(A7325_PLL1_REG, ch);     //RF freq = RFbase + (CH_Step * ch)
}

/*********************************************************************
** SetCH_A7105
*********************************************************************/
//void SetCH_A7105(Uint8 ch)
//{
//    WriteReg(A7325_PLL1_REG, ch); //PLL1, RF freq = RFbase + (CH_Step * ch)
//}

/*********************************************************************
** initRF_M
*********************************************************************/
void initRF_M(void)
{
    //init io pin
		Set_SCS;
		Clr_SCK;
		Set_SDIO;
	
	
    /* CKO = 1;*/
    /* GIO1 = 1;*/
    Reset(); //reset A7325 RF chip
    WriteID(); //write ID code
    A7325_Config_M(); //config A7325 chip
    A7325_Cal(); //calibration IF,VCO,VCOC
	
    //Delay100us(1000);   // delay 100ms for LVR stable
    //WriteReg( A7325_BATTERY_REG, A7325Config_Master[A7325_BATTERY_REG] | 0x10 ); // LVR = 1
    //A7325_RCO_Calibration(); // RCO calibraion
}

/*********************************************************************
** WriteFIFO
*********************************************************************/
void WriteFIFO(void)
{
    Uint8 i;

    //SCS=0;
		Clr_SCS;
    ByteSend(A7325_FIFO_REG);     //0x0101
    for(i=0; i <17; i++)
    {
    	ByteSend(gcTxBuff[i]);	    //发送字节
    }
    //SCS=1;
		Set_SCS;
}

/*********************************************************************
** Strobe Command
*********************************************************************/
void StrobeCmd(Uint8 cmd)
{
  // SCS = 0;
	Clr_SCS;
  Send4Bit(cmd);
  // SCS = 1;
	Set_SCS;
}

/*********************************************************************
** RxPacket
*********************************************************************/
void RxPacket(void)
{
	/*
    Uint8 i;
    Uint8 recv;
    Uint8 tmp;

    RxCnt++;

    SCS=0;
    ByteSend(A7325_FIFO_REG | 0x40);
    for(i=0; i <64; i++)
    {
        recv = ByteRead();
        tmpbuf[i]=recv;
        if((recv ^ PN9_Tab[i])!=0)
        {
            tmp = recv ^ PN9_Tab[i];
            Err_BitCnt += (BitCount_Tab[tmp>>4] + BitCount_Tab[tmp & 0x0F]);
        }
    }
    SCS=1;
    */
}

/*********************************************************************
** SelVCOBand
*********************************************************************/
void SelVCOBand(Uint8 vb1, Uint8 vb2)
{
    Uint8 diff1,diff2;

    if (vb1>=4)
        diff1 = vb1-4;
    else
        diff1 = 4-vb1;

    if (vb2>=4)
        diff2 = vb2-4;
    else
        diff2 = 4-vb2;

    if (diff1 == diff2 || diff1 > diff2)
        WriteReg(0x25, (vb1 | 0x08));//manual setting vb1 value
    else
        WriteReg(0x25, (vb2 | 0x08));//manual setting vb2 value
}

/*********************************************************************
** calibration
*********************************************************************/
void A7325_Cal(void)
{
    
    StrobeCmd(CMD_PLL); //calibration VDC,VBC,VCC procedure
    A7325_CHGroupCal(30); //calibrate channel group Bank I
    A7325_CHGroupCal(90); //calibrate channel group Bank II
    A7325_CHGroupCal(150);//calibrate channel group Bank III
}

/*********************************************************************
** A7325_Config_M
*********************************************************************/
void A7325_Config_M(void)
{
    Uint8 i;

    //0x00 mode register, for reset
    for (i=0x01; i<=0x04; i++)
        WriteReg(i, A7325Config_Master[i]);

    //0x05 fifo data register
    //0x06 id code register

    for (i=0x07; i<=0x2C; i++)
        WriteReg(i, A7325Config_Master[i]);
}

uint8_t TempTest;

/*********************************************************************
** A7325_CHGroupCal
*********************************************************************/
void A7325_CHGroupCal(Uint8 ch)
{
    uint8_t tmp = 0;
    uint8_t vb = 0;
	  uint8_t vbcf = 0;
    uint8_t vcb = 0;
		uint8_t fvcc = 0;

	  /*写7325相应的寄存器*/
    WriteReg(A7325_PLL1_REG, ch);
    WriteReg(A7325_CALIBRATION_REG, 0x1C);
    do
    {
			  /*读7325相应的寄存器*/
        TempTest = ReadReg(A7325_CALIBRATION_REG);
        TempTest &= 0x1C;
    }
    while(TempTest);

    //for check
    tmp = ReadReg(A7325_VCOCCAL_REG);
    // vcb = tmp & 0x0F; //  未用 20211123
    fvcc= (tmp >> 4) & 0x01;

    tmp = ReadReg(A7325_VCOCAL1_REG);
    // vb = tmp & 0x07;  //  未用 20211123
    vbcf = (tmp >>3) & 0x01;

    if (fvcc || vbcf)
    {
        Err_State();
    }
}

/*********************************************************************
** Err_State
*********************************************************************/
void Err_State(void)
{
    //ERR display
    //Error Proc...
    //...
    
    while(1);
}

/*********************************************************************
** RCO_Calibration
*********************************************************************/
Uint8 A7325_RCO_Calibration(void)
{
	/*
    Uint8 rcoc, rcot;

    rcot = 3;

    WriteReg( A7325_RCOSC3_REG, 0x34 ); // enable RCO
    Delay100us(10);
    do
    {
        WriteReg( A7325_RCOSC3_REG, (0x0C | (rcot<<4))); // write RCOT, RCO enable
        Delay100us( 50 ); // RCO calibration time
        rcoc = ReadReg( A7325_RCOSC1_REG ) & 0x7F;

        if ( ( rcoc < 64 ) && ( rcoc >= 20 ) )
            return rcoc;

        rcot --;
    }
    while(rcot);

    return 0xFF;*/
		return 0xFF;
}

void A7325_Enable_WOT(void)
{
    StrobeCmd( CMD_SLEEP );
    WriteReg( A7325_MODECTRL_REG, A7325Config_Master[A7325_MODECTRL_REG] | 0x08 ); // WOTE = 1
}

void A7325_Disable_WOT(void)
{
    WriteReg( A7325_MODECTRL_REG, A7325Config_Master[A7325_MODECTRL_REG] & 0xF7 ); // WOTE = 0
    // RF @ SLEEP mode

    StrobeCmd( CMD_STBY );
    Delay1ms(1);
    // RF @ STBY mode
}

void A7325_Sleep(void)
{
	StrobeCmd(CMD_SLEEP);        //发送睡眠的指令
}

void A7325_ExitSleep(void)
{
	StrobeCmd(CMD_IDLE);	
}

void A7325_Init(void)          // 初始化A7325
{
	initRF_M();
	StrobeCmd(CMD_PLL);         
	SetCH_A7325(156);				    //Freq 2478MHz
}

void A7325TX_Process(void)		//发送数据时调用
{
		StrobeCmd(CMD_STBY);	    // 在发送前，先发一次STBY
		StrobeCmd(CMD_PLL);
		SetCH_A7325(156);				  //Freq 2478MHz
	  WriteFIFO();              //将接收到的数据通过FIFO发送出去     //05
   	StrobeCmd(CMD_TX); 		    //设置 TX模式	
}

void  DirectMode_init(void)
{
	SetCH_A7325(156);	        //FREQ  2478HZ
	WriteReg(A7325_TXTEST_REG,0X17);        //PAC=2,TBG=7,set TX Power
	WriteReg(A7325_MODECTRL_REG,0X00);      //set Direct Mode , FMS = 0
	WriteReg(A7325_TX1_REG,0X06);         //TME & TMDE = 0  Disable TME &TMDE 
	StrobeCmd(CMD_PLL);
}
