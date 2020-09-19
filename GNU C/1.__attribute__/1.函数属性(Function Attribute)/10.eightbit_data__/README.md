# `__attribute__((eightbit_data))` 函数属性

# GNU

Use this attribute on the H8/300, H8/300H, and H8S to indicate that the specified variable should be placed into the eight bit data section.  The compiler will generate more efficient code for certain operations on data in the eight bit data area.  Note the eight bit data area is limited to 256 bytes of data.      

You must use GAS and GLD from GNU binutils version 2.7 or later for this attribute to work correctly.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes