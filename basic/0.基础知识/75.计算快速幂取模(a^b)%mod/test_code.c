#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
long quick_mul(long a, long k, long mod) {
    long ans = 0;
    while (k > 0) {
        if (k & 0x1) ans = (ans + a)%mod;   //当前最低位为1，结果里加上a, 再取模
        k >>= 1;                            //被乘数右移1位，相当于除以2
        a = (a + a)%mod;                    //乘数倍增，相当于乘以2, 再取模
    }
    return ans;
}

long quick_pow(long a, long k, long mod) {
    long ans = 1;
    while (k > 0) {
        if (k & 0x1) ans = quick_mul(ans, a, mod);
        k >>= 1;
        a = quick_mul(a, a, mod);
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
    k = 100;
    printf("%ld ^ %ld = %ld\n", a, k, quick_pow(a, k, 1000));   //376
    
    a = 2;
    k = 10;
    printf("%ld ^ %ld = %ld\n", a, k, quick_pow(a, k, 1000));   //24
    
    a = 1;
    k = 8;
    printf("%ld ^ %ld = %ld\n", a, k, quick_pow(a, k, 100));
    
    return 0;
}