#ifndef __MODBUS_MASTER_TEST_H
#define __MODBUS_MASTER_TEST_H

/* ���Թ��ܲ��� */
#define MB_SAMPLE_TEST_SLAVE_ADDR						1			//�ӻ��豸��ַ
#define MB_REG_START  											1			//����������ʼλ��
#define MB_SEND_REG_NUM    									4			//������������
#define MB_READ_REG_NUM    									4			//������������
#define WAITING_FOREVER											-1		//���õȴ�

/* ͨ���궨��ѡ���� */
#define MB_USER_HOLD 												1			//д������ּĴ���
#define MB_USER_COILS 											2			//д�����Ȧ
#define MB_USER_INPUT_REG										3			//������Ĵ���

extern void test(char MB);												//���Գ���

#endif
