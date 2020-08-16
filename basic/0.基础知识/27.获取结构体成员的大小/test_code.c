#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define FIELD_SIZEOF(t, f) (sizeof(((t*)0)->f))

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
    printf("FIELD_SIZEOF(struct test, i) %d\n", FIELD_SIZEOF(struct test, i));
    printf("FIELD_SIZEOF(struct test, j) %d\n", FIELD_SIZEOF(struct test, j));
    printf("FIELD_SIZEOF(struct test, k) %d\n", FIELD_SIZEOF(struct test, k));
    printf("FIELD_SIZEOF(struct test, m) %d\n", FIELD_SIZEOF(struct test, m));
    printf("FIELD_SIZEOF(struct test, n) %d\n", FIELD_SIZEOF(struct test, n));
    
    return 0;
}