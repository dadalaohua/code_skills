#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    #include <stdlib.h>
    
    double strtod (const char* str, char** endptr);
    
    str 为要转换的字符串，endstr 为第一个不能转换的字符的指针。

    strtod() 函数会扫描参数str字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过 isspace() 函数来检测），
    直到遇上数字或正负符号才开始做转换，到出现非数字或字符串结束时('\0')才结束转换，并将结果返回。
    参数 str 字符串可包含正负号、小数点或E(e)来表示指数部分。如123. 456 或123e-2。

    若endptr 不为NULL，则会将遇到的不符合条件而终止的字符指针由 endptr 传回；若 endptr 为 NULL，则表示该参数无效，或不使用该参数。

    返回值: 返回转换后的浮点型数；若不能转换或字符串为空，则返回 0.0。
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
    
    printf("%s: %.2f\n", str1, strtod(str1, NULL));
    printf("%s: %.2f\n", str2, strtod(str2, NULL));
    printf("%s: %.2f\n", str3, strtod(str3, NULL));
    printf("%s: %.2f\n", str4, strtod(str4, NULL));
    printf("%s: %.2f\n", str5, strtod(str5, NULL));
    printf("\n");
    
    printf("%s: %.2f\n", str4, strtod(str4, &ptr));
    printf("%s: %s\n", str4, ptr);
    printf("\n");
    
    printf("%s: %.2f\n", str5, strtod(str5, &ptr));
    printf("%s: %s\n", str5, ptr);
    printf("\n");
    
    printf("%s: %.2f\n", str6, strtod(str6, &ptr));
    printf("%s: %.2f\n", str6, strtod(ptr, NULL));
    printf("\n");
    
    return 0;
}