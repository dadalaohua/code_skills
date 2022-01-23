# __builtin_types_compatible_p 和 __builtin_choose_expr

## __builtin_types_compatible_p

Built-in Function: *int* **__builtin_types_compatible_p** *(type1, type2)*

You can use the built-in function `__builtin_types_compatible_p` to determine whether two types are the same.

你可以使用内置函数 __builtin_types_compatible_p 来确定两种类型是否相同。

This built-in function returns 1 if the unqualified versions of the types type1 and type2 (which are types, not expressions) are compatible, 0 otherwise. The result of this built-in function can be used in integer constant expressions.

如果类型 type1 和 type2（它们是类型，不是表达式）的非限定版本兼容，则此内置函数返回 1，否则返回 0。此内置函数的结果可用于整数常量表达式。

This built-in function ignores top level qualifiers (e.g., `const`, `volatile`). For example, `int` is equivalent to `const int`.

此内置函数忽略顶级限定符（例如，const、volatile）。例如，int 等价于 const int。

The type `int[]` and `int[5]` are compatible. On the other hand, `int` and `char *` are not compatible, even if the size of their types, on the particular architecture are the same. Also, the amount of pointer indirection is taken into account when determining similarity. Consequently, `short *` is not similar to `short **`. Furthermore, two types that are typedefed are considered compatible if their underlying types are compatible.

int[] 和 int[5] 类型是兼容的。另一方面，int 和 char * 是不兼容的，即使它们的类型的大小在特定架构上是相同的。此外，在确定相似度时还要考虑指针间接的数量。因此，short * 与 short ** 不同。此外，如果它们的基础类型兼容，则类型定义的两种类型被认为是兼容的。

An `enum` type is not considered to be compatible with another `enum` type even if both are compatible with the same integer type; this is what the C standard specifies. For example, `enum {foo, bar}` is not similar to `enum {hot, dog}`.

一个枚举类型不被认为与另一个枚举类型兼容，即使两者都兼容同一个整数类型；这是C标准规定的。例如，`enum {foo, bar}` 与`enum {hot, dog}` 不同。

You typically use this function in code whose execution varies depending on the arguments’ types. For example:

你通常在执行取决于参数类型的代码中使用此函数。例如：

```
#define foo(x)                                                  \
  ({                                                           \
    typeof (x) tmp = (x);                                       \
    if (__builtin_types_compatible_p (typeof (x), long double)) \
      tmp = foo_long_double (tmp);                              \
    else if (__builtin_types_compatible_p (typeof (x), double)) \
      tmp = foo_double (tmp);                                   \
    else if (__builtin_types_compatible_p (typeof (x), float))  \
      tmp = foo_float (tmp);                                    \
    else                                                        \
      abort ();                                                 \
    tmp;                                                        \
  })
```

*Note:* This construct is only available for C.

注意：此构造仅适用于 C。

## __builtin_choose_expr

Built-in Function: *type* **__builtin_choose_expr** *(const_exp, exp1, exp2)*

You can use the built-in function `__builtin_choose_expr` to evaluate code depending on the value of a constant expression. This built-in function returns exp1 if const_exp, which is an integer constant expression, is nonzero. Otherwise it returns exp2.

你可以使用内置函数 __builtin_choose_expr 根据常量表达式的值来评估代码。如果整数常量表达式 const_exp 不为零，则此内置函数返回 exp1。否则返回 exp2。

This built-in function is analogous to theoperator in C, except that the expression returned has its type unaltered by promotion rules. Also, the built-in function does not evaluate the expression that is not chosen. For example, if const_exp evaluates to `true`, exp2 is not evaluated even if it has side effects.

这个内置函数类似于C 的运算符 ‘? :’ ，但返回的表达式的类型不受提升规则的影响。此外，内置函数不会评估未选择的表达式。例如，如果 const_exp 计算结果为 true，即使 exp2 有副作用，也不会计算它。

This built-in function can return an lvalue if the chosen argument is an lvalue.

如果所选参数是左值，则此内置函数可以返回左值。

If exp1 is returned, the return type is the same as exp1’s type. Similarly, if exp2 is returned, its return type is the same as exp2.

如果返回 exp1，则返回类型与 exp1 的类型相同。类似地，如果返回 exp2，则其返回类型与 exp2 相同。

Example:

```
#define foo(x)                                                    \
  __builtin_choose_expr (                                         \
    __builtin_types_compatible_p (typeof (x), double),            \
    foo_double (x),                                               \
    __builtin_choose_expr (                                       \
      __builtin_types_compatible_p (typeof (x), float),           \
      foo_float (x),                                              \
      /* The void expression results in a compile-time error  \
         when assigning the result to something.  */          \
      (void)0))
```

*Note:* This construct is only available for C. Furthermore, the unused expression (exp1 or exp2 depending on the value of const_exp) may still generate syntax errors. This may change in future revisions.

注意：此构造仅适用于 C。此外，未使用的表达式（exp1 或 exp2，取决于 const_exp 的值）仍可能产生语法错误。这可能会在未来的修订版中发生变化。

https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
