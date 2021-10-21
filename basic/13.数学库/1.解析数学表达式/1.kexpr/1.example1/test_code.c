#include <stdio.h>
#include <math.h>

#include "kexpr.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
//Example 1: basic functionality
int main(int argc, char* argv[])
{
    kexpr_t *ke;
    int err;
    ke = ke_parse("5.1+6*myexp(x)", &err);   // parse expression 解析表达式
    ke_set_real(ke, "x", 1.0);               // set the value of a variable 设置变量的值
    ke_set_real_func1(ke, "myexp", exp);     // define a math function 定义一个数学函数
    printf("%g\n", ke_eval_real(ke, &err));  // compute the expression 计算表达式
    ke_destroy(ke);                          // deallocate 释放
    
    return 0;
}