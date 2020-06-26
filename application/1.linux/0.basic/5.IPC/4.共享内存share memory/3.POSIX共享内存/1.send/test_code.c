#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>      //包含errno所需要的头文件 
#include <string.h>     //包含strerror所需要的头文件  
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHM_NAME "/memmap"
#define SHM_NAME_SEM "/memmap_sem"

char sharedMem[64];  

int main(int argc, char* argv[])
{
    int fd;
    sem_t *sem;
    char *memPtr;
    char msg[] = "test string";

    fd  = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0666);  
    sem = sem_open(SHM_NAME_SEM, O_CREAT, 0666, 0);  //使用信号量

    if (fd < 0 || sem == SEM_FAILED)  
    {   
        printf("shm_open or sem_open failed..., error: %s \n", strerror(errno));
        
        return -1;  
    }  

    ftruncate(fd, sizeof(sharedMem));  

    memPtr = (char *)mmap(NULL, sizeof(sharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);  
    close(fd);  

    memmove(memPtr, msg, sizeof(msg));  

    printf("process:%d send:%s\n", getpid(), memPtr);

    sem_post(sem);  //使用信号量进行同步
    sem_close(sem);

    return 0;
}
