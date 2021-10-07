#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>
#include "assert.h"

#define OS_THREAD_TOTAL 10
#define OS_OBJECT_NAME  10

typedef struct _ST_OS_TASK
{
    char                 s8Name[OS_OBJECT_NAME];
    pthread_t            stThread;
    pthread_cond_t       stCond;
    pthread_mutex_t      stLock;
    pid_t                stPID;
    int                  iPolicy;
    unsigned char        u8Priority;
    unsigned char        u8Sleep;
    void                 (*pfnFunction)(void *);
    void                 *pParam;
    unsigned int         handle;
    int                  isToBeDestroyed;
} ST_OS_TASK;

ST_OS_TASK g_stTask[OS_THREAD_TOTAL];

//线程资源释放函数
void taskCleanup(ST_OS_TASK *pstTask)
{    
    printf("taskCleanup in name:%s\n",pstTask->s8Name);
    if( NULL != pstTask )    
    {
        if( 0 == pstTask->stThread )
        {
            //do nothing because the thread is still exists        
        }
        else
        {
            pthread_mutex_destroy(&pstTask->stLock);
            pthread_cond_destroy(&pstTask->stCond);
            memset( pstTask->s8Name, 0, OS_OBJECT_NAME );
            pstTask->stThread = 0;
            pstTask->handle = 0xFFFFFFFF;
            pstTask->isToBeDestroyed = 0;
        }
    }
    printf("taskCleanup out\n");
}

//线程运行函数
void *Task_Wrap_func(void* arg)
{
    if( NULL == arg )
    {
        perror("Task_Wrap_func arg is null\n");
    }
    
    ST_OS_TASK* pstTask = (ST_OS_TASK*)arg;

    void (*routine)(void *) = (void (*)(void*))(&taskCleanup);
    pstTask->stPID = syscall( SYS_gettid );

    printf("Task_Wrap_func in name:%s pid:%d self_tid:%lu real_tid:%d\n",
        pstTask->s8Name, getpid(), pthread_self(), pstTask->stPID);
    
    pthread_cleanup_push(routine, arg); //注册清理函数,在异常退出时调用清理程序来释放未释放的资源
    if( NULL != pstTask->pfnFunction )
    {
        pstTask->pfnFunction( pstTask->pParam );
    }
    else
    {
        perror("func is null\n");
    }
    pthread_cleanup_pop(1); //设置参数为非0来执行清理函数来释放资源
    
    printf("Task_Wrap_func out\n");
    return NULL;
}

void Task_Create( void (*pfnFunction)(void *), void *pParam, \
    unsigned int u32Stack, unsigned int u8Priority, const char *pc8Name )
{
    int nRet = 0;
    int i = 0;
    ST_OS_TASK *pstTask = NULL;
    pthread_attr_t stThreadAttr;
    
    printf("Task_Create in name:%s\n", pc8Name);
    
    for(i = 0; i < OS_THREAD_TOTAL; i++)
    {
        if(0 == g_stTask[i].stThread)
        {
            pstTask = &(g_stTask[i]);
            break;
        }
    }
    
    memset(pstTask->s8Name, 0, OS_OBJECT_NAME);
    //线程属性初始化
    pthread_attr_init(&stThreadAttr);
    //线程scope属性,设置为PTHREAD_SCOPE_SYSTEM表示与系统内所有进程一起竞争CPU，设置为PTHREAD_SCOPE_PROCESS表示与当前进程内所有线程一起竞争CPU，linux只实现了PTHREAD_SCOPE_SYSTEM，在linux下不管设置为多少最后设置的都是PTHREAD_SCOPE_SYSTEM
    pthread_attr_setscope(&stThreadAttr, PTHREAD_SCOPE_PROCESS);
    //设置线程栈大小
    pthread_attr_setstacksize(&stThreadAttr, u32Stack);
    //设置线程是否显示指定调度策略，有两种值可供选择：PTHREAD_EXPLICIT_SCHED和PTHREAD_INHERIT_SCHED，前者表示新线程使用显式指定调度策略和调度参数（即attr中的值），而后者表示继承调用者线程的值。缺省为PTHREAD_EXPLICIT_SCHED。
    pthread_attr_setinheritsched(&stThreadAttr, PTHREAD_EXPLICIT_SCHED);
    //设置线程调度策略，主要包括SCHED_OTHER（正常、非实时）、SCHED_RR（实时、轮转法）和SCHED_FIFO（实时、先入先出）三种，缺省为SCHED_OTHER，后两种调度策略仅对超级用户有效。运行时可以用pthread_attr_setschedpolicy()来改变。
    pthread_attr_setschedpolicy(&stThreadAttr, SCHED_OTHER);//正常、非实时
    //设置线程结束是否自动释放线程资源
    pthread_attr_setdetachstate(&stThreadAttr, PTHREAD_CREATE_DETACHED);//与进程中其他线程脱离同步,且在退出时自行释放所占用的资源
    
    pthread_mutex_init(&(pstTask->stLock), NULL);//初始化互斥锁
    pthread_cond_init(&(pstTask->stCond), NULL);//初始化条件变量
    
    pstTask->pfnFunction = pfnFunction;
    pstTask->pParam      = pParam;
    pstTask->u8Sleep     = 0;
    pstTask->iPolicy     = SCHED_OTHER;
    pstTask->u8Priority  = u8Priority;
    pstTask->handle      = i+1000;
    memcpy(pstTask->s8Name, pc8Name, OS_OBJECT_NAME);
    
    //参数1： 线程tid 2:线程属性结构体 3：线程函数入口 4：线程函数参数
    nRet = pthread_create(&(pstTask->stThread), &stThreadAttr, Task_Wrap_func, pstTask);
    assert(0 == nRet);
    
    pthread_attr_destroy(&stThreadAttr);
    pthread_mutex_unlock(&(pstTask->stLock));
    
    printf("Task_Create out name:%s\n", pc8Name);
}

//任务A
void Task_A(void *arg)
{
    printf("Task_A in\n");
    int i = 1;
    
    while(1)
    {
        printf("Task_A run %d time\n",i);
        i++;
        sleep(1);
    }
}

//任务B
void Task_B(void *arg)
{
    printf("Task_B in\n");
    int i = 1;
    
    while(1)
    {
        printf("Task_B run %d time\n",i);
        i++;
        sleep(1);
    }
}

int main(int argc, char* argv[])
{  
    printf("main start\n");
    memset( &(g_stTask[0]), 0, (OS_THREAD_TOTAL*sizeof(ST_OS_TASK)) );
    
    Task_Create(Task_A, NULL, 4096, 16, "Task_A");
    Task_Create(Task_B, NULL, 4096, 16, "Task_B");
    
    sleep(100);
    printf("main end\n");
 
    return 0;  
}  
