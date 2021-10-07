#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "threadPool.h"

int test_num = 200;
int test_cnt = 0;
/************************************************************************/
/*                                                                      */
/************************************************************************/
void taskFunc(void* arg)
{
    
    int num = *(int*)arg;
    printf("thread %ld is working, number = %d\n",
        pthread_self(), num);
    free(arg);
    sleep(1);
    test_cnt++;
    
    /*
    int num = test_cnt;
    printf("thread %ld is working, number = %d\n",
        pthread_self(), num);
    sleep(1);
    test_cnt++;
    */
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    // 创建线程池
    ThreadPool* pool = threadPoolCreate(3, 10, 100);
    for (int i = 0; i < test_num; ++i)
    {
        
        int* num = (int*)malloc(sizeof(int));
        *num = i + 100;
        threadPoolAdd(pool, taskFunc, num);
        
        //threadPoolAdd(pool, taskFunc, NULL);
    }

    while(test_cnt < test_num)
        sleep(1);
    
    sleep(3);

    threadPoolDestroy(pool);
    
    sleep(1);
    
    return 0;
}
