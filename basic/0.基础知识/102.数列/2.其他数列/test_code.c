#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//求和公式 1^2 + 2^2 + 3^2 + ... + n^2
int sequence_sum(int n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    // 1^2 + 2^2 + 3^2
    // 1 + 4 + 9 = 14
    printf("%d\n", sequence_sum(3));
    
    // 1^2 + 2^2 + 3^2 + 4^2 + 5^2
    // 1 + 4 + 9 + 16 + 25 = 55
    printf("%d\n", sequence_sum(5));
    return 0;
}