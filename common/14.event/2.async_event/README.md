# demo

https://mp.weixin.qq.com/s/AGGp3FJ1OeyQ8KtSIlBH9w

一个简单异步事件，根据信号触发对应事件，实现原理很简单：1.绑定信号和对应的回调函数; 2.检测信号队列或者链表，若有信号触发，便取出链表中的节点处理对应的回调函数。本设计中采用是双向链表存储信号，为了方便（偷懒），就不自己造链表的轮子了，这里使用 Linux 内核源码中的双向链表(list.h)。