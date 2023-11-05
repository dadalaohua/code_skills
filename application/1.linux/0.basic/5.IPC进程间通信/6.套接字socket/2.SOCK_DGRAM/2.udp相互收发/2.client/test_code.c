#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_DOMAIN "/tmp/SERVER.domain"
#define CLIENT_DOMAIN "/tmp/CLIENT.domain"

int main(int argc, char* argv[])
{ 
    int sockfd = 0;
    struct sockaddr_un send_addr;
    struct sockaddr_un recv_addr;
    char send_buf[512] = {0};
    char recv_buf[512] = {0};
    unsigned int len;
    int counter = 0;

    unlink(CLIENT_DOMAIN);
    bzero(&recv_addr,sizeof(recv_addr));
    recv_addr.sun_family = AF_UNIX;
    strcpy(recv_addr.sun_path, CLIENT_DOMAIN);
    
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sockfd < 0 ) {
        perror("socket error");
        exit(-1);
    }
    
    len = strlen(recv_addr.sun_path) + sizeof(recv_addr.sun_family);
    if(bind(sockfd, (struct sockaddr *)&recv_addr, len) < 0) {
        perror("bind error");
        close(sockfd);
        return -1;
    }   
    printf("Bind is ok\n");
    
    bzero(&send_addr,sizeof(send_addr));
    send_addr.sun_family = AF_UNIX;
    strcpy(send_addr.sun_path, SERVER_DOMAIN);
    
    int ret;
    while(1) {
        counter++;
        sprintf(send_buf,"Counter is %d",counter);
        
        ret = sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr*)&send_addr, sizeof(send_addr));
        printf("ret %d Send: %s\n", ret, send_buf);
        
        struct sockaddr_un addr;
        len = sizeof(addr);
        ret = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&addr, &len);
        printf("ret %d Recv: %s\n", ret, recv_buf);
        
        sleep(2);
    }
    
    close(sockfd);
    unlink(CLIENT_DOMAIN);

    return 0;
}