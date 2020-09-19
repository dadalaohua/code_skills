# `__attribute__((cdecl))` 函数属性

# GNU

On the Intel 386, the `cdecl` attribute causes the compiler to assume that the calling function will pop off the stack space used to pass arguments.  This is useful to override the effects of the -mrtd switch.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes