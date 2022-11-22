#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_init_1(void)
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

void test_init_2(void)
{
    int array[10];
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        array[i] = i;
    }
    
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

void test_init_3(void)
{
    int array[10] = {0, 1, 2, [3 ... 5] = 5, 6, 7, 8, 9};
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
    
    int array2[10] = {[0 ... 9] = 66};
    for(i = 0; i < sizeof(array2)/sizeof(int); i++) {
        printf("%d,", array2[i]);
    }
    printf("\n");
}

//置0
void test_init_4(void)
{
    int array[10] = {0};
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

void test_init_9(void)
{
    int array[10] = {};
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

void test_init_5(void)
{
    int array[10];
    memset(array, 0, sizeof(array));
    
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

//部分初始化
void test_init_6(void)
{
    int array[10] = {1, 2}; //其余数值为0
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

void test_init_7(void)
{
    int array[10] = {[5] = 5, [8] = 8}; //其余数值为0
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

//char类型
void test_init_8(void)
{
    char array[10];
    memset(array, 5, sizeof(array));
    
    int i;
    for(i = 0; i < sizeof(array)/sizeof(char); i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test_init_1();
    test_init_2();
    test_init_3();
    test_init_4();
    test_init_5();
    test_init_6();
    test_init_7();
    test_init_8();
    test_init_9();
    return 0;
}