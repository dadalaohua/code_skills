#include <stdio.h>

#include <time.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/
void getNowtime_0(void) {
    time_t current_time;
 
    time(&current_time);

    //1970年1月1日0时0分0秒(一般是)到当前时间的秒数
    printf("time: %ld\n", current_time);

}

// /* Used by other time functions.  */
// struct tm
// {
//   int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
//   int tm_min;			/* Minutes.	[0-59] */
//   int tm_hour;			/* Hours.	[0-23] */
//   int tm_mday;			/* Day.		[1-31] */
//   int tm_mon;			/* Month.	[0-11] */
//   int tm_year;			/* Year	- 1900.  */
//   int tm_wday;			/* Day of week.	[0-6] */
//   int tm_yday;			/* Days in year.[0-365]	*/
//   int tm_isdst;			/* DST.		[-1/0/1]*/
// 
// # ifdef	__USE_MISC
//   long int tm_gmtoff;		/* Seconds east of UTC.  */
//   const char *tm_zone;		/* Timezone abbreviation.  */
// # else
//   long int __tm_gmtoff;		/* Seconds east of UTC.  */
//   const char *__tm_zone;	/* Timezone abbreviation.  */
// # endif
// };

void getNowtime_1(void) {
    time_t current_time;
    struct tm* now_time;
 
    time(&current_time);
    now_time = localtime(&current_time);    //将time()返回的time_t类型数据转化为当前系统的真实时间，并将该转化结果返回。

    printf("%4.4d年%2.2d月%2.2d日，%2.2d:%2.2d:%2.2d\n", now_time->tm_year+1900, now_time->tm_mon+1, now_time->tm_mday, 
                                                            now_time->tm_hour, now_time->tm_min, now_time->tm_sec);

}

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
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    getNowtime_0();
    getNowtime_1();
    getNowtime_2();
    return 0;
}