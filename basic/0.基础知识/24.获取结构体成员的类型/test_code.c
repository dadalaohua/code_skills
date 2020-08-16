#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define typeof_member(T, m)	typeof(((T*)0)->m)

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct test_2
{
    char i;
    short j;
    int  k;
    int* m;
    int  n;
};

struct test
{
    char i;
    short j;
    int  k;
    int* m;
    struct test_2 n;
};

/****************************/

int main(int argc, char* argv[])
{
    typeof_member(struct test, i) temp_i;
    typeof_member(struct test, j) temp_j;
    typeof_member(struct test, k) temp_k;
    typeof_member(struct test, m) temp_m;
    typeof_member(struct test, n) temp_n;
    
    printf("sizeof(temp_i) %d\n", sizeof(temp_i));
    printf("sizeof(temp_j) %d\n", sizeof(temp_j));     
    printf("sizeof(temp_k) %d\n", sizeof(temp_k));
    printf("sizeof(temp_m) %d\n", sizeof(temp_m));
    printf("sizeof(temp_n) %d\n", sizeof(temp_n));
    
    return 0;
}