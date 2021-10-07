# 自旋锁

自旋锁是SMP架构中的一种low-level的同步机制。
当线程A想要获取一把自旋锁而该锁又被其它线程锁持有时，线程A会在一个循环中自旋以检测锁是不是已经可用了。对于自选锁需要注意：

- 由于自旋时不释放CPU，因而持有自旋锁的线程应该尽快释放自旋锁，否则等待该自旋锁的线程会一直在那里自旋，这就会浪费CPU时间。
- 持有自旋锁的线程在sleep之前应该释放自旋锁以便其它线程可以获得自旋锁。

使用任何锁需要消耗系统资源（内存资源和CPU时间），这种资源消耗可以分为两类：

- 建立锁所需要的资源
- 线程被阻塞时锁所需要的资源

spin lock 锁相关的API：

```c 
1 int pthread_spin_destroy(pthread_spinlock_t *);
2 int pthread_spin_init(pthread_spinlock_t *, int);
3 int pthread_spin_lock(pthread_spinlock_t *);
4 int pthread_spin_trylock(pthread_spinlock_t *);
5 int pthread_spin_unlock(pthread_spinlock_t *);
```

### **1）初始化自旋锁**

　　pthread_spin_init用来申请使用自旋锁所需要的资源并且将它初始化为非锁定状态。pshared的取值及其含义：

- PTHREAD_PROCESS_SHARED：该自旋锁可以在多个进程中的线程之间共享。
- PTHREAD_PROCESS_PRIVATE: 仅初始化本自旋锁的线程所在的进程内的线程才能够使用该自旋锁。

### 2）获得一个自旋锁

　　pthread_spin_lock用来获取（锁定）指定的自旋锁. 如果该自旋锁当前没有被其它线程所持有，**则调用该函数的线程获得该自旋锁.否则该函数在获得自旋锁之前不会返回**。如果调用该函数的线程在调用该函数时已经持有了该自旋锁，则结果是不确定的。

### 3）尝试获取一个自旋锁

　　pthread_spin_trylock会尝试获取指定的自旋锁，如果无法获取则理解返回失败。

### 4）释放（解锁）一个自旋锁

　　pthread_spin_unlock用于释放指定的自旋锁。

### 5）销毁一个自旋锁

　pthread_spin_destroy用来销毁指定的自旋锁并释放所有相关联的资源（所谓的所有指的是由pthread_spin_init自动申请的资源）在调用该函数之后如果没有调用pthread_spin_init重新初始化自旋锁，则任何尝试使用该锁的调用的结果都是未定义的。如果调用该

函数时自旋锁正在被使用或者自旋锁未被初始化则结果是未定义的。

**Pthreads提供的Mutex锁操作相关的API主要有：**

```c
1 pthread_mutex_lock (pthread_mutex_t *mutex);
2 pthread_mutex_trylock (pthread_mutex_t *mutex);
3 pthread_mutex_unlock (pthread_mutex_t *mutex);
```

**Pthreads提供的与Spin Lock锁操作相关的API主要有：**

```c
pthread_spin_lock (pthread_spinlock_t *lock);
pthread_spin_trylock (pthread_spinlock_t *lock);
pthread_spin_unlock (pthread_spinlock_t *lock);
```

 　从实现原理上来讲，Mutex属于sleep-waiting类型的锁。例如在一个双核的机器上有两个线程(线程A和线程B)，它们分别运行在Core0和Core1上。假设线程A想要通过pthread_mutex_lock操作去得到一个临界区的锁，而此时这个锁正被线程B所持有，那么线

程A就会被阻塞(blocking)，Core0 会在此时进行上下文切换(Context Switch)将线程A置于等待队列中，**此时Core0就可以运行其他的任务(例如另一个线程C)而不必进行忙等待。而Spin lock则不然，它属于busy-waiting类型的锁，如果线程A是使用**

**pthread_spin_lock操作去请求锁，那么线程A就会一直在 Core0上进行忙等待并不停的进行锁请求，直到得到这个锁为止**

 　如果大家去查阅Linux glibc中对pthreads API的实现NPTL(Native POSIX Thread Library) 的源码的话(使用”getconf GNU_LIBPTHREAD_VERSION”命令可以得到我们系统中NPTL的版本号)，就会发现pthread_mutex_lock()操作如果没有锁成功的话就会

调用system_wait()的系统调用并将当前线程加入该mutex的等待队列里。而spin lock则可以理解为在一个while(1)循环中用内嵌的汇编代码实现的锁操作(印象中看过一篇论文介绍说在linux内核中spin lock操作只需要两条CPU指令，解锁操作只用一条指令就可以完

成)。有兴趣的朋友可以参考另一个名为sanos的微内核中pthreds API的实现：mutex.c spinlock.c，尽管与NPTL中的代码实现不尽相同，但是因为它的实现非常简单易懂，对我们理解spin lock和mutex的特性还是很有帮助的。

​    对于自旋锁来说，它只需要消耗很少的资源来建立锁；随后当线程被阻塞时，它就会一直重复检查看锁是否可用了，也就是说当自旋锁处于等待状态时它会一直消耗CPU时间。

​    对于互斥锁来说，与自旋锁相比它需要消耗大量的系统资源来建立锁；随后当线程被阻塞时，线程的调度状态被修改，并且线程被加入等待线程队列；最后当锁可用时，在获取锁之前，线程会被从等待队列取出并更改其调度状态；但是在线程被阻塞期间，它不消耗

CPU资源。

​    因此自旋锁和互斥锁适用于不同的场景。自旋锁适用于那些仅需要阻塞很短时间的场景，而互斥锁适用于那些可能会阻塞很长时间的场景。



https://www.cnblogs.com/chris-cp/p/5413445.html
