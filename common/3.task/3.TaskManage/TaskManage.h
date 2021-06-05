//TaskManage.h

#ifndef __TASKMANAGE__
#define __TASKMANAGE__

/************************************************************
 * Fuction :数据类型定义区
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
#define TRUE                      (1)
#define FALSE                     (0)

#ifndef NULL
#define NULL                      ((void*)(0))
#endif

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed long    s32;
typedef signed short   s16;
typedef signed char    s8;

typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned int  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */


/************************************************************
 * Fuction :任务类型定义区
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
#define TASK_NUM_MAX 20

//运行模式
#define TASK_STOP (0)
#define TASK_RUN  (1)

/************************************************************
 * Fuction :类型定义区
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
#pragma pack(1)
typedef struct _tag_taskdata
{
    u8  statue;         //运行状态
    u32 time;           //运行周期
    u32 count_time;     //运行计数变量
    void (*fuc)(void);  //运行函数指针
} stTaskData;

typedef struct _tag_taskmanage
{
    stTaskData task[TASK_NUM_MAX]; //最大任务数管理
    u8 registerTaskNum;            //已经注册的任务
}stTaskManage;
#pragma pack()


/************************************************************
 * Fuction :功能接口区域
 * Author  :(公众号:最后一个bug)
 ***********************************************************/
extern void InitialTaskManager(void);
extern u8  RegisterTask(u32 time, void * taskFuc);
extern void Task_Process(void);
extern void Task_RunCheck(void);

#endif
