#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// 源码
// /kernel/time/time.c
// 算法解析
// https://blog.csdn.net/axx1611/article/details/1792827?reload

uint64_t mktime64(const unsigned int year0, const unsigned int mon0,
        const unsigned int day, const unsigned int hour,
        const unsigned int min, const unsigned int sec)
{
    unsigned int mon = mon0, year = year0;

    /* 1..12 -> 11,12,1..10 */
    if (0 >= (int) (mon -= 2)) {
        mon += 12;  /* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((((uint64_t)
          (year/4 - year/100 + year/400 + 367*mon/12 + day) +
          year*365 - 719499
        )*24 + hour /* now have hours - midnight tomorrow handled here */
      )*60 + min /* now have minutes */
    )*60 + sec; /* finally seconds */
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct tm now_time = {0};
    
    now_time.tm_year = 2023 - 1900;
    now_time.tm_mon  = 9 - 1;
    now_time.tm_mday = 10;
    now_time.tm_hour = 15;
    now_time.tm_min  = 17;
    now_time.tm_sec  = 0;
    
    //mktime返回的是本地时区，也就是北京时间的东八区，需要减去timezone获得UTC
    printf("%ld %ld\n", mktime(&now_time) - timezone, mktime64(now_time.tm_year + 1900, now_time.tm_mon + 1, now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec));
    
#if 0
    //测试所有时间的准确性
    for(int year = 1970; year < 2100; year++) {
        for(int mon = 1; mon < 13; mon++) {
            for(int mday = 1; mday < 29; mday++) {
                for(int hour = 0; hour < 24; hour++) {
                    for(int min = 0; min < 60; min++) {
                        for(int sec = 0; sec < 60; sec++) {
                            now_time.tm_year = year - 1900;
                            now_time.tm_mon  = mon - 1;
                            now_time.tm_mday = mday;
                            now_time.tm_hour = hour;
                            now_time.tm_min  = min;
                            now_time.tm_sec  = sec;
                            
                            //UTC
                            time_t mktime_time = mktime(&now_time) - timezone;  //mktime返回的是本地时区，也就是北京时间的东八区，需要减去timezone获得UTC
                            uint64_t mktime64_time = mktime64(now_time.tm_year + 1900, now_time.tm_mon + 1, now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
                            if(mktime_time != mktime64_time) {
                                printf("mktime_time %ld mktime64_time %ld\n", mktime_time, mktime64_time);
                                printf("%4.4d年%2.2d月%2.2d日，%2.2d:%2.2d:%2.2d\n", now_time.tm_year+1900, now_time.tm_mon+1, now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
                                exit(0);
                            }
                        }
                    }
                }
            }
        }
    }
#endif
    
    return 0;
}