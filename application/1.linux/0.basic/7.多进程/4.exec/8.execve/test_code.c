#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
#include <unistd.h>

int execve(const char *filename, char *const argv[], char *const envp[]);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *arg[] = {"ls", "-l", NULL}; 
    char * const envp[] = {"HELLO=1", "WORLD=2", NULL};
    
    printf("entering main process---\n");
    //execve("/bin/ls", arg, NULL);
    execve("./exectest/exectest", arg, envp);
    printf("exiting main process ----\n");
    return 0;
}
