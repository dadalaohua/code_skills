#include <stdio.h>
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

int main(int argc, char* argv[])
{ 
    char buffer[128];  
    int fd;
    int ret;
    int len;
    
    unlink(FIFO);   //删除文件
    ret = mkfifo(FIFO, 0666);
    if(ret < 0)
        return -1;
    
    fd = open(FIFO, O_RDONLY);
    if(fd < 0)
        return -1;
    
    while(1)
    {
        len = read(fd, buffer, sizeof(buffer));
        if(len > 0)
            printf("%s\n", buffer);
        else if(len == 0)
        {
            printf("client quit\n");
            break;
        }
        else
        {
            printf("error %d\n", len);
            break;
        }
    }
    
    close(fd);
    
    return 0;
}