#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

/*
https://www.jianshu.com/p/3be00ce8dc76

一，问题：

我在做一个tcp通信的项目，负责客户端，使用非阻塞connect遇到connect阻塞的问题，使用阻塞connect则遇到 EINPROGRESS的错误，需要找到办法解决。特此记录以作学习所用。

二，非阻塞和阻塞connect

对于阻塞式套接字，调用connect函数将激发TCP的三次握手过程，而且仅在连接建立成功或者出错时才返回，阻塞时长几十秒到几分钟不等；
对于非阻塞式套接字，如果调用connect函数会之间返回-1（表示出错），且错误为EINPROGRESS，表示连接建立，建立启动但是尚未完成；
如果返回0，则表示连接已经建立，这通常是在服务器和客户在同一台主机上时发生。

三，解决方法：

select是一种IO多路复用机制，它允许进程指示内核等待多个事件的任何一个发生，并且在有一个或者多个事件发生或者经历一段指定的时间后才唤醒它。connect本身并不具有设置超时功能，如果想对套接字的IO操作设置超时，可使用select函数。

对于select和非阻塞connect，注意两点：[1] 当连接成功建立时，描述符变成可写； [2] 当连接建立遇到错误时，描述符变为即可读，也可写，遇到这种情况，可调用getsockopt函数。

四，实现步骤：

（1） 创建socket，并利用fcntl将其设置为非阻塞
（2） 调用connect函数，如果返回0，则连接建立；如果返回-1，检查errno ，如果值为 EINPROGRESS，则连接正在建立；
（3） 为了控制连接建立时间，将该socket描述符加入到select的可读可写集合中，采用select函数设定超时；
（4） 如果规定时间内成功建立，则描述符变为可写；否则，采用getsockopt函数捕获错误信息；
（5） 恢复套接字的文件状态并返回。
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    if (argc < 3) {
        printf("please input ip and port, for example ./main 120.12.34.56 80.\n");
        return -1;
    }

    char *ipaddr = argv[1];
    unsigned int port = atoi(argv[2]);
    int fd = 0;
    struct sockaddr_in  addr;
    fd_set fdr, fdw;
    struct timeval timeout;
    int err = 0;
    int errlen = sizeof(err);
    fd = socket(AF_INET,SOCK_STREAM,0);
    if (fd < 0) {
        fprintf(stderr, "create socket failed,error:%s.\n", strerror(errno));
        return -1;
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ipaddr, &addr.sin_addr);
    /*设置套接字为非阻塞*/
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        fprintf(stderr, "Get flags error:%s\n", strerror(errno));
        close(fd);
        return -1;
    }

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        fprintf(stderr, "Set flags error:%s\n", strerror(errno));
        close(fd);
        return -1;
    }

    /*阻塞情况下linux系统默认超时时间为75s*/
    int rc = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (rc != 0) {
        if (errno == EINPROGRESS) {
            printf("Doing connection.\n");
            /*正在处理连接*/
            FD_ZERO(&fdr);
            FD_ZERO(&fdw);
            FD_SET(fd, &fdr);
            FD_SET(fd, &fdw);
            timeout.tv_sec = 10;
            timeout.tv_usec = 0;
            rc = select(fd + 1, &fdr, &fdw, NULL, &timeout);
            printf("rc is: %d\n", rc);
            /*select调用失败*/
            if (rc < 0) {
                fprintf(stderr, "connect error:%s\n", strerror(errno));
                close(fd);
                return -1;
            }

            /*连接超时*/
            if (rc == 0) {
                fprintf(stderr, "Connect timeout.\n");
                close(fd);
                return -1;
            }

            /*[1] 当连接成功建立时，描述符变成可写,rc=1*/
            if (rc == 1 && FD_ISSET(fd, &fdw)) {
                printf("Connect success\n");
                close(fd);
                return 0;
            }

            /*[2] 当连接建立遇到错误时，描述符变为即可读，也可写，rc=2 遇到这种情况，可调用getsockopt函数*/
            if (rc == 2) {
                if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
                    fprintf(stderr, "getsockopt(SO_ERROR): %s", strerror(errno));
                    close(fd);
                    return -1;
                }

                if (err) {
                    errno = err;
                    fprintf(stderr, "connect error:%s\n", strerror(errno));
                    close(fd);
                    return -1;
                }
            }
        }

        fprintf(stderr, "connect failed, error:%s.\n", strerror(errno));
        return -1;
    }

    return 0;
}