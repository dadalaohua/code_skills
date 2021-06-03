#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************
原型: int atoi(const char *nptr);

函数说明: 参数nptr字符串，如果第一个非空格字符不存在或者不是数字也不是正负号则返回零，
          否则开始做类型转换，之后检测到非数字(包括结束符 \0) 字符时停止转换，返回整型数。
************************************************************************/
int atoi(const char* str)
{
    int result = 0;
    int sign = 0;
    
    assert(str != NULL);
    
    // proc whitespace characters
    while (*str==' ' || *str=='\t' || *str=='\n')
        ++str;

    // proc sign character
    if (*str=='-')
    {
        sign = 1;
        ++str;
    }
    else if (*str=='+')
    {
        ++str;
    }

    // proc numbers
    while (*str>='0' && *str<='9')
    {
        result = result*10 + *str - '0';
        ++str;
    }

    // return result
    if (sign==1)
       return -result;
    else
       return result;
} 

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int val;
    char str[20];

    strcpy(str, "123456789");
    val = atoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);
    
    strcpy(str, "-321654987");
    val = atoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);
    
    strcpy(str, "helloworld");
    val = atoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);
    
    strcpy(str, "123helloworld");
    val = atoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);

    return 0;
}