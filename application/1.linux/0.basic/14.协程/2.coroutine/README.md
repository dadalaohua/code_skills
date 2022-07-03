https://github.com/cloudwu/coroutine/

It's an asymmetric coroutine library (like lua).

它是一个非对称协程库（像 lua）。

You can use coroutine_open to open a schedule first, and then create coroutine in that schedule. 

你可以先使用 coroutine_open 打开一个计划，然后在该计划中创建协程。

You should call coroutine_resume in the thread that you call coroutine_open, and you can't call it in a coroutine in the same schedule.

你应该在调用 coroutine_open 的线程中调用 coroutine_resume，不能在同一个计划的协程中调用它。

Coroutines in the same schedule share the stack , so you can create many coroutines without worry about memory.

同一个调度中的协程共享堆栈，因此你可以创建多个协程而不用担心内存。

But switching context will copy the stack the coroutine used.

但是切换上下文会复制协程使用的堆栈。

Read source for detail.

详细阅读来源。

Chinese blog : http://blog.codingnow.com/2012/07/c_coroutine.html