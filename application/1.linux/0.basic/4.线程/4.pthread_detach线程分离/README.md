# pthread_detach函数

在某些情况下，程序中的主线程有属于自己的业务处理流程，如果让主线程负责子线程的资源回收，调用 pthread_join() 只要子线程不退出主线程就会一直被阻塞，主要线程的任务也就不能被执行了。

在线程库函数中为我们提供了线程分离函数 pthread_detach()，调用这个函数之后指定的子线程就可以和主线程分离，当子线程退出的时候，其占用的内核资源就被系统的其他进程接管并回收了。线程分离之后在主线程中使用 pthread_join() 就回收不到子线程资源了。

## 头文件

```c
#include <pthread.h>
```



## 函数声明

```c
int pthread_detach(pthread_t thread);
```

## 返回值

pthread_detach() 在调用成功完成之后返回零。其他任何返回值都表示出现了错误。如果检测到以下任一情况，pthread_detach()将失败并返回相应的值。

EINVAL：tid是分离线程

ESRCH：tid不是当前进程中有效的为分离线程

## 参数

- thread: 子线程的线程ID



https://subingwen.cn/linux/thread/
