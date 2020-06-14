#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{ 
    int sockfd, new_fd;
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
    //SOCK_STREAM（TCP流）
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
        fprintf(stderr, "Socket error:%s\n\a", strerror(errno));
        return 0;
    }
    bzero(&server_addr, sizeof(struct sockaddr_in));    //字符清零
    server_addr.sin_family      =   AF_INET;            //地址类型
    server_addr.sin_addr.s_addr =   htonl(INADDR_ANY);  //设置本机IP地址
    server_addr.sin_port        =   htons(portnumber);  //设置本机端口号
    
    //将套接字与指定端口相连
    if(bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        return 0;
    }
    
    //指定相应的套接字变为被动连接,使得流套接字sockfd处于监听状态,设置最大连接为5
    if(listen(sockfd, 5) == -1)
    {
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        return 0;
    }
    
    sin_size = sizeof(struct sockaddr_in);
    

    //等待并接受客户请求
    if((new_fd = accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size)) == -1)
    {
        fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
        return 0;
    }
    
    fprintf(stdout,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));

    while(1)
    {
        iDataNum = recv(new_fd, buffer, sizeof(buffer), 0);
        if(iDataNum <= 0)
        { 
            perror("Recv\n");
            return 0;
        }
        printf("Recv len %d ,Recv data is %s\n", iDataNum, buffer);
        
        iDataNum = send(new_fd, buffer, iDataNum, 0);
        if(iDataNum < 0)
        { 
            perror("Send\n");
            return 0;
        }
        printf("Send len %d ,Send data is %s\n", iDataNum, buffer);
        
        memset(buffer, 0, sizeof(buffer));
    }
    
    close(new_fd);
    close(sockfd);

    return 0;
}
