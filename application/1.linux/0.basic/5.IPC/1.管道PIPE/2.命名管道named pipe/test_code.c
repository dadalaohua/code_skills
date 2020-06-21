#include <stdio.h>
#include <fcntl.h>

char *FIFO = "/tmp/my_fifo";  

int main(int argc, char* argv[])
{ 
    char buffer[80];  
    int fd;
    
    unlink(FIFO);  
    mkfifo(FIFO,0666);  
    
    if(fork() > 0)  //父进程
    {  
        char s[] = "hello!\n";
        fd = open(FIFO, O_WRONLY);
        write(fd, s, sizeof(s));
        
        close(fd);
    }
    else  //子进程
    {
        fd = open(FIFO, O_RDONLY);
        read(fd, buffer, 80);
        printf("%s", buffer);
        printf("\n");
        
        close(fd);
    }  

    return 0;
}