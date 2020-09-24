# `__attribute__((at(address)))` variable attribute

# ARM

This variable attribute enables you to specify the absolute address of a variable.

### Syntax

```
__attribute__((at(address))) 
```

Where:

- `address`

  is the desired address of the variable.

## Usage

The variable is placed in its own section, and the section containing the variable is given        an appropriate type by the compiler:

- Read-only variables are placed in a section of type RO.

- Initialized read-write variables are placed in a section of type RW.

  Variables explicitly initialized to zero are placed in:

  - A section of type ZI in RVCT 4.0 and later.
  - A section of type RW (not ZI) in RVCT 3.1 and earlier. Such variables are not                candidates for the ZI-to-RW optimization of the compiler.

- Uninitialized variables are placed in a section of type ZI.

### Note

GNU compilers do not support this variable attribute.

## Restrictions

The linker is not always able to place sections produced by the `at`        variable attribute.

The compiler faults use of the `at` attribute when it is used on        declarations with incomplete types.

## Errors

The linker gives an error message if it is not possible to place a section at a specified address.

## Example

```c
const int x1 __attribute__((at(0x10000))) = 10; /* RO */
int x2 __attribute__((at(0x12000))) = 10; /* RW */
int x3 __attribute__((at(0x14000))) = 0; /* RVCT 3.1 and earlier: RW.
                                          * RVCT 4.0 and later: ZI. */
int x4 __attribute__((at(0x16000))); /* ZI */
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124981140.htm