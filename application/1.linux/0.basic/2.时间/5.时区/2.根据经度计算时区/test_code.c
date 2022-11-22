#include <stdio.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://mp.weixin.qq.com/s/MzXPmzN1pvv7oLUT_RNkIA

时区范围是中央经线的度数向左右分别减、加7.5度。用该地的经度除以15度，
当余数小于7.5度时，商数即为该地所在的时区数，当余数大于7.5度时，商数加1即为该地所在的时区数。
*/
int calc_timezone(double longitude)
{
    int timezone = 0;
    int quotient = (int)(longitude / 15);
    double remainder = (longitude - quotient * 15);
    printf("quotient = %d, remainder = %lf\n", quotient, remainder);

    if (remainder <= 7.5)
    {
        timezone = quotient;
    }
    else
    {
        timezone = quotient + (quotient >= 0 ? + 1 : -1);
    }

    return timezone;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    double longitude = 0.0;
    printf("please input longitude:");
    scanf("%lf", &longitude);
    printf("longitude = %lf\n", longitude);
    int timezone = calc_timezone(longitude);
    printf("timezone = %d\n", timezone);

    return 0;
}