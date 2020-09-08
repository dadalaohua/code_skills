# C 库函数 - isspace()

## 描述

C 库函数 **int isspace(int c)** 检查所传的字符是否是空白字符。

标准的空白字符包括：

```
' '     (0x20)    space (SPC) 空格符
'\t'    (0x09)    horizontal tab (TAB) 水平制表符    
'\n'    (0x0a)    newline (LF) 换行符
'\v'    (0x0b)    vertical tab (VT) 垂直制表符
'\f'    (0x0c)    feed (FF) 换页符
'\r'    (0x0d)    carriage return (CR) 回车符
```

## 声明

下面是 isspace() 函数的声明。

```c
int isspace(int c);
```

## 参数

- **c** --  这是要检查的字符。

## 返回值

如果 c 是一个空白字符，则该函数返回非零值（true），否则返回 0（false）。