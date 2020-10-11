# 符号扩展(可变位长)
有时，我们可能事先不知道位的长度，来完成符号扩展，上面的技巧就失效了。（也有可能是在某些不提供位域功能的编程语言，如Java）
```
unsigned b; // number of bits representing the number in x
            // 变量b指定需要扩展的位长
int x;      // sign extend this b-bit number to r
            // 需要将变量x中的数值符号扩展的结果保存到r中
int r;      // resulting sign-extended number
            // 存放计算结果到变量r
int const m = 1U << (b - 1); // mask can be pre-computed if b is fixed
                             // 如果b是常量，那么这个掩码可以被预处理

x = x & ((1U << b) - 1);  // (Skip this if bits in x above position b are already zero.)
                          // (如果超过b位的部分都已经是0了，那么这步可以跳过)
r = (x ^ m) - m;
```
这段代码需要四次操作，但当位长是常量时，假设高位部分都已经清零了，那么这个技巧只需要两次操作。
还有一个更快但是略微损失移植性的方法，这个方法不需要假设位长度超过b的部分，即高位部分，都已经被清零：
```
int const m = CHAR_BIT * sizeof(x) - b;
r = (x << m) >> m;
```

2004年6月13日，Sean A. Irvine建议我将符号扩展的方法添加进这个页面。同时他提供了这段代码`m = (1 << (b - 1)) - 1; r = -(x & ~m) | x`。后来我在这份代码的基础上，优化出了`m = 1U << (b - 1); r = -(x & m) | x`这个版本。

但是在2007年5月11日，Shay Green提出了上面的这个比我少一个操作的版本。

2008年10月15日，Vipin Sharma 建议我考虑增加一个步骤来解决如果x在除了b位长之外的二进制部分还存在1的情况。

2009年12月31日，Chris Pirazzi建议我增加目前最快的版本，这个版本对于固定位长的符号扩展，只需要2次操作；对于变长的，也只需要3次操作。

***
### Sign extending from a variable bit-width

Sometimes we need to extend the sign of a number but we don't know a priori the number of bits, b, in which it is represented.  (Or we could be programming in a language like Java, which lacks bitfields.)  

```
unsigned b; // number of bits representing the number in x
int x;      // sign extend this b-bit number to r
int r;      // resulting sign-extended number
int const m = 1U << (b - 1); // mask can be pre-computed if b is fixed

x = x & ((1U << b) - 1);  // (Skip this if bits in x above position b are already zero.)
r = (x ^ m) - m;
```

The code above requires four operations, but when the bitwidth is a  constant rather than variable, it requires only two fast operations, assuming the upper bits are already zeroes.

A slightly faster but less portable method that doesn't depend on  the bits in x above position b being zero is:

```
int const m = CHAR_BIT * sizeof(x) - b;
r = (x << m) >> m;
```



Sean A. Irvine suggested that I add sign extension methods to this page on June 13, 2004, and he provided `m = (1 << (b - 1)) - 1; r = -(x & ~m) | x;` as a starting point from which I optimized to get  m = 1U << (b - 1); r = -(x & m) | x.   But then on May 11, 2007, Shay Green suggested the version above,  which requires one less operation than mine.  Vipin Sharma suggested I add a step to deal with situations where x had possible ones in bits  other than the b bits we wanted to sign-extend on Oct. 15, 2008. On December 31, 2009 Chris Pirazzi suggested I add the faster version,  which requires two operations for constant bit-widths and three  for variable widths.

http://graphics.stanford.edu/~seander/bithacks.html
