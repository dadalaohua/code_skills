#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int mysigninequality(int x, int y)
{
    return (x ^ y) < 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a = 1, b = 1;
    printf("a %d b %d inequality %s\n", a, b, mysigninequality(a, b) ? "true" : "false");
    
    a = 1, b = 2;
    printf("a %d b %d inequality %s\n", a, b, mysigninequality(a, b) ? "true" : "false");
    
    a = 1, b = -1;
    printf("a %d b %d inequality %s\n", a, b, mysigninequality(a, b) ? "true" : "false");
    
    a = -1, b = -1;
    printf("a %d b %d inequality %s\n", a, b, mysigninequality(a, b) ? "true" : "false");
    
    a = -1, b = -1;
    printf("a %d b %d inequality %s\n", a, b, mysigninequality(a, b) ? "true" : "false");
    
    return 0;
}