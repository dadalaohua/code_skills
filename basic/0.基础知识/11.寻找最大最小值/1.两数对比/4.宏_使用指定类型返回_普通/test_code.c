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

/*
 * ..and if you can't take the strict
 * types, you can specify one yourself.
 *
 * Or not use min/max/clamp at all, of course.
 */
 
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
/**
 * min_t - return minimum of two values, using the specified type
 * @type: data type to use
 * @x: first value
 * @y: second value
 */
#define min_t(type, a, b) min(((type) a), ((type) b))
/**
 * max_t - return maximum of two values, using the specified type
 * @type: data type to use
 * @x: first value
 * @y: second value
 */
#define max_t(type, a, b) max(((type) a), ((type) b))

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
        
        printf("x %d y %d min %u max %u\n", x, y, min_t(unsigned int, x, y), max_t(unsigned int, x, y));
    }
    
    printf("\n");
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_1000();
        y = rand_0_1000();
        
        if(rand_0_1())
            x = -x;
        
        if(rand_0_1())
            y = -y;
        
        printf("x %d y %d min %u max %u\n", x, y, min_t(unsigned int, x, y), max_t(unsigned int, x, y));
    }
    
    return 0;
}