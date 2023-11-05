#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int myaddone(int n)
{
    return -~n;
}

int mydecone(int n)
{
    return ~-n;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int val = 0;
    for(int i = 0; i < 10; i++) {
        val = myaddone(val);
        printf("val %d\n", val);
    }
    printf("\n");
    
    for(int i = 0; i < 10; i++) {
        val = mydecone(val);
        printf("val %d\n", val);
    }
    printf("\n");
    
    return 0;
}