#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigalrm_fn(int sig)
{
    printf("alarm!\n");
    alarm(2);//定时2s
    return;
}

int main(int argc, char* argv[])
{ 
    signal(SIGALRM, sigalrm_fn);
    alarm(2);//定时2s
    
    while(1)
        pause();

    return 0;
}