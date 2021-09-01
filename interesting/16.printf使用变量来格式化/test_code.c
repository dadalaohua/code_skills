#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Printf in C allows you to use variables for formatting format specifiers themselves
//C 中的 Printf 允许你使用变量来格式化格式说明符本身
//the * character achieves this effect.
//* 字符实现了这种效果。

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a = 3;
    float b = 6.412355;
    
    printf("%.*f \n",a,b);
    
    return 0;
}