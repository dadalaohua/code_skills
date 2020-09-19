# `__attribute__((interrupt))` 函数属性

# GNU

Use this attribute on the ARM, AVR, C4x, M32R/D and Xstormy16 ports to indicate that the specified function is an interrupt handler.  The compiler will generate function entry and exit sequences suitable for use in an interrupt handler when this attribute is present.      

Note, interrupt handlers for the m68k, H8/300, H8/300H, H8S, and SH processors can be specified via the `interrupt_handler` attribute.      

Note, on the AVR, interrupts will be enabled inside the function.      

Note, for the ARM, you can specify the kind of interrupt to be handled by adding an optional parameter to the interrupt attribute like this:      

```c
          void f () __attribute__ ((interrupt ("IRQ")));
     
```

​     

Permissible values for this parameter are: IRQ, FIQ, SWI, ABORT and UNDEF.       

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes