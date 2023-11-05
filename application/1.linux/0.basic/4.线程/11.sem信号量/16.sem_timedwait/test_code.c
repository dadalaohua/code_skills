#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://man7.org/linux/man-pages/man3/sem_trywait.3.html
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/


sem_t csem;

void *func1(void)
{
    printf("%s: %lu\n", __func__, pthread_self());
    
    while(1) {
        sleep(5);
        sem_post(&csem); //5秒发出一次信号
    }
    
    printf("线程1（ID：0x%x）退出\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

/*
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

其中第2个参数 struct timespec *abs_timeout要求为绝对时间，
如果手动将系统时间往后修改会导致sem_timedwait长时间阻塞
*/
void *func2(void)
{
    printf("%s: %lu\n", __func__, pthread_self());
    
    while(1) {
        struct timespec timeout = { 0 };
        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_sec += 3;    //三秒超时
        timeout.tv_nsec += 0;   //
        if (-1 == sem_timedwait(&csem, &timeout)) {
            if (errno == ETIMEDOUT)
                printf("sem_timedwait() timedout\n");
            else
                perror("sem_timedwait");
        } else {
            printf("sem_timedwait() succeeded\n");
        }
        printf("%s: %lu\n", __func__, pthread_self());
    }
    
    printf("线程2（ID：0x%x）退出\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

int main(int argc, char* argv[])
{
    printf("%s: %lu\n", __func__, pthread_self());

    int ret;
    pthread_t tid1,tid2;

    if (sem_init(&csem, 0, 0) == -1) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }
    
    pthread_create(&tid1, NULL, (void  *)func1, NULL);
    pthread_create(&tid2, NULL, (void  *)func2, NULL);
    
    while(1) {
        sleep(3);
    }
    
    return 0;
}