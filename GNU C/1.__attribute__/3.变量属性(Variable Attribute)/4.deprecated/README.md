# `__attribute__((deprecated))` variable attribute

# ARM

The `deprecated` variable attribute enables the declaration of a     deprecated variable without any warnings or errors being issued by the compiler. However, any     access to a `deprecated` variable creates a warning but still     compiles.

The warning gives the location where the variable is used and the location where it is defined. This helps you to determine why a particular definition is deprecated.

### Note

This variable attribute is a GNU compiler extension that the ARM compiler supports.      

## Example

```
extern int Variable_Attributes_deprecated_0 __attribute__((deprecated));
extern int Variable_Attributes_deprecated_1 __attribute__((deprecated));
void Variable_Attributes_deprecated_2()
{
    Variable_Attributes_deprecated_0=1;
    Variable_Attributes_deprecated_1=2;
}
```

Compiling this example generates two warning messages.

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124981701.htm