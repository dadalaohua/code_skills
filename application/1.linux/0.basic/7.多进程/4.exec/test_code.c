#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//实例3：fork()和exec()函数系列
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    pid_t pid;
    char *arg[] = {"ls", "-l", NULL}; 

    printf("This is main process, PID is %d\n", getpid());
    pid = fork();
    if (pid < 0){
        printf("fork error...\n");
        exit(-1);
    }
    else if (pid == 0){//This is the child process
       printf("This is child process, PID is %d\n", getpid());
       //execl("/bin/ls", "ls", "-l", NULL); 
       //execlp("ls", "ls", "-l", NULL);
       //execle("/bin/ls", "ls", "-l", NULL, NULL);
       //execv("/bin/ls", arg);
       //execvp("ls", arg);
       execve("/bin/ls", arg, NULL);//上面的六个函数的运行结果都是一样的
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