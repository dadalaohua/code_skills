#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
RMQ（区间最值问题，Range Minimum/Maximum Query）
ST算法（Sparse Table，稀疏表）主要用于解决区间最值问题（即RMQ问题）

参考
https://www.cnblogs.com/yoke/p/6949838.html
https://blog.csdn.net/qq_37957064/article/details/111471570
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
void st(int* num, int numlen, int interval[][2], int intervallen) {
    int k = log2(numlen);
    //dp[i][j]表示以 i 为起点，长度为 2^j 的区间中的最值
    int dp[numlen][k + 1];
    memset(dp, 0, sizeof(dp));
    
    //先预处理2^0长度的最值
    for(int i = 0; i < numlen; i++)
        dp[i][0] = num[i];
    
    //预处理
    for(int j = 1; (1 << j) <= numlen; j++) {
        for(int i = 0; i + (1 << j) - 1 <= numlen; i++) {
            //printf("i %d j %d\n", i, j);
            dp[i][j] = fmax(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
    
    int left, right, ans;
    for(int i = 0; i < intervallen; i++) {
        left = interval[i][0];
        right = interval[i][1];
        k = log2(right - left + 1);
        //printf("i %d j %d i %d j %d\n", left, k, right - (1 << k) + 1, k);
        ans = fmax(dp[left][k], dp[right - (1 << k) + 1][k]);
        printf("i %2d left %d right %d max %d\n", i, left, right, ans);
    }
}

int main(int argc, char* argv[])
{
    int num[] = {1, 2, 5, 3, 9, 7};
    int interval[][2] = {
                            {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, 
                                    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, 
                                            {2, 2}, {2, 3}, {2, 4}, {2, 5}, 
                                                    {3, 3}, {3, 4}, {3, 5}, 
                                                            {4, 4}, {4, 5}, 
                                                                    {5, 5}, 
                        };
    printf("numlen %zu intervallen %zu\n", sizeof(num) / sizeof(int), sizeof(interval) / sizeof(interval[0]));
    st(num, sizeof(num) / sizeof(int), interval, sizeof(interval) / sizeof(interval[0]));
    printf("\n");
    
    int num2[] = {3, 1};
    int interval2[][2] = {
                            {0, 0}, {0, 1},
                                    {1, 1},
                        };
    printf("numlen %zu intervallen %zu\n", sizeof(num2) / sizeof(int), sizeof(interval2) / sizeof(interval2[0]));
    st(num2, sizeof(num2) / sizeof(int), interval2, sizeof(interval2) / sizeof(interval2[0]));
    return 0;
}