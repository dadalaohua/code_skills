#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void new_op(int signum,siginfo_t *info,void *myact)//三参数信号处理函数的实现
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("%c ",(*( (char*)((*info).si_ptr)+i)));
    }
    printf("\n");
    printf("handle signal %d over \n",signum);
}

int main(int argc, char* argv[])
{ 
    struct sigaction act; 
    union sigval mysigval;
    int i;
    int sig;
    pid_t pid; 
    char data[10] = "abcdedghi";
    
    mysigval.sival_ptr = data;

    sig = atoi(argv[1]);
    pid = getpid();

    sigemptyset(&act.sa_mask);
    act.sa_sigaction = new_op;//三参数信号处理函数
    act.sa_flags = SA_SIGINFO;//信息传递开关
    if(sigaction(sig, &act, NULL) < 0)
    {
        printf("install sigal error\n");
    }
    
    while(1)
    {
        sleep(2);
        printf("wait for the signal\n");
        sigqueue(pid, sig, mysigval);//向本进程发送信号，并传递附加信息
    }

    return 0;
}