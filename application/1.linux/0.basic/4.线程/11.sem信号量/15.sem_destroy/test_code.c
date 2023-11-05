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
https://man7.org/linux/man-pages/man3/sem_destroy.3.html

#include <semaphore.h>

int sem_destroy(sem_t *sem);

Link with -pthread.

sem_destroy() destroys the unnamed semaphore at the address
pointed to by sem.

Only a semaphore that has been initialized by sem_init(3) should
be destroyed using sem_destroy().

Destroying a semaphore that other processes or threads are
currently blocked on (in sem_wait(3)) produces undefined
behavior.

Using a semaphore that has been destroyed produces undefined
results, until the semaphore has been reinitialized using
sem_init(3).
*/
sem_t csem;

void *func1(void)
{
    printf("%s: %lu\n", __func__, pthread_self());
    
    while(1) {
        sleep(3);
        sem_post(&csem); //3秒发出一次信号
        printf("%s: %lu\n", __func__, pthread_self());
    }
    
    printf("线程1（ID：0x%x）退出\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

void *func2(void)
{
    printf("%s: %lu\n", __func__, pthread_self());
    
    while(1) {
        sem_wait(&csem);
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
    
    sem_destroy(&csem);
    
    return 0;
}