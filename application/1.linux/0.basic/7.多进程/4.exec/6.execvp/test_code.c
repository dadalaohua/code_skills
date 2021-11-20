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

int execvp(const char *file, char *const argv[]);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *arg[] = {"ls", "-l", NULL}; 
    
    printf("entering main process---\n");
    execvp("ls", arg);
    printf("exiting main process ----\n");
    return 0;
}
