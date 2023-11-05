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
https://man7.org/linux/man-pages/man3/sem_post.3.html

sem_post() increments (unlocks) the semaphore pointed to by sem.
If the semaphore's value consequently becomes greater than zero,
then another process or thread blocked in a sem_wait(3) call will
be woken up and proceed to lock the semaphore.

sem_post() returns 0 on success; on error, the value of the
semaphore is left unchanged, -1 is returned, and errno is set to
indicate the error.
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

/*
int sem_wait(sem_t *sem);

sem_wait() decrements (locks) the semaphore pointed to by sem.
If the semaphore's value is greater than zero, then the decrement
proceeds, and the function returns, immediately.  If the
semaphore currently has the value zero, then the call blocks
until either it becomes possible to perform the decrement (i.e.,
the semaphore value rises above zero), or a signal handler
interrupts the call.
*/
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
    
    return 0;
}