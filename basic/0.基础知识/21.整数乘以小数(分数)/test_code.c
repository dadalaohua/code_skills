#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
 * Multiplies an integer by a fraction, while avoiding unnecessary
 * overflow or loss of precision.
 */
#define mult_frac(x, numer, denom)(			\
{							\
	typeof(x) quot = (x) / (denom);			\
	typeof(x) rem  = (x) % (denom);			\
	(quot * (numer)) + ((rem * (numer)) / (denom));	\
}							\
)

/************************************************************************/
/*                                                                      */
/************************************************************************/


/****************************/

int main(int argc, char* argv[])
{
    int x, numer, denom;
    
    x = 10;     //正数
    numer = 2;  //分子
    denom = 3;  //分母
    
    //mult_frac = x*numer/denom;
    
    printf("x %d numer %d denom %d mult_frac %d\n",
            x, numer, denom, mult_frac(x, numer, denom));
    
    return 0;
}