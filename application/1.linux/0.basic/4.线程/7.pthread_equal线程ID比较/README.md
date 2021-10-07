# pthread_equal函数

在 Linux 中线程 ID 本质就是一个无符号长整形，因此可以直接使用比较操作符比较两个线程的 ID，但是线程库是可以跨平台使用的，在某些平台上 pthread_t 可能不是一个单纯的整形，这中情况下比较两个线程的 ID 必须要使用比较函数

## 头文件

```c
#include <pthread.h>
```



## 函数声明

```c
int pthread_equal(pthread_t t1, pthread_t t2);
```

## 返回值

返回值：如果两个线程 ID 相等返回非 0 值，如果不相等返回 0

## 参数

参数：t1 和 t2 是要比较的线程的线程 ID



https://subingwen.cn/linux/thread/
