#ifndef TASK_H
#define TASK_H

#include"typedef.h"


// 任务清单
typedef enum _TASK_LIST
{
	TASK_DISP_CLOCK,            // 显示时钟
	TASK_KEY_SAN,             // 按键扫描
	TASK_ADC,
	TASK_DISP_WS,             // 工作状态显示
	TASK_TDS,
	TASK_HVS,
	TASK_MonitorWater,
	//TASK_FAUCET,
	TASK_Flow,

	TASK_WIFI,
	//TASK_FINDSAVEDATA,
	// 这里添加你的任务。。。。
	TASKS_MAX                // 总的可供分配的定时任务数目
} 
TASK_LIST;




typedef struct _TASK_COMPONENTS
{
	void (*TaskHook)(void);  // 要运行的任务函数
	INT16U Timer;             // 计时器
	INT16U ItvTime;           // 任务运行间隔时间
	INT8U Run;               // 程序运行标记：0-不运行，1运行
} 
TASK_COMPONENTS;			 // 任务定义



extern TASK_COMPONENTS TaskComps[];

extern void TaskRemarks(void);
extern void TaskProcess(void) REENTRANT;



#endif

