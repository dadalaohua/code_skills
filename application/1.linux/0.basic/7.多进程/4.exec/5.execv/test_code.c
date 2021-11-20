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

int execv(const char *path, char *const argv[]);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *arg[] = {"ls", "-l", NULL};
    
    printf("entering main process---\n");
    execv("/bin/ls", arg);
    printf("exiting main process ----\n");
    return 0;
}
