https://blog.csdn.net/u012218309/article/details/81939716



POSIX线程（POSIX threads），简称Pthreads，是线程的POSIX标准。该标准定义了创建和操纵线程的一整套API。在类Unix操作系统（Unix、Linux、Mac OS X等）中，都使用Pthreads作为操作系统的线程。Windows操作系统也有其移植版pthreads-win32。

说白了，使用Pthreads方便移值。今天我们就来学习一下Pthreads的简单用法，废话不多说，直接先贴一段程序，根据这个程序一步一步展开，将涉及到的知识点都介绍一遍。

 

先看main函数程序：

int main()
{
    printf("main start\n");
    memset( &(g_stTask[0]), 0, (OS_THREAD_TOTAL*sizeof(ST_OS_TASK)) );
    
    Task_Create(Task_A, NULL, 4096, 16, "Task_A");
    Task_Create(Task_B, NULL, 4096, 16, "Task_B");
 
    sleep(100);
    printf("main end\n");
    return 0;
}
 

这个测试程序利用Task_create函数创建了两个线程：Task_A和Task_B，这两个任务每秒记一次数并打印出来，这个Task_create就是我们自己定义的使用pthread创建线程的函数

//任务A
void Task_A(void *arg)
{
    printf("Task_A in\n");
    int i = 1;
    while(1)
    {
        printf("Task_A run %d time\n",i);
        i++;
        //sleep(1);
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
        //sleep(1);
    }
}
 

下面我们来看看Task_create是怎么实现的

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





Task_create函数参数1：线程要执行的函数（和pthread_create里那个线程要执行的函数不是一个，原因下面有提到）；参数2：函数的参数；参数3：线程优先级；参数4：线程名。

 

步骤1：要建立一个全局Task管理变量g_stTask[i]，方便管理多个线程，每次建立新线程就从g_stTask[i]中取一个可用的

typedef struct _ST_OS_TASK
{
    char                 s8Name[OS_OBJECT_NAME];
    pthread_t            stThread;
    pthread_cond_t       stCond;
    pthread_mutex_t      stLock;
    pid_t                stPID;
    int                  iPolicy;
    unsigned char         u8Priority;
    bool                 b8Sleep;
    void                 (*pfnFunction)(void *);
    void                 *pParam;
    unsigned int         handle;
    int                  isToBeDestroyed;
} ST_OS_TASK;
步骤2：设置一系列线程属性，具体设置规则本文最后的注解中有详细介绍

步骤3：将各个参数都赋值给获取的g_stTask[i]

步骤4：创建线程

 

为什么Task_create的传入的函数指针(Task_A和Task_B)和pthread_create传入的函数指针(Task_Wrap_func)不是一个？

我们先来看看Task_wrap_func的定义：

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
 
    printf("Task_Wrap_func in name:%s pid:%d self_tid:%ld real_tid:%d\n",
        pstTask->s8Name,getpid(),pthread_self(),pstTask->stPID);
    pthread_cleanup_push(routine, arg);
    if( NULL != pstTask->pfnFunction )
    {
        pstTask->pfnFunction( pstTask->pParam );
    }
    else
    {
        perror("func is null\n");
    }
    pthread_cleanup_pop(1);

    printf("Task_Wrap_func out\n");
    return NULL;
}
 

可以看到，Task_wrap_func只执行了一次，而真正的循环计数任务在Task_A和Task_B两个函数里，Task_wrap_func通过g_stTask[i]来获得由Task_create传入的函数指针来调用Task_A或Task_B

 

为什么要这样设计？

假如线程函数执行过程中发生未知错误退出，或者被其他线程调用pthread_cancel退出，那么如果此时线程内部获取资源没有释放，比如内部获取的锁没有释放，那么就会导致死锁。所以我们使用pthread_create的时候最好不要直接把真正执行任务的函数指针赋给它做参数，最好使用本文使用的方法：在pthread_cleanup_push和pthread_cleanup_pop中间调用真正执行任务的函数(pthread_cleanup_push在本文最后的注解中有详细介绍)，这样在任务函数异常退出时，系统会调用pthread_cleanup_push注册的清理函数协助释放掉任务函数内获取的资源。

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
            pstTask->isToBeDestroyed = false;
        }
    }
    printf("taskCleanup out\n");
}
 

 

注解

pthread_attr_setscope设置的线程scope属性：

设置为PTHREAD_SCOPE_SYSTEM表示与系统内所有进程一起竞争CPU，设置为PTHREAD_SCOPE_PROCESS表示与当前进程内所有线程一起竞争CPU，linux只实现了PTHREAD_SCOPE_SYSTEM，在linux下不管设置为多少最后设置的都是PTHREAD_SCOPE_SYSTEM

 

pthread_attr_setinheritsched：

有两种值可供选择：PTHREAD_EXPLICIT_SCHED和PTHREAD_INHERIT_SCHED，前者表示新线程使用显式指定调度策略和调度参数（即attr中的值），而后者表示继承调用者线程的值。缺省为PTHREAD_EXPLICIT_SCHED

 

pthread_attr_setschedpolicy：

设置线程调度策略，主要包括SCHED_OTHER（正常、非实时）、SCHED_RR（实时、轮转法）和SCHED_FIFO（实时、先入先出）三种，缺省为SCHED_OTHER，后两种调度策略仅对超级用户有效。运行时可以用过pthread_setschedparam()来改变。

 

pthread_attr_setdetachstate：

表示新线程是否与进程中其他线程脱离同步， 如果设置为PTHREAD_CREATE_DETACHED 则新线程不能用pthread_join()来同步，且在退出时自行释放所占用的资源。缺省为PTHREAD_CREATE_JOINABLE状态。这个属性也可以在线程创建并运行以后用pthread_detach()来设置，而一旦设置为PTHREAD_CREATE_DETACH状态（不论是创建时设置还是运行时设置）则不能再恢复到PTHREAD_CREATE_JOINABLE状态

 

pthread_cleanup_push和pthread_cleanup_pop的使用

void pthread_cleanup_push(void (*rtn)(void *)，void *arg);
 
void pthread_cleanup_pop(int execute);
pthread_cleanup_push来注册清理函数rtn,这个函数有一个参数arg。在以下三种情形之一发生时，注册的清理函数被执行：

　　1）调用pthread_exit。

　　2）作为对取消线程请求(pthread_cancel)的响应。

3）以非0参数调用pthread_cleanup_pop。

 

根据这样的设定，当线程运行时，如果某一段代码需要持有系统资源(比如锁)，那么在这段代码的头尾加上pthread_cleanup_push和pthread_cleanup_pop来保护这段代码，当执行到这段代码中间遇到异常退出或者被其他线程调用pthread_cancel退出时，便可以调用清理程序来释放未释放的资源。

当然，程序如果正常结束那么便会执行到pthread_cleanup_pop函数，此时可设置pthread_cleanup_pop参数为非0来执行清理函数来释放资源。

 

pid tid 及真实tid：

进程pid: getpid()                

线程tid: pthread_self()      //进程内唯一，但是在不同进程则不唯一。

线程pid: syscall(SYS_gettid)  //系统内是唯一的

