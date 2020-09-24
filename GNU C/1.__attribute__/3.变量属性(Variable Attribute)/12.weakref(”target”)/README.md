# `__attribute__((weakref("target")))` variable attribute

# ARM

This variable attribute marks a variable declaration as an     alias that does not by itself require a definition to be given for     the target symbol.

### Note

This variable attribute is a GNU compiler extension that the ARM compiler supports.

### Syntax

```c
__attribute__((weakref("target")))
```

Where `target` is the target symbol.

## Restrictions

This attribute can only be used on variables that are declared as static.

## Example

In the following example, `a` is assigned        the value of `y` through a weak reference:

```c
extern int y;
static int x __attribute__((weakref("y")));
void foo (void)
{
  int a = x;
  ...
}
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124984010.htm