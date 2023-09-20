#include"config.h"
#include"task.h"




//**************************************************************************************
//* Variable definition                            
//**************************************************************************************
/*static*/ TASK_COMPONENTS TaskComps[TASKS_MAX] = 
{ // �������������񡣡�����
	{SyStemTimeTask, 100, 100, 0},           // ��ʾʱ�� TaskDisplayClock
	{TaskKeySan, 5, 5, 0},          // ����ɨ�� TaskKeySan
	//{MonitorAppADC,20,20,0},		//����
	{DisplayUpdate,200,200,0},//��ʾ����
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
//	��������	: TimerInit	
//	����		: yzy	
//	ģ�鹦��	: �����ʼ�� 
//	����ֵ      : ��	
//  ��������    : 
//  ���ļ�¼	:
//**************************************************************************************
#if 0
void TaskInit(void)
{

}
#endif

//**************************************************************************************
//* FunctionName   : TaskProcess()
//* Description    : ������
//* EntryParameter : None
//* ReturnValue    : None
//**************************************************************************************
void TaskProcess(void) 
{
    RTDATA INT8U i;
	
    for(i=0; i<TASKS_MAX; i++)         // �������ʱ�䴦��
    {
        if(TaskComps[i].Run)          // ʱ�䲻Ϊ0
        {
			TaskComps[i].TaskHook();   // ��������
			TaskComps[i].Run = 0;      // ��־��0
        }
    }   
}





