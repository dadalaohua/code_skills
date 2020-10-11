# 计算一个数里位被置1的个数 **统计从最高位到指定的某位之间**

```
uint64_t v; // Compute the rank (bits set) in v from the MSB（最高位） to pos.
            // 计算v中从第pos位到最高位的rank(二进制位1的个数)
unsigned int pos; // Bit position to count bits upto.
                  // 指定某一位，向最高位统计(从右边数)
uint64_t r; // Resulting rank of bit at pos goes here.
            // 保存统计的结果

// Shift out bits after given position.
// 将其余的位右移出去
r = v >> (sizeof(v) * CHAR_BIT - pos);
// Count set bits in parallel.
// 并行地统计1的个数
// r = (r & 0x5555...) + ((r >> 1) & 0x5555...);
r = r - ((r >> 1) & ~0UL/3);
// r = (r & 0x3333...) + ((r >> 2) & 0x3333...);
r = (r & ~0UL/5) + ((r >> 2) & ~0UL/5);
// r = (r & 0x0f0f...) + ((r >> 4) & 0x0f0f...);
r = (r + (r >> 4)) & ~0UL/17;
// r = r % 255;
r = (r * (~0UL/255)) >> ((sizeof(v) - 1) * CHAR_BIT);
```
2009年11月21日，Juha Järvi将这个算法发给了我，这个算法是下一个算法（给定从某位到最高位1的个数，推算出该位的位置）的逆运算。
***

### Count bits set (rank) from the most-significant bit upto a given position

The following finds the the rank of a bit, meaning it returns the sum of bits that are set to 1 from the most-signficant bit downto the bit at the given position.

```
  uint64_t v;       // Compute the rank (bits set) in v from the MSB to pos.
  unsigned int pos; // Bit position to count bits upto.
  uint64_t r;       // Resulting rank of bit at pos goes here.

  // Shift out bits after given position.
  r = v >> (sizeof(v) * CHAR_BIT - pos);
  // Count set bits in parallel.
  // r = (r & 0x5555...) + ((r >> 1) & 0x5555...);
  r = r - ((r >> 1) & ~0UL/3);
  // r = (r & 0x3333...) + ((r >> 2) & 0x3333...);
  r = (r & ~0UL/5) + ((r >> 2) & ~0UL/5);
  // r = (r & 0x0f0f...) + ((r >> 4) & 0x0f0f...);
  r = (r + (r >> 4)) & ~0UL/17;
  // r = r % 255;
  r = (r * (~0UL/255)) >> ((sizeof(v) - 1) * CHAR_BIT);
```

Juha Järvi sent this to me on November 21, 2009 as an inverse operation  to the computing the bit position with the given rank, which follows.

http://graphics.stanford.edu/~seander/bithacks.html