#include <stdio.h>

/*
Functions defined with `__attribute__((weak))` export their symbols weakly.
Functions declared with `__attribute__((weak))` and then defined without `__attribute__((weak))` behave as weak functions. This is not the same behavior as the `__weak` keyword.

若两个或两个以上全局符号（函数或变量名）名字一样，而其中之一声明为weak symbol（弱符号），则这些全局符号不会引发重定义错误。链接器会忽略弱符号，去使用普通的全局符号来解析所有对这些符号的引用，但当普通的全局符号不可用时，链接器会使用弱符号。当有函数或变量名可能被用户覆盖时，该函数或变量名可以声明为一个弱符号
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
//如果外部存在Function_Attributes_weak_0函数，则调用外部的函数，没有的话调用本地的
extern int Function_Attributes_weak_0(int b) __attribute__((weak));
extern int Function_Attributes_weak_1(int b);

int Function_Attributes_weak_0(int b)
{
    return 0;
}

__attribute__((weak)) int Function_Attributes_weak_1(int b)
{
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("hello world!!!\n");
    printf("weak_0 : %d\n", Function_Attributes_weak_0(0));
    printf("weak_1 : %d\n", Function_Attributes_weak_1(0));
    
    return 0;
}