# 优先级队列

### 1. 优先级队列的特点

优先级队列也是一种基于队列的数据结构，但是它**「不遵循FIFO」**，而是按照每个元素的优先级进行出队：**「最高优先级的先出队」**。

### 2. 优先级队列的实现

TencentOS-tiny中环形队列的实现在`tos_prio_queue.h`和`tos_prio_queue.c`中。

优先级队列在数据入队的时候，会按照入队元素的优先级进行一次排序，**「将优先级值最小（优先级最高的元素）放在队头」**，出队的时候只需要取第一个元素即可。

正是因为这种特性，优先级队列的底层存储结构不能使用数组（排序太麻烦），而是使用了二项堆的数据结构。

> ❝
>
> 二项堆是一种二叉树集合的数据结构，在本文中不再深入讲解，有兴趣的读者可以自己搜索阅读。
>
> ❞

下面只给出优先级队列的API，**「理解其规则，会用即可」**。

- 创建优先级队列

```
__API__ k_err_t tos_prio_q_create(k_prio_q_t *prio_q, void *mgr_array, void *pool, size_t item_cnt, size_t item_size);
```

|   参数    |            描述            |
| :-------: | :------------------------: |
|  prio_q   |    优先级队列控制块指针    |
| mgr_array | 提供一块缓冲区用于内部管理 |
|   pool    |        队列的缓冲区        |
| item_cnt  |    队列可容纳的元素数量    |
| item_size |  每个元素的大小，单位字节  |

其中用于内部管理的缓存区大小可以使用宏定义来计算，比如有5个元素的管理缓冲区大小：

```
uint8_t mgr_pool[TOS_PRIO_Q_MGR_ARRAY_SIZE(5)];
```

- 元素入队

```
__API__ k_err_t tos_prio_q_enqueue(k_prio_q_t *prio_q, void *item, size_t item_size, k_prio_t prio);
```

其中优先级的值遵循：数值越小，优先级越高。

- 元素出队

```
__API__ k_err_t tos_prio_q_dequeue(k_prio_q_t *prio_q, void *item, size_t *item_size, k_prio_t *prio);
```

其中prio需要传入一个地址，用于记录出队元素的优先级。



https://mp.weixin.qq.com/s/RpmJ7DxsSwQaVhGHJTHg9A

https://gitee.com/Tencent/TencentOS-tiny

