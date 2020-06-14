7、高精度定时器 posix_timer
（注： 编译时 需加上 -lrt）

　　最强大的定时器接口来自POSIX时钟系列，其创建、初始化以及删除一个定时器的行动被分为三个不同的函数：timer_create()(创建定时器)、timer_settime()(初始化定时器)以及 timer_delete()(销毁它)。

创建一个定时器：

int timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid)

　　进程可以通过调用 timer_create() 创建特定的定时器，定时器是每个进程自己的，不是在 fork 时继承的。clock_id 说明定时器是基于哪个时钟的，*timerid 装载的是被创建的定时器的 ID。该函数创建了定时器，并将他的 ID 放入timerid指向的位置中。参数evp指定了定时器到期要产生的异步通知。如果evp为 NULL，那么定时器到期会产生默认的信号，对 CLOCK_REALTIMER来说，默认信号就是SIGALRM。如果要产生除默认信号之外的其它信号，程序必须将 evp->sigev_signo设置为期望的信号码。struct sigevent 结构中的成员 evp->sigev_notify说明了定时器到期时应该采取的行动。通常，这个成员的值为SIGEV_SIGNAL，这个值说明在定时器到期时，会产生一个信号。程序可以将成员 evp->sigev_notify设为SIGEV_NONE来防止定时器到期时产生信号。

　　如果几个定时器产生了同一个信号，处理程序可以用 evp->sigev_value来区分是哪个定时器产生了信号。要实现这种功能，程序必须在为信号安装处理程序时，使用struct sigaction的成员sa_flags中的标志符SA_SIGINFO。

clock_id取值为以下： 
CLOCK_REALTIME :Systemwide realtime clock. 
CLOCK_MONOTONIC:Represents monotonic time. Cannot be set. 
CLOCK_PROCESS_CPUTIME_ID :High resolution per-process timer. 
CLOCK_THREAD_CPUTIME_ID :Thread-specific timer. 
CLOCK_REALTIME_HR :High resolution version of CLOCK_REALTIME. 
CLOCK_MONOTONIC_HR :High resolution version of CLOCK_MONOTONIC.

struct sigevent
{
int sigev_notify; //notification type
int sigev_signo; //signal number
union sigval   sigev_value; //signal value
void (*sigev_notify_function)(union sigval);
pthread_attr_t *sigev_notify_attributes;
}
union sigval
{
int sival_int; //integer value
void *sival_ptr; //pointer value
}

通过将evp->sigev_notify设定为如下值来定制定时器到期后的行为： 
SIGEV_NONE：什么都不做，只提供通过timer_gettime和timer_getoverrun查询超时信息。 
SIGEV_SIGNAL: 当定时器到期，内核会将sigev_signo所指定的信号传送给进程。在信号处理程序中，si_value会被设定会sigev_value。 
SIGEV_THREAD: 当定时器到期，内核会(在此进程内)以sigev_notification_attributes为线程属性创建一个线程，并且让它执行sigev_notify_function，传入sigev_value作为为一个参数。

启动一个定时器： 
timer_create()所创建的定时器并未启动。要将它关联到一个到期时间以及启动时钟周期，可以使用timer_settime()。

int timer_settime(timer_t timerid, int flags, const struct itimerspec *value, struct itimerspect *ovalue);
​
struct itimespec{
    struct timespec it_interval; 
    struct timespec it_value;   
}; 

　　如同settimer()，it_value用于指定当前的定时器到期时间。当定时器到期，it_value的值会被更新成it_interval 的值。如果it_interval的值为0，则定时器不是一个时间间隔定时器，一旦it_value到期就会回到未启动状态。timespec的结构提供了纳秒级分辨率：

struct timespec{
    time_t tv_sec;
    long tv_nsec;  
};

