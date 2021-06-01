#include <stdio.h>
#include <stdlib.h>

#define CHAR_BIT 8
/************************************************************************/
/*                                                                      */
/************************************************************************/
//这两个函数必须满足INT_MIN <= x - y <= INT_MAX

int min2(int x, int y)
{
    return y + ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1)));
}

int max2(int x, int y)
{
    return x - ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1)));
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int min(int x, int y)
{
    return y ^ ((x ^ y) & -(x < y));
}

int max(int x, int y)
{
    return x ^ ((x ^ y) & -(x < y));
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int x1 = 20, y1 = 35;
    int x2 = 56, y2 = -23;
    
    printf("x:%d, y:%d min:%d\n", x1, y1, min(x1, y1));
    printf("x:%d, y:%d min:%d\n", x2, y2, min(x2, y2));
    
    printf("x:%d, y:%d max:%d\n", x1, y1, max(x1, y1));
    printf("x:%d, y:%d max:%d\n", x2, y2, max(x2, y2));
    
    printf("x:%d, y:%d min:%d\n", x1, y1, min2(x1, y1));
    printf("x:%d, y:%d min:%d\n", x2, y2, min2(x2, y2));
    
    printf("x:%d, y:%d max:%d\n", x1, y1, max2(x1, y1));
    printf("x:%d, y:%d max:%d\n", x2, y2, max2(x2, y2));
    
    return 0;
}