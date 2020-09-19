# `__attribute__((model (model-name)))` 函数属性

# GNU

On the M32R/D, use this attribute to set the addressability of an object, and of the code generated for a function.  The identifier model-name is one of `small`, `medium`, or `large`, representing each of the code models.      

Small model objects live in the lower 16MB of memory (so that their addresses can be loaded with the `ld24` instruction), and are callable with the `bl` instruction.      

Medium model objects may live anywhere in the 32-bit address space (the compiler will generate `seth/add3` instructions to load their addresses), and are callable with the `bl` instruction.      

Large model objects may live anywhere in the 32-bit address space (the compiler will generate `seth/add3` instructions to load their addresses), and may not be reachable with the `bl` instruction (the compiler will generate the much slower `seth/add3/jl` instruction sequence).      

On IA-64, use this attribute to set the addressability of an object.  At present, the only supported identifier for model-name is `small`, indicating addressability via “small” (22-bit) addresses (so that their addresses can be loaded with the `addl` instruction).  Caveat: such addressing is by definition not position independent and hence this attribute must not be used for objects defined by shared libraries.         

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes