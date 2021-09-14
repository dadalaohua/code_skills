#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,__N,...) __N
#define VA_NUM_ARGS(...)    VA_NUM_ARGS_IMPL(__VA_ARGS__,9,8,7,6,5,4,3,2,1)
            
#define __CONNECT2(__0, __1)            __0##__1
#define __CONNECT3(__0, __1, __2)       __0##__1##__2

#define CONNECT2(__0, __1)             __CONNECT2(__0, __1)
#define CONNECT3(__0, __1, __2)        __CONNECT3(__0, __1, __2)

#define __using1(__declare)                                                     \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL;                   \
                )


#define __using2(__declare, __on_leave_expr)                                    \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL;                   \
                 __on_leave_expr                                                \
                )


#define __using3(__declare, __on_enter_expr, __on_leave_expr)                   \
            for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL ?                  \
                    ((__on_enter_expr),1) : 0;                                  \
                 __on_leave_expr                                                \
                )

#define __using4(__dcl1, __dcl2, __on_enter_expr, __on_leave_expr)              \
            for (__dcl1, __dcl2, *CONNECT3(__using_, __LINE__,_ptr) = NULL;     \
                 CONNECT3(__using_, __LINE__,_ptr)++ == NULL ?                  \
                    ((__on_enter_expr),1) : 0;                                  \
                 __on_leave_expr                                                \
                )

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define using(...)  \
    CONNECT2(__using, VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)
/************************************************************************/
/*                                                                      */
/************************************************************************/
void enter_func(void)
{
    printf("enter_func\n");
}

void leave_func(void)
{
    printf("leave_func\n");
}

void body_func(void)
{
    printf("body_func\n");
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    using(int a = 0,printf("========= On Enter =======\r\n"),
                    printf("========= On Leave =======\r\n"))
    {
        printf("\t In Body a=%d \r\n", ++a);
    }
    
    printf("\n");

    using(int func = 0, enter_func(), leave_func())
    {
        printf("body_func %d\n", func);
        body_func();
    }
    
    printf("\n");
    
    using(int test1 = 1)
    {
        printf("test1 %d\n", test1);
        body_func();
    }
    
    printf("\n");
    
    using(int test2 = 2, leave_func())
    {
        printf("test2 %d\n", test2);
        body_func();
    }
    
    printf("\n");
    
    using(int test3 = 3, enter_func(), leave_func())
    {
        printf("test3 %d\n", test3);
        body_func();
    }
    
    printf("\n");
    
    using(int test4 = 4, test5 = 5, enter_func(), leave_func())
    {
        printf("test4 %d test5 %d\n", test4, test5);
        body_func();
    }
    
    printf("\n");
    
    return 0;
}