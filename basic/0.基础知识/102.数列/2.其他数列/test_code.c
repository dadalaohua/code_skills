#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    数列 1 3 6 10 15 21 28 36 45 ...
    
等差数列的求和公式 1 + 2 + 3 + ... + n
*/
int sequence_1(int n) {
    return n * (n + 1) / 2;
}

/*
像是梯形公式
*/
int sequence_1_1(int left, int right) {
    return (right + left) * (right - left + 1) / 2;
}

/*
    数列 1 4 10 20 35 56 84 120 165 ...
    
上一个数列的求和公式 1 + 3 + 6 + 10 + 15 + 21 ... + n
*/
int sequence_2(int n) {
    return (n * (n + 1) * (n + 2)) / 6;
}

int sequence_2_1(int left, int right) {
    return ((right * (right + 1) * (right + 2)) - (left > 0 ? ((left - 1) * left * (left + 1)) : 0)) / 6;
}

/*
    数列 1 5 14 30 55 91 140 204 285 ...
    
求和公式 1^2 + 2^2 + 3^2 + 4^2 + 5^2 ... + n^2
         1   + 4   + 9   + 16   + 25 ... + n^2
*/
int sequence_3(int n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    for(int i = 1; i < 10; i++) {
        printf("%d,", sequence_1(i));
    }
    printf("\n");
    
    for(int i = 1; i < 10; i++) {
        printf("%d,", sequence_2(i));
    }
    printf("\n");
    
    for(int i = 1; i < 10; i++) {
        printf("%d,", sequence_3(i));
    }
    printf("\n");
    
    for(int i = 1; i < 10; i++) {
        printf("left %d right %d sum %d\n", i, 10, sequence_1_1(i, 10));
    }
    printf("\n");
    
    for(int i = 1; i < 10; i++) {
        printf("left %d right %d sum %d\n", i, 10, sequence_2_1(i, 10));
    }
    printf("\n");
    
    return 0;
}