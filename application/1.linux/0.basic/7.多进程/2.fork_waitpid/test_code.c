#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//实例2：fork(), waitpid()实例，创建两个子进程，只是等待第二个子进程，并且设置为非阻塞
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    pid_t pid;
    int i = 0;
    printf("This is main process, PID is %d\n", getpid());
   
    for (i = 0; i < 2; ++i){
        pid = fork();
        if (pid < 0){
            printf("fork error...\n");
            exit(-1);
        }
        else if (pid == 0){//This is the child process
            printf("This is child process, PID is %d\n", getpid());
            exit(11);//将子进程的退出码设置为11
        }
        else{//This is the main process
            printf("This is main process waiting for the exit of child process.\n");
        }
    }
    int child_status;
    pid_t child_pid2;
    sleep(1);//一定要等待，因为waitpid设为了无阻塞的，如果不等待，当执行完waitpid下面的语句的时候子进程2可能还没有退出，那么就得不到它的退出码了
    child_pid2 = waitpid(pid, &child_status, WNOHANG);
    printf("This is main process. The second child status is %d, and child pid is %d, WIFEXITED(child_status) is %d, WEXITSTATUS(child_status) is %d\n", child_status, child_pid2, WIFEXITED(child_status), WEXITSTATUS(child_status));
    
    exit(0);

    return 0;
}