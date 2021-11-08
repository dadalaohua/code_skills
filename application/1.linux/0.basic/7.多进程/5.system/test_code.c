#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//实例4：system()
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int status;
    printf("This is main process...\n");
    status = system("ls -l");
    //status = system("ls");
    if(status < 0){
        printf("system is error.\n");
        exit(-1);
    }

    printf("WEXITSTATUS(status) is %d\n", WEXITSTATUS(status));
    exit(0);

    return 0;
}