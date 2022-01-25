#include <stdio.h>

// 真正的目标函数
#include "lib/func.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void wrap_magicfunc(void)
{
    // 在调用目标函数之前，做一些处理
    printf("before call magic func do something... \n");
    
    magicfunc();
    
    // 在调用目标函数之后，做一些处理
    printf("after call magic func do something... \n");
}

