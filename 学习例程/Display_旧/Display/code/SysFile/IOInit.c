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

	//RS
	PORT_Init(PORT2,PIN1,OUTPUT);//

	//RW
	PORT_Init(PORT2,PIN2,OUTPUT);//

	//EN
	PORT_Init(PORT2,PIN3,OUTPUT);//

	//DB0
	PORT_Init(PORT14,PIN7,OUTPUT);//

	//DB1
	PORT_Init(PORT1,PIN0,OUTPUT);//
	
	//DB2
	PORT_Init(PORT1,PIN1,OUTPUT);//

	//DB3
	PORT_Init(PORT1,PIN2,OUTPUT);//

	//DB4
	PORT_Init(PORT1,PIN3,OUTPUT);//	

	//DB5
	PORT_Init(PORT1,PIN4,OUTPUT);//

	//DB6
	PORT_Init(PORT1,PIN5,OUTPUT);//	

	//DB7
	PORT_Init(PORT1,PIN6,OUTPUT);//

	//blaklight
	PORT_Init(PORT1,PIN7,OUTPUT);//
	GPIO_Output(PORT1,PIN7,1);

	//key
	PORT_Init(PORT7,PIN2,INPUT);//
	PORT_Init(PORT7,PIN0,INPUT);//
	PORT_Init(PORT3,PIN0,INPUT);//
	PORT_Init(PORT5,PIN0,INPUT);//

#endif	
}








