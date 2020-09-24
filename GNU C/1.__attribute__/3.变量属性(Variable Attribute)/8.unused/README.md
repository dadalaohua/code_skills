# `__attribute__((unused))` variable attribute

# ARM

Normally, the compiler warns if a variable is declared but is never referenced. This     attribute informs the compiler that you expect a variable to be unused and tells it not to issue a     warning if it is not used.

### Note

This variable attribute is a GNU compiler extension that the ARM compiler supports.      

## Example

```c
void Variable_Attributes_unused_0()
{
    static int aStatic =0;
    int aUnused __attribute__((unused));
    int bUnused;
    aStatic++;
}
```

In this example, the compiler warns that `bUnused` is declared but never        referenced, but does not warn about `aUnused`.

### Note

The GNU compiler does not give any warning.

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124982981.htm