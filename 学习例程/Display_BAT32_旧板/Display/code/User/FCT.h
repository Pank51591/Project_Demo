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
	
	INT16U PumpADC;
	INT16U HVS;//��ѹ����״̬0�أ�1��
	
	INT16U faucet_Uart;//ˮ��ͷͨѶ״̬��1����
	INT16U wifi_Uart;//1����
	INT16U FrontFlow;//ǰ��������
	
	INT16U Pump;//ˮ��״̬
	INT16U wasteValve;//��ˮ��
	INT16U InletValve;//��ˮ��
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


//====================================
typedef struct
{
	INT8U hand;//
	INT8U len;
	INT8U cmd;//
	INT8U FCTstep;//
	
	INT8U rawTDS_H;
	INT8U rawTDS_L;//
	
	INT8U purTDS;//��ˮTDS
	
	INT8U wifi;//

	INT8U purHVS;//��ˮ��ѹ����
	INT8U liveHVS;//����ˮ��ѹ����
	INT8U FrontFlow;//ǰ��������
	INT8U faucetCOMM;//ˮ��ͷͨѶ
	INT8U rawNTC;//ԭˮNTC
	INT8U outNTC;//��ˮNTC

	INT8U type;//����
	INT8U sfw_Ver;//����汾
	INT8U sum;
}
FCT_rg_data;




#pragma pack()

extern FCTREG fctReg;

extern void FCT_FaucetDataProc(INT8U *pdat,INT16U len);
extern void FCT_ModeInit(void);
extern void FCT_Monitor(void);

extern void FCT_rg_main(INT8U*buf,INT8U len);
extern void FCT_powerdown(void);

#endif

