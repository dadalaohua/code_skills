# `__attribute__((packed))` type attribute

The `packed` type attribute specifies that a type must have the smallest possible alignment.

### Note

This type attribute is a GNU compiler extension that the ARM compiler supports.

This attribute is equivalent to `__packed`.

## Errors

Taking the address of a field with the `packed` attribute or in a structure with the `packed` attribute yields a `__packed`-qualified        pointer. The compiler produces a type error if you attempt to implicitly cast this pointer        to a non-`__packed` pointer. This contrasts with its behavior        for address-taken fields of a `#pragma pack`ed structure.

The compiler generates a warning message if you use this attribute in a  `typedef`.

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124980173.htm