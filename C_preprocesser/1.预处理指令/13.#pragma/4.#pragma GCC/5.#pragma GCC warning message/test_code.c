#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#if 0
#pragma GCC warning  "this warning is not seen"
#endif
void foo(void)
{
  return;
#pragma GCC warning  "this warning is seen"
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    printf("hello world\n");
    
    return 0;
}