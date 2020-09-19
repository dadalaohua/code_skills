#include <stdio.h>
#include <string.h>

/*
nonnull (arg-index, ...),参数不能为空
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
//所有参数不能为NULL
void * my_memcpy_1(void *dest, const void *src, size_t len) __attribute__((nonnull));
//参数1, 2不能为NULL
void * my_memcpy_2(void *dest, const void *src, size_t len) __attribute__((nonnull (1, 2)));

void * my_memcpy_1(void *dest, const void *src, size_t len)
{
    return memcpy(dest, src, len);
}

void * my_memcpy_2(void *dest, const void *src, size_t len)
{
    return memcpy(dest, src, len);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char buf1[] = "Hello World!";
    char buf2[20];

    my_memcpy_1(buf2, buf1, sizeof(buf1));
    
    printf("buf2 %s\n", buf2);
    
    memset(buf2, 0, sizeof(buf2));
    
    my_memcpy_2(buf2, buf1, sizeof(buf1));
    
    printf("buf2 %s\n", buf2);
    
    //警告： 实参为 NULL，需要非 NULL 值(实参 1) [-Wnonnull]
    //警告： 实参为 NULL，需要非 NULL 值(实参 2) [-Wnonnull]
    my_memcpy_1(NULL, NULL, sizeof(buf1));
    //警告： 实参为 NULL，需要非 NULL 值(实参 1) [-Wnonnull]
    //警告： 实参为 NULL，需要非 NULL 值(实参 2) [-Wnonnull]
    my_memcpy_2(NULL, NULL, sizeof(buf1));
    
    return 0;
}