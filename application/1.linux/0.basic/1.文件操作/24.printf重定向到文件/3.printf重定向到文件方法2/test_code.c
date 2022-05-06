#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int fd = open("test.log", O_WRONLY | O_CREAT);
    dup2(fd, 1); //1代表标准输出
    printf("Hello world\n");
    
    close(fd);
    
    return 0;
}