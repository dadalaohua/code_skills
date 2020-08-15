#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * swap - swap values of @a and @b
 * @a: first value
 * @b: second value
 */
#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

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
    swap(x, y);
    printf("swap x y, x %d y %d\n", x, y);
    
    x = -656;
    y = 593;
    printf("x %d y %d\n", x, y);
    swap(x, y);
    printf("swap x y, x %d y %d\n", x, y);
    
    x = 0;
    y = 758;
    printf("x %d y %d\n", x, y);
    swap(x, y);
    printf("swap x y, x %d y %d\n", x, y);
    
    return 0;
}