# stb_divide

https://github.com/nothings/stb

有符号整数的三种除法/模数

In *ONE* source file, put:

在一个源文件中，输入：

```
#define STB_DIVIDE_IMPLEMENTATION
// #define C_INTEGER_DIVISION_TRUNCATES  // see Note 1
// #define C_INTEGER_DIVISION_FLOORS     // see Note 2
#include "stb_divide.h"
```

Other source files should just include stb_divide.h

其他源文件应该只包含 stb_divide.h

Note 1: On platforms/compilers that you know signed C division truncates, you can #define C_INTEGER_DIVISION_TRUNCATES.

注 1：在你知道有符号 C 除法截断的平台/编译器上，您可以#define C_INTEGER_DIVISION_TRUNCATES。

Note 2: On platforms/compilers that you know signed C division floors (rounds to negative infinity), you can #define C_INTEGER_DIVISION_FLOORS.

注意 2：在你知道有符号 C 除法层（舍入到负无穷大）的平台/编译器上，您可以#define C_INTEGER_DIVISION_FLOORS。

You can #define STB_DIVIDE_TEST in which case the implementation will generate a main() and compiling the result will create a program that tests the implementation. Run it with no arguments and any output indicates an error; run it with any argument and it will also print the test results. Define STB_DIVIDE_TEST_64 to a 64-bit integer type to avoid overflows in the result-checking which give false negatives.

你可以 #define STB_DIVIDE_TEST 在这种情况下，实现将生成一个 main() 并且编译结果将创建一个测试实现的程序。 不带参数运行它，任何输出都表示错误； 使用任何参数运行它，它还会打印测试结果。 将 STB_DIVIDE_TEST_64 定义为 64 位整数类型，以避免结果检查中的溢出，从而导致漏报。

ABOUT

关于

This file provides three different consistent divide/mod pairs implemented on top of arbitrary C/C++ division, including correct handling of overflow of intermediate calculations:

该文件提供了在任意 C/C++ 除法之上实现的三种不同的一致除法/模对，包括正确处理中间计算溢出：

    trunc:   a/b truncates to 0,           a%b has same sign as a
    trunc：a/b 截断为 0，a%b 与 a 的符号相同
    floor:   a/b truncates to -inf,        a%b has same sign as b
    floor：a/b 截断为 -inf，a%b 与 b 具有相同的符号
    eucl:    a/b truncates to sign(b)*inf, a%b is non-negative
    eucl：a/b 截断为 sign(b)*inf，a%b 是非负数

Not necessarily optimal; I tried to keep it generally efficient, but there may be better ways.

不一定是最优的； 我试图保持它总体上的效率，但可能有更好的方法。

Briefly, for those who are not familiar with the problem, we note the reason these divides exist and are interesting:

简而言之，对于那些不熟悉这个问题的人，我们注意到这些分歧存在的原因并且很有趣：

    'trunc' is easy to implement in hardware (strip the signs, compute, reapply the signs), thus is commonly defined by many languages (including C99)
    'trunc' 易于在硬件中实现（剥离符号、计算、重新应用符号），因此通常由许多语言（包括 C99）定义


​    
    'floor' is simple to define and better behaved than trunc;for example it divides integers into fixed-size buckets without an extra-wide bucket at 0, and for a fixed divisor N there are only |N| possible moduli.
    'floor' 定义简单且比 trunc 表现更好；例如，它将整数划分为固定大小的桶，而在 0 处没有超宽的桶，对于固定除数 N，只有 |N| 可能的模数。
    
    'eucl' guarantees fixed-sized buckets *and* a non-negative modulus and defines division to be whatever is needed to achieve that result.
    'eucl' 保证固定大小的桶 * 和 * 非负模数，并将除法定义为实现该结果所需的任何内容。

See "The Euclidean definition of the functions div and mod" by Raymond Boute (1992), or "Division and Modulus for Computer Scientists" by Daan Leijen (2001)

参见 Raymond Boute (1992) 的“函数 div 和 mod 的欧几里德定义”，或 Daan Leijen (2001) 的“计算机科学家的除法和模数”

We assume of the built-in C division:
    (a) modulus is the remainder for the corresponding division
    (b) a/b truncates if a and b are the same sign

我们假设内置的 C 除法：
     (a) 模数是相应除法的余数
     (b) 如果 a 和 b 是相同的符号，则 a/b 截断

Property (a) requires (a/b)*b + (a%b)==a, and is required by C.
Property (b) seems to be true of all hardware but is *not* satisfied by the euclidean division operator we define, so it's possibly not always true. If any such platform turns up, we can add more cases.(Possibly only stb_div_trunc currently relies on property (b).)

属性 (a) 需要 `(a/b)*b + (a%b)==a`，并且是 C 所需要的。
属性 (b) 似乎适用于所有硬件，但我们定义的欧几里德除法运算符*不*满足，因此它可能并不总是正确的。 如果出现任何此类平台，我们可以添加更多案例。（目前可能只有 stb_div_trunc 依赖于属性 (b)。）

