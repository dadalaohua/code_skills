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

int execl(const char *path, const char *arg, ...);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("entering main process---\n");
    execl("/bin/ls","ls", "-l", NULL);
    printf("exiting main process ----\n");
    return 0;
}
