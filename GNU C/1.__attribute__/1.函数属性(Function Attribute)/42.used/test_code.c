#include <stdio.h>
#include <stdarg.h>
/*
This function attribute informs the compiler that a static function is to be retained in the object file, even if it is unreferenced.
Functions marked with__attribute__((used))are tagged in the object file to avoid removal by linker unused section removal.

这个函数属性通知编译器在目标文件中保留一个静态函数，即使它没有被引用。
标记为__attribute__((used))的函数被标记在目标文件中，以避免链接器删除未使用的节。

used： This attribute, attached to a function, means that code must be emitted for the
       function even if it appears that the function is not referenced. This is useful,
       for example, when the function is referenced only in inline assembly.
向编译器说明这段代码有用，即使在没有用到的情况下编译器也不会警告
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
//三个函数均未使用，编译时只有lose_this函数有警告
static int lose_this(int arg);
static int keep_this(int arg) __attribute__((used));     // retained in object file
static int keep_this_too(int arg) __attribute__((used)); // retained in object file

static int lose_this(int arg)
{
    return 0;
}

static int keep_this(int arg)
{
    return 0;
}

static int keep_this_too(int arg)
{
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("hello world!!!\n");
    
    return 0;
}