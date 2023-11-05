#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// https://blog.csdn.net/MengXP/article/details/111520934

#define _DAY_SEC            (24 * 60 * 60)      /* secs in a day */
#define _YEAR_SEC           (365 * _DAY_SEC)    /* secs in a year */
#define _FOUR_YEAR_SEC      (1461 * _DAY_SEC)   /* secs in a 4 year interval */
#define _BASE_DOW           4                   /* 01-01-70 was a Thursday */
#define _LEAP_YEAR_ADJUST   17                  /* Leap years 1900 - 1970 */
#define _MAX_YEAR           138                 /* 2038 is the max year */
#define _MAX__TIME32_T      0x7fffd27f          /* number of seconds from
                                                   00:00:00, 01/01/1970 UTC to
                                                   23:59:59, 01/18/2038 UTC */
 
#define _MAX_YEAR64         1100                /* 3000 is the max year */
#define _MAX__TIME64_T      0x793406fff         /* number of seconds from
                                                   00:00:00, 01/01/1970 UTC to
                                                   23:59:59. 12/31/3000 UTC */
/*
 * Macro to determine if a given year, expressed as the number of years since
 * 1900, is a leap year.
 */
#define _IS_LEAP_YEAR(y)        (((y % 4 == 0) && (y % 100 != 0)) || \
                                ((y + 1900) % 400 == 0))
/*
 * Number of leap years from 1970 up to, but not including, the specified year
 * (expressed as the number of years since 1900).
 */
#define _ELAPSED_LEAP_YEARS(y)  (((y - 1)/4) - ((y - 1)/100) + ((y + 299)/400) \
                                - _LEAP_YEAR_ADJUST)

typedef long long __time64_t;

void my_gmtime64_s(struct tm *ptm, const __time64_t tim)
{
    int _lpdays[] = {-1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int _days[] = {-1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364};
    __time64_t caltim = tim;    /* calendar time to convert */
    int islpyr = 0;             /* is-current-year-a-leap-year flag */
    int tmptim;
    int *mdays;                 /* pointer to days or lpdays */
    struct tm *ptb = ptm;
 
    if(!ptm)
        return;
 
    memset(ptm, 0, sizeof(struct tm));
 
    if(caltim > _MAX__TIME64_T)
        return;
 
    /* Determine the years since 1900. Start by ignoring leap years. */
    tmptim = (int)(caltim / _YEAR_SEC) + 70;
    caltim -= ((__time64_t)(tmptim - 70) * _YEAR_SEC);
 
    /* Correct for elapsed leap years */
    caltim -= ((__time64_t)_ELAPSED_LEAP_YEARS(tmptim) * _DAY_SEC);
 
    /*
     * If we have underflowed the __time64_t range (i.e., if caltim < 0),
     * back up one year, adjusting the correction if necessary.
     */
    if (caltim < 0)
    {
        caltim += (__time64_t)_YEAR_SEC;
        tmptim--;
        if (_IS_LEAP_YEAR(tmptim))
        {
            caltim += _DAY_SEC;
            islpyr++;
        }
    }
    else
    {
        if (_IS_LEAP_YEAR(tmptim))
            islpyr++;
    }
 
    /*
     * tmptim now holds the value for tm_year. caltim now holds the
     * number of elapsed seconds since the beginning of that year.
     */
    ptb->tm_year = tmptim;
 
    /*
     * Determine days since January 1 (0 - 365). This is the tm_yday value.
     * Leave caltim with number of elapsed seconds in that day.
     */
    ptb->tm_yday = (int)(caltim / _DAY_SEC);
    caltim -= (__time64_t)(ptb->tm_yday) * _DAY_SEC;
 
    /* Determine months since January (0 - 11) and day of month (1 - 31) */
    if (islpyr)
        mdays = _lpdays;
    else
        mdays = _days;
 
    for (tmptim = 1; mdays[tmptim] < ptb->tm_yday; tmptim++);
 
    ptb->tm_mon = --tmptim;
    ptb->tm_mday = ptb->tm_yday - mdays[tmptim];
 
    /* Determine days since Sunday (0 - 6) */
    ptb->tm_wday = ((int)(tim / _DAY_SEC) + _BASE_DOW) % 7;
 
    /*
     *  Determine hours since midnight (0 - 23), minutes after the hour
     *  (0 - 59), and seconds after the minute (0 - 59).
     */
    ptb->tm_hour = (int)(caltim / 3600);
    caltim -= (__time64_t)ptb->tm_hour * 3600L;
 
    ptb->tm_min = (int)(caltim / 60);
    ptb->tm_sec = (int)(caltim - (ptb->tm_min) * 60);
 
    ptb->tm_isdst = 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    time_t i;
    struct tm test_time1, *test_time2;

    for (i = 0; i <= 0x1FFFFFFFF; i++) {
        my_gmtime64_s(&test_time1, i);
        test_time2 = gmtime(&i);

        if (test_time1.tm_year != test_time2->tm_year ||\
            test_time1.tm_mon != test_time2->tm_mon ||
            test_time1.tm_mday != test_time2->tm_mday ||
            test_time1.tm_hour != test_time2->tm_hour ||
            test_time1.tm_min != test_time2->tm_min ||
            test_time1.tm_sec != test_time2->tm_sec ||
            test_time1.tm_wday != test_time2->tm_wday ||
            test_time1.tm_yday != test_time2->tm_yday)
        {
            printf("gmtime not passed i = %ld\r\n", i);
            break;
        }
    }

    if (i > 0x1FFFFFFFF)
    {
        printf("passed\r\n");
    }
    return 0;
}