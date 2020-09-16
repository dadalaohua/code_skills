# `__attribute__((format))` 函数属性
This attribute causes the compiler to check that the supplied arguments are in the 		correct format for the specified function.
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

