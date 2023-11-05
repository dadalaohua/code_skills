#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_DOMAIN "/tmp/SERVER.domain"

int main(int argc, char* argv[])
{ 
    int sockfd = 0;
    struct sockaddr_un addr;
    char recv_buf[512] = {0};
    unsigned int len;

    unlink(SERVER_DOMAIN);
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_DOMAIN);
    
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sockfd < 0 ) {
        perror("socket error");
        exit(-1);
    }
    
    len = strlen(addr.sun_path) + sizeof(addr.sun_family);
    if(bind(sockfd, (struct sockaddr *)&addr, len) < 0) {
        perror("bind error");
        close(sockfd);
        exit(-1);
    }   
    printf("Bind is ok\n");
    
    int ret;
    while(1)
    {
        struct sockaddr_un recv_addr;
        len = sizeof(recv_addr);
        ret = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&recv_addr, &len);
        printf("ret %d Recv: %s\n", ret, recv_buf);
        
        struct sockaddr_un send_addr;
        bzero(&send_addr, sizeof(send_addr));
        send_addr.sun_family = AF_UNIX;
        strcpy(send_addr.sun_path, recv_addr.sun_path);
        
        ret = sendto(sockfd, recv_buf, strlen(recv_buf), 0, (struct sockaddr*)&send_addr, sizeof(send_addr));
        printf("ret %d Send: %s\n", ret, recv_buf);
    }
    
    close(sockfd);
    unlink(SERVER_DOMAIN);

    return 0;
}