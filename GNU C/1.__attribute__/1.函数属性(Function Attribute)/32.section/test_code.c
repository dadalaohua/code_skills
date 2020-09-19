#include <stdio.h>
#include <stdarg.h>
/*
The `section` function attribute enables you to place code in different sections of the image.

section 函数属性使您能够将代码放置在镜像的不同部分中。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Function_Attributes_section_0 被放置到RO section new_section 中，而不是 .text 中。
//通过命令查看代码段objdump -h test_code.o
void Function_Attributes_section_0 (void) __attribute__((section ("new_section")));
void Function_Attributes_section_0 (void)
{
    static int aStatic =0;
    aStatic++;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    Function_Attributes_section_0();
    
    return 0;
}