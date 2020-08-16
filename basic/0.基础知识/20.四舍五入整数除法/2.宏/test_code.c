#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define DIV_ROUND_CLOSEST(n, d) ((((n) < 0) ^ ((d) < 0)) ? (((n) - (d)/2)/(d)) : (((n) + (d)/2)/(d)))


int divRoundClosest(const int n, const int d)
{
    return ((n < 0) ^ (d < 0)) ? ((n - d/2)/d) : ((n + d/2)/d);
}
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