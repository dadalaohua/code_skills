#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
int mkfifo(const char *pathname, mode_t mode);
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
char *FIFO = "/tmp/my_fifo";

int test_function(void)
{
    char buffer[128];
    int ret;
    int fd;
    int len;
    
    unlink(FIFO);   //删除文件
    ret = mkfifo(FIFO, 0666);
    if(ret < 0)
        return -1;
    
    if(fork() > 0)  //父进程
    {
        char s[] = "hello!\n";
        fd = open(FIFO, O_WRONLY);
        if(fd < 0)
            return -1;
        write(fd, s, sizeof(s));
        
        close(fd);
    }
    else  //子进程
    {
        fd = open(FIFO, O_RDONLY);
        if(fd < 0)
            return -1;
        len = read(fd, buffer, sizeof(buffer));
        if(len > 0)
            printf("len:%d buffer:%s\n", len, buffer);
        else
            printf("len:%d\n", len);
        
        close(fd);
    }
    
    exit(0);
}

int test_function_2(void)
{
    char buffer[128];
    int ret;
    int fd;
    int len;
    
    unlink("testfifo"); //删除文件
    ret = mkfifo("testfifo", 0666);
    if(ret < 0)
        return -1;
    
    if(fork() > 0)  //父进程
    {
        fd = open(FIFO, O_RDONLY);
        if(fd < 0)
            return -1;
        len = read(fd, buffer, sizeof(buffer));
        if(len > 0)
            printf("len:%d buffer:%s\n", len, buffer);
        else
            printf("len:%d\n", len);
        
        close(fd);
    }
    else  //子进程
    {
        char s[] = "hello!\n";
        fd = open(FIFO, O_WRONLY);
        if(fd < 0)
            return -1;
        write(fd, s, sizeof(s));
        
        close(fd);
    }
    
    exit(0);
}

int main(int argc, char* argv[])
{ 
    test_function();
    //test_function_2();
    
    return 0;
}