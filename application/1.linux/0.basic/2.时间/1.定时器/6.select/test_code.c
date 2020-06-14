#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

static char msg[] = "I received a msg.\n";
int len;

int usSleep(long us) 
 {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = us;

    return select(0, NULL, NULL, NULL, &tv);
 }

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

    for(;;)
    {
        sigqueue(getpid(), 50, tsval);

        usSleep(2000000);
    }
    
    return 0;
}