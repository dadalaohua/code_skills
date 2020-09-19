# `__attribute__((const))` 函数属性
# GNU

Many functions do not examine any values except their arguments, and have no effects except the return value.  Basically this is just slightly more strict class than the `pure` attribute below, since function is not allowed to read global memory.      

Note that a function that has pointer arguments and examines the data pointed to must *not* be declared `const`.  Likewise, a function that calls a non-`const` function usually must not be `const`.  It does not make sense for a `const` function to return `void`.      

The attribute `const` is not implemented in GCC versions earlier than 2.5.  An alternative way to declare that a function has no side effects, which works in the current version and in some older versions, is as follows:      

```c
          typedef int intfn ();
          
          extern const intfn square;
     
```

This approach does not work in GNU C++ from 2.6.0 on, since the language specifies that the `const` must be attached to the return value.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

The `const` function attribute specifies that a function examines only its arguments, and has no effect except     for the return value. That is, the function does not read or modify any global memory.

If a function is known to operate only on its arguments then it can be subject to common sub-expression elimination and loop optimizations.

This attribute is stricter than `__attribute__((pure))` because functions are not permitted to read global        memory.

### Note

​        This function attribute is a GNU compiler extension that the ARM compiler supports. It has the keyword equivalent `__pure`.      

## Example

```c
#include <stdio.h>

// __attribute__((const)) functions do not read or modify any global memory
int my_double(int b) __attribute__((const));
int my_double(int b) {
  return b*2;
}

int main(void) {
    int i;
    int result;
    for (i = 0; i < 10; i++)
    {
       result = my_double(i);
       printf (" i = %d ; result = %d \n", i, result);
    }
}
```



1、const 函数属性指定一个函数只检查它的参数，除了返回值之外没有其他效果。也就是说，该函数不读取或修改任何全局内存。
2、如果已知函数只对其参数进行操作，则可以对其进行公共子表达式消除和循环优化。
这个属性比`__attribute__((pure))`更严格，因为函数不允许读取全局内存。
3、这个函数属性是ARM编译器支持的GNU编译器扩展。它的关键字与`__pure` 相同。

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124974244.htm

## const
该属性只能用于带有数值类型参数的函数上，当重复调用带有数值参数的函数时，由于返回值是相同的。所以此时编译器可以进行优化处理，除第一次需要运算外， 其它只需要返回第一次的结果。
该属性主要适用于没有静态状态（static state）和副作用的一些函数，并且返回值仅仅依赖输入的参数。为了说明问题，下面举个非常“糟糕”的例子，该例子将重复调用一个带有相同参数值的函数，具体如下：

```c
extern int  square( int  n ) __attribute__ ( (const) ); 
for (i = 0; i < 100; i++ )         
{    
    total += square (5) + i;       
}
```
添加`__attribute__((const))`声明，编译器只调用了函数一次，以后只是直接得到了相同的一个返回值。

事实上，const参数不能用在带有指针类型参数的函数中，因为该属性不但影响函数的参数值，同样也影响到了参数指向的数据，它可能会对代码本身产生严重甚至是不可恢复的严重后果。并且，带有该属性的函数不能有任何副作用或者是静态的状态，类似getchar（）或time（）的函数是不适合使用该属性。