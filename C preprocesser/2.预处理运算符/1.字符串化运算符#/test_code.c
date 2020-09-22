#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//宏延续运算符（\）
#define  message_for(a, b)  \
    printf(#a " and " #b ": We love you!\n")    //字符串常量化运算符（#）
//在宏定义中，当需要把一个宏的参数转换为字符串常量时，则使用字符串常量化运算符（#）。在宏中使用的该运算符有一个特定的参数或参数列表

#define  message_test(a)  printf(#a " say hello!\n")    //字符串常量化运算符（#）
#define  message_abc(a, b, c)  printf(#a " , " #b " and " #c " say 666!\n")    //字符串常量化运算符（#）

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    message_for(Amy, Bob);                      //Amy and Bob: We love you!
    message_test(Candy);                        //Candy say hello!
    message_abc(A, B, C);                       //A , B and C say 666!

    return 0;
}