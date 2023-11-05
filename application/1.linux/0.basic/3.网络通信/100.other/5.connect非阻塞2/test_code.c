#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

/*
linux将connect函数设置为非阻塞的模式
https://blog.csdn.net/w_weixiaotao/article/details/107764786

Linux中connect函数有两种情况：
1、如果是连接本机的IP地址，connect函数是不阻塞的，连接成功就返回0，connect连接失败就返回-1.
2、如果是连接外部设备，connect函数默认是阻塞的，将connect函数设为不阻塞有这样几种方法：

利用signal和定时器函数alarm可以将connect函数的阻塞中断掉，但是TCP连接没有中断，在后续的时间内，如果外部设备打开之后，不用调用connect函数自己就会进行连接，
*/

//1ms中断
void sigroutine(int signo)
{
   // switch (signo){
       // case SIGALRM:
           // signal(SIGALRM, sigroutine);
           // break;
   // }
   return;
}

int main(int argc, char* argv[])
{ 
    int sockfd;
    char sendbuffer[200];
    char recvbuffer[200];
    struct sockaddr_in server_addr;
    struct hostent *host;
    int portnumber, nbytes;
    
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
    
    bzero(&server_addr,sizeof(server_addr));                        //字符清零
    server_addr.sin_family  =   AF_INET;                            //地址类型
    server_addr.sin_port    =   htons(portnumber);                  //端口号
    server_addr.sin_addr    =   *((struct in_addr *)host->h_addr);  //IP地址
    //inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); //填IP地址的第二个方法
    //server_addr.sin_addr.s_addr =   inet_addr("127.0.0.1"); //填IP地址的第三个方法
    
    sigset(SIGALRM, sigroutine);
    alarm(2);
    if(connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr,"Connect error:%s\n",strerror(errno));
        return 0;
    }
    alarm(0);
    
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
