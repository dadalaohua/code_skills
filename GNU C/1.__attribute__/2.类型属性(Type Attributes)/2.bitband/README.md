# `__attribute__((bitband))` type attribute
# ARM

`__attribute__((bitband))` is a type attribute     that gives you efficient atomic access to single-bit values in SRAM     and Peripheral regions of the memory architecture.

It is possible to set or clear a single bit directly with a single memory access in certain memory regions, rather than having to use the traditional read, modify, write approach. It is also possible to read a single bit directly rather than having to use the traditional read then shift and mask operation.

The following example illustrates the use of `__attribute__((bitband))`.

```c
typedef struct {
  int i : 1;
  int j : 2;
  int k : 3;
} BB __attribute__((bitband));
BB bb __attribute__((at(0x20000004));
void foo(void)
{
  bb.i = 1;
}
```

For peripherals that are sensitive to the memory access width, byte, halfword, and word stores or loads to the alias space are generated for `char`, `short`, and `int` types of bitfields of bit-banded structs respectively.

In the following example, bit-banded access is generated for `bb.i`.

```c
typedef struct {
  char i : 1;
  int j : 2;
  int k : 3;
} BB __attribute__((bitband));
BB bb __attribute__((at(0x20000004)));
void foo()
{
  bb.i = 1;
}
```

If you do not use `__attribute__((at()))` to place the bit-banded variable in the bit-band region, you must relocate it using another method. You can do this by either using an appropriate scatter-loading description file or by using the `--rw_base` linker command-line option. See the Linker Reference for more information.

## Restrictions

The following restrictions apply:

- This type attribute can only be used with `struct`. Any union type or other aggregate type with a union as a member cannot be bit-banded.
- Members of structs cannot be bit-banded individually.
- Bit-banded accesses are only generated for single-bit bitfields.
- Bit-banded accesses are not generated for `const` objects, pointers, and local objects.
- Bit-banding is only available on some processors. For example, the Cortex-M3 and Cortex-M4 processors.

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124979689.htm