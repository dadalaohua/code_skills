# 条件变量函数


严格意义上来说，条件变量的主要作用不是处理线程同步，而是进行线程的阻塞。如果在多线程程序中只使用条件变量无法实现线程的同步，必须要配合互斥锁来使用。虽然条件变量和互斥锁都能阻塞线程，但是二者的效果是不一样的，二者的区别如下：

假设有 A-Z 26 个线程，这 26 个线程共同访问同一把互斥锁，如果线程 A 加锁成功，那么其余 B-Z 线程访问互斥锁都阻塞，所有的线程只能顺序访问临界区
条件变量只有在满足指定条件下才会阻塞线程，如果条件不满足，多个线程可以同时进入临界区，同时读写临界资源，这种情况下还是会出现共享资源中数据的混乱。
一般情况下条件变量用于处理生产者和消费者模型，并且和互斥锁配合使用。条件变量类型对应的类型为 `pthread_cond_t`，这样就可以定义一个条件变量类型的变量了：

```C
pthread_cond_t cond;
```

被条件变量阻塞的线程的线程信息会被记录到这个变量中，以便在解除阻塞的时候使用。

条件变量操作函数函数原型如下：

```C
#include <pthread.h>
pthread_cond_t cond;
// 初始化
int pthread_cond_init(pthread_cond_t *restrict cond,
      const pthread_condattr_t *restrict attr);
// 销毁释放资源        
int pthread_cond_destroy(pthread_cond_t *cond);
```

- 参数:

  - cond: 条件变量的地址

  - attr: 条件变量属性，一般使用默认属性，指定为 NULL

```C
// 线程阻塞函数, 哪个线程调用这个函数, 哪个线程就会被阻塞
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
```

通过函数原型可以看出，该函数在阻塞线程的时候，需要一个互斥锁参数，这个互斥锁主要功能是进行线程同步，让线程顺序进入临界区，避免出现数共享资源的数据混乱。该函数会对这个互斥锁做以下几件事情：

1. 在阻塞线程时候，如果线程已经对互斥锁 `mutex` 上锁，那么会将这把锁打开，这样做是为了避免死锁
2. 当线程解除阻塞的时候，函数内部会帮助这个线程再次将这个 `mutex` 互斥锁锁上，继续向下访问临界区

```C
// 表示的时间是从1971.1.1到某个时间点的时间, 总长度使用秒/纳秒表示
struct timespec {
	time_t tv_sec;      /* Seconds */
	long   tv_nsec;     /* Nanoseconds [0 .. 999999999] */
};
// 将线程阻塞一定的时间长度, 时间到达之后, 线程就解除阻塞了
int pthread_cond_timedwait(pthread_cond_t *restrict cond,
           pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
```

这个函数的前两个参数和 `pthread_cond_wait` 函数是一样的，第三个参数表示线程阻塞的时长，但是需要额外注意一点：`struct timespec` 这个结构体中记录的时间是`从1971.1.1到某个时间点的时间，总长度使用秒/纳秒表示`。因此赋值方式相对要麻烦一点：

```C
time_t mytim = time(NULL);	// 1970.1.1 0:0:0 到当前的总秒数
struct timespec tmsp;
tmsp.tv_nsec = 0;
tmsp.tv_sec = time(NULL) + 100;	// 线程阻塞100s
```

```C
// 唤醒阻塞在条件变量上的线程, 至少有一个被解除阻塞
int pthread_cond_signal(pthread_cond_t *cond);
// 唤醒阻塞在条件变量上的线程, 被阻塞的线程全部解除阻塞
int pthread_cond_broadcast(pthread_cond_t *cond);
```

调用上面两个函数中的任意一个，都可以换线被 `pthread_cond_wait` 或者 `pthread_cond_timedwait` 阻塞的线程，区别就在于 `pthread_cond_signal` 是唤醒至少一个被阻塞的线程（总个数不定），`pthread_cond_broadcast` 是唤醒所有被阻塞的线程。




https://subingwen.cn/linux/thread-sync/
