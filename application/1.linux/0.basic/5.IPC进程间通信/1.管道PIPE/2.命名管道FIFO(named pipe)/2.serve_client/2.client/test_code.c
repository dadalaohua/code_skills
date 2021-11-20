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
    char s1[] = "hello!\n";
    char s2[] = "world!\n";
    
    fd = open(FIFO, O_WRONLY);
    if(fd < 0)
        return -1;
    
    write(fd, s1, sizeof(s1));
    write(fd, s2, sizeof(s2));
    
    sleep(1);
    
    close(fd);
    
    return 0;
}