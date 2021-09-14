#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define __CONNECT3(__A, __B, __C)       __A##__B##__C
#define CONNECT3(__A, __B, __C)         __CONNECT3(__A, __B, __C)

#define using(__declare, __on_enter_expr, __on_leave_expr)                   \
         for (__declare, *CONNECT3(__using_, __LINE__,_ptr) = NULL;          \
              CONNECT3(__using_, __LINE__,_ptr)++ == NULL ?                  \
                 ((__on_enter_expr),1) : 0;                                  \
              __on_leave_expr                                                \
             )

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

    using(int func = 0, enter_func(), leave_func())
    {
        printf("body_func %d\n", func);
        body_func();
    }
    
    return 0;
}