#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/bug.h
*/

/*
__CHECKER__ 是与 Sparse 相关的一个宏开关，从kernel顶层Makefile中可以看出
，当指定参数C=1或C=2时会调用Sparse。 Sparse是2004年由Linus创建的kernel代码静态检查工具。
sparse - Semantic Parser for C
https://stackoverflow.com/questions/53120610/what-does-the-attribute-force-do
https://bbs.csdn.net/topics/300072412
所以在这里该宏没有用
*/
// # define __force	__attribute__((force))

# define __force
/*
 * BUILD_BUG_ON_INVALID() permits the compiler to check the validity of the
 * expression but avoids the generation of any code, even if that expression
 * has side-effects.
 */
#define BUILD_BUG_ON_INVALID(e) ((void)(sizeof((__force long)(e))))

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct test {
    int a;
    char b;
};

int main(int argc, char* argv[])
{
    int a = 2;
    int b = 8;
    BUILD_BUG_ON_INVALID(b = a);
    printf("a = %d, b = %d\n", a, b);
    
    struct test x = {0};
    struct test y;
    
    BUILD_BUG_ON_INVALID(x.a = y.a);
    BUILD_BUG_ON_INVALID(x.a != y.a);
    BUILD_BUG_ON_INVALID(x.a == y.a);
    
    //BUILD_BUG_ON_INVALID(x = y);

    return 0;
}