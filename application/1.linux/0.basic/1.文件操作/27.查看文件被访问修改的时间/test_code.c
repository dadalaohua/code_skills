#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// time_t     st_atime;      //文件最后被访问的时间
// time_t     st_mtime;      //文件内容最后被修改的时间
// time_t     st_ctime;      //文件状态改变时间

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct stat sta;
    stat("README.md", &sta);
    
    time_t time1;
    struct tm tm1;
 
    //文件最后被访问的时间
    time1 = sta.st_atime;
    localtime_r(&time1, &tm1);
    printf("%4.4d年%2.2d月%2.2d日，%2.2d:%2.2d:%2.2d\n", tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min,tm1.tm_sec);
    
    //文件内容最后被修改的时间
    time1 = sta.st_mtime;
    localtime_r(&time1, &tm1);
    printf("%4.4d年%2.2d月%2.2d日，%2.2d:%2.2d:%2.2d\n", tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min,tm1.tm_sec);

    //文件状态改变的时间
    time1 = sta.st_ctime;
    localtime_r(&time1, &tm1);
    printf("%4.4d年%2.2d月%2.2d日，%2.2d:%2.2d:%2.2d\n", tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min,tm1.tm_sec);

    return 0;
}