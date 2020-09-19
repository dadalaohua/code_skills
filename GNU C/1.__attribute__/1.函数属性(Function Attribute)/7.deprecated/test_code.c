#include <stdio.h>

/*
This function attribute indicates that a function exists but the compiler must generate a warning if the deprecated function     is used.

此函数属性指示存在某个函数，但如果使用了 deprecated 函数，则编译器必须生成警告。

用于表示该函数已弃用
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
//编译时会提示警告
int Function_Attributes_deprecated_0(int b) __attribute__((deprecated));
int Function_Attributes_deprecated_1(int b) __attribute__((deprecated("deprecated_1")));

int Function_Attributes_deprecated_0(int b)
{
    return 0;
}

int Function_Attributes_deprecated_1(int b)
{
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("hello world!!!\n");
    Function_Attributes_deprecated_0(0);
    Function_Attributes_deprecated_1(1);
    
    return 0;
}