# loom -- A lock-less thread pool for C99

https://github.com/silentbicycle/loom

loom creates a task queue and pool of worker threads. Workers run tasks
as they're scheduled, and otherwise sleep until work is available.

loom 创建一个任务队列和工作线程池。 工作者按计划运行任务，否则会休眠直到有工作。

Note: This is still very early in development. I have stress-tested it
on multi-core x86 / x86-64 systems, and it should be safely lock-less
there, but there may be race conditions on hardware platforms with
different memory barriers. `__sync_bool_compare_and_swap` is used
internally, so portability will be limited to platforms / compilers
where that functionality is available.

注意：这仍处于开发的早期阶段。 我已经在多核 x86 / x86-64 系统上对其进行了压力测试，它应该是安全无锁的，但在具有不同内存屏障的硬件平台上可能存在竞争条件。 `__sync_bool_compare_and_swap` 在内部使用，因此可移植性将仅限于具有该功能的平台/编译器。


## Key Features:

- Lock-less: Lock contention overhead is avoided by using [atomic
  compare-and-swap][1] operations internally.
- 无锁：通过在内部使用 [atomic compare-and-swap][1] 操作来避免锁争用开销。
- Allocation-free: Does no allocation after initialization.
- 无分配：在初始化后不做任何分配。
- Backpressure support: The backlog size is exposed, to allow
  proportional push-back against upstream code filling the queue.
- 支持背压。积压的大小是公开的，以允许按比例推回填充队列的上游代码。
- The number of threads and size of the task queue can be tuned for
  specific applications.
- 线程的数量和任务队列的大小可以针对特定的应用进行调整。
- ISC License: You can use it freely, even for commercial purposes.
- ISC许可证：你可以免费使用它，甚至用于商业目的。


[1]: http://en.wikipedia.org/wiki/Compare-and-swap


## Getting Started 入门

First, initialize the thread pool:

首先，初始化线程池：

```c
/* The default configuration. If a C99-style struct literal is used,
 * any omitted fields will be replaced with the defaults below. */
/* 默认配置。如果使用的是C99风格的结构体字面。任何省略的字段将被替换成下面的默认值。*/
loom_config cfg = {
    // Number of threads to start upfront; more will start on demand.
    // 预先启动的线程数； 更多将按需启动。
    .init_threads = 0,

    // Max number of threads too run
    // 要运行的最大线程数
    .max_threads = 8,

    // Max msec. idle threads should sleep, to avoid busywaiting.
    // They will be awakened when new tasks are added.
    // 最大毫秒。 空闲线程应该休眠，以避免忙等待。
    // 当添加新任务时，它们将被唤醒。
    .max_delay = 1000,
    
    // Base-2 log of the task queue size (e.g. 10 => 1024 tasks).
    // A larger size uses more memory, but allows more flexibility in
    // the backlog size before it fills up.
    // 以2为底的log 任务队列大小（例如 10 => 1024 个任务）。
    // 更大的尺寸会使用更多的内存，但允许在积压的大小上有更大的灵活性，在它填满之前。
    .ring_sz2 = 8,
};
struct loom *l = NULL;

if (LOOM_INIT_RES_OK != loom_init(&cfg, &l)) { /* error... */ }
```

Then, schedule tasks in it:

然后，在其中安排任务：

```c
    loom_task task = {
        // Task callback: void task_cb(void *closure_environment) {}
        // 任务回调
        .task_cb = task_cb,

        // Cleanup callback: Called to free *env if task is canceled.
        // 清理回调: 如果任务被取消，则调用释放 *env。
        .cleanup_cb = cleanup_cb,

        // void * to a data to pass to the callbacks.
        // void * 到要传递给回调的数据。
        .env = (void *)closure_environment,
    };

    int i = 0;
    for (i = 0; i < RETRY_COUNT; i++) {
        size_t backpressure = 0;
        /* Retry adding task, pushing back if the queue is
         * currently full and cannot schedule more tasks. */
        //重试添加任务，如果队列当前已满且无法安排更多任务，则推回。
        if (loom_enqueue(l, &task, &backpressure)) { break; }
        do_pushback(backpressure);
    }
    if (i == RETRY_COUNT) {  /* failed to enqueue -- queue full */ }
```

Finally, notify the thread pool that the system is shutting down:

最后，通知线程池，系统要关闭了：

```c
while (!loom_shutdown(l)) {
    /* Do other stuff, giving threads a chance to shut down;
     * loom_shutdown will return true once they've halted. */
    // 做其他事情，让线程有机会关闭；一旦它们停止，loom_shutdown 将返回 true。
}

loom_free(l);
```

To get info about the threadpool as it runs, use:

要获得线程池运行时的信息，请使用：

```c
/* Get the size of the queue. 获取队列的大小。*/
size_t loom_queue_size(struct loom *l);

/* Get statistics from the currently running thread pool. 从当前运行的线程池中获取统计信息。*/
bool loom_get_stats(struct loom *l, loom_info *info);
```


## Implementation 实施

The threadpool is based on a ring buffer of task structs, and uses
atomic compare-and-swap instructions to update offsets for cells that
have been reserved for write, committed, requested for read, and
released. Tasks are copied into the ring queue by value when written,
and read into the worker thread's stack and released immediately to help
keep the ring queue from filling up. Because a ring buffer is used, the
offsets can wrap, reusing memory.

线程池基于任务结构的环形缓冲区，并使用原子比较和交换指令来更新已保留用于写入、提交、请求读取和释放的单元格的偏移量。 任务在写入时按值复制到环形队列中，并读入工作线程的堆栈并立即释放，以帮助防止环形队列被填满。 因为使用了环形缓冲区，所以偏移量可以回绕，重复使用内存。

To avoid a race condition on releasing writes or reads (by just
incrementing the commit/done offsets), producer and consumer threads
mark a write or read as complete by a mark field, and then atomically
compare-and-swap the commit or done offset to advance past any that have
been marked already.

为了避免释放写入或读取的竞争条件（仅通过增加提交/完成偏移量），生产者和消费者线程通过标记字段将写入或读取标记为完成，然后原子地比较和交换提交或完成偏移量，以超越任何已经被标记的。

Worker threads attempt to request tasks from the queue, and if the queue
is empty (the commit offset is the same as the read offset), they poll
on an alert pipe for progressively longer periods of time (up to
`max_delay`) to avoid busywaiting. If a new task is added, the client
thread writes to their pipe, waking them up immediately.

工作线程尝试从队列中请求任务，如果队列为空（提交偏移量与读取偏移量相同），它们会在警报管道上轮询越来越长的时间段（直至 `max_delay`）以避免忙等待。 如果添加了新任务，客户端线程将写入其管道，立即唤醒它们。

When `loom_shutdown` is called, the alert pipes are closed, causing the
worker threads to switch to a mode where they cancel remaining tasks
(using their cleanup callbacks, if given), then exit when the queue is
empty.

当`loom_shutdown`被调用时，警报管道被关闭，导致工作线程切换到取消剩余任务的模式（使用它们的清理回调，如果有的话），然后在队列为空时退出。


## Future Development 未来发展

- Performance tuning 性能调整

- Optional thread shutdown (most likely via `pthread_cancel`) 可选的线程关闭（很可能是通过`pthread_cancel`关闭）。
