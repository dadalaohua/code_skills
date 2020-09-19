# `__attribute__((fastcall))` 函数属性

# GNU

On the Intel 386, the `fastcall` attribute causes the compiler to pass the first two arguments in the registers ECX and EDX.  Subsequent arguments are passed on the stack.  The called function will pop the arguments off the stack.  If the number of arguments is variable all arguments are pushed on the stack.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes