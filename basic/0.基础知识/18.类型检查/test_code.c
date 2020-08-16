#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
 * Check at compile time that something is of a particular type.
 * Always evaluates to 1 so you may use it easily in comparisons.
 */
#define typecheck(type,x) \
({	type __dummy; \
	typeof(x) __dummy2; \
	(void)(&__dummy == &__dummy2); \
	1; \
})

/*
 * Check at compile time that 'function' is a certain type, or is a pointer
 * to that type (needs to use typedef for the function type.)
 */
#define typecheck_fn(type,function) \
({	typeof(type) __tmp = function; \
	(void)__tmp; \
})

/************************************************************************/
/*                                                                      */
/************************************************************************/
int test_function(void)
{
    printf("test function\n");
    
    return;
}

/****************************/

int main(int argc, char* argv[])
{
    int i;
    
    //typecheck(char, i);   //类型错误，会在编译时提示警告或出错
    typecheck(int, i);
    
    //typecheck_fn(char (*)(void), test_function);  //类型错误，会在编译时提示警告或出错
    //typecheck_fn(int (*)(int), test_function);    //类型错误，会在编译时提示警告或出错
    typecheck_fn(int (*)(void), test_function);
    
    return 0;
}