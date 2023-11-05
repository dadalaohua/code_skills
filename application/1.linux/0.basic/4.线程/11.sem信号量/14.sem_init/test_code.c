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
https://man7.org/linux/man-pages/man3/sem_init.3.html

#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);

Link with -pthread.

sem_init() initializes the unnamed semaphore at the address
pointed to by sem.  The value argument specifies the initial
value for the semaphore.

The pshared argument indicates whether this semaphore is to be
shared between the threads of a process, or between processes.

If pshared has the value 0, then the semaphore is shared between
the threads of a process, and should be located at some address
that is visible to all threads (e.g., a global variable, or a
variable allocated dynamically on the heap).

If pshared is nonzero, then the semaphore is shared between
processes, and should be located in a region of shared memory
(see shm_open(3), mmap(2), and shmget(2)).  (Since a child
created by fork(2) inherits its parent's memory mappings, it can
also access the semaphore.)  Any process that can access the
shared memory region can operate on the semaphore using
sem_post(3), sem_wait(3), and so on.

Initializing a semaphore that has already been initialized
results in undefined behavior.
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