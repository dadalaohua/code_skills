#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    #include <stdlib.h>
    
    float strtof(const char * restrict str，char ** restrict str_end);
    

    函数丢弃任何空格字符（由std :: isspace（）确定），直到找到第一个非空白字符。
    然后，它需要尽可能多的字符来形成有效的浮点表示并将它们转换为浮点值。 有效的浮点值可以是以下值之一：

十进制浮点表达式。它由以下部分组成：
    （可选）加号或减号 
    非空十进制数字序列可选地包含小数点字符（由当前C确定locale）（定义有效数字）
    （可选），e或者E跟随可选的负号或加号和非空序列的十进制数字（定义指数）
二进制浮点表达式。它由以下部分组成：
    （可选）加号或减号 
    0x 或 0X 
    非空的十六进制数字序列可选地包含小数点字符（由当前C确定locale）（定义有效数字）
    （可选），p或者P跟随可选的负号或加号和非空序列的十进制数字（定义指数）
无限表达。它由以下部分组成：
    （可选）加号或减号 
    INF或者INFINITY无视事件
非数字表达式。它由以下部分组成：
    （可选）加号或减号 
    NAN或NAN(char_sequence)忽略该NAN部分的情况。char_sequence只能包含字母数字字符。结果是静态的NaN浮点值。
任何其他可能被当前安装的C接受的表达式 locale

这些函数将str_end指向的指针设置为指向经过最后解释的字符的字符。 如果str_end是NULL，它将被忽略。

参数
str - 指向要解释的以空字符结尾的字节字符串
str_end - 指向字符的指针。

返回值 浮点值对应str的成功内容。 如果转换后的值超出相应返回类型的范围，则会发生范围错误，并返回HUGE_VAL，HUGE_VALF或HUGE_VALL。 如果不能执行转换，则返回0。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *ptr;
    char *str1 = "-123.45";
    char *str2 = "100e-2";
    char *str3 = "54321";
    char *str4 = "321.12hello";
    char *str5 = "world";
    char *str6 = "123.45 654.32";
    char *str7 = "Nan";
    char *str8 = "nan(2)";
    char *str9 = "inF";
    char *str10 = "-0.0000000123";
    char *str11 = "1.27893e+4657";
    
    printf("%s: %f\n", str1, strtof(str1, NULL));
    printf("%s: %f\n", str2, strtof(str2, NULL));
    printf("%s: %f\n", str3, strtof(str3, NULL));
    printf("%s: %f\n", str4, strtof(str4, NULL));
    printf("%s: %f\n", str5, strtof(str5, NULL));
    printf("\n");
    
    printf("%s: %f\n", str4, strtof(str4, &ptr));
    printf("%s: %s\n", str4, ptr);
    printf("\n");
    
    printf("%s: %f\n", str5, strtof(str5, &ptr));
    printf("%s: %s\n", str5, ptr);
    printf("\n");
    
    printf("%s: %f\n", str6, strtof(str6, &ptr));
    printf("%s: %f\n", str6, strtof(ptr, NULL));
    printf("\n");
    
    printf("%s: %f\n", str7, strtof(str7, NULL));
    printf("%s: %f\n", str8, strtof(str8, NULL));
    printf("%s: %f\n", str9, strtof(str9, NULL));
    printf("%s: %f\n", str10, strtof(str10, NULL));
    printf("%s: %f\n", str11, strtof(str11, NULL));//数值结果超出范围
    if (errno == ERANGE) {
        perror("error:");
        printf("strerror: %s\n", strerror(errno));
        errno = 0;
    }
    
    printf("\n");
    
    return 0;
}