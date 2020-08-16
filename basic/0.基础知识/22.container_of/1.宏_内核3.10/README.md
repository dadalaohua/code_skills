container_of

内核中可以查看
include/linux/kernel.h 

kernel 3.10


container_of原理:
已知结构体type的成员member的地址ptr，求解结构体type的起始地址。
type的起始地址 = ptr - size      (这里需要都转换为char *，因为它为单位字节)。

container of函数原型：
#define container_of(ptr, type, member) ({              \         
const typeof( ((type *)0)->member ) *__mptr = (ptr);    \         
(type *)( (char *)__mptr - offsetof(type,member) );})

其次为 offserof 函数原型：
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

container_of（ptr, type,member）函数的实现包括两部分：
           1.  判断ptr 与 member 是否为同一类型
           2.  计算size大小，结构体的起始地址 = (type *)((char *)ptr - size)   (注：强转为该结构体指针)
    现在我们知道container_of()的作用就是通过一个结构变量中一个成员的地址找到这个结构体变量的首地址。

    container_of(ptr,type,member),这里面有ptr,type,member分别代表指针、类型、成员。
