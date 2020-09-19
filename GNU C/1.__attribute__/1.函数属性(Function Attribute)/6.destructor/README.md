# `__attribute__((destructor))` 函数属性
# GNU

The `constructor` attribute causes the function to be called automatically before execution enters `main ()`.  Similarly, the `destructor` attribute causes the function to be called automatically after `main ()` has completed or `exit ()` has been called.  Functions with these attributes are useful for initializing data that will be used implicitly during the execution of the program.      

These attributes are not currently implemented for Objective-C.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes



若函数被设定为`constructor`属性，则该函数会在`main（）`函数执行之前被自动的执行
类似的，若函数被设定为`destructor`属性，则该函数会`在main（）`函数执行之后或者`exit（）`被调用后被自动的执行。

