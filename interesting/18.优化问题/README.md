# 优化问题

不开优化编译

```shell
gcc -o test_code test_code.c -Wall
```

运行结果：

```shell
bar
Segmentation fault (core dumped)
```

O1优化编译

```shell
gcc -o test_code test_code.c -Wall -O1
```

运行结果：

```shell
bar
```

O2优化编译

```shell
gcc -o test_code test_code.c -Wall -O2
```

运行结果：

```shell
bar
bar
```

https://kukuruku.co/post/i-do-not-know-c/

Q: Turns out, bar() is invoked even when x is the null pointer (and the program does not crash). Is it the optimizer’s error, or is everything correct?

Answer

A: Everything’s correct. If x is the null pointer, undefined behavior occurs in line (1), and no one owes anything the programmer: the program does not have to crash in line (1), or make a return in line (2) in case it has managed to execute line (1). If we talk about the rules the compiler has been guided by, it all happens the following way. After the analysis of line (1), the compiler thinks that x cannot be a null pointer, and eliminates (2) and (3) as the dead code. Variable y is removed as unused. Reading from memory is also eliminated, since the *x type is not qualified as volatile.

That’s how the unused variable has removed the check for the null pointer.

