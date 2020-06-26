#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{ 
    pid_t pid;
    int sig;
    union sigval mysigval;
    
    sig = atoi(argv[1]);
    pid = atoi(argv[2]);
    
    sigqueue(pid, sig, mysigval);
    sleep(2);

    return 0;
}