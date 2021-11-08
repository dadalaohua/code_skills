#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <spawn.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    pid_t child_pid;
    int ret;
    int wait_val;

    printf("This is main process......\n");
    ret = posix_spawn(&child_pid, "ls", NULL, NULL, argv, NULL);
    if (ret != 0){
        printf("posix_spawn is error\n");
        exit(-1);
    }

    wait(&wait_val);
    printf("This is main process and the wait value is %d\n", wait_val);

    exit(0);

    return 0;
}