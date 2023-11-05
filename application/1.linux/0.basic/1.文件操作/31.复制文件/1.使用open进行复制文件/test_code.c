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
int cp_file(const char* src_path, const char* dst_path)
{
    int src_fd, dst_fd;
    char buff[1024];
    int len;
    
    src_fd = open(src_path, O_RDWR|O_CREAT);
    if(src_fd == -1) {
        return -1;
    }
    dst_fd = open(dst_path, O_RDWR|O_CREAT);
    if(dst_fd == -1) {
        close(src_fd);
        return -1;
    }
    
    while((len = read(src_fd, buff, 1024))) {
        write(dst_fd, buff, len);
    }
    
    close(src_fd);
    close(dst_fd);
    
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("cp file %d \n", cp_file("Makefile", "cpMakefile"));
    return 0;
}