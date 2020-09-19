# `__attribute__((always_inline))` 函数属性
# GNU

```
always_inline
```

Generally, functions are not inlined unless optimization is specified.  For functions declared inline, this attribute inlines the function even if no optimization level was specified.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This function attribute indicates that a function must be inlined.

The compiler attempts to inline the function, regardless of the characteristics of the function.

In some circumstances the compiler may choose to ignore the `__attribute__((always_inline))` attribute and not inline a function. For example:

- A recursive function is never inlined into itself.
- Functions making use of `alloca()` are never inlined.

### Note

This function attribute is a GNU compiler extension that the ARM compiler supports. It has the keyword equivalent `__forceinline`.      

## Example

```c
static int max(int x, int y) __attribute__((always_inline));
static int max(int x, int y)
{
    return x > y ? x : y; // always inline if possible
}
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124974010.htm

1、这个函数属性表示一个函数必须是内联的

编译器尝试内联函数，而不考虑函数的特征，在某些情况下，编译器可能会选择忽略`attribute__((always_inline))`属性，而不内联函数。例如:

  递归函数永远不会内联到自身中。

  使用`alloca()`的函数从不内联。

2、这个函数属性是ARM编译器支持的GNU编译器扩展。它的关键字等效于内联的 `__forceinline`。

