#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/if.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//如果网卡已连上网线，返回0，否则返回-1.
int check_nic(char *nic)
{
    struct ifreq ifr;
    int skfd = socket(AF_INET, SOCK_DGRAM, 0);

    strcpy(ifr.ifr_name, nic);
    if (ioctl(skfd, SIOCGIFFLAGS, &ifr) < 0) {
        close(skfd);
        return -1;
    }
    close(skfd);
    //printf("0x%x 0x%x 0x%x\n", ifr.ifr_flags, IFF_RUNNING, IFF_UP);
    if(ifr.ifr_flags & IFF_RUNNING)
        return 0;  // 网卡已插上网线
    else 
        return -1;
}

int main(int argc, char* argv[])
{
    printf("%s %d\n", "eth0", check_nic("eth0"));
    return 0;
}