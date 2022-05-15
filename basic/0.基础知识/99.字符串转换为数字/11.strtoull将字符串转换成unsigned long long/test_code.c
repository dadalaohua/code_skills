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
    
    unsigned long long strtoull(const char * restrict str，char ** restrict str_end，int base);
    
    解释str指向的字节字符串中的无符号整数值。

    放弃任何空白字符（通过调用标识isspace()），直到找到第一个非空白字符，
    然后接收尽可能多的字符以形成有效的base-n（其中n = base）无符号整数表示并将它们转换为整数值。
    有效的无符号整数值由以下部分组成：

        （可选）加号或减号 
        （可选）prefix（0）指示八进制基数（只适用于基数为8或​0​）
        （可选）前缀（0x或0X）表示十六进制基数（仅适用于基数为16或​0​）
        数字序列
        
    base的有效值集合是{0,1,2,3，...，36}。base-2整数的有效数字集合是{0,1}，对于base-3整数是{0,1,2}，
    依此类推。对于大于等于的基数10，有效数字包含字母字符，从Aa基数为11的整数开始，到Zz基数为36的整数。
    字符的情况被忽略。

    其他数字格式可以被当前安装的C语言环境接受。

    如果基数的值是​0​，数字基地是自动检测：如果前缀是0，基地是八进制的，如果前缀是0x或0X，基地是十六进制，否则基数是十进制。

    如果减号是输入序列的一部分，则根据数字序列计算的数值将被否定，如同使用无符号整数环绕规则的结果类型中的一元减号一样。

    这些函数将str_end指向的指针设置为指向经过最后解释的字符的字符。 如果str_end是NULL，它将被忽略。

参数
    str - 指向要解释的以空字符结尾的字节字符串
    str_end - 指向字符的指针。
    base - 解释的整数值的基数

返回值
    整数值对应str成功的内容。
    如果转换后的值超出了相应返回类型的范围，则会发生范围错误（errno设置为ERANGE），并返回ULONG_MAX或ULLONG_MAX。
    如果不能执行转换，则返回0。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str10[30] = "1234567890";  //10进制数
    char str16[30] = "0xA55ABCDE";  //16进制数
    char str10_2[30] = "1234567890 Hello world";  //10进制数
    char str16_2[30] = "0xA55ABCDE Hello world";  //16进制数
    char *ptr;
    unsigned long ret;

    ret = strtoull(str10, NULL, 10);
    printf("数字: %lu\n", ret);
    
    printf("\n");
    
    ret = strtoull(str16, NULL, 16);
    printf("数字: %lu\n", ret);
    
    printf("\n");
    
    ret = strtoull(str10_2, &ptr, 10);
    printf("数字: %lu\n", ret);
    printf("字符串部分:%s\n", ptr);
    
    printf("\n");
    
    ret = strtoull(str16_2, &ptr, 16);
    printf("数字: %lu\n", ret);
    printf("字符串部分:%s\n", ptr);
    
    printf("\n");
    
    //自动转换
    ret = strtoull(str10, NULL, 0);
    printf("数字: %lu\n", ret);
    printf("\n");
    
    ret = strtoull(str16, NULL, 0);
    printf("数字: %lu\n", ret);
    printf("\n");
    
    return 0;
}