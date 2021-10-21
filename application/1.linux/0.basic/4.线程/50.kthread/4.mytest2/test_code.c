#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "kthread.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
static void *worker_pipeline(void *shared, int step, void *in) // kt_pipeline() callback
{
    int *val = (int*)shared;
    
    printf("worker_pipeline %d\n", step);
    
    if (step == 0) {
        *val += 1;
        printf("worker_pipeline step %d val %d\n", step, *val);
        
        //只往下进行5次，超过5次后返回0，退出
        if(*val < 6) {
            int *to = malloc(sizeof(int));
            *to = 1234 + *val;
            
            return to; //传递给下一个步骤的数据
        }
    } else if (step == 1) {
        int *getint = (int *)in; //获取上一个步骤的数据

        printf("worker_pipeline step %d *getint %d\n", step, *getint);

        *getint += 6543;
        
        return getint; //传递给下一个步骤的数据
    } else if (step == 2) {
        int *getint = (int *)in;
        
        printf("worker_pipeline step %d *getint %d\n", step, *getint);
        
        free(getint);
    }
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    int pl_threads = 2;
    int arg = 0;

    //2个线程同时运行，回调函数为worker_pipeline，共享参数为arg，共3个步骤
    kt_pipeline(pl_threads, worker_pipeline, &arg, 3);
    
    sleep(2);
    
    return 0;
}