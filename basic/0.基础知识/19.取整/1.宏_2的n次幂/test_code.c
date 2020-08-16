#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
 * This looks more complex than it should be. But we need to
 * get the type for the ~ right in round_down (it needs to be
 * as wide as the result!), and we want to evaluate the macro
 * arguments just once each.
 */
#define __round_mask(x, y) ((__typeof__(x))((y)-1))
/**
 * round_up - round up to next specified power of 2
 * @x: the value to round
 * @y: multiple to round up to (must be a power of 2)
 *
 * Rounds @x up to next multiple of @y (which must be a power of 2).
 * To perform arbitrary rounding up, use roundup() below.
 */
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
/**
 * round_down - round down to next specified power of 2
 * @x: the value to round
 * @y: multiple to round down to (must be a power of 2)
 *
 * Rounds @x down to next multiple of @y (which must be a power of 2).
 * To perform arbitrary rounding down, use rounddown() below.
 */
#define round_down(x, y) ((x) & ~__round_mask(x, y))

/************************************************************************/
/*                                                                      */
/************************************************************************/
/****************************/
/*     rand_0_3000()函数         */
/*返回0～3000的随机函数      */
/****************************/
int rand_0_3000(void)
{
    return rand()%3001;
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
    int i;
    unsigned int x, y;
    
    y = 128;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_3000();
        
        printf("x %d y %d round_up %d\n", x, y, round_up(x, y));
        printf("x %d y %d round_down %d\n", x, y, round_down(x, y));
    }
    
    y = 512;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_3000();
        
        printf("x %d y %d round_up %d\n", x, y, round_up(x, y));
        printf("x %d y %d round_down %d\n", x, y, round_down(x, y));
    }
    
    y = 1024;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_3000();
        
        printf("x %d y %d round_up %d\n", x, y, round_up(x, y));
        printf("x %d y %d round_down %d\n", x, y, round_down(x, y));
    }
    
    return 0;
}