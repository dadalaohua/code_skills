#include <stdio.h>

// 真正的目标函数
#include "func_wrap.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
// 这里不能直接引用 lib/func.h 中的函数，而要由链接器来完成解析。
extern void __real_magicfunc(void);

void __wrap_magicfunc(void)
{
    // 在调用目标函数之前，做一些处理
    printf("before call magic func do something... \n");
    
    __real_magicfunc();
    
    // 在调用目标函数之后，做一些处理
    printf("after call magic func do something... \n");
}

