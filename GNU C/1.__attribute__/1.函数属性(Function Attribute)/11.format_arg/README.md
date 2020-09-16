# `__attribute__((format_arg(string-index)))` 函数属性
- This attribute specifies that a function takes a format string as an     argument. Format strings can contain typed placeholders that are intended to be passed to       `printf`-style functions such as `printf()`, `scanf()`, `strftime()`, or `strfmon()`.

This attribute causes the compiler to perform placeholder type checking on the specified argument when the output of the function is used in calls to a `printf`-style function.
### Note
This function attribute is a GNU compiler extension that the ARM compiler supports.
### Syntax
```c
　　__attribute__((format_arg(string-index)))      
```

　　Where `string-index` specifies the argument that is the format string argument (starting from one).
　　
## Example
The following example declares two functions, `myFormatText1()` and `myFormatText2()`, that provide format strings to `printf()`.
　　
The first function, `myFormatText1()`, does not specify the `format_arg` attribute. The compiler does not check the types of the `printf` arguments for consistency with the format string.
　　
The second function, `myFormatText2()`, specifies the `format_arg` attribute. In the subsequent calls to `printf()`, the compiler checks that the types of the supplied arguments `a` and `b` are consistent with the format string argument to `myFormatText2()`. The compiler produces a warning when a `float` is provided where an `int` is expected.
　　
```c
#include <stdio.h>
　　
// Function used by printf. No format type checking.
extern char *myFormatText1 (const char *);
　　
// Function used by printf. Format type checking on argument 1.
extern char *myFormatText2 (const char *) __attribute__((format_arg(1)));
　　　
int main(void) {
　　  int a;
　　  float b;
　　
　　  a = 5;
　　  b = 9.099999;
　　
　　  printf(myFormatText1("Here is an integer: %d\n"), a); // No type checking. Types match anyway.
　　  printf(myFormatText1("Here is an integer: %d\n"), b); // No type checking. Type mismatch, but no warning                            
　　
　　  printf(myFormatText2("Here is an integer: %d\n"), a); // Type checking. Types match.
　　  printf(myFormatText2("Here is an integer: %d\n"), b); // Type checking. Type mismatch results in Warning:  #181-D
　　}
```
```shell
$ armcc format_arg_test.c -c
"format_arg_test.c", line 18: Warning:  #181-D: argument is incompatible with corresponding format string conversion
　　     printf(myFormatText2("Here is an integer: %d\n"), b);
　　                                                       ^
format_arg_test.c: 1 warning, 0 errors
```

