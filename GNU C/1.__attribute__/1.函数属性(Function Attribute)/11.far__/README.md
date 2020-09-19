# `__attribute__((far))` 函数属性

# GNU

On 68HC11 and 68HC12 the `far` attribute causes the compiler to use a calling convention that takes care of switching memory banks when entering and leaving a function.  This calling convention is also the default when using the 

-mlong-calls

 option.      

On 68HC12 the compiler will use the `call` and `rtc` instructions to call and return from a function.      

On 68HC11 the compiler will generate a sequence of instructions to invoke a board-specific routine to switch the memory bank and call the real function.  The board-specific routine simulates a `call`.  At the end of a function, it will jump to a board-specific routine instead of using `rts`.  The board-specific return routine simulates the `rtc`.       

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes