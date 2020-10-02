# 计算整数的符号

## 计算一个整数的符号(是+或者-) 
```
int v;      // 待检测的数
int sign;   // 符号结果，0表示正数或者0，-1表示负数

// CHAR_BIT 是一个字节的位数 (通常是8).
sign = -(v < 0);  // if v < 0 then -1, else 0. 
// 或者避免使用CPU判断，因为那会增加cost:
sign = -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
// 或者更少的运算:
sign = v >> (sizeof(int) * CHAR_BIT - 1); 
```
更多的人喜欢用-1表示复数，+1表示正数或者0，那么我们可以用: 
```
sign = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));  // if v < 0 then -1, else +1
```
另外用-1，0，+1分别表示负数，0，正数的方法有: 
```
sign = (v != 0) | -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
```
//或者更快一点的方法，但移植性差:
```
sign = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));  // -1, 0, or +1
```
//或者更简洁，移植性高和速度快的方法是:
```
sign = (v > 0) - (v < 0); // -1, 0, or +1
```
如果你想知道一个数是不是非负数，结果是1(非负)否则0(负数),那么可以用: 
```
sign = 1 ^ ((unsigned int)v >> (sizeof(int) * CHAR_BIT - 1)); // if v < 0 then 0, else 1
```

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