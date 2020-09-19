# `__attribute__((sentinel))` 函数属性
# GNU

This function attribute ensures that a parameter in a function call is an explicit `NULL`.  The attribute is only valid on variadic functions.  By default, the sentinel is located at position zero, the last parameter of the function call.  If an optional integer position argument P is supplied to the attribute, the sentinel must be located at position P counting backwards from the end of the argument list.      

```C
          __attribute__ ((sentinel))
          is equivalent to
          __attribute__ ((sentinel(0)))
     
```

The attribute is automatically set with a position of 0 for the built-in functions `execl` and `execlp`.  The built-in function `execle` has the attribute set with a position of 1.      

A valid `NULL` in this context is defined as zero with any pointer type.  If your system defines the `NULL` macro with an integer type then you need to add an explicit cast.  GCC replaces `stddef.h` with a copy that redefines NULL appropriately.      

The warnings for missing or incorrect sentinels are enabled with -Wformat.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM
`__attribute__((sentinel))` function attribute

This function attribute generates a warning if the specified parameter in a function call is not NULL.

Syntax
`__attribute__ ((sentinel(p)))`
Where:
p
is an optional integer position argument. If this argument is supplied, the compiler checks the parameter at position p counting backwards from the end of the argument list.
By default, the compiler checks the parameter at position zero, the last parameter of the function call. That is, `__attribute__ ((sentinel))` is equivalent to `__attribute__ ((sentinel(0)))`

https://www.keil.com/support/man/docs/armcc/armcc_chr1370356896662.htm

如果函数调用中指定的参数不为NULL，则此函数属性将生成警告。
语法
`__attribute__ ((sentinel(p)))`
Where：
`p`
是可选的整数位置参数。如果提供了此参数，编译器将检查位置p处的参数，从参数列表的末尾向反方向进行计数(从末尾向前计数)。
默认情况下，编译器在函数调用的最后一个参数0处检查参数。
也就是说，`__attribute__ ((sentinel))）`相当于`__attribute__ ((sentinel(0)))`



`__attribute__ ((sentinel(n)))` 限制了**可变参数**的参数数量至少为 `n+1`

`__attribute__ ((sentinel(n)))` 表示可变参数中，从后朝前数，第n个参数为 `NULL`。