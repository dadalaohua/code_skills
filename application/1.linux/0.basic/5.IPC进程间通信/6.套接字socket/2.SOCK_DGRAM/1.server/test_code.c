#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_DOMAIN "/tmp/UNIX.domain"

int main(int argc, char* argv[])
{ 
    int sockfd = 0;
    struct sockaddr_un addr;
    char recv_buf[20] = "";
    unsigned int len;

    unlink(UNIX_DOMAIN);
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, UNIX_DOMAIN);
    
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sockfd < 0 )
    {
        perror("socket error");
        exit(-1);
    }
    
    len = strlen(addr.sun_path) + sizeof(addr.sun_family);
    if(bind(sockfd, (struct sockaddr *)&addr, len) < 0)
    {
        perror("bind error");
        close(sockfd);
        exit(-1);
    }   
    printf("Bind is ok\n");
    
    while(1)
    {
        len = strlen(addr.sun_path) + sizeof(addr.sun_family);
        recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&addr, &len);
        printf("Recv: %s\n",recv_buf);
    }
    
    close(sockfd);

    return 0;
}