# `__attribute__((section("malloc")))` 函数属性
This function attribute indicates that the function can be treated like `malloc` and the compiler can perform the associated optimizations.

## Example

```c
void * foo(int b) __attribute__((malloc))
```



此函数属性表示可以将函数视为“malloc”，编译器可以执行相关的优化。 



GNU

The malloc attribute is used to tell the compiler that a function may be treated as if any non-NULL pointer it returns cannot alias any other pointer valid when the function returns and that the memory has undefined content. This often improves optimization. Standard functions with this property include malloc and calloc. realloc-like functions do not have this property as the memory pointed to does not have undefined content.

malloc属性用于告诉编译器，一个函数可以被当作它返回的任何非空指针的别名，而当该函数返回时，它所返回的任何非空指针不能与任何其他有效指针别名，并且内存具有未定义的内容。这通常可以改善优化。具有此属性的标准函数包括malloc和calloc。类似realloc的函数没有此属性，因为指向的内存没有未定义的内容。 

`__attribute__((malloc))` function attribute
`__attribute__((malloc))` 是由如此标记的函数返回的块不得包含任何指向其他对象的指针.目的是帮助编译器估计哪些指针可能指向同一个对象：该属性告诉GCC它不必担心你的函数返回的对象可能包含指向它正在跟踪的其他东西的指针.