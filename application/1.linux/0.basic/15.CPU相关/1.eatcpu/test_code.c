#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sysinfo.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

void * thr_task(void *arg) {
    sleep(1);
    printf("thr thread sched_getcpu = %d\n", sched_getcpu());
    while(1);
    return NULL;
}

int main(int argc, char* argv[])
{
    int cpu_total;
    int cpu_num;
    
    cpu_total = get_nprocs_conf();  //返回CPU总核数，包括系统中禁用的核的数目，因此该值并不代表当前系统中可用的核数。
    cpu_num = get_nprocs(); //返回系统当前可用的核数
    
    printf("cpu total: %d\n", cpu_total);
    printf("cpu num: %d\n", cpu_num);
    
    pthread_t thr[cpu_num];
    
    for(int i = 0; i < cpu_num; i++) {
        if (pthread_create(&thr[i], NULL, thr_task, NULL) != 0) {
            fprintf(stderr, "Error: pthread_create\n");
        }

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);  //初始化，设为空
        CPU_SET(i, &cpuset);   //将cpu id 加入cpu集中 

        printf("pthread_setaffinity_np cpu%d\n", i);
        pthread_setaffinity_np(thr[i], sizeof(cpuset), &cpuset);
    }
    printf("main thread sched_getcpu = %d\n", sched_getcpu());

    pthread_join(thr[0], NULL);

    return 0;
}