pthread_create函数

函数简介

pthread_create是UNIX环境创建线程函数
说明：
创建的线程并不具备与主线程（即调用pthread_create()的线 程）同样的执行序列，而其逻辑是在start_routine(arg)函数中运行。
第一个参数thread返回创建的线程ID，
第二个参数我们也设为空指针，这样将生成默认属性的线程。
当创建线程成功时，函数返回0，若不为0则说明创建线程 失败，常见的错误返回代码为EAGAIN和EINVAL。前者表示系统限制创建新的线程，例如线程数目过多了；后者表示第二个参数代表的线程属性值非法。
创建线程成功后，新创建的线程则运行参数三和参数四确定的函数，原来的线程则继续运行下一行代码。

头文件

#include<pthread.h>

函数声明

int pthread_create(pthread_t *restrict tidp,const pthread_attr_t *restrict_attr,void*（*start_rtn)(void*),void *restrict arg);

返回值

若成功则返回0，否则返回出错编号

参数

第一个参数为指向线程标识符的指针。

第二个参数用来设置线程属性。

第三个参数是线程运行函数的起始地址。

最后一个参数是运行函数的参数。

Unix 线程传参数时，注意事项：
线程函数要求的格式void * thread_function(void * argc);

另外

在编译时注意加上-lpthread参数，以调用静态链接库。因为pthread并非Linux系统的默认库

pthread_join函数

函数简介

函数pthread_join用来等待一个线程的结束。

函数原型为：

extern int pthread_join __P (pthread_t __th, void **__thread_return);

参数：

第一个参数为被等待的线程标识符，第二个参数为一个用户定义的指针，它可以用来存储被等待线程的返回值。这个函数是一个线程阻塞的函数，调用它的函数将一直等待到被等待的线程结束为止，当函数返回时，被等待线程的资源被收回。如果执行成功，将返回0，如果失败则返回一个错误号。