# posix_spawn

https://blog.csdn.net/yiwuxue/article/details/22189685

posix_spawn() 函数的说明：

```c
#include <spawn.h>
int posix_spawn(pid_t *restrict pid,   
                const char *restrict path,  
                const posix_spawn_file_actions_t *file_actions,  
                const posix_spawnattr_t *restrict attrp,  
                char *const argv[restrict], char *const envp[restrict]);  
  
  
int posix_spawnp(pid_t *restrict pid,   
                 const char *restrict file,  
                 const posix_spawn_file_actions_t *file_actions,  
                 const posix_spawnattr_t *restrict attrp,  
                 char *const argv[restrict], char * const envp[restrict]); 
```



file_atction: 包含了新进程将要对文件描述符执行的动作的信息的数据结构。

```c
struct posix_spawn_file_actions_t  
{  
    int __allocated;  
    int __used;  
    struct __spawn_action *actions;  
    int __pad[16];  
}; 
```



attrp 参数: 包含关于新进程的调度策略，进程组，信号，标志等信息。

```c
struct posix_spawnattr_t  
{  
    short int __flags;  //用于指示在新进程中将要修改哪个属性  
    pid_t     __pgrp;   //新进程即将加入的进程组ID  
    sigset_t  __sd;     //新进程被迫默认使用的默认信号处理的信号集合  
    sigset_t  __ss;     //新进程将要使用的信号掩码  
    struct sched_param  __sp;  //将要赋给新进程的调度参数  
    int  __policy;      //新进程将要使用的调度策略  
    int  __pad[16];  
}; 
```

