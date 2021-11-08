#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//实例1：fork(), wait()实例
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    pid_t pid;

    printf("This is main process, PID is %d\n", getpid());
    
    pid = fork();
    if (pid < 0){
        printf("fork error...\n");
        exit(-1);
    }
    else if (pid == 0){//This is the child process
       printf("This is child process, PID is %d\n", getpid());
       sleep(3);//子进程休眠3秒,这样就可以看到wait函数阻塞了父进程，因为三秒之后，wait语句下面的语句才开始执行
       exit(11);//将子进程的退出码设置为11
    }
    else{//This is the main process
        printf("This is main process waiting for the exit of child process.\n");
        int child_status;
        pid = wait(&child_status);
        printf("This is main process. The child status is %d, and child pid is %d, WIFEXITED(child_status) is %d, WEXITSTATUS(child_status) is %d\n", child_status, pid, WIFEXITED(child_status), WEXITSTATUS(child_status));
    }

    exit(0);

    return 0;
}