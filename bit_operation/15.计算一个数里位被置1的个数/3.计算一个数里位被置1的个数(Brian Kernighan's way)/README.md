# 计算一个数里位被置1的个数（Brian Kernighan's way） 

```
unsigned int v; // count the number of bits set in v
                // 计算变量v的二进制中1的个数
unsigned int c; // c accumulates the total bits set in v
                // 保存计算的结果
for (c = 0; v; c++)
{
  v &= v - 1; // clear the least significant bit set
              // 清除掉从最低位到最高位数的第一个为1的位
}
```
Brian Kernighan的方法运算次数取决于二进制位中1的个数。所以如果一个32位字长的数，只有最高位是1，那么这个算法只会执行1次。
1988年，发布于《C程序设计语言》（第二版），作者Brian W. Kernighan和Dennis M. Ritchie。在此书的练习2-9中提到了这个算法。
2006年4月19日，Don Knuth向我指出这个算法，“是被Peter Wegner首先在CACM 3 (1960), 322发表的”。（同时也被Derrick Lehmer独立发现，并且在1964年由Beckenbach编辑发表在一本书上）

***

### Counting bits set, Brian Kernighan's way


```
unsigned int v; // count the number of bits set in v
unsigned int c; // c accumulates the total bits set in v
for (c = 0; v; c++)
{
  v &= v - 1; // clear the least significant bit set
}
```

Brian Kernighan's method goes through as many iterations as there are set bits.  So if we have a 32-bit word with only the high bit set, then it will only go once through the loop.

Published in 1988, the C Programming Language 2nd Ed.  (by Brian W. Kernighan and Dennis M. Ritchie)  mentions this in exercise 2-9. On April 19, 2006 Don Knuth pointed out to me that this method  "was first published by Peter Wegner in CACM 3 (1960), 322.  (Also discovered independently by Derrick Lehmer and published  in 1964 in a book edited by Beckenbach.)"

http://graphics.stanford.edu/~seander/bithacks.html