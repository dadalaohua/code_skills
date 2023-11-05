#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// https://blog.csdn.net/skysky97/article/details/83275201
#define SECS_PER_HOUR        (60 * 60)
#define SECS_PER_DAY         (SECS_PER_HOUR * 24)
#define DIV(a, b)            ((a) / (b) - ((a) % (b) < 0))
#define LEAPS_THRU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))

#define __isleap(year) \
    ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
    
/***************************************************************************//**
 * \brief       Convert UTC seconds to tm struct.
 * \param       t : seconds from 1970-1-1 0:0:0
 * \param       tp : tm struct pointer
 * \return      0 : overflow error
 * \return      1 : success
 * \author      glic __offtime
 * \note        timezone is ignored
 *               struct tm
 *               {
 *               	int tm_sec;            Seconds. [0-60] (1 leap second) 
 *               	int tm_min;            Minutes. [0-59] 
 *               	int tm_hour;           Hours.   [0-23] 
 *               	int tm_mday;           Day.     [1-31] 
 *               	int tm_mon;            Month.   [0-11] 
 *               	int tm_year;           Year - 1900.  
 *               	int tm_wday;           Day of week. [0-6] 
 *               	int tm_yday;           Days in year.[0-365] 
 *               }
 ******************************************************************************/
int gmtime64 (const long long *t, struct tm *tp)
{
    const unsigned short int __mon_yday[2][13] =
    {
        /* Normal years.  */
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
        /* Leap years.  */
        { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
    };
    long int days, rem, y;
    const unsigned short int *ip;

    days = *t / SECS_PER_DAY;
    rem = *t % SECS_PER_DAY;
    while (rem < 0)
    {
        rem += SECS_PER_DAY;
        --days;
    }
    while (rem >= SECS_PER_DAY)
    {
        rem -= SECS_PER_DAY;
        ++days;
    }

    tp->tm_hour = rem / SECS_PER_HOUR;
    rem %= SECS_PER_HOUR;
    tp->tm_min = rem / 60;
    tp->tm_sec = rem % 60;
    /* January 1, 1970 was a Thursday.  */
    tp->tm_wday = (4 + days) % 7;
    if (tp->tm_wday < 0)
    tp->tm_wday += 7;
    y = 1970;
    
    while (days < 0 || days >= (__isleap (y) ? 366 : 365))
    {
        /* Guess a corrected year, assuming 365 days per year.  */
        long int yg = y + days / 365 - (days % 365 < 0);
        /* Adjust DAYS and Y to match the guessed year.  */
        days -= ((yg - y) * 365
               + LEAPS_THRU_END_OF (yg - 1)
               - LEAPS_THRU_END_OF (y - 1));
        y = yg;
    }

    tp->tm_year = y - 1900;
    if (tp->tm_year != y - 1900)
    {
        /* The year cannot be represented due to overflow.  */
        //__set_errno (EOVERFLOW);
        return 0;
    }

    tp->tm_yday = days;
    ip = __mon_yday[__isleap(y)];
    for (y = 11; days < (long int) ip[y]; --y)
        continue;
    days -= ip[y];
    tp->tm_mon = y;
    tp->tm_mday = days + 1;
    return 1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    time_t i;
    struct tm test_time1, *test_time2;

    for (i = 0; i <= 0x1FFFFFFFF; i++) {
        gmtime64 ((long long*)&i, &test_time1);
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