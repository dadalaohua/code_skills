#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

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
    act.sa_handler = show_msg;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(50, &act, NULL);
    len = strlen(msg);
    
    for(;;)
    {
        sleep(2); 
        
        sigqueue(getpid(), 50, tsval);
    }

   return 0;
}