#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * roundup - round up to the next specified multiple
 * @x: the value to up
 * @y: multiple to round up to
 *
 * Rounds @x up to next multiple of @y. If @y will always be a power
 * of 2, consider using the faster roundup().
 */
#define roundup(x, y) (					\
{							\
	typeof(y) __y = y;				\
	(((x) + (__y - 1)) / __y) * __y;		\
}							\
)
/**
 * rounddown - round down to next specified multiple
 * @x: the value to round
 * @y: multiple to round down to
 *
 * Rounds @x down to next multiple of @y. If @y will always be a power
 * of 2, consider using the faster rounddown().
 */
#define rounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)

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
    
    y = 100;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_3000();
        
        printf("x %d y %d roundup %d\n", x, y, roundup(x, y));
        printf("x %d y %d rounddown %d\n", x, y, rounddown(x, y));
    }
    
    y = 600;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_3000();
        
        printf("x %d y %d roundup %d\n", x, y, roundup(x, y));
        printf("x %d y %d rounddown %d\n", x, y, rounddown(x, y));
    }
    
    y = 1666;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_3000();
        
        printf("x %d y %d roundup %d\n", x, y, roundup(x, y));
        printf("x %d y %d rounddown %d\n", x, y, rounddown(x, y));
    }
    
    return 0;
}