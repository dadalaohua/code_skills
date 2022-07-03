# Protothreads

http://dunkels.com/adam/pt/

Protothreads are extremely lightweight stackless threads designed for severely memory constrained systems, such as small embedded systems or wireless sensor network nodes. Protothreads provide linear code execution for event-driven systems implemented in C. Protothreads can be used with or without an underlying operating system to provide blocking event-handlers. Protothreads provide sequential flow of control without complex state machines or full multi-threading.

Protothreads 是极其轻量级的无堆栈线程，专为内存严重受限的系统设计，例如小型嵌入式系统或无线传感器网络节点。 Protothreads 为用 C 实现的事件驱动系统提供线性代码执行。Protothreads 可以在有或没有底层操作系统的情况下使用，以提供阻塞事件处理程序。 Protothreads 提供顺序控制流，无需复杂的状态机或完整的多线程。

```c
#include "pt.h"
 
struct pt pt;
struct timer timer;
 
PT_THREAD(example(struct pt *pt))
{
  PT_BEGIN(pt);
 
  while(1) {
    if(initiate_io()) {
      timer_start(&timer);
      PT_WAIT_UNTIL(pt,
         io_completed() ||
         timer_expired(&timer));
      read_data();
    }
  }
  PT_END(pt);
}
```

Example protothreads code.

示例 protothreads 代码。

While protothreads originally were created for memory-constrained embedded systems, it has found many uses as a general purpose library too. Examples include multimedia streaming server software, grid computing research software, and MPEG decoding software for Internet TVs.

虽然 protothreads 最初是为内存受限的嵌入式系统创建的，但它也发现了许多用作通用库的用途。 示例包括多媒体流服务器软件、网格计算研究软件和用于互联网电视的 MPEG 解码软件。

**[Read more...](http://dunkels.com/adam/pt/about.html)**

Main features:

主要特点：

- Very small RAM overhead - only two bytes per protothread and no extra stacks 非常小的 RAM 开销 - 每个 protothread 只有两个字节，没有额外的堆栈
- Highly portable - the protothreads library is 100% pure C and no architecture specific assembly code 高度可移植 - protothreads 库是 100% 纯 C 语言，没有特定于架构的汇编代码
- Can be used with or without an OS 可以在有或没有操作系统的情况下使用
- Provides blocking wait without full multi-threading or stack-switching 提供阻塞等待，无需完整的多线程或堆栈切换
- Freely available under a BSD-like open source license 在类似 BSD 的开源许可证下免费提供

Example applications:

示例应用：

- Memory constrained systems 内存受限系统
- Event-driven protocol stacks 事件驱动的协议栈
- Small embedded systems 小型嵌入式系统
- Sensor network nodes 传感器网络节点
- Portable C applications 便携式 C 应用程序

For example usages, see the [Examples page](http://dunkels.com/adam/pt/examples.html).

有关示例用法，请参阅 示例页面

The protothreads library is released under an open source [BSD-style license](http://dunkels.com/adam/pt/license.html) that freely allows for both non-commercial and commercial usage. The only requirement is that credit is given. [Download the full source code here](http://dunkels.com/adam/pt/download.html).

protothreads 库是在开源  BSD-style license 下发布的，它可以自由地用于非商业和商业用途。唯一的要求是给予信用。 在此处下载完整的源代码

Protothreads were invented by [Adam Dunkels](http://dunkels.com/adam) with support from Oliver Schmidt <ol.sc@web.de>.

在 Oliver Schmidt <ol.sc@web.de> 的支持下，发明了 protothread。



# Protothreads API

This page contains a condensed version of the protothreads API. For the full version, please see the [documentation](http://dunkels.com/adam/pt/documentation.html).

此页面包含 protothreads API 的精简版本。 如需完整版，请参阅文档。

**void PT_INIT(struct pt \*pt);**
Initialize a protothread. 初始化一个 protothread 。

**void PT_BEGIN(struct pt \*pt);**
Declare the start of a protothread inside the C function implementing the protothread. 在实现 protothread 的 C 函数中声明一个 protothread 的开始。

**void PT_WAIT_UNTIL(struct pt \*pt, condition);**
Block and wait until condition is true. 阻塞并等待，直到条件为真。

**void PT_WAIT_WHILE(struct pt \*pt, condition);**
Block and wait while condition is true. 在条件为真时进行阻塞和等待。

**void PT_WAIT_THREAD(struct pt \*pt, thread);**
Block and wait until a child protothread completes. 阻塞并等待，直到一个子线程完成。

**void PT_SPAWN(struct pt \*pt, struct pt \*child, thread);**
Spawn a child protothread and wait until it exits. 生成一个子线程并等待它退出。

**void PT_RESTART(struct pt \*pt);**
Restart the protothread. 重新启动 protothread。

**void PT_EXIT(struct pt \*pt);**
Exit the protothread. 退出 protothread。

**void PT_END(struct pt \*pt);**
Declare the end of a protothread. 声明一个 protothread 的结束。

**int PT_SCHEDULE(protothread);**
Schedule a protothread. 调度一个protothread。

**void PT_YIELD(struct pt \*pt);**
Yield from the current protothread. 从当前的protothread中退出。