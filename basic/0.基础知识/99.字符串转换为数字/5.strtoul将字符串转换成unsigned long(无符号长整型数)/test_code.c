#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    #include <stdlib.h>
    
    unsigned long strtoul (const char* str, char** endptr, int base);
    
    str - 要转换为长整数的字符串。
    endptr - 对类型为 char* 的对象的引用，其值由函数设置为 str 中数值后的下一个字符。
    base - 基数，必须介于 2 和 36（包含）之间，或者是特殊值 0。
    
    string to unsigned long
    
    str 为要转换的字符串，endstr 为第一个不能转换的字符的指针，base 为字符串 str 所采用的进制。

    strtoul() 会将参数 str 字符串根据参数 base 来转换成无符号的长整型数(unsigned long)。
    参数 base 范围从2 至36，或0。参数 base 代表 str 采用的进制方式，如 base 值为10 则采用10 进制，若 base 值为16 则采用16 进制数等。

    strtoul() 会扫描参数 str 字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过 isspace() 函数来检测），
    直到遇上数字或正负符号才开始做转换，再遇到非数字或字符串结束时('\0')结束转换，并将结果返回。

    当 base 的值为 0 时，默认采用 10 进制转换，但如果遇到 '0x' / '0X' 前置字符则会使用 16 进制转换，遇到 '0' 前置字符则会使用 8 进制转换。
    若 endptr 不为NULL，则会将遇到的不符合条件而终止的字符指针由 endptr 传回；若 endptr 为 NULL，则表示该参数无效，或不使用该参数。本文最后的范例没有展示 endptr 参数的使用，你可以参考 strtol() 函数的范例来更加直观地了解 endptr 参数。

    返回值: 返回转换后的无符号长整型数；如果不能转换或者 str 为空字符串，那么返回 0；
    如果转换得到的值超出unsigned long int 所能表示的范围，函数将返回 ULONG_MAX（在 limits.h 头文件中定义），并将 errno 的值设置为 ERANGE。
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

    ret = strtoul(str10, NULL, 10);
    printf("数字: %lu\n", ret);
    
    printf("\n");
    
    ret = strtoul(str16, NULL, 16);
    printf("数字: %lu\n", ret);
    
    printf("\n");
    
    ret = strtoul(str10_2, &ptr, 10);
    printf("数字: %lu\n", ret);
    printf("字符串部分:%s\n", ptr);
    
    printf("\n");
    
    ret = strtoul(str16_2, &ptr, 16);
    printf("数字: %lu\n", ret);
    printf("字符串部分:%s\n", ptr);
    
    printf("\n");
    
    return 0;
}