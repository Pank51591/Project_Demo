/**
  ******************************************************************************
  * @file    modbus_master_test.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   modbus����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "modbus_master_test.h"
#include "mb_m.h"
#include "mbport.h"
#include "user_mb_app.h"
/**
  * @brief  ���Գ���
  * @param  ����ѡ��
  * @retval ��
  */
void test(char MB)
{
	USHORT Hlod_buff[4];
	UCHAR	Coils[4]={1,0,1,0};

	Hlod_buff[0] =  HAL_GetTick() & 0xff;		           //��ȡʱ��� ���1��8λ
	Hlod_buff[1] = (HAL_GetTick() & 0xff00) >> 8;      //��ȡʱ��� ���9��16λ
	Hlod_buff[2] = (HAL_GetTick() & 0xff0000) >> 16 ;  //��ȡʱ��� ���17��24λ
	Hlod_buff[3] = (HAL_GetTick() & 0xff000000) >> 24; //��ȡʱ��� ���25��32λ
	
	/* ע����������API��mb_m.h�� */
	switch(MB)
	{
		case MB_USER_HOLD: 
					/* д������ּĴ���ֵ */
					eMBMasterReqWriteMultipleHoldingRegister(MB_SAMPLE_TEST_SLAVE_ADDR, //�ӻ��豸��ַ
																									 MB_REG_START, 							//������ʼλ��
																									 MB_SEND_REG_NUM, 					//д��������
																									 Hlod_buff, 								//����
																									 WAITING_FOREVER);					//���õȴ�
		break;
		
		case MB_USER_COILS:
					/* д�����Ȧ */
					eMBMasterReqWriteMultipleCoils(MB_SAMPLE_TEST_SLAVE_ADDR, //�ӻ��豸��ַ
																				 MB_REG_START, 							//������ʼλ��
																				 MB_SEND_REG_NUM, 					//д��������
																				 Coils, 										//����
																				 WAITING_FOREVER);					//���õȴ�
		break;
		
		case MB_USER_INPUT_REG:
					/* ������Ĵ��� */
					eMBMasterReqReadInputRegister(MB_SAMPLE_TEST_SLAVE_ADDR,	//�ӻ��豸��ַ
																				MB_REG_START,               //������ʼλ��
																				MB_READ_REG_NUM,						//����������
																				WAITING_FOREVER);						//���õȴ�
		break;
	}
}	



