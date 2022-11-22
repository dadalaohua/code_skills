#include <stdio.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://mp.weixin.qq.com/s/MzXPmzN1pvv7oLUT_RNkIA
*/

time_t get_utc_time(void)
{
    return time(NULL);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    time_t utc_time = get_utc_time();   //UTC时间
    printf("utc_time = %ld s\n", utc_time);

    struct tm *gmt_tm = gmtime(&utc_time); //GMT时间
    printf("gmt time = %.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", gmt_tm->tm_year + 1900,
                                                         gmt_tm->tm_mon + 1,
                                                         gmt_tm->tm_mday,
                                                         gmt_tm->tm_hour,
                                                         gmt_tm->tm_min,
                                                         gmt_tm->tm_sec);
    int gmt_hour = gmt_tm->tm_hour;

    struct tm *local_tm = localtime(&utc_time); //本地时区表示
    printf("local time = %.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", local_tm->tm_year + 1900,
                                                           local_tm->tm_mon + 1,
                                                           local_tm->tm_mday,
                                                           local_tm->tm_hour,
                                                           local_tm->tm_min,
                                                           local_tm->tm_sec);
    int local_hour = local_tm->tm_hour;


    int local_time_zone = local_hour - gmt_hour;
    if (local_time_zone < -12) 
    {
        local_time_zone += 24; 
    } 
    else if (local_time_zone > 12) 
    {
        local_time_zone -= 24;
    }else{}

    printf("local_time_zone = %d\n", local_time_zone);

    return 0;
}