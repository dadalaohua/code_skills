# `__attribute__((aligned))` variable attribute

The `aligned` variable attribute specifies a minimum alignment for the variable or structure field, measured in bytes.

### Note

This variable attribute is a GNU compiler extension that the ARM compiler supports.      

## Example

```c
/* Aligns on 16-byte boundary */
int x __attribute__((aligned (16)));
/* In this case, the alignment used is the maximum alignment for a scalar data type. For ARM, this is 8 bytes. */
short my_array
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124981436.htm