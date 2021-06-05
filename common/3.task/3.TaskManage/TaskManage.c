//TaskManage.c

#include "TaskManage.h"

/************************************************************
 * descri  : 变量定义区
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
stTaskManage sTaskManage;

/************************************************************
 * Fuction : InitialTaskManager
 * descri  : 初始化任务管理
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
 void InitialTaskManager(void)
 {
    u8 i = 0;
    for(i = 0;i< TASK_NUM_MAX;i++)
    {
        sTaskManage.task[i].statue     = TASK_STOP;   //运行标识
        sTaskManage.task[i].time       = 0;           //运行周期
        sTaskManage.task[i].count_time = 0;           //运行计数变量
        sTaskManage.task[i].fuc        = NULL;        //运行函数指针
    }
   
    sTaskManage.registerTaskNum = 0;    //已经注册的任务计数清零
 }
 
/************************************************************
 * Fuction : RegisterTask
 * descri  : 注册任务
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
 u8  RegisterTask(u32 time, void * taskFuc)
 {
    if(sTaskManage.registerTaskNum >= TASK_NUM_MAX)return FALSE;
    if(taskFuc == NULL)return FALSE;
   
    if(sTaskManage.task[sTaskManage.registerTaskNum].fuc == NULL) //找到没有使用的任务数据
    {
        sTaskManage.task[sTaskManage.registerTaskNum].statue     = TASK_STOP;   //运行状态
        sTaskManage.task[sTaskManage.registerTaskNum].time       = time;        //运行周期
        sTaskManage.task[sTaskManage.registerTaskNum].count_time = 0;           //运行计数变量
        sTaskManage.task[sTaskManage.registerTaskNum].fuc        = taskFuc;     //运行函数指针
       
        sTaskManage.registerTaskNum++;//已经注册的任务计数
        return TRUE;//注册成功
    }

    return FALSE; //全部注册完毕
    
 }
 
/************************************************************
 * Fuction : Task_Process
 * descri  : 任务处理过程
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
void Task_Process(void)
{
    u8 taskcount= 0;
    //遍历已经注册的任务
    for(taskcount = 0; taskcount < sTaskManage.registerTaskNum;taskcount++)
    {
        if(sTaskManage.task[taskcount].statue == TASK_RUN)//任务可以运行
        {
       
            (*sTaskManage.task[taskcount].fuc)();
            sTaskManage.task[taskcount].statue = TASK_STOP;
        }

    }
   
}

/************************************************************
 * Fuction : Task_RunCheck
 * descri  : 任务运行条件核对
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
void Task_RunCheck(void)
{
    u8 taskcount= 0;
    //遍历已经注册的任务
    for(taskcount = 0; taskcount < sTaskManage.registerTaskNum;taskcount++)
    {
        if((++sTaskManage.task[taskcount].count_time) >= sTaskManage.task[taskcount].time) //任务时间到来
        {
            sTaskManage.task[taskcount].count_time = 0;
            sTaskManage.task[taskcount].statue     = TASK_RUN;
       
        }

    }
}
