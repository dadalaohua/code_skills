#include <stdio.h>
#include <math.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//求不小于 x 的最小整数，也即向上取整
int main(int argc, char* argv[])
{
    double x = 100.654;
    int val;
    val = ceil(x);
    printf("%d\n", val);    //101
    
    return 0;
}