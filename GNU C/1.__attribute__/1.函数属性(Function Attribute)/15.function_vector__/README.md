# `__attribute__((function_vector))` 函数属性

# GNU

Use this attribute on the H8/300, H8/300H, and H8S to indicate that the specified function should be called through the function vector.  Calling a function through the function vector will reduce code size, however; the function vector has a limited size (maximum 128 entries on the H8/300 and 64 entries on the H8/300H and H8S) and shares space with the interrupt vector.      

You must use GAS and GLD from GNU binutils version 2.7 or later for this attribute to work correctly.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes