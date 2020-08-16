#include <stdio.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef long long           s64;

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
 * abs() handles unsigned and signed longs, ints, shorts and chars.  For all
 * input types abs() returns a signed long.
 * abs() should not be used for 64-bit types (s64, u64, long long) - use abs64()
 * for those.
 */
#define abs(x) ({						\
		long ret;					\
		if (sizeof(x) == sizeof(long)) {		\
			long __x = (x);				\
			ret = (__x < 0) ? -__x : __x;		\
		} else {					\
			int __x = (x);				\
			ret = (__x < 0) ? -__x : __x;		\
		}						\
		ret;						\
	})

#define abs64(x) ({				\
		s64 __x = (x);			\
		(__x < 0) ? -__x : __x;		\
	})


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
    long long z;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_100();
        
        if(rand_0_1())
            x = -x;
        
        printf("x %d abs %ld \n", x, abs(x));
    }
    
    printf("\n");
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_100();
        y = rand_0_100();
        
        if(rand_0_1())
            x = -x;
        
        if(rand_0_1())
            y = -y;
        
        printf("x+y %d abs %ld \n", x+y, abs(x+y));
    }
    
    printf("\n");
    
    for(i = 0; i < 10; i++)
    {
        z = rand_0_100();
        
        if(rand_0_1())
            z = -z;
        
        printf("z %lld abs64 %lld \n", z, abs64(z));
    }
    
    return 0;
}