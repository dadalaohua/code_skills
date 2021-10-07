# pthread_self函数

每一个线程都有一个唯一的线程 ID，ID 类型为 pthread_t，这个 ID 是一个无符号长整形数，如果想要得到当前线程的线程 ID，可以调用函数pthread_self

## 头文件

```c
#include <pthread.h>
```



## 函数声明

```c
pthread_t pthread_self(void);
```

## 返回值

返回值：返回当前线程的线程ID

## 参数

无



https://subingwen.cn/linux/thread/
