#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/
extern char** environ;

int main(int argc, char* argv[])
{
    printf("exectest pid=%d\n", getpid());
    
    int i;
    
    for (i = 0; argv[i]!=NULL; i++)
    {
        printf("%s\n", argv[i]);
    }
    
    printf("\n");
    
    for (i = 0; environ[i]!=NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
    
    return 0;
}
