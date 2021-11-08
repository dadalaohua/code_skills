#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void sigchld_handler(int signum)
{
    int status;
    pid_t pid;
 
    if((pid = waitpid(-1, &status, WNOHANG)) < 0){
        printf("waitpid error\n");
        return;
    }
    printf("The signal is %d, child:%d exit status is %d\n", signum, pid, WEXITSTATUS(status));
}
 
//不可被信号终端的睡眠函数
void unbreak_sleep(int sec)
{
    while(sec > 0){
        sec = sleep(sec);
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    signal(SIGCHLD, sigchld_handler);
    
    pid_t pid = fork();
    if(pid < 0){
        printf("fork error\n");
        return -1;
    }
    else if(pid == 0){//子进程
        printf("子进程:%d....等待3秒之后退出,退出码是100\n", getpid());
        sleep(3);
        printf("子进程退出\n");
        exit(100);
    }
    else if(pid > 0){//父进程
        printf("父进程:%d,创建的子进程的pid = %d, 父进程等待7秒\n", getpid(), pid);        
        //sleep(7);
        unbreak_sleep(7);
    }
 
    printf("父进程退出\n");
    exit(0);

    return 0;
}