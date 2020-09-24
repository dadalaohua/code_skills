#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_define(void)
{ 
    printf("Date :%s\n", __DATE__ );            //当前日期，一个以 "MMM DD YYYY" 格式表示的字符常量
                                                //Date :Sep 24 2020
    printf("Time :%s\n", __TIME__ );            //当前时间，一个以 "HH:MM:SS" 格式表示的字符常量
                                                //Time :21:16:55
    printf("File :%s\n", __FILE__ );            //包含当前文件名，一个字符串常量
                                                //File :test_code.c
    printf("Function :%s\n", __FUNCTION__ );    //包含函数名，一个字符串常量
                                                //Function :test_define
    printf("Line :%d\n", __LINE__ );            //包含当前行号，一个十进制常量
                                                //Line :16

    printf("ANSI :%d\n", __STDC__ );            //当编译器以 ANSI 标准编译时，则定义为 1
                                                //ANSI :1
    printf("Function :%s\n", __func__ );        //包含函数名，一个字符串常量
                                                //Function :test_define
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test_define();

    return 0;
}