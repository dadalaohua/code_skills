# N位长的串的位反转（5*lg(N)次操作，并行）
```
unsigned int v; // 32-bit word to reverse bit order
                // 反转32位长的字

// swap odd and even bits
// 反转奇数位和偶数位的位
v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
// swap consecutive pairs
// 反转两两一组的位
v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
// swap nibbles ...
// 反转半字节
v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
// swap bytes
// 反转字节
v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
// swap 2-byte long pairs
// 反转两字节一组的位
v = ( v >> 16             ) | ( v               << 16);
```
下面的这个变种时间复杂度同样是O(lg(N))，然而它需要额外的操作来反转变量v。它的优点是常数在过程中计算，这样可以占用更少的内存。
```
unsigned int s = sizeof(v) * CHAR_BIT; // bit size; must be power of 2
                                       // 位长；必须要是2的乘幂
unsigned int mask = ~0;
while ((s >>= 1) > 0)
{
  mask ^= (mask << s);
  v = ((v >> s) & mask) | ((v << s) & ~mask);
}
```
这些方法很适合用在N很大的场景下。如果你需要用在大于64位的整型数时，那么就便需要按照对应的模式添加代码；不然只会有低32位会被反转，答案也会保存在低32位下。
参考1983年的Dr.Dobb日志，Binary Magic Numbers中Edwin Freed的文章可以查到更多信息。
2005年9月13日，Ken Raeburn提出了第二个变种。
2006年3月19日，Veldmeijer提到，第一个版本的算法的最后一行可以不用位与操作。
***
### Reverse an N-bit quantity in parallel in 5 * lg(N) operations:



```
unsigned int v; // 32-bit word to reverse bit order

// swap odd and even bits
v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
// swap consecutive pairs
v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
// swap nibbles ... 
v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
// swap bytes
v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
// swap 2-byte long pairs
v = ( v >> 16             ) | ( v               << 16);
```

The following variation is also O(lg(N)), however it requires more  operations to reverse v.  Its virtue is in taking less slightly memory  by computing the constants on the fly.

```
unsigned int s = sizeof(v) * CHAR_BIT; // bit size; must be power of 2 
unsigned int mask = ~0;         
while ((s >>= 1) > 0) 
{
  mask ^= (mask << s);
  v = ((v >> s) & mask) | ((v << s) & ~mask);
}
```

These methods above are best suited to situations where N is large. If you use the above with 64-bit ints (or larger), then you need to add more lines (following the pattern); otherwise only the lower 32 bits will be reversed and the result will be in the lower 32 bits.

  See Dr. Dobb's Journal 1983, Edwin Freed's article on Binary Magic  Numbers for more information.  The second variation was suggested by Ken Raeburn on September 13, 2005.  Veldmeijer mentioned that the first version could do without ANDS in the last line on March 19, 2006.

http://graphics.stanford.edu/~seander/bithacks.html