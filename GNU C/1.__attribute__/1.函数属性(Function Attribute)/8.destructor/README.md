# `__attribute__((destructor))` 函数属性
若函数被设定为`constructor`属性，则该函数会在`main（）`函数执行之前被自动的执行
类似的，若函数被设定为`destructor`属性，则该函数会`在main（）`函数执行之后或者`exit（）`被调用后被自动的执行。

