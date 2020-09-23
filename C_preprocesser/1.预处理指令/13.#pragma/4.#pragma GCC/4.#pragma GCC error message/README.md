# `#pragma GCC error message`

Generates an error message.  This pragma *is* considered to indicate an error in the compilation, and it will be treated as such.

Newlines can be included in the string by using the ‘\n’ escape sequence.  They will be displayed as newlines even if the -fmessage-length option is set to zero.

The error is only generated if the pragma is present in the code after pre-processing has been completed.  It does not matter however if the code containing the pragma is unreachable:

```c
#if 0
#pragma GCC error "this error is not seen"
#endif
void foo (void)
{
  return;
#pragma GCC error "this error is seen"
}
```

https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas
