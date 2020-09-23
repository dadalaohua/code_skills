#include <stdio.h>              //包含一个源代码文件
#include <stdlib.h>             //包含一个源代码文件
#include <string.h>             //包含一个源代码文件
#include <unistd.h>             //包含一个源代码文件

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define PI          3.1415926   //定义宏
#define FILE_SIZE   30          //定义宏
#define DEBUG                   //定义宏
#define TESTMODE    1           //定义宏

#ifndef MESSAGE                 //如果宏没有定义，则返回真
#define MESSAGE                 //定义宏
#endif                          //结束条件编译块

#if !defined (MSG)              //如果宏没有定义，则返回真
   #define MSG "Hello world!"   //定义宏
#endif                          //结束条件编译块

//宏延续运算符（\）
#define  message_for(a, b)  \
    printf(#a " and " #b ": We love you!\n")    //字符串常量化运算符（#）
//在宏定义中，当需要把一个宏的参数转换为字符串常量时，则使用字符串常量化运算符（#）。在宏中使用的该运算符有一个特定的参数或参数列表

#define  message_test(a)  printf(#a " say hello!\n")    //字符串常量化运算符（#）
#define  message_abc(a, b, c)  printf(#a " , " #b " and " #c " say 666!\n")    //字符串常量化运算符（#）
    
//标记粘贴运算符（##）
//宏定义内的标记粘贴运算符（##）会合并两个参数。它允许在宏定义中两个独立的标记被合并为一个标记
#define tokenpaster(n) printf ("token" #n " = %d\n", token##n)

#define square(x) ((x) * (x))   //带有参数的宏

//#error用于生成一个自定义编译错误信息
//格式#error message 

//如果使用使用C++编译器则会报错
#ifdef __cplusplus
   #error this file should not be processed with C++ Compiler
#endif

//没有定义TESTERROR，会报错，无法编译
// #ifndef TESTERROR
   // #error TESTERROR
// #endif

//#warning用于生成一个自定义编译警告信息
//格式#warning message 
//编译时进行警告
#ifndef TESTWARNING
   #warning test_warning
#endif
/************************************************************************/
/*                                                                      */
/************************************************************************/
#undef  FILE_SIZE               //取消已定义的宏
#define FILE_SIZE   20          //定义宏
int file_size(void)
{ 
    return FILE_SIZE;
}

void test_define(void)
{ 
    printf("Date :%s\n", __DATE__ );            //当前日期，一个以 "MMM DD YYYY" 格式表示的字符常量
                                                //Date :Sep 21 2020
    printf("Time :%s\n", __TIME__ );            //当前时间，一个以 "HH:MM:SS" 格式表示的字符常量
                                                //Time :22:54:12
    printf("File :%s\n", __FILE__ );            //包含当前文件名，一个字符串常量
                                                //File :test_code.c
    printf("Function :%s\n", __FUNCTION__ );    //包含函数名，一个字符串常量
                                                //Function :test_define
    printf("Line :%d\n", __LINE__ );            //包含当前行号，一个十进制常量
                                                //Line :73
    
    printf("ANSI :%d\n", __STDC__ );            //当编译器以 ANSI 标准编译时，则定义为 1
                                                //ANSI :1
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int token36 = 80;
    
    printf("PI : %f\n", PI);                    //PI : 3.141593
    
    printf("file_size : %d\n", file_size());    //file_size : 20
    
    test_define();
    
#ifdef DEBUG                                    //如果宏已经定义，则返回真
    printf("DEBUG\n");                          //DEBUG
#endif                                          //结束条件编译块

#ifndef MESSAGE                                 //如果宏没有定义，则返回真
    printf("MESSAGE\n");                        //不符合条件不会打印
#endif                                          //结束条件编译块

    printf("MSG %s\n", MSG);                    //MSG Hello world!

#if TESTMODE == 1                               //如果给定条件为真，则编译下面代码
    printf("TESTMODE == 1\n");                  //TESTMODE == 1
#elif TESTMODE == 2                             //如果前面的 #if 给定条件不为真，当前条件为真，则编译下面代码
    printf("TESTMODE == 2\n");                  //不符合条件不会打印
#else                                           //其余条件
    printf("TESTMODE == 3\n");                  //不符合条件不会打印
#endif                                          //结束条件编译块

    message_for(Amy, Bob);                      //Amy and Bob: We love you!
    message_test(Candy);                        //Candy say hello!
    message_abc(A, B, C);                       //A , B and C say 666!
    
    tokenpaster(36);                            //token36 = 80
    
    printf("square(%d) = %d\n", 6, square(6));  //square(6) = 36
    
//#line 用于强制指定新的行号和编译文件名，并对源程序的代码重新编号
//格式 #line number filename
//filename可省略
//本质是重定义__LINE__和__FILE__
#line 666 
    printf("File :%s Line :%d\n", __FILE__, __LINE__ ); //File :test_code.c Line :666
#line 888 "testline.c"
    printf("File :%s Line :%d\n", __FILE__, __LINE__ ); //File :testline.c Line :888

    return 0;
}