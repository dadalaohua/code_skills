#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
long quick_mul(long a, long k) {
    long ans = 0;
    while (k > 0) {
        if ((k & 1) == 1) ans += a; //当前最低位为1，结果里加上a
        k >>= 1;                    //被乘数右移1位，相当于除以2
        a += a;                     //乘数倍增，相当于乘以2
    }
    return ans;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    long a, k;
    
    a = 10;
    k = 666;
    printf("%ld × %ld = %ld\n", a, k, quick_mul(a, k));
    
    a = 15;
    k = 4;
    printf("%ld × %ld = %ld\n", a, k, quick_mul(a, k));
    
    a = 25;
    k = 3;
    printf("%ld × %ld = %ld\n", a, k, quick_mul(a, k));
    
    return 0;
}