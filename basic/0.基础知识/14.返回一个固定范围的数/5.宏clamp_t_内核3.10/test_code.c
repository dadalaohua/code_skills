#include <stdio.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * clamp_t - return a value clamped to a given range using a given type
 * @type: the type of variable to use
 * @val: current value
 * @min: minimum allowable value
 * @max: maximum allowable value
 *
 * This macro does no typechecking and uses temporary variables of type
 * 'type' to make all the comparisons.
 */
#define clamp_t(type, val, min, max) ({		\
	type __val = (val);			\
	type __min = (min);			\
	type __max = (max);			\
	__val = __val < __min ? __min: __val;	\
	__val > __max ? __max: __val; })

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
        
        printf("x %d clamp %d \n", x, clamp_t(int, x, 20, 45));
    }
    
    printf("\n");
    
    return 0;
}