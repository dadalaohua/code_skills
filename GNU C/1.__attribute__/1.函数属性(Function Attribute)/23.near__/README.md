# `__attribute__((near))` 函数属性

# GNU

On 68HC11 and 68HC12 the `near` attribute causes the compiler to use the normal calling convention based on `jsr` and `rts`.  This attribute can be used to cancel the effect of the -mlong-calls option.         

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes