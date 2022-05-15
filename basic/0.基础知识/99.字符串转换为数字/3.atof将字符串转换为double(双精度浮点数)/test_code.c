#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    #include <stdlib.h>
    
    double atof (const char* str);
    
    ascii to floating point numbers
    
    atof() 会扫描参数str字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过 isspace() 函数来检测），
    直到遇上数字或正负符号才开始做转换，而再遇到非数字或字符串结束时('\0')才结束转换，并将结果返回。
    参数str 字符串可包含正负号、小数点或E(e)来表示指数部分，如123. 456 或123e-2。

    返回值: 返回转换后的浮点数；如果字符串 str 不能被转换为 double，那么返回 0.0。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *str1 = "-123.45";
    char *str2 = "100e-2";
    char *str3 = "54321";
    char *str4 = "321.12hello";
    char *str5 = "world";
    
    printf("%s: %.2f\n", str1, atof(str1));
    printf("%s: %.2f\n", str2, atof(str2));
    printf("%s: %.2f\n", str3, atof(str3));
    printf("%s: %.2f\n", str4, atof(str4));
    printf("%s: %.2f\n", str5, atof(str5));
    printf("\n");
    
    return 0;
}