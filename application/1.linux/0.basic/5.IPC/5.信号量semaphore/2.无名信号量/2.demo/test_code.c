#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

sem_t sem;

void* change_resource(void *argc)
{
    int count = 0;
    printf("change resource start\n");
    while (1)
    {
        sem_wait(&sem);
        printf("resource changed count: %d\n", count++);
    }
}

int main(int argc, char* argv[])
{
    pthread_t thread; 
    int ret; 
    
    ret = sem_init(&sem, 0, 0);
    if (ret == -1)
    {
        printf("sem_init failed \n");
        return -1;
    }

    ret = pthread_create(&thread, NULL, change_resource, NULL);
    if (ret != 0)
    {
        printf("pthread_create failed \n");
        return -1;
    }

    while (1)
    {
        sem_post(&sem);
        sleep(1);
    }

    return 0;
}