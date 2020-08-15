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
#define min(x,y) ({ \
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void) (&_x == &_y);\
    _x < _y ? _x : _y; })

/**
 * max - return maximum of two values of the same or compatible types
 * @x: first value
 * @y: second value
 */
#define max(x,y) ({ \
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void) (&_x == &_y);\
    _x > _y ? _x : _y; })

/**
 * min3 - return minimum of three values
 * @x: first value
 * @y: second value
 * @z: third value
 */
#define min3(x, y, z) min((typeof(x))min(x, y), z)

/**
 * max3 - return maximum of three values
 * @x: first value
 * @y: second value
 * @z: third value
 */
#define max3(x, y, z) max((typeof(x))max(x, y), z)
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
    int i, x, y, z;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_1000();
        y = rand_0_1000();
        z = rand_0_1000();
        
        printf("x %d y %d z %d min %d max %d\n", x, y, z, min3(x, y, z), max3(x, y, z));
    }
    
    printf("\n");
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_1000();
        y = rand_0_1000();
        z = rand_0_1000();
        
        if(rand_0_1())
            x = -x;
        
        if(rand_0_1())
            y = -y;
        
        if(rand_0_1())
            z = -z;
        
        printf("x %d y %d z %d min %d max %d\n", x, y, z, min3(x, y, z), max3(x, y, z));
    }
    
    return 0;
}