#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    //C99
    
    #include <stdlib.h>
    
    long long strtoll(const char * restrict str，char ** restrict str_end，int base);
    
    解释str指向的字节字符串中的整数值。

    放弃任何空格字符（通过调用标识isspace()），直到找到第一个非空白字符，
    然后接收尽可能多的字符以形成有效的base-n（其中n = base）整数表示并将它们转换为整数值。
    有效的整数值由以下部分组成：
        （可选）加号或减号 
        （可选）prefix（0）指示八进制基数（只适用于基数为8或​0​）
        （可选）前缀（0x或0X）表示十六进制基数（仅适用于基数为16或​0​）
        数字序列
    
    base的有效值集合是{0,2,3，...，36}。base-2整数的有效数字集合是{0,1}，对于base-3整数是{0,1,2}，依此类推。
    对于大于等于的基数10，有效数字包含字母字符，从Aa基数为11的整数开始，到Zz基数为36的整数。字符的情况被忽略。

    其他数字格式可以被当前安装的C语言环境接受。

    如果基数的值是​0​，数字基地是自动检测：如果前缀是0，基地是八进制的，如果前缀是0x或0X，基地是十六进制，否则基数是十进制。

    如果减号是输入序列的一部分，则根据数字序列计算的数值将被否定，如同在结果类型中使用一元减号一样。

    这些函数将str_end指向的指针设置为指向经过最后解释的字符的字符。 如果str_end是NULL，它将被忽略。

    如果str为空或者没有预期的形式，则不执行转换，并且（如果str_end不是NULL），则str的值将存储在str_end指向的对象中。

参数
str - 指向要解释的以空字符结尾的字节字符串
str_end - 指向字符的指针。
base - 解释的整数值的基数

返回值
    如果成功，则返回与内容相对应的整数值str。
    如果转换后的值脱离的相应返回类型的范围时，发生错误的范围（设定errno到ERANGE）和LONG_MAX，LONG_MIN，LLONG_MAX或LLONG_MIN返回。
    如果不能执行转换，​0​则被返回。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str10[30] = "123456";  //10进制数
    char str16[30] = "0xA55A";  //16进制数
    char str10_2[30] = "123456 Hello world";  //10进制数
    char str16_2[30] = "0xA55A Hello world";  //16进制数
    char *ptr;
    long ret;

    ret = strtoll(str10, NULL, 10);
    printf("数字: %ld\n", ret);
    
    printf("\n");
    
    ret = strtoll(str16, NULL, 16);
    printf("数字: %ld\n", ret);
    
    printf("\n");
    
    ret = strtoll(str10_2, &ptr, 10);
    printf("数字: %ld\n", ret);
    printf("字符串部分:%s\n", ptr);
    
    printf("\n");
    
    ret = strtoll(str16_2, &ptr, 16);
    printf("数字: %ld\n", ret);
    printf("字符串部分:%s\n", ptr);
    
    printf("\n");
    
    //自动转换
    ret = strtoll(str10, NULL, 0);
    printf("数字: %ld\n", ret);
    printf("\n");
    
    ret = strtoll(str16, NULL, 0);
    printf("数字: %ld\n", ret);
    printf("\n");
    
    return 0;
}