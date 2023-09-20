#ifndef FCT_H
#define FCT_H

#pragma pack(1)

typedef struct
{
	INT16U DeviceAddr;//�豸��ַ
	INT16U ProductType;//��Ʒ���� 0��ˮ����1����
	INT16U productName;//��Ʒ���� 0�ƾ���1������2���ۣ�3����о��4miniϵ��(0x0401mni1,0x0402mini2)
	INT16U ProductModel;//��Ʒ�ͺ�(500,600,700,800)
	INT16U version;//�汾��8λӲ���汾,��8λ����汾

	INT16U cmd;//���ƼĴ���
	
	INT16U WorkState;//
	
	INT16U TempRes;//
	INT16U rawTDSRes;
	INT16U netTDSRes;//
	INT16U LeakRes;//
	INT16U PumpADC;
	INT16U HVS;//��ѹ����״̬0�أ�1��
	
	INT16U faucet_Uart;//ˮ��ͷͨѶ״̬��1����
	INT16U Faucet_LEDR;//ˮ��ͷLED R��1����
	INT16U Faucet_LEDB;//ˮ��ͷLED B��1����
	
	INT16U Pump;//ˮ��״̬
	INT16U wasteValve;//��ˮ��
	INT16U InletValve;//��ˮ��

	INT16U Temp2Res;//
}
FCTREG;

typedef struct
{
	INT8U NTCFlag:1;//
	INT8U rawTDSFlag:1;
	INT8U netTDSFlag:1;//
	INT8U LeakFlag:1;//
	INT8U PumpFlag:1;

	INT8U HVSFlag:1;//��ѹ����״̬0�أ�1��
	INT8U wifiFlag:1;//wifiͨѶ״̬��1����
	INT8U FaucetFlag:1;//ˮ��ͷͨѶ״̬��1���� 
}
FCT_FLAG;


#pragma pack()

extern FCTREG fctReg;

extern void FCT_FaucetDataProc(INT8U *pdat,INT16U len);
extern void FCT_ModeInit(void);
extern void FCT_Monitor(void);

#endif

