# `__attribute__((format))` 函数属性
# GNU

The `format` attribute specifies that a function takes `printf`, `scanf`, `strftime` or `strfmon` style arguments which should be type-checked against a format string.  For example, the declaration:      

```c
          extern int
          my_printf (void *my_object, const char *my_format, ...)
                __attribute__ ((format (printf, 2, 3)));
     
```

​     

causes the compiler to check the arguments in calls to `my_printf` for consistency with the `printf` style format string argument `my_format`.      

The parameter archetype determines how the format string is interpreted, and should be `printf`, `scanf`, `strftime` or `strfmon`.  (You can also use `__printf__`, `__scanf__`, `__strftime__` or `__strfmon__`.)  The parameter string-index specifies which argument is the format string argument (starting from 1), while first-to-check is the number of the first argument to check against the format string.  For functions where the arguments are not available to be checked (such as `vprintf`), specify the third parameter as zero.  In this case the compiler only checks the format string for consistency.  For `strftime` formats, the third parameter is required to be zero.  Since non-static C++ methods have an implicit `this` argument, the arguments of such methods should be counted from two, not one, when giving values for string-index and first-to-check.      

In the example above, the format string (`my_format`) is the second argument of the function `my_print`, and the arguments to check start with the third argument, so the correct parameters for the format attribute are 2 and 3.      

The `format` attribute allows you to identify your own functions which take format strings as arguments, so that GCC can check the calls to these functions for errors.  The compiler always (unless -ffreestanding or -fno-builtin is used) checks formats for the standard library functions `printf`, `fprintf`, `sprintf`, `scanf`, `fscanf`, `sscanf`, `strftime`, `vprintf`, `vfprintf` and `vsprintf` whenever such warnings are requested (using -Wformat), so there is no need to modify the header file stdio.h.  In C99 mode, the functions `snprintf`, `vsnprintf`, `vscanf`, `vfscanf` and `vsscanf` are also checked.  Except in strictly conforming C standard modes, the X/Open function `strfmon` is also checked as are `printf_unlocked` and `fprintf_unlocked`.  See [Options Controlling C Dialect](https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/C-Dialect-Options.html#C-Dialect-Options).      

The target may provide additional types of format checks.  See [Format Checks Specific to Particular Target Machines](https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Target-Format-Checks.html#Target-Format-Checks).      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This attribute causes the compiler to check that the supplied arguments are in the  correct format for the specified function.

## Syntax
```c
__attribute__((format(function, string-index, first-to-check)))
```
Where `function` is a `printf`-style function, such as `printf()`, `scanf()`, `strftime()`, `gnu_printf()`, `gnu_scanf()`, `gnu_strftime()`, or 			`strfmon()`.
`string-index` specifies the index of the string argument in your function (starting from 			one).
`first-to-check` is the index of the first argument to check against the format 			string.
## Example
```c
#include <stdio.h>

extern char *myFormatText1 (const char *, ...);
extern char *myFormatText2 (const char *, ...) __attribute__((format(printf, 1, 2)));


int main(void) {
  int a, b;
  float c;

  a = 5;
  b = 6;
  c = 9.099999;

myFormatText1("Here are some integers: %d , %d\n", a, b); // No type checking. Types match.
myFormatText1("Here are some integers: %d , %d\n", a, c); // No type checking. Type mismatch, but no warning.


myFormatText2("Here are some integers: %d , %d\n", a, b); // Type checking. Types match.
myFormatText2("Here are some integers: %d , %d\n", a, c); // Type checking. Warning: 181-D: argument is incompatible...
}				
```
`myFormatText1()` is a function that is given a string and two arguments to print. It has no format checking, so when it is passed a float argument and the function is expecting an integer, there is a silent type-mismatch. 

`myFormatText2()` is identical to `myFormatText1()`, except it has `__attribute__((format()))`. When it receives an argument of an unexpected type, it raises a warning message. 

https://www.keil.com/support/man/docs/armcc/armcc_sam1436458756975.htm

1、此属性使编译器检查提供的参数是否为指定函数的正确格式。
2、语法
`__attribute__((format(function, string-index, first-to-check)))`
function 是 printf 样式的函数，比如 printf()、scanf()、strftime()、gnu_printf()、gnu_scanf()、gnu_strftime()或strfmon()。
string-index 指定函数中字符串参数的索引(从一个开始)。
first-to-check 是检查格式字符串的第一个参数的索引。*/

`myFormatText1()` 是一个函数，它有一个字符串和两个要打印的参数。它没有格式检查，所以当它被传递一个浮点型参数时，函数期望的是一个整数，就会有一个静默的类型不匹配。
`myFormatText2()` 与` myFormatText1()` 相同，不同之处在于它有`__attribute__((format())`。当它接收到一个意外类型的参数时，它会发出一条警告消息。



format的语法格式为：
- format (archetype, string-index, first-to-check)
　　其中，“archetype”指定是哪种风格；“string-index”指定传入函数的第几个参数是格式化字符串；“first-to-check”指定从函数的第几个参数开始按上述规则进行检查。
具体的使用如下所示：
- `__attribute__((format(printf, a, b)))`
- `__attribute__((format(scanf, a, b)))`
　　其中参数m与n的含义为：
 　　　a：第几个参数为格式化字符串(format string);
 　　　b：参数集合中的第一个，即参数“…”里的第一个参数在函数参数总数排在第几。

