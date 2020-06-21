#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>      //包含errno所需要的头文件 
#include <string.h>     //包含strerror所需要的头文件  
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char* argv[])
{ 
    int *memPtr;  

    memPtr = (int *) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);  
    if (memPtr == MAP_FAILED)  
    {
        printf("mmap failed, error: %s \n", strerror(errno));
        
        return -1;  
    }

    *memPtr = 0;  
    
    if (fork() == 0)  
    {  
        *memPtr = 1;
        
        printf("child:set memory %d\n", *memPtr);

        exit(0);  
    }
    else
    {
        sleep(1);  

        printf("parent:memory value %d\n", *memPtr);
        
        exit(0);
    }

    return 0;
}