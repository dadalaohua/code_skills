#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
#include <unistd.h>
extern char **environ;

int execle(const char *path, const char *arg, ..., char * const envp[]);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char * const envp[] = {"HELLO=1", "WORLD=2", NULL};
    
    printf("entering main process---\n");
    //execle("/bin/ls", "ls", "-l", NULL, NULL);
    execle("./exectest/exectest", "exectest", "testarg", NULL, envp);
    printf("exiting main process ----\n");
    return 0;
}