　　如果flags的值为TIMER_ABSTIME，则value所指定的时间值会被解读成绝对值(此值的默认的解读方式为相对于当前的时间)。这个经修改的行为可避免取得当前时间、计算“该时间”与“所期望的未来时间”的相对差额以及启动定时器期间造成竞争条件。 
　　如果ovalue的值不是NULL，则之前的定时器到期时间会被存入其所提供的itimerspec。如果定时器之前处在未启动状态，则此结构的成员全都会被设定成0。

获得一个活动定时器的剩余时间：

int timer_gettime(timer_t timerid,struct itimerspec *value);

取得一个定时器的超限运行次数： 
　　有可能一个定时器到期了，而同一定时器上一次到期时产生的信号还处于挂起状态。在这种情况下，其中的一个信号可能会丢失。这就是定时器超限。程序可以通过调用timer_getoverrun来确定一个特定的定时器出现这种超限的次数。定时器超限只能发生在同一个定时器产生的信号上。由多个定时器，甚至是那些使用相同的时钟和信号的定时器，所产生的信号都会排队而不会丢失。

int timer_getoverrun(timer_t timerid);

　　执行成功时，timer_getoverrun()会返回定时器初次到期与通知进程(例如通过信号)定时器已到期之间额外发生的定时器到期次数。举例来说，在我们之前的例子中，一个1ms的定时器运行了10ms，则此调用会返回9。如果超限运行的次数等于或大于DELAYTIMER_MAX，则此调用会返回DELAYTIMER_MAX。 
　　执行失败时，此函数会返回-1并将errno设定会EINVAL，这个唯一的错误情况代表timerid指定了无效的定时器。

删除一个定时器：

int timer_delete (timer_t timerid);

　　一次成功的timer_delete()调用会销毁关联到timerid的定时器并且返回0。执行失败时，此调用会返回-1并将errno设定会 EINVAL，这个唯一的错误情况代表timerid不是一个有效的定时器。

例1：

void  handle()
{
 time_t t;
 char p[32];
 time(&t);
 strftime(p, sizeof(p), "%T", localtime(&t));
 printf("time is %s\n", p);
}
​
int main()
{
 struct sigevent evp;
 struct itimerspec ts;
 timer_t timer;
 int ret;
 evp.sigev_value.sival_ptr = &timer;
 evp.sigev_notify = SIGEV_SIGNAL;
 evp.sigev_signo = SIGUSR1;
 signal(SIGUSR1, handle);
 ret = timer_create(CLOCK_REALTIME, &evp, &timer);
 if( ret )
  perror("timer_create");
 ts.it_interval.tv_sec = 1;
 ts.it_interval.tv_nsec = 0;
 ts.it_value.tv_sec = 3;
 ts.it_value.tv_nsec = 0;
 ret = timer_settime(timer, 0, &ts, NULL);
 if( ret )
  perror("timer_settime");
 while(1);
}

例2：

void  handle(union sigval v)
{
 time_t t;
 char p[32];
 time(&t);
 strftime(p, sizeof(p), "%T", localtime(&t));
 printf("%s thread %lu, val = %d, signal captured.\n", p, pthread_self(), v.sival_int);
 return;
}
​
int main()
{
 struct sigevent evp;
 struct itimerspec ts;
 timer_t timer;
 int ret;
 memset   (&evp,   0,   sizeof   (evp));
 evp.sigev_value.sival_ptr = &timer;
 evp.sigev_notify = SIGEV_THREAD;
 evp.sigev_notify_function = handle;
 evp.sigev_value.sival_int = 3;   //作为handle()的参数
 ret = timer_create(CLOCK_REALTIME, &evp, &timer);
 if( ret)
  perror("timer_create");
 ts.it_interval.tv_sec = 1;
 ts.it_interval.tv_nsec = 0;
 ts.it_value.tv_sec = 3;
 ts.it_value.tv_nsec = 0;
 ret = timer_settime(timer, TIMER_ABSTIME, &ts, NULL);
 if( ret )
  perror("timer_settime");
 while(1);
}