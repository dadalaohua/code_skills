# C 库宏 - NULL

## 描述

C 库宏 **NULL** 是一个空指针常量的值。它可以被定义为 **((void\*)0), 0**  或 **0L**，这取决于编译器供应商。

## 声明

下面是取决于编译器的 NULL 宏的声明。

```c
#define NULL ((char *)0)

或

#define NULL 0L

或

#define NULL 0
```

## 参数

- **NA**

## 返回值

- **NA**