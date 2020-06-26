#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_DOMAIN "/tmp/UNIX.domain"

int main(int argc, char* argv[])
{
    int connect_fd;
    struct sockaddr_un srv_addr;
    char snd_buf[1024];
    char rcv_buf[1024];
    int ret;
    int i;

    //create client socket
    connect_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(connect_fd < 0)
    {
        perror("client create socket failed");
        return 1;
    }

    //set server sockaddr_un
    srv_addr.sun_family = AF_UNIX;
    strcpy(srv_addr.sun_path, UNIX_DOMAIN);

    //connect to server
    ret = connect(connect_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if(ret == -1)
    {
        perror("connect to server failed!");
        close(connect_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }

    //receive message from server
    memset(rcv_buf, 0, 1024);
    int rcv_num = read(connect_fd, rcv_buf, sizeof(rcv_buf));
    printf("receive message from server (%d) :%s\n", rcv_num, rcv_buf);
    //printf("\n");

    //send message to server
    memset(snd_buf, 0, 1024);
    strcpy(snd_buf, "message from client");
    printf("sizeof(snd_buf): %d\n", sizeof(snd_buf));
    sleep(2);

    //send message to server
    for(i = 0; i < 4; i++)
    {
        write(connect_fd, snd_buf, sizeof(snd_buf));
    }
    
    close(connect_fd);

    return 0;
}