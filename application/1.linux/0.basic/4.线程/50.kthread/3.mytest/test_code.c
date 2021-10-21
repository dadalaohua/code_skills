#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "kthread.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
static void hello_function(void *arg, long i, int tid)
{
    int *val = (int *)arg;
    *val = *val + 1;
    
    printf("hello world %ld %d\n", i, *val);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    int n_threads = 2;
    long n = 10;
    int arg = 0;
    
    kt_for(n_threads, hello_function, &arg, n);
    
    sleep(3);
    
    return 0;
}