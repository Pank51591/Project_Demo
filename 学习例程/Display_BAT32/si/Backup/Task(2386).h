#ifndef TASK_H
#define TASK_H

#include"typedef.h"


// �����嵥
typedef enum _TASK_LIST
{
	TASK_DISP_CLOCK,            // ��ʾʱ��
	TASK_KEY_SAN,             // ����ɨ��
	TASK_ADC,
	TASK_DISP_WS,             // ����״̬��ʾ
	TASK_TDS,
	TASK_HVS,
	TASK_MonitorWater,
	//TASK_FAUCET,
	TASK_Flow,

	TASK_WIFI,
	//TASK_FINDSAVEDATA,
	// �������������񡣡�����
	TASKS_MAX                // �ܵĿɹ�����Ķ�ʱ������Ŀ
} 
TASK_LIST;




typedef struct _TASK_COMPONENTS
{
	void (*TaskHook)(void);  // Ҫ���е�������
	INT16U Timer;             // ��ʱ��
	INT16U ItvTime;           // �������м��ʱ��
	INT8U Run;               // �������б�ǣ�0-�����У�1����
} 
TASK_COMPONENTS;			 // ������



extern TASK_COMPONENTS TaskComps[];

extern void TaskRemarks(void);
extern void TaskProcess(void) REENTRANT;



#endif

