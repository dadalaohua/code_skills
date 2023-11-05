#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://leetcode.cn/problems/count-primes/solutions/507273/ji-shu-zhi-shu-by-leetcode-solution/
*/
bool isPrime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int countPrimes_1(int n) {
    int ans = 0;
    for (int i = 2; i < n; ++i) {
        ans += isPrime(i);
    }
    return ans;
}

int countPrimes_2(int n) {
    if (n < 2) {
        return 0;
    }
    int isPrime[n];
    memset(isPrime, 0, sizeof(isPrime));
    int ans = 0;
    for (int i = 2; i < n; ++i) {
        if (!isPrime[i]) {
            ans += 1;
            if ((long long)i * i < n) {
                for (int j = i * i; j < n; j += i) {
                    isPrime[j] = 1;
                }
            }
        }
    }
    return ans;
}

int countPrimes_3(int n) {
    if (n < 2) {
        return 0;
    }
    int isPrime[n];
    int primes[n], primesSize = 0;
    memset(isPrime, 0, sizeof(isPrime));
    for (int i = 2; i < n; ++i) {
        if (!isPrime[i]) {
            primes[primesSize++] = i;
        }
        for (int j = 0; j < primesSize && i * primes[j] < n; ++j) {
            isPrime[i * primes[j]] = 1;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
    return primesSize;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //计算 1000 以内的质数数量
    printf("%d\n", countPrimes_1(1000));
    printf("%d\n", countPrimes_2(1000));
    printf("%d\n", countPrimes_3(1000));
    return 0;
}