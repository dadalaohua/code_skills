# `__attribute__((section("warn_unused_result")))` 函数属性
# GNU

```
warn_unused_result
```

The `warn_unused_result` attribute causes a warning to be emitted if a caller of the function with this attribute does not use its return value.  This is useful for functions where not checking the result is either a security problem or always a bug, such as `realloc`. 

```c
          int fn () __attribute__ ((warn_unused_result));
          int foo ()
          {
            if (fn () < 0) return -1;
            fn ();
            return 0;
          }
     
```

results in warning on line 5.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

In GNU-mode, warn if a function returns a result that is never used.

https://www.keil.com/support/man/docs/armcc/armcc_sam1436521435865.htm

在GNU模式下，如果函数返回一个结果，但是却不去使用它，则发出警告。

