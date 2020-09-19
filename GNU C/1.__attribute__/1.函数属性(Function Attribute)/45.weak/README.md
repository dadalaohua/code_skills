# `__attribute__((section("weak")))` 函数属性
# GNU

The `weak` attribute causes the declaration to be emitted as a weak symbol rather than a global.  This is primarily useful in defining library functions which can be overridden in user code, though it can also be used with non-function declarations.  Weak symbols are supported for ELF targets, and also for a.out targets when using the GNU assembler and linker.

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM
Functions defined with `__attribute__((weak))` export their symbols     weakly.

Functions declared with `__attribute__((weak))` and then defined without          `__attribute__((weak))` behave as weak        functions. This is not the same behavior as the `__weak` keyword.

### Note

This function attribute is a GNU compiler extension that the ARM compiler supports.      

## Example

```c
extern int Function_Attributes_weak_0 (int b) __attribute__((weak));
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124978893.htm



`__attribute__((weak))` function attribute
- 什么是弱符号？
   若两个或两个以上全局符号（函数或变量名）名字一样，而其中之一声明为weak symbol（弱符号），则这些全局符号不会引发重定义错误。链接器会忽略弱符号，去使用普通的全局符号来解析所有对这些符号的引用，但当普通的全局符号不可用时，链接器会使用弱符号。当有函数或变量名可能被用户覆盖时，该函数或变量名可以声明为一个弱符号。弱符号也称为weak alias（弱别名）。

