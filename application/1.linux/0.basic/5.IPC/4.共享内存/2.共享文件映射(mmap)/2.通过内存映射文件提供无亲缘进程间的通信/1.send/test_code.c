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

    ftruncate(fd, sizeof(int));  //将参数fd指定的文件大小改为参数length指定的大小

    memPtr = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);  
    close(fd);  

    if (memPtr == MAP_FAILED)  
    { 
        printf("mmap failed, error: %s \n", strerror(errno));
        
        return -1;  
    }

    *memPtr = 111;
    printf("process:%d send:%d\n", getpid(), *memPtr);

    return 0;
}