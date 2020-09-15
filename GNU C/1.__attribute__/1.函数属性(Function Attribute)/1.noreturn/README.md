# `__attribute__((noreturn))`函数属性

Informs the compiler that the function does not return. The     compiler can then perform optimizations by removing code that is never reached.

### Note

This function attribute is a GNU compiler extension that the ARM compiler supports. It has the `__declspec` equivalent `__declspec(noreturn)`.       

If the function reaches an explicit or implicit return, `__attribute__((noreturn))` is ignored and the compiler generates a warning:

```
Warning:  #1461-D: function declared with "noreturn" does return
```

## Usage

Use this attribute to reduce the cost of calling a function that never returns, such as   `exit()`. 

Best practice is to always terminate non-returning functions with `while(1);`.

1、通知编译器该函数不返回。然后，编译器可以通过删除从未到达的代码来执行优化。
2、这个函数属性是 ARM 编译器支持的 GNU 编译器扩展。`__declspec(noreturn)`与之等价。
3、如果函数达到显式或隐式返回，则忽略((noreturn))，编译器生成一个警告
4、使用此属性可减少调用从不返回的函数(如exit())的成本。
5、最佳实践是始终使用while(1);终止不返回的函数。
6、例程

```c
void overflow(void) __attribute__((noreturn)); // called on overflow

int negate(int x) 
{
    if (x == 0x80000000) overflow();
    return -x;
}

void overflow(void)
{
    __asm {
        SVC 0x123; // hypothetical exception-throwing system service
    }

    while (1);
}
```