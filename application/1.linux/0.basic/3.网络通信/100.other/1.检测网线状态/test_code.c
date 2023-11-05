#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


/*

$ cat /sys/class/net/eth0/carrier
1

1表示接上，０表示没接上。

下面的命令表示网线状态是 UP还是DOWN:

$ cat /sys/class/net/eth0/operstate
up

Down的话可以用命令 UP起来：
*/

#define CARRIER_PATH    "/sys/class/net/eth0/carrier"
#define OPERSTATE_PATH  "/sys/class/net/eth0/operstate"
/************************************************************************/
/*                                                                      */
/************************************************************************/
int connect_check_real(void)
{
    int ret;
    int fp;
    char status[10] = {0};
    int result = -1;
    //一定要只读模式打开,读写模式打开不可以  
    int skfd = open(CARRIER_PATH, O_RDONLY) ;
    if(skfd < 0) {
        printf("cat eth0 error!\n") ;
    } else {
        printf("cat eth0 success! %d\n", skfd);
        
        ret = read(skfd, status, 10);
        printf("carrier %d status:%s\n",ret, status);
    
        if(status[0] == '1') {
            result = 0;
        }
        close(skfd);
    }
    
    fp = open (OPERSTATE_PATH, O_RDONLY);
    
    if (fp < 0) {
        printf("open file operstate failure %d\n", fp);
        return -1;
    }
    
    memset(status,0,sizeof(status));
    ret = read (fp, status, 10);
    printf("ret %d status:%s\n", ret, status);
    if (NULL != strstr(status, "up")) {
        printf("on line now \n");
    } else if (NULL != strstr(status, "down")) {
        printf("off off \n");
    
        result = -1;
    } else {
        printf("unknow error\n");
    
        result = -1;
    }
    
    close (fp);
    
    return result;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%d\n", connect_check_real());
    return 0;
}