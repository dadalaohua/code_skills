# **计算模除 模数是** `(1<<s)-1` **时 没有除法**

```c
unsigned int n;                      // numerator
                                     // 变量n为分子（被模除的数）
const unsigned int s;                // s > 0
const unsigned int d = (1 << s) - 1; // so d is either 1, 3, 7, 15, 31, ...).
                                     // 那么变量d从小到大依次为:1, 3, 7, 15, 31, ...
unsigned int m;                      // n % d goes here.
                                     // 保存n%d的结果
for (m = n; n > d; n = m)
{
  for (m = 0; n; n >>= s)
  {
    m += n & d;
  }
}
// Now m is a value from 0 to d, but since with modulus division
// 此时m的值范围时0到d，但由于这里是模除（译者注：所以需要特殊处理m等于d的情况）
// we want m to be 0 when it is d.
// 当m的值为d时，我们希望m的值变成0
m = m == d ? 0 : m;
```

这个用来处理 模数是比2的乘幂少1的整数 的模除技巧，最多需要 5 + (4 + 5 * ceil(N / s)) * ceil(lg(N / s)) 次操作，此处N表示被模数的有效位。也就是说，这个技巧最多需要O(N * lg(N))的时间复杂度。
2001年8月15日，出自Sean Anderson之手。
2004年6月17日，Sean A. Irvine纠正了我一个错误，我之前曾错误地写道“我们也可以在后面直接对m赋值，m = ((m + 1) & d) - 1;”。
2005年4月25日，Michael Miller订正了代码中的一处排版显示错误。

***

### Compute modulus division by (1 << s) - 1 without a division operator



```
unsigned int n;                      // numerator
const unsigned int s;                // s > 0
const unsigned int d = (1 << s) - 1; // so d is either 1, 3, 7, 15, 31, ...).
unsigned int m;                      // n % d goes here.

for (m = n; n > d; n = m)
{
  for (m = 0; n; n >>= s)
  {
    m += n & d;
  }
}
// Now m is a value from 0 to d, but since with modulus division
// we want m to be 0 when it is d.
m = m == d ? 0 : m;
```

This method of modulus division by an integer that is one less than a power of 2 takes at most  5 + (4 + 5 * ceil(N / s)) * ceil(lg(N / s)) operations, where N is the  number of bits in the numerator.  In other words, it takes at most  O(N * lg(N)) time.

Devised by Sean Anderson, August 15, 2001.  Before Sean A. Irvine corrected me on June 17, 2004, I mistakenly commented that we could alternatively assign  `m = ((m + 1) & d) - 1;` at the end.  Michael Miller spotted a typo in the code April 25, 2005.

http://graphics.stanford.edu/~seander/bithacks.html