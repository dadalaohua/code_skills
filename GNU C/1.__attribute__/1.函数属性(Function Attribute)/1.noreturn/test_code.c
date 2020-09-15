#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
__attribute__ noreturn    表示没有返回值

1、通知编译器该函数不返回。然后，编译器可以通过删除从未到达的代码来执行优化。
2、这个函数属性是 ARM 编译器支持的 GNU 编译器扩展。__declspec(noreturn) 与之等价。
3、如果函数达到显式或隐式返回，则忽略((noreturn))，编译器生成一个警告
4、使用此属性可减少调用从不返回的函数(如exit())的成本。
5、最佳实践是始终使用while(1);终止不返回的函数。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
void overflow(void) __attribute__((noreturn)); //没有noreturn会有警告

void overflow(void)
{
    printf("overflow\n");
    while (1);
}

int foo(int n)
{
    if (n > 10)
        overflow();
    else
        return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int val;

    printf("请输入一个数字：");
    scanf("%d", &val); 
    printf("val : %d\n", val);
    
    foo(val);
    
    printf("normal\n");

    return 0;
}