#include <stdio.h>
#include <dlfcn.h>

// 库的头文件
#include "func.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef void (*pFunc)(void);

void magicfunc(void)
{
    // 在调用目标函数之前，做一些处理
    printf("before call magic func do something... \n");
    
    //打开动态链接库
    void *handle = dlopen("./lib/libfunc.so", RTLD_NOW);
    
    // 查找库中的目标函数
    pFunc pf = dlsym(handle, "magicfunc");
    
    // 调用目标函数
    pf();
    
    // 关闭动态库句柄
    dlclose(handle);
    
    // 在调用目标函数之后，做一些处理
    printf("after call magic func do something... \n");
}

