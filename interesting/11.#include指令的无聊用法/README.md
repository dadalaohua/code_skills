# 一个#include指令的无聊用法

## 来看一个#include指令的无聊用法。

```c
#include<stdio.h>
int main(void)
{
    printf
    #include"test.txt"
    return 0;
}
```

其中test.txt的内容如下：

```
("Hello World\n");
```

## 编译运行结果

```
Hello World
```

## 小结

看起来没啥用的内容。
不过在你需要的文本内容比较长，不想直接复制在源代码里面的时候，其实就可以考虑这种方式了。

## 原理

其实原理也很简单，就是预编译的时候，将#include文件的内容嵌入到所在位置罢了，等同于：

```c
#include<stdio.h>
int main(void)
{
    printf
    ("Hello World\n");
    return 0;
}
```

