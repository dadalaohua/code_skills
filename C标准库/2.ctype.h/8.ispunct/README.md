# C 库函数 - ispunct()

## 描述

C 库函数 **int ispunct(int c)** 检查所传的字符是否是标点符号字符。标点符号字符可以是非字母数字（正如 isalnum 中的一样）的任意图形字符（正如 isgraph 中的一样）。

## 声明

下面是 ispunct() 函数的声明。

```c
int ispunct(int c);
```

## 参数

- **c** --  这是要检查的字符。

## 返回值

如果 c 是一个标点符号字符，则该函数返回非零值（true），否则返回 0（false）。