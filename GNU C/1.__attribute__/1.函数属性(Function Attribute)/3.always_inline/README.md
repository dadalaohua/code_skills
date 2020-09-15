# `__attribute__((always_inline))` 函数属性
This function attribute indicates that a function must be inlined.

The compiler attempts to inline the function, regardless of the characteristics of the function.

In some circumstances the compiler may choose to ignore the `__attribute__((always_inline))` attribute and not inline a function. For example:

- A recursive function is never inlined into itself.
- Functions making use of `alloca()` are never inlined.

1、这个函数属性表示一个函数必须是内联的

编译器尝试内联函数，而不考虑函数的特征，在某些情况下，编译器可能会选择忽略`attribute__((always_inline))`属性，而不内联函数。例如:

  递归函数永远不会内联到自身中。

  使用`alloca()`的函数从不内联。

2、这个函数属性是ARM编译器支持的GNU编译器扩展。它的关键字等效于内联的 `__forceinline`。

