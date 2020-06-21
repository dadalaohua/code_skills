#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>      //包含errno所需要的头文件 
#include <string.h>     //包含strerror所需要的头文件  
#include <fcntl.h>
#include <sys/mman.h>

#define PATH_NAME "/tmp/memmap"  

int main(int argc, char* argv[])
{
    int *memPtr;  
    int fd;  

    fd = open(PATH_NAME, O_RDWR | O_CREAT, 0666);  
    if (fd < 0)  
    {  
        printf("open file %s failed..., error: %s \n", PATH_NAME, strerror(errno));
        
        return -1;  
    }
    
    printf("open file %s success\n", PATH_NAME);

    memPtr = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);  
    close(fd);  

    if (memPtr == MAP_FAILED)  
    {  
        printf("mmap failed, error: %s \n", strerror(errno));
        
        return -1;  
    }  

    printf("process:%d receive:%d\n", getpid(), *memPtr);    

    return 0;
}