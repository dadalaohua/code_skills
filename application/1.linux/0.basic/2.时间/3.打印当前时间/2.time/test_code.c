#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/
void getNowtime_0(void) {
    time_t current_time;
 
    time(&current_time);

    //1970年1月1日0时0分0秒(一般是)到当前时间的秒数
    printf("time: %ld\n", current_time);

    //方法二：直接返回，值填NULL
    printf("time: %ld\n", time(NULL));
    
    current_time = time(NULL);
    printf("time: %ld\n", time(NULL));
    
    //sleep(1);
    
    //求time1和time2 的差值
    //double difftime( time_t time1 , time_t time2 );
    printf("difftime: %f\n", difftime(time(NULL), current_time));
}

// /* Used by other time functions.  */
// struct tm
// {
//   int tm_sec;			/* Seconds.	[0-60] (1 leap second) */ 秒
//   int tm_min;			/* Minutes.	[0-59] */ 分
//   int tm_hour;			/* Hours.	[0-23] */ 时
//   int tm_mday;			/* Day.		[1-31] */ 日
//   int tm_mon;			/* Month.	[0-11] */ 月份
//   int tm_year;			/* Year	- 1900.  */ 星期 - 取值区间[0, 6]，0代表星期天，1代表星期1
//   int tm_wday;			/* Day of week.	[0-6] */ 星期 - 取值区间[0, 6]，0代表星期天，1代表星期1
//   int tm_yday;			/* Days in year.[0-365]	*/ 从每年的1月1日开始的天数-取值区间为[0, 365]，0代表1月1日
//   int tm_isdst;			/* DST.		[-1/0/1]*/  夏令时标识符，使用夏令时，tm_isdst为正，不使用夏令时，tm_isdst为0，不了解情况时，tm_isdst为负
// 
// # ifdef	__USE_MISC
//   long int tm_gmtoff;		/* Seconds east of UTC.  */ 指定了日期变更线东面时区中UTC东部时区正秒数或UTC西部时区的负秒数
//   const char *tm_zone;		/* Timezone abbreviation.  */ 当前时区的名字(与环境变量TZ有关)
// # else
//   long int __tm_gmtoff;		/* Seconds east of UTC.  */
//   const char *__tm_zone;		/* Timezone abbreviation.  */
// # endif
// };

void getNowtime_1(void) {
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};  
    time_t current_time;
    struct tm* now_time;
 
    time(&current_time);
    
    //本地时间（受时区影响，与环境变量TZ有关）
    now_time = localtime(&current_time);    //将time()返回的time_t类型数据转化为当前系统的真实时间，并将该转化结果返回。

    printf("%4.4d年%2.2d月%2.2d日，%2.2d:%2.2d:%2.2d %s\n", now_time->tm_year+1900, now_time->tm_mon+1, now_time->tm_mday, 
                                                            now_time->tm_hour, now_time->tm_min, now_time->tm_sec, wday[now_time->tm_wday]);

    //char *asctime (const struct tm *__tp);
    //asctime( )将参数p_tm指向的tm结构体数据转换成实际使用的时间日期表示方法，并以字符串形式返回(与ctime函数相同)。字符串格式为："Thu Jun  1 20:16:21 2023\n"。
    printf("%s", asctime(now_time));
    
    //char *ctime (const time_t *__timer)
    //同asctime, ctime一律使用当地时间，asctime则用tm结构内的timezone资讯来表示。
    printf("%s", ctime(&current_time));

    //time_t mktime( struct tm* p_tm );
    //tm --> time_t
    printf("%ld %ld\n", mktime(now_time), current_time);

    //国际标准时间（GMT）,差了8个小时
    now_time = gmtime(&current_time);   /*获取GMT时间*/
    printf("%4.4d年%2.2d月%2.2d日，%2.2d:%2.2d:%2.2d %s\n", now_time->tm_year+1900, now_time->tm_mon+1, now_time->tm_mday, 
                                                            now_time->tm_hour, now_time->tm_min, now_time->tm_sec, wday[now_time->tm_wday]);

    printf("%s", asctime(now_time));
}

