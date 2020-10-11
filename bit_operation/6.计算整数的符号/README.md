# 计算整数的符号

## 计算一个整数的符号(是+或者-) 
```
int v;      // we want to find the sign of v
            // 我们希望得出v的符号（正负）
int sign;   // the result goes here
            // 结果保存在这个变量里

// CHAR_BIT is the number of bits per byte (normally 8).
// 常量CHAR_BIT指是一个比特里包含多少位（通常情况下是8位）
sign = -(v < 0);  // if v < 0 then -1, else 0.
// or, to avoid branching on CPUs with flag registers (IA32):
// 或者，为了防止在有标志寄存器的CPU(Intel32位X86架构)上出现分支指令
sign = -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
// or, for one less instruction (but not portable):
// 或者，牺牲移植性来减少一个指令
sign = v >> (sizeof(int) * CHAR_BIT - 1);
```
对于32位整型数来说，上面的最后一条语句会计算`sign=v>>31`。这样的方式比`sign=-(v<0)`这种直接的方式要快一次运算左右。由于右移时，最左端的符号位会被填充到多出来的位中，所以在这个技巧（指v>>31）能够工作。如果最左端的符号位是1，那么结果就是-1；否则就是0。因为右移时，负数的所有位都会被填充为1，而二进制位全1正好是是-1的补码。不过不幸的是，这个操作是依赖底层实现的（所以是说牺牲了移植性）。

也许你可能更喜欢，对于正数返回1，对于负数返回-1，那么有：

```
sign = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));  // if v < 0 then -1, else +1
```
更或者，还有对于负数零正数而返回-1, 0, 1的方案，那么有：
```
sign = (v != 0) | -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
// Or, for more speed but less portability:
// 或者，牺牲移植性来提升速度
sign = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));  // -1, 0, or +1
// Or, for portability, brevity, and (perhaps) speed:
// 或者，更易移植，更加简洁，或者(有可能)更快的方案
sign = (v > 0) - (v < 0); // -1, 0, or +1
```
反之，如果你希望对于负数返回0，非负数返回+1，那么有：
```
sign = 1 ^ ((unsigned int)v >> (sizeof(int) * CHAR_BIT - 1)); // if v < 0 then 0, else 1
```
附加说明：
2003年3月7日，Augus Duggan指出1989 ANSI C标准指明带符号数右移的结构是由编译器实现时定义(implementation-defined)的，所以这个技巧有可能不会正常工作。
2005年9月28日，Toby Speight为了提高移植性，他提议使用CHAR_BIT常量表示比特的长度，而不是简单地假设比特长度是8位。

2006年3月4日，Augus提出了几种更具移植性的代码版本，包括类型转换。

2009年9月12日，[Rohit Gary](http://rpg-314.blogspot.com/)提出了集中支持非负数的代码版本。

***

### Compute the sign of an integer



```
int v;      // we want to find the sign of v
int sign;   // the result goes here 

// CHAR_BIT is the number of bits per byte (normally 8).
sign = -(v < 0);  // if v < 0 then -1, else 0. 
// or, to avoid branching on CPUs with flag registers (IA32):
sign = -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
// or, for one less instruction (but not portable):
sign = v >> (sizeof(int) * CHAR_BIT - 1); 
```

The last expression above evaluates to sign = v >> 31  for 32-bit integers.   This is one operation faster than the obvious way, sign = -(v < 0). This trick works because when signed integers are shifted right, the value  of the far left bit is copied to the other bits.  The far left bit is 1  when the value is negative and 0 otherwise; all 1 bits gives -1.   Unfortunately, this behavior is architecture-specific.

Alternatively, if you prefer the result be either -1 or +1, then use:

```
sign = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));  // if v < 0 then -1, else +1
```



On the other hand, if you prefer the result be either -1, 0, or +1, then use:

```
sign = (v != 0) | -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
// Or, for more speed but less portability:
sign = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));  // -1, 0, or +1
// Or, for portability, brevity, and (perhaps) speed:
sign = (v > 0) - (v < 0); // -1, 0, or +1
```

If instead you want to know if something is non-negative, resulting in +1 or else 0, then use:

```
sign = 1 ^ ((unsigned int)v >> (sizeof(int) * CHAR_BIT - 1)); // if v < 0 then 0, else 1
```

Caveat:  On March 7, 2003, Angus Duggan pointed out that the 1989 ANSI C  specification leaves the result of signed right-shift implementation-defined, so on some systems this hack might not work.  For greater portability,  Toby Speight suggested on September 28, 2005 that CHAR_BIT be used here  and throughout rather than assuming bytes were 8 bits long.  Angus recommended the more portable versions above, involving casting on March 4, 2006. [Rohit Garg](http://rpg-314.blogspot.com/) suggested the version  for non-negative integers on September 12, 2009.



http://graphics.stanford.edu/~seander/bithacks.html

```

```