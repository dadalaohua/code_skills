# `__attribute__((alias))` variable attribute

This variable attribute enables you to specify multiple aliases for a variable.

### Syntax

```
type newname        __attribute__((alias("oldname"))); 
```

Where:

- `oldname`

  is the name of the variable to be aliased

- `newname`

  is the new name of the aliased variable.

## Usage

Aliases must be defined in the same translation unit as the original variable.

### Note

You cannot specify aliases in block scope. The compiler ignores aliasing attributes attached to local variable definitions and treats the variable definition as a normal local definition.

In the output object file, the compiler replaces alias references with a reference to the        original variable name, and emits the alias alongside the original name. For example:

```c
int oldname = 1;
extern int newname __attribute__((alias("oldname")));
```

This code compiles to:

```
     LDR      r1,[r0,#0]  ; oldname
     ...
oldname
newname
     DCD      0x00000001
```

If the original variable is defined as `static` but the alias is        defined as `extern`, then the compiler changes the original variable to be external.

### Note

Function names might also be aliased using the corresponding function attribute            `__attribute__((alias))`.

## Example

```c
#include <stdio.h>
int oldname = 1;
extern int newname __attribute__((alias("oldname"))); // declaration
void foo(void)
{
    printf("newname = %d\n", newname); // prints 1
}
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124980906.htm