#include <stdio.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/
/* Force a compilation error if condition is false, but also produce a result
* (of value 0 and type size_t), so it can be used e.g. in a structure
* initializer (or wherever else comma expressions aren't permitted). */
/* Linux calls these BUILD_BUG_ON_ZERO/_NULL, which is rather misleading. */
#define STATIC_ZERO_ASSERT(condition) (sizeof(struct { int:-!(condition); }) )
#define STATIC_NULL_ASSERT(condition) ((void *)STATIC_ZERO_ASSERT(condition) )
/* Force a compilation error if condition is false */
#define STATIC_ASSERT(condition) ((void)STATIC_ZERO_ASSERT(condition))

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    /*
        如果值为0，会在编译时报错
        error: negative width in bit-field ‘<anonymous>’
        位域不能是负宽度
        预处理的值为
        ((void)(sizeof(struct { int:-!(0); }) ));
        也就是
        ((void)(sizeof(struct { int:-1; }) ));
        位域宽度为负
    */
    //STATIC_ASSERT(0);
    
    /*
        预处理的值为
        ((void)(sizeof(struct { int:-!(1); }) ));
        也就是
        ((void)(sizeof(struct { int:0; }) ));
        合法
    */
    STATIC_ASSERT(1);
    
    /*
        预处理的值为
        ((void)(sizeof(struct { int:-!(5 < 10); }) ));
        也就是
        ((void)(sizeof(struct { int:0; }) ));
        合法
    */
    STATIC_ASSERT(5 < 10);
    
    /*
        如果值为NULL，会在编译时报错
        error: negative width in bit-field ‘<anonymous>’
        位域不能是负宽度
        预处理的值为
        ((void *)(sizeof(struct { int:-!(((void *)0)); }) ) );
        不合法
    */
    //STATIC_NULL_ASSERT(NULL);
    
    return 0;
}