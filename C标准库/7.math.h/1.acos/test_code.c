#include <stdio.h>
#include <math.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define PI 3.14159265

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    double x, ret;

    x = 0.9;

    ret = acos(x) * 180.0 / PI;
    printf("%lf 的反余弦是 %lf 度\n", x, ret);

    return 0;
}