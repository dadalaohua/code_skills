#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{ 
    int sockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sin_size, iDataNum;
    char buffer[4096];
    int portnumber = 8080;

    if(argc != 2)
    {
         fprintf(stderr, "Usage:%s portnumber\a\n", argv[0]);
         return 0;
    }
    
    //设置端口
    if((portnumber = atoi(argv[1])) < 0)
    {
        fprintf(stderr, "Usage:%s portnumber\a\n", argv[0]);
        return 0;
    }
  
    //AF_INET（TCP/IP – IPv4）
    //SOCK_DGRAM（UDP数据报）
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
    {
        fprintf(stderr, "Socket error:%s\n\a", strerror(errno));
        return 0;
    }
    bzero(&server_addr, sizeof(struct sockaddr_in));    //字符清零
    server_addr.sin_family      =   AF_INET;            //地址类型
    server_addr.sin_addr.s_addr =   htonl(INADDR_ANY);  //IP地址
    server_addr.sin_port        =   htons(portnumber);  //端口号
    
    //将套接字与指定端口相连
    if(bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        return 0;
    }
    
    sin_size = sizeof(struct sockaddr_in);
    
    while(1)
    {
        iDataNum = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &sin_size); 
        
        fprintf(stdout,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
        
        if(iDataNum < 0)
        { 
            perror("Recv\n");
            return 0;
        }
        
        printf("Recv data is %s\n", buffer);

        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    }
    
    close(sockfd);

    return 0;
}