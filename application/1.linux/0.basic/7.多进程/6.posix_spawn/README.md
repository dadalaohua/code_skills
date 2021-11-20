# posix_spawn

https://blog.csdn.net/yiwuxue/article/details/22189685

https://blog.csdn.net/defrag257/article/details/121322553

https://www.man7.org/linux/man-pages/man3/posix_spawn.3.html

https://www.unix.com/man-page/freebsd/3/posix_spawn/

https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/posix_spawn.2.html

posix_spawn函数可用于替代fork/vfork+exec用于执行程序，同时提供比system函数更多的控制权

引入这个函数的原因主要有以下几点：

- 调用fork绝大多数情况下是用于exec的（少数用于低效的多进程处理和daemon进程脱离父进程控制等用途），调用vfork几乎一定是用于exec的

- fork/vfork+exec手写起来比较复杂，特别是vfork写起来有很多坑，比如共享stack和signal handler有损坏父进程执行上下文的可能性（所以提供一个模板用于调用）

- 有些设备没有MMU，根本实现不了写时复制


当前Linux上是通过“分配stack + 屏蔽所有信号 + clone(CLONE_VM|CLONE_VFORK,stack) + exec”实现的，在FreeBSD上是用vfork + exec实现的，而在macOS上这个函数是一个系统调用

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

posix_spawn函数包括posix_spawn和posix_spawnp两个函数，都包括6个参数

第一个参数pid是一个输出参数，可以传入一个pid_t变量的地址，返回创建的pid，也可以是NULL表示不需要返回pid 

第二个参数path/file，对于posix_spawn，直接执行path路径指向的程序，对于posix_spawnp，如果file不包含/，则认为是一个命令，会搜索PATH环境变量

第三个参数file_actions，指向一个posix_spawn_file_actions_t对象，也可以是NULL表示继承所有没有设置fcntl(fd, SETFD, 1)的文件描述符，这个对象使用posix_spawn_file_actions_init初始化，使用posix_spawn_file_actions_destroy销毁，使用posix_spawn_file_actions_addopen添加打开文件操作，使用posix_spawn_file_actions_addclose添加关闭文件操作，使用posix_spawn_file_actions_adddup2添加复制文件描述符操作


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

第四个参数attrp，指向一个posix_spawnattr_t对象，也可以是NULL表示使用默认值，这个对象使用posix_spawnattr_init初始化，使用posix_spawnattr_destroy销毁，使用posix_spawnattr_setflags、posix_spawnattr_setpgroup、posix_spawnattr_setsigdefault、posix_spawnattr_setsigmask等设置参数，其中posix_spawnattr_setflags可以设置POSIX_SPAWN_RESETIDS、posix_spawnattr_SETPGROUP、posix_spawnattr_SETSIGMASK、posix_spawnattr_SETSIGDEFAULT等


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

第五个参数argv，就是main函数的第二个参数char *argv[]，其中argv[0]是命令名称，必须提供，数组最后一个元素一定要是NULL

第六个参数envp，就是main函数的第三个参数`char *envp[]`或全局变量`extern char **environ;`，数组最后一个元素一定要是NULL，这个参数也可以是NULL，表示没有环境变量

函数成功返回0，失败返回非0的errno错误码
