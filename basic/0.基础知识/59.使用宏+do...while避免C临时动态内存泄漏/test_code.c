#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MEMORY_GUARD_BEGIN(type, variable)  do{ type* variable = (type*)malloc(sizeof(type))

#define MEMORY_GUARD_END(variable)          free(variable); variable =NULL;}while(0)

/************************************************************************/
/*                                                                      */
/************************************************************************/
void simple1(void)
{
    MEMORY_GUARD_BEGIN(char, buf);
    
    *buf = 5;
    
    printf("buf %d\n", *buf);
    
    MEMORY_GUARD_END(buf);
}

void simple2(void)
{
    typedef struct
    {
        int a;
        char b[5];
    } test_type;
    
    MEMORY_GUARD_BEGIN(test_type, buf);
    
    buf->a = 5;
    buf->b[0] = 10;
    buf->b[1] = 11;
    buf->b[2] = 12;
    buf->b[3] = 13;
    buf->b[4] = 14;
    
    printf("buf->a %d\n", buf->a);
    printf("buf->b[0] %d\n", buf->b[0]);
    printf("buf->b[1] %d\n", buf->b[1]);
    printf("buf->b[2] %d\n", buf->b[2]);
    printf("buf->b[3] %d\n", buf->b[3]);
    printf("buf->b[4] %d\n", buf->b[4]);
    
    MEMORY_GUARD_END(buf);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    simple1();
    
    simple2();
    
    return 0;
}