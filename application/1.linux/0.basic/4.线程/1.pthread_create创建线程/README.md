# pthread_create函数

## 函数简介

pthread_create是UNIX环境创建线程函数
说明：
创建的线程并不具备与主线程（即调用pthread_create()的线程）同样的执行序列，而其逻辑是在start_routine(arg)函数中运行。
第一个参数thread返回创建的线程ID，
第二个参数我们也设为空指针，这样将生成默认属性的线程。
当创建线程成功时，函数返回0，若不为0则说明创建线程 失败，常见的错误返回代码为EAGAIN和EINVAL。前者表示系统限制创建新的线程，例如线程数目过多了；后者表示第二个参数代表的线程属性值非法。
创建线程成功后，新创建的线程则运行参数三和参数四确定的函数，原来的线程则继续运行下一行代码。

## 头文件

```c
#include <pthread.h>
```



## 函数声明

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
```

## 返回值

返回值：线程创建成功返回 0，创建失败返回对应的错误号

## 参数

- thread: 传出参数，是无符号长整形数，线程创建成功，会将线程 ID 写入到这个指针指向的内存中

- attr: 线程的属性，一般情况下使用默认属性即可，写 NULL

- start_routine: 函数指针，创建出的子线程的处理动作，也就是该函数在子线程中执行。

- arg: 作为实参传递到 start_routine 指针指向的函数内部




Unix 线程传参数时，注意事项：
线程函数要求的格式

```c
void * thread_function(void * argc);
```



另外

在编译时注意加上-lpthread参数，以调用静态链接库。因为pthread并非Linux系统的默认库

错误原因是因为编译器链接不到线程库文件（动态库），需要在编译的时候通过参数指定出来，动态库名为 libpthread.so 需要使用的参数为 -l，根据规则掐头去尾最终形态应该写成：-lpthread（参数和参数值中间可以有空格）。


