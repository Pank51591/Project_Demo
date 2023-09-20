#include"config.h"
#include"task.h"




//**************************************************************************************
//* Variable definition                            
//**************************************************************************************
/*static*/ TASK_COMPONENTS TaskComps[TASKS_MAX] = 
{ // 这里添加你的任务。。。。
	{SyStemTimeTask, 100, 100, 0},           // 显示时钟 TaskDisplayClock
	{TaskKeySan, 5, 5, 0},          // 按键扫描 TaskKeySan
	//{MonitorAppADC,20,20,0},		//串口
	{DisplayUpdate,200,200,0},//显示更新
	{MonitorState,10,10,0},
	//{MonitorTDS,sec(1),sec(1),0},
	//{MonitorWater,500,500,0},
	//{Faucet_Display,sec(1),sec(1)},
	//{UpdataFlowMeterWaterVolume,10,10},
	//{MonitrorAlarm,200,200,0},
	//{MonitorBigData,100,100,0},
	//{DisplayBoardTask,500,500,0},
	//{Display_Send,50,50,0},
};  

//*************************************************************************************
//	函数名称	: TimerInit	
//	作者		: yzy	
//	模块功能	: 任务初始化 
//	返回值      : 无	
//  参数介绍    : 
//  更改记录	:
//**************************************************************************************
#if 0
void TaskInit(void)
{

}
#endif

//**************************************************************************************
//* FunctionName   : TaskProcess()
//* Description    : 任务处理
//* EntryParameter : None
//* ReturnValue    : None
//**************************************************************************************
void TaskProcess(void) 
{
    RTDATA INT8U i;
	
    for(i=0; i<TASKS_MAX; i++)         // 逐个任务时间处理
    {
        if(TaskComps[i].Run)          // 时间不为0
        {
			TaskComps[i].TaskHook();   // 运行任务
			TaskComps[i].Run = 0;      // 标志清0
        }
    }   
}





