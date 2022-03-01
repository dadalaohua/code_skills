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
//方法一：定义时赋值
void test_init_1(void)
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

//方法二
void test_init_2(void)
{
    struct member testnum = {
        .int_num        = 643,
        .char_num       = 32,
        .float_num      = 5.1348,
        .string         = "you need knowledge",
        .buf[0]         = 8,
        .buf[1]         = 5,
        .buf[2]         = 3,
        .struct_num.val = 664,
    };
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

//方法三
void test_init_3(void)
{
    struct member testnum = {
        int_num        : 9463,
        char_num       : 37,
        float_num      : 6.184,
        string         : "To keep power",
        buf            : {5, 2, 9},
        struct_num     : {.val = 976},
    };
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

//方法四
void test_init_4(void)
{
    struct member testnum;
    testnum.int_num        = 1024,
    testnum.char_num       = 128,
    testnum.float_num      = 64.219,
    testnum.string         = "never give up",
    testnum.buf[0]         = 32,
    testnum.buf[1]         = 64,
    testnum.buf[2]         = 'A',
    testnum.struct_num.val = 886,
    
    printf("testnum.int_num         %d\n", testnum.int_num);
    printf("testnum.char_num        %d\n", testnum.char_num);
    printf("testnum.float_num       %f\n", testnum.float_num);
    printf("testnum.string          %s\n", testnum.string);
    printf("testnum.buf             %d %d %d\n", testnum.buf[0], testnum.buf[1], testnum.buf[2]);
    printf("testnum.struct_num.val  %d\n", testnum.struct_num.val);
    printf("\n");
}

//方法五
void test_init_5(void)
{
    struct member testnum;
    testnum = (struct member){682, 65, 5.141592, "hello world!", {1, 2, 3}, {.val = 8}};
    
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
    test_init_1();
    test_init_2();
    test_init_3();
    test_init_4();
    test_init_5();
    
    return 0;
}