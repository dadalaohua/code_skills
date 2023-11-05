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
https://man7.org/linux/man-pages/man3/sem_getvalue.3.html

#include <semaphore.h>

int sem_getvalue(sem_t *restrict sem, int *restrict sval);

Link with -pthread.


sem_getvalue() places the current value of the semaphore pointed
to sem into the integer pointed to by sval.

If one or more processes or threads are blocked waiting to lock
the semaphore with sem_wait(3), POSIX.1 permits two possibilities
for the value returned in sval: either 0 is returned; or a
negative number whose absolute value is the count of the number
of processes and threads currently blocked in sem_wait(3).  Linux
adopts the former behavior.
*/
sem_t csem;

void *func1(void)
{
    printf("%s: %lu\n", __func__, pthread_self());
    
    int sval;
    while(1) {
        sleep(3);
        sem_getvalue(&csem, &sval);
        
        printf("%s sem_post before: sval %d\n", __func__, sval);
        
        sem_post(&csem); //3秒发出一次信号
        
        sem_getvalue(&csem, &sval);
        
        printf("%s sem_post after: sval %d\n", __func__, sval);
        
        printf("%s: sval %d, id %lu\n", __func__, sval, pthread_self());
    }
    
    printf("线程1（ID：0x%x）退出\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

void *func2(void)
{
    printf("%s: %lu\n", __func__, pthread_self());
    
    int sval;
    while(1) {
        sem_getvalue(&csem, &sval);
        
        printf("%s sem_wait before: sval %d\n", __func__, sval);
        
        sem_wait(&csem);
        
        sem_getvalue(&csem, &sval);
        
        printf("%s sem_wait before: sval %d\n", __func__, sval);
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