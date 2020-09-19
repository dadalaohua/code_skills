# `__attribute__((long_call))` 函数属性

# GNU

This attribute specifies how a particular function is called on ARM.  Both attributes override the -mlong-calls (see [ARM Options](https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/ARM-Options.html#ARM-Options)) command line switch and `#pragma long_calls` settings.  The `long_call` attribute causes the compiler to always call the function by first loading its address into a register and then using the contents of that register.   The `short_call` attribute always places the offset to the function from the call site into the `BL' instruction directly.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes