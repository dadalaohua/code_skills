2、setitimer


int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue));
int getitimer(int which, struct itimerval *value);
​
strcut timeval
{
   long tv_sec; 
   long tv_usec; 
};
​
struct itimerval
{
   struct timeval it_interval; 
   struct timeval it_value; 
};

setitimer() 比 alarm() 功能强大，支持3种类型的定时器：

① ITIMER_REAL：给一个指定的时间间隔，按照实际的时间来减少这个计数，当时间间隔为0的时候发出SIGALRM信号。 
② ITIMER_VIRTUAL：给定一个时间间隔，当进程执行的时候才减少计数，时间间隔为0的时候发出SIGVTALRM信号。 
③ ITIMER_PROF：给定一个时间间隔，当进程执行或者是系统为进程调度的时候，减少计数，时间到了，发出SIGPROF信号。

　　setitimer() 第一个参数 which 指定定时器类型（上面三种之一）；第二个参数是结构 itimerval 的一个实例；第三个参数可不做处理。 
　　下面是关于setitimer调用的一个简单示范，在该例子中，每隔一秒发出一个SIGALRM，每隔0.5秒发出一个SIGVTALRM信号：：

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
​
int sec;
​
void sigroutine(int signo){
   switch (signo){
   case SIGALRM:
       printf("Catch a signal -- SIGALRM \n");
       signal(SIGALRM, sigroutine);
       break;
   case SIGVTALRM:
       printf("Catch a signal -- SIGVTALRM \n");
       signal(SIGVTALRM, sigroutine);
       break;
   }
   return;
}
​
int main()
{
   struct itimerval value, ovalue, value2;
​
   sec = 5;
   printf("process id is %d ", getpid());
   signal(SIGALRM, sigroutine);
   signal(SIGVTALRM, sigroutine);
   value.it_value.tv_sec = 1;
   value.it_value.tv_usec = 0;
   value.it_interval.tv_sec = 1;
   value.it_interval.tv_usec = 0;
   setitimer(ITIMER_REAL, &value, &ovalue);
   value2.it_value.tv_sec = 0;
   value2.it_value.tv_usec = 500000;
   value2.it_interval.tv_sec = 0;
   value2.it_interval.tv_usec = 500000;
   setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
   for(;;);
}

该例子的执行结果如下：

localhost:~$ ./timer_test
process id is 579
Catch a signal – SIGVTALRM
Catch a signal – SIGALRM
Catch a signal – SIGVTALRM
Catch a signal – SIGVTALRM
Catch a signal – SIGALRM
Catch a signal –GVTALRM


　

注意：Linux信号机制基本上是从Unix系统中继承过来的。早期Unix系统中的信号机制比较简单和原始，后来在实践中暴露出一些问题，因此，把那些建立在早期机制上的信号叫做”不可靠信号”，信号值小于SIGRTMIN(Red hat 7.2中，SIGRTMIN=32，SIGRTMAX=63)的信号都是不可靠信号。这就是”不可靠信号”的来源。它的主要问题是：进程每次处理信号后，就将对信号的响应设置为默认动作。在某些情况下，将导致对信号的错误处理；因此，用户如果不希望这样的操作，那么就要在信号处理函数结尾再一次调用 signal()，重新安装该信号。