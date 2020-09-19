# `__attribute__((nothrow))` 函数属性

# GNU

The nothrow attribute is used to inform the compiler that a function cannot throw an exception. For example, most functions in the standard C library can be guaranteed not to throw an exception with the notable exceptions of qsort and bsearch that take function pointer arguments. The nothrow attribute is not implemented in GCC versions earlier than 3.3. 
https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This function attribute asserts that a call to a function 		never results in a C++ exception being propagated from the call into the caller.

### Note

This function attribute is a GNU compiler extension that the ARM compiler supports. It  has the `__declspec` equivalent `__declspec(nothrow)`.

## Example

```c
struct S
{
    ~S();
};
extern void f(void) __attribute__((nothrow));
void g(void)
{
    S s;
    f();
}
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1386607552703.htm



nothrow属性用于通知编译器函数不能引发异常。例如，标准C库中的大多数函数都可以保证不会抛出异常，但qsort和bsearch这两个显著的异常使用函数指针参数。

可用于函数声明。告诉编译器被声明的函数以及函数内部调用的其它函数都不会抛出异常。