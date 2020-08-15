#include <stdio.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * min - return minimum of two values of the same or compatible types
 * @x: first value
 * @y: second value
 */
#ifndef min
#define min(x,y) ({ \
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void) (&_x == &_y);\
    _x < _y ? _x : _y; })
#endif

/**
 * max - return maximum of two values of the same or compatible types
 * @x: first value
 * @y: second value
 */
#ifndef max
#define max(x,y) ({ \
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void) (&_x == &_y);\
    _x > _y ? _x : _y; })
#endif
/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/
/*     rand01()函数         */
/*返回0～1000的随机函数      */
/****************************/
int rand_0_1000(void)
{
    return rand()%1001;
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
    int i, x, y;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_1000();
        y = rand_0_1000();
        
        printf("x %d y %d min %d max %d\n", x, y, min(x, y), max(x, y));
    }
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_1000();
        y = rand_0_1000();
        
        if(rand_0_1())
            x = -x;
        
        if(rand_0_1())
            y = -y;
        
        printf("x %d y %d min %d max %d\n", x, y, min(x, y), max(x, y));
    }
    
    return 0;
}