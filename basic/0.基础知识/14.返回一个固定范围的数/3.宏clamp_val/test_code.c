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

/**
 * clamp_t - return a value clamped to a given range using a given type
 * @type: the type of variable to use
 * @val: current value
 * @lo: minimum allowable value
 * @hi: maximum allowable value
 *
 * This macro does no typechecking and uses temporary variables of type
 * @type to make all the comparisons.
 */
#define clamp_t(type, val, lo, hi) min_t(type, max_t(type, val, lo), hi)

/**
 * clamp_val - return a value clamped to a given range using val's type
 * @val: current value
 * @lo: minimum allowable value
 * @hi: maximum allowable value
 *
 * This macro does no typechecking and uses temporary variables of whatever
 * type the input argument @val is.  This is useful when @val is an unsigned
 * type and @lo and @hi are literals that will otherwise be assigned a signed
 * integer type.
 */
#define clamp_val(val, lo, hi) clamp_t(typeof(val), val, lo, hi)

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
        
        printf("x %d clamp %d \n", x, clamp_val(x, 20, 45));
    }
    
    printf("\n");
    
    return 0;
}