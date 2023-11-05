#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
https://blog.csdn.net/qq_43379523/article/details/123090937
*/

#define IP "85.199.214.100"    // "0.uk.pool.ntp.org"
#define PORT 123
 
//此函数是实现秒数转换成UTC时间
void Calc_Time(unsigned long Second_data)
{
    const int Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned long Year = 1970;
    unsigned long Month = 1;
    unsigned long Day = 1;
    unsigned long Hour = 0;
    unsigned long Min = 0;
    unsigned long Second = 0;
 
    unsigned int Pass4year;
    int hours_per_year;
    if(Second_data < 0) {
        Second_data = 0;
    }
    Second = Second_data % 60;   //取秒
    Second_data /= 60;
    Min = Second_data % 60;     //取分
    Second_data /= 60;   //余下的小时
 
    //过去有多少个4年，每4年有 1461*24小时
    Pass4year = Second_data / (1461 * 24);
    //计算年份
    Year = 1970 + Pass4year * 4;
    //剩下的小时数
    Second_data = Second_data % (1461 * 24);
    //校正闰年影响的年份，计算一年中剩下的小时数
    for(;;) {
        //一年的hour = 365*24
        hours_per_year = 365 * 24;
        //判断闰年
        if((((Year % 4) == 0) && ((Year % 100) != 0)) || ((Year % 400) == 0)) {
            hours_per_year += 24;
        }
        if(Second_data < hours_per_year){
            break;
        }
        Year++;
        Second_data -= hours_per_year;
    }
    //小时数
    Hour = Second_data % 24;
 
    Second_data /= 24;  //剩下的天数
 
    Second_data += 1;   //天数从1号开始
 
    if((((Year % 4) == 0) && ((Year % 100) != 0)) || ((Year % 400) == 0)) {
        if(Second_data >60) {
            Second_data--;
        } else {
            if(Second_data == 60) {
                Day = 29;
                Month = 1;
                return;
            }
        }
    }
    
    //计算月日
    for(Month = 0;Days[Month]<Second_data;Month++){
        Second_data -= Days[Month];
    }
    Day = Second_data;
    Month = Month + 1;
    printf("Year [%ld] :Month [%ld]: Day [%ld] :Hour  [%ld]: Min  [%ld]: Second  [%ld]\n", Year, Month, Day, Hour, Min, Second);
    return;
}

int main()
{
    int fb = 0, len = 0;
    char buf[48]={'\0'};
    buf[0] = 3 | (4 << 3);
    struct sockaddr_in server_addr;
    len = sizeof(server_addr);
    
    //创建套接字
    fb = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);
    bind(fb, (struct sockaddr *)&server_addr, len);
 
    //发送数据
    int ret = sendto(fb, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, len);
    if(ret < len)
        return 0;
    bzero(buf, 48);
        //接收数据
    int rec = recvfrom(fb, buf, 48, 0, (struct sockaddr *)&server_addr, (socklen_t*)&len);
    printf("收到信息长度[%d]\n", rec);
    printf("收到发来的信息buf :\n");
    for(int i = 0; i < rec; i++){
        printf("0x%02x,", (unsigned char)buf[i]);
    }
    printf("\n");
    
    int t = 0;
    for(int i = 40; i <= 43; i++){
        unsigned char c = (unsigned char)buf[i];
        t = (t << 8) | c;
    }
    
    t -= 2208988800;    // (1970 - 1900) in seconds //1970.1.1 0:0:0
    t += 8 * 60 * 60;   // UTC to Beijin
    
    printf("收到时间 %d s\n", t);
    
    Calc_Time(t);
    
    close(fb);
    
    return 0;
}