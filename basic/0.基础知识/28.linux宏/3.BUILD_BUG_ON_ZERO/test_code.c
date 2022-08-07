#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/bug.h
*/

/* Force a compilation error if condition is true, but also produce a
   result (of value 0 and type size_t), so the expression can be used
   e.g. in a structure initializer (or where-ever else comma expressions
   aren't permitted). */
#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int:-!!(e); }))
#define BUILD_BUG_ON_NULL(e) ((void *)sizeof(struct { int:-!!(e); }))

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%zu\n", BUILD_BUG_ON_ZERO(0));
    printf("%p\n", BUILD_BUG_ON_NULL(NULL));
    
    return 0;
}