#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char* argv[])
{ 
    int sockfd;
    struct sockaddr_in server_addr;
    char sendbuffer[200];
    char recvbuffer[200];
    int sin_size, iDataNum;
    struct hostent *host;
    int portnumber = 8080;

    if(argc != 3)
    {
        fprintf(stderr,"Usage :%s hostname portnumber\a\n",argv[0]);
        return 0;
    }
    
    if((host = gethostbyname(argv[1])) == NULL)
    {
        herror("Get host name error\n");
        return 0;
    }
    
    if((portnumber = atoi(argv[2])) < 0)
    {
        fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
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
    server_addr.sin_port        =   htons(portnumber);  //端口号
    server_addr.sin_addr        =   *((struct in_addr *)host->h_addr);  //IP地址
    //inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); //填IP地址的第二个方法
    //server_addr.sin_addr.s_addr =   inet_addr("127.0.0.1"); //填IP地址的第三个方法
    
    sin_size = sizeof(struct sockaddr_in);
    
    while(1)
    {
        printf("Please input your word:\n");
        scanf("%s",sendbuffer);
        printf("\n");
        
        if(strcmp(sendbuffer, "quit")==0)
            break;

        sendto(sockfd, sendbuffer, sizeof(sendbuffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));  

        recvfrom(sockfd, recvbuffer, sizeof(recvbuffer), 0, (struct sockaddr *)&server_addr, &sin_size);  

        printf("recv data of my world is :%s\n",recvbuffer);
    }
    
    close(sockfd);

    return 0;
}