#include"config.h"
#include"IOInit.h"


/*void GPIO_SetMode(GPIO_TypeDef* gpio,u16 Pin,GPIOMode_TypeDef  GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin  = Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;

	GPIO_Init(gpio, &GPIO_InitStructure);
}*/

void IOInit(void)
{
#if 1
	//UV_IN
	PORT_Init(PORT4,PIN1,OUTPUT);//
	
	//��ѹ���� SW-AD
	PORT_Init(PORT12,PIN4,INPUT);//1
	PORT_Init(PORT12,PIN1,INPUT);//2

	//������ OFF_CHK
	PORT_Init(PORT12,PIN2,INPUT);//


	//��ˮ�� DCF2
	PORT_Init(PORT13,PIN0,OUTPUT);//��ˮ��1
	PORT_Init(PORT3,PIN0,OUTPUT);//��ˮ��2

	//��ˮ�� DCF1
	PORT_Init(PORT12,PIN0,OUTPUT);//

	//��ѹ�� DCF4
	PORT_Init(PORT3,PIN1,OUTPUT);//// ˮ�� 6 14V ʹ��
	PORT_Init(PORT6,PIN3,OUTPUT);//// ˮ��  0--14V    In--6V
	PORT_Init(PORT7,PIN5,OUTPUT);//// ˮ��  0--24V    In--24V

	// ������
	PORT_Init(PORT13,PIN6,INPUT);//RO������
	PORT_Init(PORT14,PIN0,INPUT);//ǰ��������	

	//���Ƭ
	PORT_Init(PORT7,PIN4,OUTPUT);//

	//TDS1-1
	PORT_Init(PORT7,PIN0,OUTPUT);//

	//TDS1-2
	PORT_Init(PORT7,PIN1,OUTPUT);//

	//TDS2-1
	PORT_Init(PORT0,PIN1,OUTPUT);//

	//TDS2-2
	PORT_Init(PORT0,PIN0,OUTPUT);//	

	//WIFI
	PORT_Init(PORT2,PIN6,OUTPUT);//	
	GPIO_Output(PORT2,PIN6,0);//�͵�ƽ��
	//LEDB

	//C_A
	PORT_Init(PORT14,PIN7,OUTPUT);//

	//C_B
	PORT_Init(PORT14,PIN6,OUTPUT);//

	//C_C
	PORT_Init(PORT1,PIN0,OUTPUT);//

	//C_D
	PORT_Init(PORT1,PIN1,OUTPUT);//

	//D_A
	PORT_Init(PORT1,PIN2,OUTPUT);//
	
	//D_B
	PORT_Init(PORT1,PIN5,OUTPUT);//

	//D_C
	PORT_Init(PORT1,PIN6,OUTPUT);//

	//D_D
	PORT_Init(PORT1,PIN7,OUTPUT);//	

	//I2C
	//PORT_Init(PORT7,PIN2,OUTPUT);//	
	//PORT_Init(PORT7,PIN3,OUTPUT);//	
	//IIC_Init();
#endif	
}








