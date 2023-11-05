#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main(int argc, char* argv[])
{ 
    int sockfd;
    char sendbuffer[200];
    char recvbuffer[200];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct hostent *host;
    int portnumber, nbytes;
    int local_port = 8080;  //设置本地端口
    
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
    //SOCK_STREAM（TCP流）
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
        return 0;
    }
    
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(local_port);  // 指定客户端的通讯端口
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //设置本机IP地址
    
    if (bind(sockfd, (struct sockaddr *)&client_addr,sizeof(client_addr)) != 0) {
        printf("bind error: %s \n", strerror(errno));
        close(sockfd);
        return -1;
    }
    
    bzero(&server_addr,sizeof(server_addr));                        //字符清零
    server_addr.sin_family  =   AF_INET;                            //地址类型
    server_addr.sin_port    =   htons(portnumber);                  //端口号
    server_addr.sin_addr    =   *((struct in_addr *)host->h_addr);  //IP地址
    //inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); //填IP地址的第二个方法
    //server_addr.sin_addr.s_addr =   inet_addr("127.0.0.1"); //填IP地址的第三个方法
    
    if(connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr,"Connect error:%s\n",strerror(errno));
        return 0;
    }
    
    while(1)
    {
        printf("Please input your word:\n");
        scanf("%s",sendbuffer);
        printf("\n");
        
        if(strcmp(sendbuffer,"quit")==0)
            break;
        
        nbytes = send(sockfd, sendbuffer, sizeof(sendbuffer), 0);
        if(nbytes < 0)
        { 
            perror("Send\n");
            return 0;
        }
        
        nbytes = recv(sockfd, recvbuffer, sizeof(recvbuffer), 0);
        if(nbytes < 0)
        { 
            perror("Recv\n");
            return 0;
        }
        printf("rece len %d, recv data of my world is :%s\n", nbytes, recvbuffer);
        
        memset(sendbuffer, 0, sizeof(sendbuffer));
        memset(recvbuffer, 0, sizeof(recvbuffer));
    }

    close(sockfd);

    return 0;
}
