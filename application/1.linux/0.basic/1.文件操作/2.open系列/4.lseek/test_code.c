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
    int fd;
    char *buf = "Hello world";
    fd = open("./testfile", O_RDWR);
    printf("fd = %d\n", fd);
    if(fd == -1) {
        printf("open testfile failed\n");
        fd = open("./testfile", O_RDWR | O_CREAT, 0777);
        if(fd > 0){
            printf("creat testfile success\n");
        }
    }
    //ssize_t write(int fd , const void *buf , size_t count);
    //将缓冲区buf指针指向内存数据，写conut大小到fd。
    write(fd, buf, strlen(buf));
    printf("fd = %d\n", fd);
    close(fd);   //关闭fd文件
    
    char readbuf[50] = {0};
    fd = open("./testfile", O_RDWR);
    int readlen = read(fd, readbuf, strlen(buf));
    printf("read=%d , context:%s\n", readlen, readbuf);
    
    //指向文件开头
    lseek (fd, 0, SEEK_SET); 
    readlen = read(fd, readbuf, strlen(buf));
    printf("read=%d , context:%s\n", readlen, readbuf);
    
    //指向当前位置-5
    lseek (fd, -5, SEEK_CUR); 
    readlen = read(fd, readbuf, 6);
    printf("read=%d , context:%s\n", readlen, readbuf);
    
    //指向文件末尾-5
    lseek (fd, -5, SEEK_END); 
    readlen = read(fd, readbuf, 6);
    printf("read=%d , context:%s\n", readlen, readbuf);
    
    close(fd);
    return 0;
}