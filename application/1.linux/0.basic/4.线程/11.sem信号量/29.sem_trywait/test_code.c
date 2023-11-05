#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>

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
int sem_trywait(sem_t *sem);

sem_trywait与 sem_wait() 类似，若信号不可用，
则返回错误(errno 设置为EAGAIN)而不是阻塞
*/
void *func2(void)
{
    printf("%s: %lu\n", __func__, pthread_self());
    
    while(1) {
        if (-1 == sem_trywait(&csem)) {
            if (errno == EAGAIN)
                printf("sem_trywait() EAGAIN\n");
            else
                perror("sem_trywait");
        } else {
            printf("sem_trywait() succeeded\n");
        }
        sleep(1);
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