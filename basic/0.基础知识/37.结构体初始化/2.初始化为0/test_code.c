#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct teststruct {
    int val;
};

struct member {
    int int_num;
    char char_num;
    float float_num;
    char* string;
    unsigned char buf[3];
    struct teststruct struct_num;
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
//让栈变为脏数据
void test_init_confusion(void)
{
    struct member testnum = {666, 16, 3.141592, "hello world!", {1, 2, 3}, {.val = 8}};
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

//方法一
void test_init_zero_1(void)
{
    struct member testnum = {0};
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

//方法二
void test_init_zero_2(void)
{
    struct member testnum = {};
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

//方法三
void test_init_zero_3(void)
{
    struct member testnum;
    memset(&testnum, 0, sizeof(testnum));
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

//方法四
void test_init_zero_4(void)
{
    struct member testnum;
    testnum = (struct member){0};
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

int main(int argc, char* argv[])
{
    test_init_confusion();
    test_init_zero_1();
    test_init_confusion();
    test_init_zero_2();
    test_init_confusion();
    test_init_zero_3();
    test_init_confusion();
    test_init_zero_4();
    
    return 0;
}