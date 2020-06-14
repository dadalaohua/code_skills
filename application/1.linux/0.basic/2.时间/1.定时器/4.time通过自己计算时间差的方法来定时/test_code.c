#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static char msg[] = "I received a msg.\n";
int len;
static time_t lasttime;

void show_msg(int signo)
{
    write(STDERR_FILENO, msg, len);
}

int main(int argc, char* argv[])
{
    struct sigaction act;
    union sigval tsval;
    
    act.sa_handler = show_msg;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(50, &act, NULL);
    len = strlen(msg);
    
    time(&lasttime);
    
    for(;;)
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