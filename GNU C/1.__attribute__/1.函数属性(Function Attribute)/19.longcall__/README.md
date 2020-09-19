# `__attribute__((longcall))` 函数属性

# GNU

On the RS/6000 and PowerPC, the `longcall` attribute causes the compiler to always call this function via a pointer, just as it would if the 

-mlongcall

 option had been specified.  The `shortcall` attribute causes the compiler not to do this.  These attributes override both the 

-mlongcall

 switch and the `#pragma longcall` setting.      

See [RS/6000 and PowerPC Options](https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/RS_002f6000-and-PowerPC-Options.html#RS_002f6000-and-PowerPC-Options), for more information on whether long calls are necessary.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes