#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
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
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    x = 7;
    y = 4;
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    x = 176;
    y = 154;
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    x = 310;
    y = 154;
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    x = -5;
    y = 4;
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    x = 7;
    y = -4;
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    x = 176;
    y = -154;
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    x = -310;
    y = 154;
    printf("x %d y %d divRoundClosest %d\n", x, y, divRoundClosest(x, y));
    
    return 0;
}