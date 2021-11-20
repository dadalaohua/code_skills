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

int execlp(const char *file, const char *arg, ...);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("entering main process---\n");
    execlp("ls", "ls", "-l", NULL);
    printf("exiting main process ----\n");
    return 0;
}
