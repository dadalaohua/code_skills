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

int execvpe(const char *file, char *const argv[], char *const envp[]);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *arg[] = {"ls", "-l", NULL}; 
    char * const envp[] = {"HELLO=1", "WORLD=2", NULL};
    
    printf("entering main process---\n");
    //execvpe("ls", arg, NULL);
    execvpe("./exectest/exectest", arg, envp);
    printf("exiting main process ----\n");
    return 0;
}
