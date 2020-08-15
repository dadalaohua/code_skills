#include <stdio.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/* Indirect macros required for expanded argument pasting, eg. __LINE__. */
#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)

/* Not-quite-unique ID. */
#ifndef __UNIQUE_ID
# define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __LINE__)
#endif

/*
 * min()/max()/clamp() macros must accomplish three things:
 *
 * - avoid multiple evaluations of the arguments (so side-effects like
 *   "x++" happen only once) when non-constant.
 * - perform strict type-checking (to generate warnings instead of
 *   nasty runtime surprises). See the "unnecessary" pointer comparison
 *   in __typecheck().
 * - retain result as a constant expressions when called with only
 *   constant expressions (to avoid tripping VLA warnings in stack
 *   allocation usage).
 */
#define __typecheck(x, y) \
		(!!(sizeof((typeof(x) *)1 == (typeof(y) *)1)))

/*
 * This returns a constant expression while determining if an argument is
 * a constant expression, most importantly without evaluating the argument.
 * Glory to Martin Uecker <Martin.Uecker@med.uni-goettingen.de>
 */
#define __is_constexpr(x) \
	(sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))

#define __no_side_effects(x, y) \
		(__is_constexpr(x) && __is_constexpr(y))

#define __safe_cmp(x, y) \
		(__typecheck(x, y) && __no_side_effects(x, y))

#define __cmp(x, y, op)	((x) op (y) ? (x) : (y))

#define __cmp_once(x, y, unique_x, unique_y, op) ({	\
		typeof(x) unique_x = (x);		\
		typeof(y) unique_y = (y);		\
		__cmp(unique_x, unique_y, op); })

#define __careful_cmp(x, y, op) \
	__builtin_choose_expr(__safe_cmp(x, y), \
		__cmp(x, y, op), \
		__cmp_once(x, y, __UNIQUE_ID(__x), __UNIQUE_ID(__y), op))

/*
 * ..and if you can't take the strict
 * types, you can specify one yourself.
 *
 * Or not use min/max/clamp at all, of course.
 */
 
/**
 * min_t - return minimum of two values, using the specified type
 * @type: data type to use
 * @x: first value
 * @y: second value
 */
#define min_t(type, x, y)	__careful_cmp((type)(x), (type)(y), <)

/**
 * max_t - return maximum of two values, using the specified type
 * @type: data type to use
 * @x: first value
 * @y: second value
 */
#define max_t(type, x, y)	__careful_cmp((type)(x), (type)(y), >)

/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/
/*     rand01()函数         */
/*返回0～1000的随机函数      */
/****************************/
int rand_0_1000(void)
{
    return rand()%1001;
}

/****************************/
/*     rand01()函数         */
/*返回0、1的随机函数        */
/****************************/
int rand_0_1(void)
{
    return rand()%2;
}

/****************************/

int main(int argc, char* argv[])
{
    int i, x, y;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_1000();
        y = rand_0_1000();
        
        printf("x %d y %d min %u max %u\n", x, y, min_t(unsigned int, x, y), max_t(unsigned int, x, y));
    }
    
    printf("\n");
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_1000();
        y = rand_0_1000();
        
        if(rand_0_1())
            x = -x;
        
        if(rand_0_1())
            y = -y;
        
        printf("x %d y %d min %u max %u\n", x, y, min_t(unsigned int, x, y), max_t(unsigned int, x, y));
    }
    
    return 0;
}