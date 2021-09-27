#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
long quick_mul(long a, long k) {
    long ans = 0;
    while (k > 0) {
        if (k & 0x1) ans += a; //当前最低位为1，结果里加上a
        k >>= 1;                    //被乘数右移1位，相当于除以2
        a += a;                     //乘数倍增，相当于乘以2
    }
    return ans;
}

long quick_pow(long a, long k) {
    long ans = 1;
    while (k > 0) {
        if (k & 0x1) ans = quick_mul(ans, a);
        k >>= 1;
        a = quick_mul(a, a);
    }
    return ans;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    long a, k;
    
    a = 2;
    k = 10;
    printf("%ld ^ %ld = %ld\n", a, k, quick_pow(a, k));
    
    a = 5;
    k = 2;
    printf("%ld ^ %ld = %ld\n", a, k, quick_pow(a, k));
    
    a = 1;
    k = 8;
    printf("%ld ^ %ld = %ld\n", a, k, quick_pow(a, k));
    
    return 0;
}