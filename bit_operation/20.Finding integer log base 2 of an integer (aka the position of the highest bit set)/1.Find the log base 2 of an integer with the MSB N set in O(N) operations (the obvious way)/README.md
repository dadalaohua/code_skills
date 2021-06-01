# Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)

### Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)



在 O(N) 操作中找到一个整数的对数基数 2，MSB N 设置为 O(N)（显而易见的方法）

在O(N)操作中找到以2为底MSB N的整数的log(明显的方法)



```
unsigned int v; // 32-bit word to find the log base 2 of
unsigned int r = 0; // r will be lg(v)

while (v >>= 1) // unroll for more speed...
{
  r++;
}
```

The log base 2 of an integer is the same as the position of the highest  bit set (or most significant bit set, MSB).  The following log base 2  methods are faster than this one.

整数的对数基数 2 与最高位集（或最高有效位集，MSB）的位置相同。 下面的 log base 2 方法比这个方法快。

整数以2为底的对数与最高位集(或最高有效位集，MSB)的位置相同。下面的log以2为底的方法比这种方法快。

http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious

