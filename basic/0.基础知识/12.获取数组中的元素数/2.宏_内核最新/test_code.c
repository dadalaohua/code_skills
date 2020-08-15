#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//#define __CHECKER__
/************************************************************************/
/*                                                                      */
/************************************************************************/
#ifdef __CHECKER__
#define BUILD_BUG_ON_ZERO(e) (0)
#else /* __CHECKER__ */
/*
 * Force a compilation error if condition is true, but also produce a
 * result (of value 0 and type int), so the expression can be used
 * e.g. in a structure initializer (or where-ever else comma expressions
 * aren't permitted).
 */
#define BUILD_BUG_ON_ZERO(e) ((int)(sizeof(struct { int:(-!!(e)); })))
#endif /* __CHECKER__ */

/* Are two types/vars the same type (ignoring qualifiers)? */
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

/* &a[0] degrades to a pointer: a different type from an array */
#define __must_be_array(a)	BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))

/**
 * ARRAY_SIZE - get the number of elements in array @arr
 * @arr: array to be sized
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))

/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    unsigned char buf1[] = {'1', '2', '3', '4', '5', '6'};
    unsigned int buf2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int i;
    
    printf("buf1 len %d\n", ARRAY_SIZE(buf1));
    for(i = 0; i < ARRAY_SIZE(buf1); i++)
    {
        printf("%c ", buf1[i]);
    }
    printf("\n");
    
    printf("buf2 len %d\n", ARRAY_SIZE(buf2));
    for(i = 0; i < ARRAY_SIZE(buf2); i++)
    {
        printf("%d ", buf2[i]);
    }
    printf("\n");
    
    return 0;
}