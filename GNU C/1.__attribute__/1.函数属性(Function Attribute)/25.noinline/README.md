# \_\_attribute\_\_((noinline)) 函数属性
# GNU

This function attribute prevents a function from being considered for inlining.   

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This function attribute suppresses the inlining of a function at the call points of the function.

### Note

This function attribute is a GNU compiler extension that the        ARM compiler supports. It has the `__declspec` equivalent          `__declspec(noinline)`.

In GNU mode, if this attribute is applied to a type instead of a function, the result is a warning rather than an error.

## Example

```c
int fn(void) __attribute__((noinline));
int fn(void)
{
    return 42;
}
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124975804.htm

This function attribute suppresses the inlining of a function at the call points of the function.
声明为非内联函数