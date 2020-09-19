# `__attribute__((section("used")))` 函数属性
# GNU

This attribute, attached to a function, means that code must be emitted for the function even if it appears that the function is not referenced.  This is useful, for example, when the function is referenced only in inline assembly.  

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This function attribute informs the compiler that a static     function is to be retained in the object file, even if it is unreferenced.

Functions marked with `__attribute__((used))`are tagged in the object file to avoid removal by linker unused section        removal.

### Note

Static variables can also be marked as used, by using `__attribute__((used))`. 

## Example

```c
static int lose_this(int);
static int keep_this(int) __attribute__((used));     // retained in object file
static int keep_this_too(int) __attribute__((used)); // retained in object file
```

1、这个函数属性通知编译器在目标文件中保留一个静态函数，即使它没有被引用。
2、标记为`__attribute__((used))`的函数被标记在目标文件中，以避免链接器删除未使用的节。
3、静态变量也可以标记为used，方法是使用` __attribute__((used))`。
4、例程
```c
static int lose_this(int);
static int keep_this(int) __attribute__((used));     // retained in object file
static int keep_this_too(int) __attribute__((used)); // retained in object file
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124978363.htm

`__attribute_((used))`function attribute
`__attribute_((used))` 其作用是告诉编译器避免被链接器因为未用过而被优化掉。

used： This attribute, attached to a function, means that code must be emitted for the
       function even if it appears that the function is not referenced. This is useful,
       for example, when the function is referenced only in inline assembly.
向编译器说明这段代码有用，即使在没有用到的情况下编译器也不会警告

