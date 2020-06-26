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
    struct stat fileStat;

    fd = shm_open(SHM_NAME, O_RDWR, 0);
    sem = sem_open(SHM_NAME_SEM, 0);

    if (fd < 0 || sem == SEM_FAILED)  
    {  
        printf("shm_open or sem_open failed..., error: %s \n", strerror(errno));
        
        return -1;  
    }
    
    fstat(fd, &fileStat);

    memPtr = (char *)mmap(NULL, fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    sem_wait(sem);
 
    printf("process:%d recv:%s\n", getpid(), memPtr);

    sem_close(sem);

    return 0;
}
