#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_DOMAIN "/tmp/UNIX.domain"

int main(int argc, char* argv[])
{
    int lsn_fd, apt_fd;
    struct sockaddr_un srv_addr;
    struct sockaddr_un clt_addr;
    socklen_t clt_len;
    int ret;
    int i;
    char recv_buf[1024];
    char send_buf[1024];

    //create socket to bind local IP and PORT
    lsn_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(lsn_fd < 0)
    {
        perror("can't create communication socket!");
        return 1;
    }

    //create local IP and PORT
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, UNIX_DOMAIN, sizeof(srv_addr.sun_path) - 1);
    unlink(UNIX_DOMAIN);

    //bind sockfd and sockaddr
    ret = bind(lsn_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if(ret == -1)
    {
        perror("can't bind local sockaddr!");
        close(lsn_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }

    //listen lsn_fd, try listen 1
    ret = listen(lsn_fd, 1);
    if(ret == -1)
    {
        perror("can't listen client connect request");
        close(lsn_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }

    clt_len = sizeof(clt_addr);
    while(1)
    {
        apt_fd = accept(lsn_fd, (struct sockaddr*)&clt_addr, &clt_len);
        if(apt_fd < 0)
        {
            perror("can't listen client connect request");
            close(lsn_fd);
            unlink(UNIX_DOMAIN);
            return 1;
        }

        printf("received a connection\n");
        printf("send message to client\n");
        memset(send_buf, 0, 1024);
        strcpy(send_buf, "Hello, you have connected to server succeed");

        int snd_num = write(apt_fd, send_buf, 1024);
        if(snd_num != 1024)
        {
            perror("send messge to client failed\n");
            close(apt_fd);
            close(lsn_fd);
            unlink(UNIX_DOMAIN);
            return 1;
        }
        //read and printf client info
        printf("============info=================\n");
        for(i = 0; i < 4; i++)
        {
            memset(recv_buf, 0, 1024);
            int rcv_num = read(apt_fd, recv_buf, sizeof(recv_buf));
            printf("Message from client (%d) :%s\n", rcv_num, recv_buf);
        }
    }
    close(apt_fd);
    close(lsn_fd);
    unlink(UNIX_DOMAIN);

    return 0;
}