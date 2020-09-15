#include <stdio.h>
#include <stddef.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct test_address {
    char test_name[50];
    char test_val[25];
    int test_int;
    long test_long;
};

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    printf("test_address 结构中的 test_name 偏移 = %d 字节。\n", offsetof(struct test_address, test_name));

    printf("test_address 结构中的 test_val 偏移 = %d 字节。\n", offsetof(struct test_address, test_val));

    printf("test_address 结构中的 test_int 偏移 = %d 字节。\n", offsetof(struct test_address, test_int));

    printf("test_address 结构中的 test_long 偏移 = %d 字节。\n", offsetof(struct test_address, test_long));
   
    return 0;
}