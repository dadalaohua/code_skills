4、通过自己计算时间差的方法来定时

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
​
static char msg[] = "I received a msg.\n";
int len;
static time_t lasttime;
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
    time(&lasttime);
    while ( 1 )
    {
        time_t nowtime;
        
        time(&nowtime);
        
        if (nowtime - lasttime >= 2)
        {
            
            sigqueue(getpid(), 50, tsval);
            lasttime = nowtime;
        }
    }
    return 0;
}

这个和上面不同之处在于，是自己手工计算时间差的，如果你想更精确的计算时间差，你可以把 time 函数换成 gettimeofday，这个可以精确到微妙。