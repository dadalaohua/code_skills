# `__attribute__((pure))` 函数属性
Many functions have no effects except to return a value, and their return value depends     only on the parameters and global variables. Functions of this kind can be subject to data flow     analysis and might be eliminated.

### Note

This function attribute is a GNU compiler extension that the ARM compiler supports.

Although related, this function attribute is not          equivalent to the `__pure` keyword. The function attribute equivalent to            `__pure` is `__attribute__((const))`.

## Example

```
int Function_Attributes_pure_0(int b) __attribute__((pure));
int Function_Attributes_pure_0(int b)
{
    return b++;
}
int foo(int b)
{
    int aLocal=0;
    aLocal += Function_Attributes_pure_0(b);
    aLocal += Function_Attributes_pure_0(b);
    return 0;
}
```

The call to `Function_Attributes_pure_0` in this example might be eliminated because its result is not used.

1、许多函数除了返回一个值外没有其他效果，它们的返回值只依赖于参数和全局变量。这类函数可以进行数据流分析，可能会被删除。
2、这个函数属性是ARM编译器支持的GNU编译器扩展。
3、虽然相关，但是这个函数属性并不等同于 __pure 关键字。与 __pure 等价的函数属性是`__attribute__((const))`。

4、例程

```c
int Function_Attributes_pure_0(int b) __attribute__((pure));

int Function_Attributes_pure_0(int b)
{
    return b++;
}
int foo(int b)
{
    int aLocal=0;
    aLocal += Function_Attributes_pure_0(b);
    aLocal += Function_Attributes_pure_0(b);
    return 0;
}
```
本例中对 `Function_Attributes_pure_0` 的调用可能被取消，因为它的结果没有被使用。