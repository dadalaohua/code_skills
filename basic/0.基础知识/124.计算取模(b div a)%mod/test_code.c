#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
long quick_mul_mod(long a, long k, long mod) {
    long ans = 0;
    while (k > 0) {
        if (k & 0x1) ans = (ans + a) % mod;     //当前最低位为1，结果里加上a, 再取模
        k >>= 1;                                //被乘数右移1位，相当于除以2
        a = (a + a) % mod;                      //乘数倍增，相当于乘以2, 再取模
    }
    return ans;
}

long quick_pow_mod(long a, long k, long mod) {
    long ans = 1;
    while (k > 0) {
        if (k & 0x1) ans = quick_mul_mod(ans, a, mod);
        k >>= 1;
        a = quick_mul_mod(a, a, mod);
    }
    return ans;
}

/*

https://leetcode.cn/problems/minimum-number-of-operations-to-make-string-sorted/solutions/728290/shi-zi-fu-chuan-you-xu-de-zui-shao-cao-z-qgra/comments/%C3%AF%C2%BC%C2%8C/

费马小定理
    若 m 为质数 a 与 m 互质
    a^(m-1) mod m = 1
    a^(m-1) * a^(-1) = a^(-1)       mod m
    a^(m-2) * a * a^(-1) = a^(-1)   mod m
    a^(m-2) = a^(-1)                mod m
    
乘法逆元
    ( b / a ) mod m
    ( b * a ^ -1) mod m
    ( b * a ^ -1 * 1) mod m
    ( b * a ^ -1 * a ^ (m - 1)) mod m
    ( b * a ^ (m - 2)) mod m
    
乘法在取模的意义下满足分配率
    ( a * b ) mod m = ( (a mod m) * (b mod m) ) mod m
*/
long div_mod(long b, long a, long mod) {
    return b * quick_pow_mod(a, mod - 2, mod) % mod;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    long a, b;
    long mod = 1e9 + 7;
    
    a = 2;
    b = 100;
    
    printf("%ld / %ld mod %ld = %ld\n", b, a, mod, div_mod(b, a, mod));
    
    a = 1;
    b = 2e9;
    printf("%ld / %ld mod %ld = %ld\n", b, a, mod, div_mod(b, a, mod));
    
    a = 5e9;
    b = 15e9;
    printf("%ld / %ld mod %ld = %ld\n", b, a, mod, div_mod(b, a, mod));
    
    return 0;
}