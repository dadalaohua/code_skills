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
 * clamp - return a value clamped to a given range with strict typechecking
 * @val: current value
 * @lo: lowest allowable value
 * @hi: highest allowable value
 *
 * This macro does strict typechecking of @lo/@hi to make sure they are of the
 * same type as @val.  See the unnecessary pointer comparisons.
 */
#define clamp(val, lo, hi) min((typeof(val))max(val, lo), hi)

/************************************************************************/
/*                                                                      */
/************************************************************************/
/****************************/
/*     rand_0_100()函数         */
/*返回0～100的随机函数      */
/****************************/
int rand_0_100(void)
{
    return rand()%101;
}

/****************************/

int main(int argc, char* argv[])
{
    int i, x;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    printf("range min %d ~ max %d \n", 20, 45);
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_100();
        
        printf("x %d clamp %d \n", x, clamp(x, 20, 45));
    }
    
    printf("\n");
    
    return 0;
}