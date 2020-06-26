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
    char send_buf[20] = "";
    unsigned int len;
    int counter = 0;

    bzero(&addr,sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, UNIX_DOMAIN);
    
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sockfd < 0 )
    {
        perror("socket error");
        exit(-1);
    }
    
    while(1)
    {
        counter++;
        sprintf(send_buf,"Counter is %d",counter);
        
        len = strlen(addr.sun_path) + sizeof(addr.sun_family);
        sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr*)&addr, len);
        printf("Send: %s\n",send_buf);
        
        sleep(2);
    }
    
    close(sockfd);

    return 0;
}