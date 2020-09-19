# `__attribute__((section("unused")))` 函数属性
# GNU

This attribute, attached to a function, means that the function is meant to be possibly unused.  GCC will not produce a warning for this function. 

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes


# ARM
The `unused` function attribute prevents the compiler from generating     warnings if the function is not referenced. This does not change the behavior of the unused     function removal process.

### Note

This function attribute is a GNU compiler extension that the ARM compiler supports.      

## Example

```c
static int Function_Attributes_unused_0(int b) __attribute__
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124978129.htm

1、如果未引用函数，unused 函数属性将阻止编译器生成警告。这不会改变未使用的函数删除过程的行为。

2、这个函数属性是ARM编译器支持的GNU编译器扩展。

3、例程

```c
static int Function_Attributes_unused_0(int b) __attribute__((unused))
```



`__attribute__((unused))`function attribute
`__attribute__((unused))` 其作用是即使没有使用这个函数，编译器也不警告。


unused：This attribute, attached to a function, means that the function is meant to be possibly unused. GCC will not produce a warning for this function.

表示该函数或变量可能不使用，这个属性可以避免编译器产生警告信息。