/*
%a 星期几的简写
%A 星期几的全称
%b 月分的简写
%B 月份的全称
%c 标准的日期的时间串
%C 年份的后两位数字
%d 十进制表示的每月的第几天
%D 月/天/年
%e 在两字符域中，十进制表示的每月的第几天
%F 年-月-日
%g 年份的后两位数字，使用基于周的年
%G 年分，使用基于周的年
%h 简写的月份名
%H 24小时制的小时
%I 12小时制的小时
%j 十进制表示的每年的第几天
%m 十进制表示的月份
%M 十时制表示的分钟数
%n 新行符
%p 本地的AM或PM的等价显示
%r 12小时的时间
%R 显示小时和分钟：hh:mm
%S 十进制的秒数
%t 水平制表符
%T 显示时分秒：hh:mm:ss
%u 每周的第几天，星期一为第一天 （值从0到6，星期一为0）
%U 第年的第几周，把星期日做为第一天（值从0到53）
%V 每年的第几周，使用基于周的年
%w 十进制表示的星期几（值从0到6，星期天为0）
%W 每年的第几周，把星期一做为第一天（值从0到53）
%x 标准的日期串
%X 标准的时间串
%y 不带世纪的十进制年份（值从0到99）
%Y 带世纪部分的十进制年份
%z，%Z 时区名称，如果不能得到时区名称则返回空字符。
%% 百分号
*/
void getNowtime_2(void) {
    time_t current_time;
    struct tm* now_time;

    time(&current_time);
    now_time = localtime(&current_time);

    char YMD[15] = {0};
    char HMS[10] = {0};
    strftime(YMD, sizeof(YMD), "%F ", now_time);    //将时间格式化为年-月-日
    strftime(HMS, sizeof(HMS), "%T", now_time);     //将时间格式化为显示时分秒：hh:mm:ss

    printf("\nCurrent time: %s %s\n", YMD, HMS);
    
    char Y[5] = {0};
    char m[5] = {0};
    char d[5] = {0};
    char H[5] = {0};
    char M[5] = {0};
    char S[5] = {0};
    strftime(Y, sizeof(Y), "%Y ", now_time);    //将时间格式化为带世纪部分的十进制年份
    strftime(m, sizeof(m), "%m ", now_time);    //将时间格式化为十进制表示的月份
    strftime(d, sizeof(d), "%d ", now_time);    //将时间格式化为十进制的每月中的第几天
    strftime(H, sizeof(H), "%H ", now_time);    //将时间格式化为24小时制的小时
    strftime(M, sizeof(M), "%M ", now_time);    //将时间格式化为十进制表示的分钟数
    strftime(S, sizeof(S), "%S ", now_time);    //将时间格式化为十进制表示的秒数

    printf("\nCurrent time: %s - %s - %s %s : %s : %s\n", Y, m, d, H, M, S);
    
    //struct tm 转换成 char*
    struct tm t;
    char date_time[64];
    strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", localtime_r(&current_time, &t));
    printf("clock_gettime : date_time=%s\n", date_time);
    
    //char* 转换成 struct tm
    struct tm tp;
    strptime(date_time, "%Y-%m-%d %H:%M:%S", &tp);
    printf("\nCurrent time: %d - %d - %d %d : %d : %d\n", tp.tm_year + 1900, tp.tm_mon + 1, tp.tm_mday, tp.tm_hour, tp.tm_min, tp.tm_sec);
}

#include <sys/time.h>

// struct timeval
// {
//     __time_t tv_sec;        /* Seconds. */  
//     __suseconds_t tv_usec;  /* Microseconds. */  
// };
// tv_sec为1970年1月1日0时0分0秒到now的的秒数
// tv_usec为微秒数，即秒后面的零头。

// int gettimeofday(struct timeval*tv, struct timezone *tz);  
  
// struct timezone{  
     // int tz_minuteswest;/*格林威治时间往西方的时差*/  
     // int tz_dsttime;/*DST 时间的修正方式，一般为NULL*/  
// };  

