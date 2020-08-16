#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
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

/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    int i;
    int x, y;

    x = 5;
    y = 4;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    x = 7;
    y = 4;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    x = 176;
    y = 154;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    x = 310;
    y = 154;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    x = -5;
    y = 4;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    x = 7;
    y = -4;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    x = 176;
    y = -154;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    x = -310;
    y = 154;
    printf("x %d y %d DIV_ROUND_CLOSEST %d\n", x, y, DIV_ROUND_CLOSEST(x, y));
    
    return 0;
}