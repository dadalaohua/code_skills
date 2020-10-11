# 根据掩码把两个数进行位合并 

```
unsigned int a;    // value to merge in non-masked bits
                   // 将变量a中没被掩码覆盖的位保留下来
unsigned int b;    // value to merge in masked bits
                   // 将变量b中被掩码覆盖的位保留下来
unsigned int mask; // 1 where bits from b should be selected; 0 where from a.
                   // 如果某一位是1，那么结果中对应的位就保存b所对应位置的值；如果是0，则保存a所对应位置的值。
unsigned int r;    // result of (a & ~mask) | (b & mask) goes here
                   // 这里保存(a & ~mask) | (b & mask)的结果

r = a ^ ((a ^ b) & mask); 
```
这个算法比这种简单的实现`(a & ~mask) | (b & mask)`节省一次操作。然而如果掩码是一个常量，那么这两种算法实际上都差不多。
2006年2月9日，Ron Jeffery将这个算法发给我了。

***

### Merge bits from two values according to a mask

```
unsigned int a;    // value to merge in non-masked bits
unsigned int b;    // value to merge in masked bits
unsigned int mask; // 1 where bits from b should be selected; 0 where from a.
unsigned int r;    // result of (a & ~mask) | (b & mask) goes here

r = a ^ ((a ^ b) & mask); 
```

This shaves one operation from the obvious way of combining two sets of bits according to a bit mask.  If the mask is a constant, then there may be no advantage.

Ron Jeffery sent this to me on February 9, 2006.

http://graphics.stanford.edu/~seander/bithacks.html