#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//求和公式1
//a1 首项 an 末项 n 项数
int arithmetic_progression_sum_1(int a1, int an, int n) {
    return (n * (a1 + an)) / 2;
}

//求和公式2
//a1 首项 n 项数 d 公差
int arithmetic_progression_sum_2(int a1, int n, int d) {
    return n * a1 + n * (n - 1) * d / 2;
}

//求和公式3
//a1 首项 n 项数 d 公差
int arithmetic_progression_sum_3(int a1, int n, int d) {
    return d * n * n / 2 + (a1 * n - d * n / 2);
}

//求和公式 1 + 2 + 3 + ... + n
//n 项数
int arithmetic_progression_sum_4(int n) {
    return n * (n + 1) / 2;
}

//求和公式 1 + 3 + 5 + ... + (2n - 1)
//n 项数
int arithmetic_progression_sum_5(int n) {
    return n * n;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a1 = 2;
    int an = 12;
    int n = 3;
    int d = 5;
    // 2 + 7 + 12 = 21
    printf("%d\n", arithmetic_progression_sum_1(a1, an, n));
    printf("%d\n", arithmetic_progression_sum_2(a1, n, d));
    printf("%d\n", arithmetic_progression_sum_3(a1, n, d));
    
    // 1 + 2 + 3 + ... + 100 = 5050
    printf("%d\n", arithmetic_progression_sum_4(100));
    
    // 1 + 3 + 5 = 9
    printf("%d\n", arithmetic_progression_sum_5(3));
    return 0;
}