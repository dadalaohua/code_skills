3、用 sleep 以及 usleep 实现定时执行任务

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
​
static char msg[] = "I received a msg.\n";
int len;
​
void show_msg(int signo)
{
    write(STDERR_FILENO, msg, len);
}
​
int main()
{
    struct sigaction act;
    union sigval tsval;
    act.sa_handler = show_msg;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(50, &act, NULL);
    len = strlen(msg);
    while ( 1 )
    {
        sleep(2); 
        
        sigqueue(getpid(), 50, tsval);
    }
    return 0;
}

看到了吧，这个要比上面的简单多了，而且你用秒表测一下，时间很准，指定2秒到了就给你输出一个字符串。所以，如果你只做一般的定时，到了时间去执行一个任务，这种方法是最简单的。