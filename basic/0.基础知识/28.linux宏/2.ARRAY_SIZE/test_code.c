#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/kernel.h
*/

/* Force a compilation error if condition is true, but also produce a
   result (of value 0 and type size_t), so the expression can be used
   e.g. in a structure initializer (or where-ever else comma expressions
   aren't permitted). */
#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int:-!!(e); }))
#define BUILD_BUG_ON_NULL(e) ((void *)sizeof(struct { int:-!!(e); }))

/* Are two types/vars the same type (ignoring qualifiers)? */
#ifndef __same_type
# define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#endif

/* &a[0] degrades to a pointer: a different type from an array */
#define __must_be_array(a) BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))

//#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int buf[10] = {0};
    printf("%zu\n", ARRAY_SIZE(buf));
    
    int array[1] = {0};
    printf("%zu\n", ARRAY_SIZE(array));
    
    //下面这些会编译不过
    // int* val;
    // printf("%zu\n", ARRAY_SIZE(val));
    
    // int val;
    // printf("%zu\n", ARRAY_SIZE(&val));
    
    return 0;
}