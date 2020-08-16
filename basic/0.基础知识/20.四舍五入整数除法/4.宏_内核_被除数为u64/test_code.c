#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef u32			uint32_t;
typedef u64			uint64_t;

/**
 * do_div - returns 2 values: calculate remainder and update new dividend
 * @n: uint64_t dividend (will be updated)
 * @base: uint32_t divisor
 *
 * Summary:
 * ``uint32_t remainder = n % base;``
 * ``n = n / base;``
 *
 * Return: (uint32_t)remainder
 *
 * NOTE: macro parameter @n is evaluated multiple times,
 * beware of side effects!
 */
# define do_div(n,base) ({					\
	uint32_t __base = (base);				\
	uint32_t __rem;						\
	__rem = ((uint64_t)(n)) % __base;			\
	(n) = ((uint64_t)(n)) / __base;				\
	__rem;							\
 })

/*
 * Divide positive or negative dividend by positive or negative divisor
 * and round to closest integer. Result is undefined for negative
 * divisors if the dividend variable type is unsigned and for negative
 * dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor)(			\
{							\
	typeof(x) __x = x;				\
	typeof(divisor) __d = divisor;			\
	(((typeof(x))-1) > 0 ||				\
	 ((typeof(divisor))-1) > 0 ||			\
	 (((__x) > 0) == ((__d) > 0))) ?		\
		(((__x) + ((__d) / 2)) / (__d)) :	\
		(((__x) - ((__d) / 2)) / (__d));	\
}							\
)
/*
 * Same as above but for u64 dividends. divisor must be a 32-bit
 * number.
 */
#define DIV_ROUND_CLOSEST_ULL(x, divisor)(		\
{							\
	typeof(divisor) __d = divisor;			\
	unsigned long long _tmp = (x) + (__d) / 2;	\
	do_div(_tmp, __d);				\
	_tmp;						\
}							\
)
/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    int i;
    uint64_t x;
    uint32_t y;

    x = 4611686018427387903;
    y = 4;
    printf("x %lld y %d DIV_ROUND_CLOSEST_ULL %lld\n", x, y, DIV_ROUND_CLOSEST_ULL(x, y));
    
    x = 7;
    y = 4;
    printf("x %lld y %d DIV_ROUND_CLOSEST_ULL %lld\n", x, y, DIV_ROUND_CLOSEST_ULL(x, y));
    
    x = 176;
    y = 154;
    printf("x %lld y %d DIV_ROUND_CLOSEST_ULL %lld\n", x, y, DIV_ROUND_CLOSEST_ULL(x, y));
    
    x = 310;
    y = 154;
    printf("x %lld y %d DIV_ROUND_CLOSEST_ULL %lld\n", x, y, DIV_ROUND_CLOSEST_ULL(x, y));
    
    return 0;
}