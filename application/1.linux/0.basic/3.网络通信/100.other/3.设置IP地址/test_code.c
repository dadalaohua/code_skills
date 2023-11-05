#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define NETWORK_CARD    "eth0"
#define IPADDR          "192.168.31.50"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void set_ip(char* network_card, char* ipaddr)
{
    struct ifreq ifr;
    struct sockaddr_in sai;
    int sockfd;                     /* socket fd we use to manipulate stuff with */

    char *p;

    /* Create a channel to the NET kernel. */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    /* get interface name */
    strncpy(ifr.ifr_name, network_card, strlen(network_card) + 1);

    memset(&sai, 0, sizeof(struct sockaddr));
    sai.sin_family = AF_INET;
    sai.sin_port = 0;

    sai.sin_addr.s_addr = inet_addr(ipaddr);

    p = (char *) &sai;
    memcpy( (((char *)&ifr + offsetof(struct ifreq, ifr_addr) )),
                    p, sizeof(struct sockaddr));

    ioctl(sockfd, SIOCSIFADDR, &ifr);
    ioctl(sockfd, SIOCGIFFLAGS, &ifr);

    ifr.ifr_flags |= IFF_UP | IFF_RUNNING;
    // ifr.ifr_flags &= ~selector;  // unset something

    ioctl(sockfd, SIOCSIFFLAGS, &ifr);
    close(sockfd);
}

int ip_mac_check(void)
{
    int sock;
    int ret;
    struct ifreq ifr;
    int result = -1;
 
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        return result;
    }

    strcpy(ifr.ifr_name, NETWORK_CARD);
    ret = ioctl(sock, SIOCGIFADDR, &ifr);
    printf("res : %d\n", ret);
    if(ret < 0) {
        printf("Get IP failure %d\n", ret);

        set_ip(NETWORK_CARD, IPADDR);
    } else {
        printf("IP: %s\n",inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
    }
 
    strcpy(ifr.ifr_name, NETWORK_CARD);
    ret = ioctl(sock, SIOCGIFHWADDR, &ifr);
    if(ret < 0) {
        close(sock);
        return result;
    }

    int i;
    char mac[32];
    for(i = 0; i < 6; ++i) {
        sprintf(mac + 3*i, "%02x:", (unsigned char)ifr.ifr_hwaddr.sa_data[i]);
    }
    printf("ret : %d\n", ret);
    printf("MAC: %s\n", mac);

    close(sock);

    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%d\n", ip_mac_check());
    return 0;
}