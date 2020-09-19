#include <stdio.h>
/*
__attribute__((constructor)) function attribute

若函数被设定为constructor属性，则该函数会在main（）函数执行之前被自动的执行
类似的，若函数被设定为destructor属性，则该函数会在main（）函数执行之后或者exit（）被调用后被自动的执行。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
// __attribute__((const)) functions do not read or modify any global memory
int my_double(int b) __attribute__((const));

void before_main() __attribute__((constructor));
void after_main()  __attribute__((destructor));

void before_main()  
{  
   printf("before main\n");  
}  
  
void after_main()  
{  
   printf("after main\n");  
}  
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    printf("in main\n");

    return 0;
}