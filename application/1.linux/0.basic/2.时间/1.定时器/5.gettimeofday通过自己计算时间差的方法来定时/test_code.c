#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

static char msg[] = "I received a msg.\n";
int len;

void show_msg(int signo)
{
    write(STDERR_FILENO, msg, len);
}

int main(int argc, char* argv[])
{
    struct sigaction act;
    union sigval tsval;
    struct timeval nowtime, lasttime;
    
    act.sa_handler = show_msg;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(50, &act, NULL);
    len = strlen(msg);
    
    gettimeofday(&lasttime, NULL);
    
    for(;;)
    {
        gettimeofday(&nowtime, NULL);
        
        if (nowtime.tv_sec - lasttime.tv_sec >= 2)
        {
            sigqueue(getpid(), 50, tsval);
            lasttime.tv_sec = nowtime.tv_sec;
        }
    }
    
    return 0;
}