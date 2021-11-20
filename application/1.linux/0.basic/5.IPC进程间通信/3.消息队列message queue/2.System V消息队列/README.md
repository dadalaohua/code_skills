# Linux进程间通信

https://www.cnblogs.com/52php/p/5862114.html

下面来说说如何用不用消息队列来进行进程间的通信，消息队列与命名管道有很多相似之处。

### 一、什么是消息队列

消息队列提供了一种从一个进程向另一个进程发送一个数据块的方法。  每个数据块都被认为含有一个类型，接收进程可以独立地接收含有不同类型的数据结构。我们可以通过发送消息来避免命名管道的同步和阻塞问题。但是消息队列与命名管道一样，每个数据块都有一个最大长度的限制。

Linux用宏MSGMAX和MSGMNB来限制一条消息的最大长度和一个队列的最大长度。

### 二、在Linux中使用消息队列

Linux提供了一系列消息队列的函数接口来让我们方便地使用它来实现进程间的通信。它的用法与其他两个System V PIC机制，即信号量和共享内存相似。

**1、msgget()函数**

该函数用来创建和访问一个消息队列。它的原型为：

> int msgget(key_t, key, int msgflg);

与其他的IPC机制一样，程序必须提供一个键来命名某个特定的消息队列。msgflg是一个权限标志，表示消息队列的访问权限，它与文件的访问权限一样。msgflg可以与IPC_CREAT做或操作，表示当key所命名的消息队列不存在时创建一个消息队列，如果key所命名的消息队列存在时，IPC_CREAT标志会被忽略，而只返回一个标识符。

它返回一个以key命名的消息队列的标识符（非零整数），失败时返回-1.

**2、msgsnd()函数**

该函数用来把消息添加到消息队列中。它的原型为：

> int msgsend(int msgid, const void *msg_ptr, size_t msg_sz, int msgflg);

msgid是由msgget函数返回的消息队列标识符。

msg_ptr是一个指向准备发送消息的指针，但是消息的数据结构却有一定的要求，指针msg_ptr所指向的消息结构一定要是以一个长整型成员变量开始的结构体，接收函数将用这个成员来确定消息的类型。所以消息结构要定义成这样： 

```c
struct my_message {
    long int message_type;
    /* The data you wish to transfer */
};
```

msg_sz 是msg_ptr指向的消息的长度，注意是消息的长度，而不是整个结构体的长度，也就是说msg_sz是不包括长整型消息类型成员变量的长度。

msgflg 用于控制当前消息队列满或队列消息到达系统范围的限制时将要发生的事情。

如果调用成功，消息数据的一分副本将被放到消息队列中，并返回0，失败时返回-1.

**3、msgrcv()函数**

该函数用来从一个消息队列获取消息，它的原型为

> int msgrcv(int msgid, void *msg_ptr, size_t msg_st, long int msgtype, int msgflg);

msgid, msg_ptr, msg_st 的作用也函数msgsnd()函数的一样。

msgtype 可以实现一种简单的接收优先级。如果msgtype为0，就获取队列中的第一个消息。如果它的值大于零，将获取具有相同消息类型的第一个信息。如果它小于零，就获取类型等于或小于msgtype的绝对值的第一个消息。

msgflg 用于控制当队列中没有相应类型的消息可以接收时将发生的事情。

调用成功时，该函数返回放到接收缓存区中的字节数，消息被复制到由msg_ptr指向的用户分配的缓存区中，然后删除消息队列中的对应消息。失败时返回-1。

**4、msgctl()函数**

该函数用来控制消息队列，它与共享内存的shmctl函数相似，它的原型为：

> int msgctl(int msgid, int command, struct msgid_ds *buf);

command是将要采取的动作，它可以取3个值，

- IPC_STAT：把msgid_ds结构中的数据设置为消息队列的当前关联值，即用消息队列的当前关联值覆盖msgid_ds的值。
- IPC_SET：如果进程有足够的权限，就把消息列队的当前关联值设置为msgid_ds结构中给出的值
- IPC_RMID：删除消息队列

buf是指向msgid_ds结构的指针，它指向消息队列模式和访问权限的结构。msgid_ds结构至少包括以下成员： 

```
struct msgid_ds
{
    uid_t shm_perm.uid;
    uid_t shm_perm.gid;
    mode_t shm_perm.mode;
};
```

成功时返回0，失败时返回-1.

