# `__attribute__((noreturn))`函数属性

# GNU

```
noreturn
```

A few standard library functions, such as `abort` and `exit`, cannot return.  GCC knows this automatically.  Some programs define their own functions that never return.  You can declare them `noreturn` to tell the compiler this fact.  For example,      

```c
          void fatal () __attribute__ ((noreturn));
          
          void
          fatal (/* ... */)
          {
            /* ... */ /* Print error message. */ /* ... */
            exit (1);
          }
     
```

The `noreturn` keyword tells the compiler to assume that `fatal` cannot return.  It can then optimize without regard to what would happen if `fatal` ever did return.  This makes slightly better code.  More importantly, it helps avoid spurious warnings of uninitialized variables.      

The `noreturn` keyword does not affect the exceptional path when that applies: a `noreturn`-marked function may still return to the caller by throwing an exception or calling `longjmp`.      

Do not assume that registers saved by the calling function are restored before calling the `noreturn` function.      

It does not make sense for a `noreturn` function to have a return type other than `void`.      

The attribute `noreturn` is not implemented in GCC versions earlier than 2.5.  An alternative way to declare that a function does not return, which works in the current version and in some older versions, is as follows:      

```c
          typedef void voidfn ();
          
          volatile voidfn fatal;
     
```

This approach does not work in GNU C++.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

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

## Example

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

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124976881.htm

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

