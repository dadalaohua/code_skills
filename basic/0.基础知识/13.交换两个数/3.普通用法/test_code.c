#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void swap(int *x, int *y)
{
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

void swap2(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    int x, y;
    
    x = 63;
    y = 93;
    printf("x %d y %d\n", x, y);
    swap(&x, &y);
    printf("swap x y, x %d y %d\n", x, y);
    
    x = -656;
    y = 593;
    printf("x %d y %d\n", x, y);
    swap(&x, &y);
    printf("swap x y, x %d y %d\n", x, y);
    
    x = 0;
    y = 758;
    printf("x %d y %d\n", x, y);
    swap(&x, &y);
    printf("swap x y, x %d y %d\n", x, y);
    
    x = 0;
    y = 0;
    printf("x %d y %d\n", x, y);
    swap(&x, &y);
    printf("swap x y, x %d y %d\n", x, y);
    
    printf("\n");
    //swap2
    x = 63;
    y = 93;
    printf("x %d y %d\n", x, y);
    swap2(&x, &y);
    printf("swap2 x y, x %d y %d\n", x, y);
    
    x = -656;
    y = 593;
    printf("x %d y %d\n", x, y);
    swap2(&x, &y);
    printf("swap2 x y, x %d y %d\n", x, y);
    
    x = 0;
    y = 758;
    printf("x %d y %d\n", x, y);
    swap2(&x, &y);
    printf("swap2 x y, x %d y %d\n", x, y);
    
    x = 0;
    y = 0;
    printf("x %d y %d\n", x, y);
    swap2(&x, &y);
    printf("swap2 x y, x %d y %d\n", x, y);
    
    return 0;
}