// gettimeofday( )把目前的时间信息存入tv指向的结构体，当地时区信息则放到tz指向的结构体。
void getNowtime_3(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("time %lu:%lu\n", tv.tv_sec, tv.tv_usec);
    
    
    
    //https://man7.org/linux/man-pages/man3/timeradd.3.html
    
    //int timerisset(struct timeval *tvp);
    //timerisset 如果 tvp 指向的 timeval 结构体的任何一个字段包含非零值，Timerisset()返回true(非零)。
    struct timeval tv_1 = {0};
    printf("timer is set %d\n", timerisset(&tv_1)); //timer is set 0
    gettimeofday(&tv_1, NULL);
    printf("timer is set %d\n", timerisset(&tv_1)); //timer is set 1
    
    //void timerclear(struct timeval *tvp);
    //timerclear() 将tvp指向的 timeval 结构体清零，使其表示Epoch: 1970-01-01 00:00:00 +0000 (UTC)
    timerclear(&tv_1);
    printf("timer is set %d\n", timerisset(&tv_1)); //timer is set 0
    
    //void timeradd(struct timeval *a, struct timeval *b, struct timeval *res);
    //timeradd()将a和b中的时间值相加，并将总和放入res所指向的 timeval 中。结果被规范化，使得res->tv_usec的值范围在0到999,999之间。
    struct timeval tv_a, tv_b, tv_res;
    gettimeofday(&tv_a, NULL);
    usleep(500 * 1000);
    gettimeofday(&tv_b, NULL);
    printf("time %lu:%lu\n", tv_a.tv_sec, tv_a.tv_usec);
    printf("time %lu:%lu\n", tv_b.tv_sec, tv_b.tv_usec);
    
    timeradd(&tv_a, &tv_b, &tv_res);
    printf("time add %lu:%lu\n", tv_res.tv_sec, tv_res.tv_usec);
    
    //void timersub(struct timeval *a, struct timeval *b, struct timeval *res);
    //timersub()从a中的时间值中减去b中的时间值，并将结果放入res所指向的 timeval 中。结果被规范化，使得res->tv_usec的值范围在0到999,999之间。
    timersub(&tv_b, &tv_a, &tv_res);
    printf("time sub %lu:%lu\n", tv_res.tv_sec, tv_res.tv_usec);
    
    //int timercmp(struct timeval *a, struct timeval *b, CMP);
    //timercmp()使用比较运算符CMP比较a和b中的 timer 值，并根据比较结果返回true(非零)或false(0)。
    //有些系统(但不是Linux/glibc)有一个不完整的timercmp()实现，其中>=，<=和==的CMP不起作用;应用程序可以使用 !timercmp(..., <) !timercmp(..., >) !timercmp(..., !=)
    printf("time a > b %d\n", timercmp(&tv_a, &tv_b, >));
    printf("time a < b %d\n", timercmp(&tv_a, &tv_b, <));
    printf("time a != b %d\n", timercmp(&tv_a, &tv_b, !=));
    
}

// CLOCK_REALTIME           系统当前时间，从1970年1.1日算起
// CLOCK_MONOTONIC          系统的启动时间，不能被设置
// CLOCK_PROCESS_CPUTIME_ID 本进程运行时间
// CLOCK_THREAD_CPUTIME_ID  本线程运行时间
// struct tm *localtime(const time_t *clock);  //线程不安全
// struct tm* localtime_r( const time_t* timer, struct tm* result );//线程安全

// struct timespec {
    // time_t tv_sec;   // 秒 seconds
    // long tv_nsec;    // 纳秒 nanoseconds
// };

void nowtime_ns(void)
{
    printf("----------------struct timespec-------------------\n");
    printf("[time(NULL)]     :     %ld\n", time(NULL)); 
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("clock_gettime : tv_sec=%ld, tv_nsec=%ld\n",ts.tv_sec, ts.tv_nsec);
    
    struct tm t;
    char date_time[64];
    strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", 
                                            localtime_r(&ts.tv_sec, &t));
    printf("clock_gettime :date_time=%s, tv_nsec=%ld\n", date_time, ts.tv_nsec);
}

void nowtime_us(void)
{
    printf("------------struct timeval------------------\n");
    printf("[time(NULL)]    :    %ld\n", time(NULL));
    struct timeval us;
    gettimeofday(&us, NULL);
    printf("gettimeofday: tv_sec=%ld, tv_usec=%ld\n", us.tv_sec, us.tv_usec);
    
    struct tm t;
    char date_time[64];
    strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S",
                                                localtime_r(&us.tv_sec, &t));
    printf("gettimeofday: date_time=%s, tv_usec=%ld\n", date_time, us.tv_usec);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    getNowtime_0();
    getNowtime_1();
    getNowtime_2();
    getNowtime_3();
    
    nowtime_ns();
    nowtime_us();
    return 0;
}