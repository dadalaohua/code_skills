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

time_t my_timegm(register struct tm * t)
/* struct tm to seconds since Unix epoch */
{
    register long year;
    register time_t result;
#define MONTHSPERYEAR   12      /* months per calendar year */
    static const int cumdays[MONTHSPERYEAR] =
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

    /*@ +matchanyintegral @*/
    year = 1900 + t->tm_year + t->tm_mon / MONTHSPERYEAR;
    result = (year - 1970) * 365 + cumdays[t->tm_mon % MONTHSPERYEAR];
    result += (year - 1968) / 4;
    result -= (year - 1900) / 100;
    result += (year - 1600) / 400;
    if ((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0) &&
        (t->tm_mon % MONTHSPERYEAR) < 2)
        result--;
    result += t->tm_mday - 1;
    result *= 24;
    result += t->tm_hour;
    result *= 60;
    result += t->tm_min;
    result *= 60;
    result += t->tm_sec;
    if (t->tm_isdst == 1)
        result -= 3600;
    /*@ -matchanyintegral @*/
    return (result);
}

/*
mktime()使用tzname检测时区。tzset()从TZ环境变量初始化tzname变量。如果TZ变量出现在环境中，但它的值为空或无法正确解释它的值，则使用UTC。
*/
time_t my_timegm_2(struct tm *tm)
{
    time_t ret;
    char *tz;

    tz = getenv("TZ");
    setenv("TZ", "", 1);
    tzset();
    ret = mktime(tm);
    if (tz)
        setenv("TZ", tz, 1);
    else
        unsetenv("TZ");
    tzset();
    return ret;
}

//使用环境变量修改时区
//timezone 时区
//dir 方向
//例如 东八区 my_timezone_timegm(&now_time, 8, 0)
//例如 西八区 my_timezone_timegm(&now_time, 8, 1)
time_t my_timezone_timegm(struct tm *tm, int timezone, int dir)
{
    time_t ret;
    char *tz;
    char szTime[32];
    sprintf(szTime, "CST%c%d", dir ? '+' : '-', timezone);
    
    tz = getenv("TZ");
    setenv("TZ", szTime, 1);
    tzset();
    ret = mktime(tm);
    if (tz)
        setenv("TZ", tz, 1);
    else
        unsetenv("TZ");
    tzset();
    return ret;
}

//自己计算时区偏差
time_t my_timezone_timegm_2(struct tm *tm, int timezone, int dir)
{
    return my_timegm(tm) + (dir * 2 - 1) *3600 * timezone;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://cloud.tencent.com/developer/ask/sof/102519528
https://stackoverflow.com/questions/530519/stdmktime-and-timezone-info
https://blog.csdn.net/qq_40986747/article/details/104607251
*/
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
    //my_timegm 是Time, Clock, and Calendar Programming In C中发布了一个线程安全版本
    //my_timegm_2 根据timegm manpage的可移植(非线程安全)版本
    //
    printf("%ld %ld %ld %ld\n", mktime(&now_time) - timezone, my_timegm(&now_time), my_timegm_2(&now_time), mktime64(now_time.tm_year + 1900, now_time.tm_mon + 1, now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec));
    
    
    printf("%ld %ld\n", mktime(&now_time), my_timezone_timegm(&now_time, 8, 0));
    
    //每个区减少1小时 3600秒
    for(int i = 0; i < 13; i++) {
        printf(" 东 %d 区 ： %ld \n", i, my_timezone_timegm(&now_time, i, 0));
    }
    printf("\n");
    
    //每个区增加1小时 3600秒
    for(int i = 0; i < 13; i++) {
        printf(" 西 %d 区 ： %ld \n", i, my_timezone_timegm(&now_time, i, 1));
    }
    printf("\n");
    
    printf("%ld %ld\n", mktime(&now_time), my_timezone_timegm_2(&now_time, 8, 0));
    
    //每个区减少1小时 3600秒
    for(int i = 0; i < 13; i++) {
        printf(" 东 %d 区 ： %ld \n", i, my_timezone_timegm_2(&now_time, i, 0));
    }
    printf("\n");
    
    //每个区增加1小时 3600秒
    for(int i = 0; i < 13; i++) {
        printf(" 西 %d 区 ： %ld \n", i, my_timezone_timegm_2(&now_time, i, 1));
    }
    printf("\n");
    
    return 0;
}