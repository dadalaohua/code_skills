# pthread_cancel函数

线程取消的意思就是在某些特定情况下在一个线程中杀死另一个线程。使用这个函数杀死一个线程需要分两步：

1. 在线程 A 中调用线程取消函数 pthread_cancel，指定杀死线程 B，这时候线程 B 是死不了的
2. 在线程 B 中进行一次系统调用（从用户区切换到内核区），否则线程 B 可以一直运行。

## 头文件

```c
#include <pthread.h>
```



## 函数声明

```c
int pthread_cancel(pthread_t thread);
```

## 返回值

返回值：函数调用成功返回 0，调用失败返回非 0 错误号。

## 参数

- thread: 要杀死的线程的线程 ID



## 其他

关于系统调用有两种方式：

- 直接调用 Linux 系统函数

- 调用标准 C 库函数，为了实现某些功能，在 Linux 平台下标准 C 库函数会调用相关的系统函数



https://subingwen.cn/linux/thread/
