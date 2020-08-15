#include <stdio.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define __ALIGN_KERNEL(x, a)		__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))

/* @a is a power of 2 value */
#define ALIGN(x, a)		__ALIGN_KERNEL((x), (a))
#define ALIGN_DOWN(x, a)	__ALIGN_KERNEL((x) - ((a) - 1), (a))
#define __ALIGN_MASK(x, mask)	__ALIGN_KERNEL_MASK((x), (mask))
#define PTR_ALIGN(p, a)		((typeof(p))ALIGN((unsigned long)(p), (a)))
#define IS_ALIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)

/************************************************************************/
/*                                                                      */
/************************************************************************/
/****************************/
/*     rand_0_100()函数         */
/*返回0～100的随机函数      */
/****************************/
int rand_0_10000(void)
{
    return rand()%10001;
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
    int i, x, a;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    //ALIGN
    printf("ALIGN:\n");
    
    a = 512;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d ALIGN %d\n", x, a, ALIGN(x, a));
    }
    printf("\n");
    
    a = 1024;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d ALIGN %d\n", x, a, ALIGN(x, a));
    }
    printf("\n");
    
    a = 2048;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d ALIGN %d\n", x, a, ALIGN(x, a));
    }
    printf("\n");
    
    //ALIGN_DOWN
    printf("\n");
    printf("ALIGN_DOWN:\n");
    
    a = 512;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d ALIGN_DOWN %d\n", x, a, ALIGN_DOWN(x, a));
    }
    printf("\n");
    
    a = 1024;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d ALIGN_DOWN %d\n", x, a, ALIGN_DOWN(x, a));
    }
    printf("\n");
    
    a = 2048;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d ALIGN_DOWN %d\n", x, a, ALIGN_DOWN(x, a));
    }
    printf("\n");
    
    //PTR_ALIGN
    printf("\n");
    printf("PTR_ALIGN:\n");
    
    a = 512;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d PTR_ALIGN %d\n", x, a, PTR_ALIGN(x, a));
    }
    printf("\n");
    
    a = 1024;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d PTR_ALIGN %d\n", x, a, PTR_ALIGN(x, a));
    }
    printf("\n");
    
    a = 2048;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d PTR_ALIGN %d\n", x, a, PTR_ALIGN(x, a));
    }
    printf("\n");
    
    //IS_ALIGNED
    printf("\n");
    printf("IS_ALIGNED:\n");
    
    a = 512;
    
    x = 512;
    printf("x %d a %d IS_ALIGNED %d\n", x, a, IS_ALIGNED(x, a));
    
    x = 1024;
    printf("x %d a %d IS_ALIGNED %d\n", x, a, IS_ALIGNED(x, a));
    
    x = 1536;
    printf("x %d a %d IS_ALIGNED %d\n", x, a, IS_ALIGNED(x, a));
    
    x = 2048;
    printf("x %d a %d IS_ALIGNED %d\n", x, a, IS_ALIGNED(x, a));
    
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d IS_ALIGNED %d\n", x, a, IS_ALIGNED(x, a));
    }
    printf("\n");
    
    a = 1024;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d IS_ALIGNED %d\n", x, a, IS_ALIGNED(x, a));
    }
    printf("\n");
    
    a = 2048;
    for(i = 0; i < 10; i++)
    {
        x = rand_0_10000();
        
        printf("x %d a %d IS_ALIGNED %d\n", x, a, IS_ALIGNED(x, a));
    }
    printf("\n");
    
    return 0;
}