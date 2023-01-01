#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*         m
    排列 P
           n
*/
int permutation(int m, int n) {
    int val = 1;
    for(int i = n; i >= n - m + 1; i--) {
        val *= i;
    }
    return val;
}

/*         m
    组合 C
           n
*/
int combination(int m, int n) {
    int up_val = 1;
    int down_val = 1;
    for(int i = n; i >= n - m + 1; i--) {
        up_val *= i;
    }
    for(int i = m; i >= 1; i--) {
        down_val *= i;
    }
    return up_val / down_val;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int m = 1, n = 1;
    for(int i = 1; i < 10; i++) {
        m = i;
        n = i;
        printf("P m %d n %d : %d\n", m, n, permutation(m, n));
    }
    printf("\n");
    
    for(int i = 1; i < 10; i++) {
        n = i;
        for(int j = 0; j <= i; j++) {
            m = j;
            printf("P m %d n %d : %d\n", m, n, permutation(m, n));
        }
        printf("\n");
    }
    printf("\n");
    
    for(int i = 1; i < 10; i++) {
        m = i;
        n = i;
        printf("C m %d n %d : %d\n", m, n, combination(m, n));
    }
    printf("\n");
    
    for(int i = 1; i < 10; i++) {
        n = i;
        for(int j = 0; j <= i; j++) {
            m = j;
            printf("C m %d n %d : %d\n", m, n, combination(m, n));
        }
        printf("\n");
    }
    printf("\n");
    
    return 0;
}