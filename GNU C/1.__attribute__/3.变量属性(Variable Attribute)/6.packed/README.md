# `__attribute__((packed))` variable attribute

# ARM

The `packed` variable attribute specifies     that a structure field has the smallest possible alignment. That is,     one byte for a variable field, and one bit for a bitfield, unless you specify a larger value with the `aligned` attribute.

## Example

```c
struct
{
    char a;
    int b __attribute__((packed));
} Variable_Attributes_packed_0;
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124982232.htm