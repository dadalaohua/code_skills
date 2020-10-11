# 计算一个数里位被置1的个数 给定从某位到最高位1的个数，推算该位的位置
接下来这份64位的代码可以选取出从左到右第r个二进制1的位置。也就是说，如果我们从最高位往右，统计二进制位为1的个数，直到达到了预期的rank（译者：解释见上一条），那么我们停下的位置就是答案。如果超出了最低位还没有算出结果，那么会返回64。这段代码可以改编出32位版本，也可以从最右边开始统计。
```
// Do a normal parallel bit count for a 64-bit integer,
// 并行地统计出二进制1的个数
 // but store all intermediate steps.
 // 保存所有的中间结果
 // a = (v & 0x5555...) + ((v >> 1) & 0x5555...);
 a =  v - ((v >> 1) & ~0UL/3);
 // b = (a & 0x3333...) + ((a >> 2) & 0x3333...);
 b = (a & ~0UL/5) + ((a >> 2) & ~0UL/5);
 // c = (b & 0x0f0f...) + ((b >> 4) & 0x0f0f...);
 c = (b + (b >> 4)) & ~0UL/0x11;
 // d = (c & 0x00ff...) + ((c >> 8) & 0x00ff...);
 d = (c + (c >> 8)) & ~0UL/0x101;
 t = (d >> 32) + (d >> 48);
 // Now do branchless select!
 // 这里进行无分支指令的条件选取
 s  = 64;
 // if (r > t) {s -= 32; r -= t;}
 s -= ((t - r) & 256) >> 3; r -= (t & ((t - r) >> 8));
 t  = (d >> (s - 16)) & 0xff;
 // if (r > t) {s -= 16; r -= t;}
 s -= ((t - r) & 256) >> 4; r -= (t & ((t - r) >> 8));
 t  = (c >> (s - 8)) & 0xf;
 // if (r > t) {s -= 8; r -= t;}
 s -= ((t - r) & 256) >> 5; r -= (t & ((t - r) >> 8));
 t  = (b >> (s - 4)) & 0x7;
 // if (r > t) {s -= 4; r -= t;}
 s -= ((t - r) & 256) >> 6; r -= (t & ((t - r) >> 8));
 t  = (a >> (s - 2)) & 0x3;
 // if (r > t) {s -= 2; r -= t;}
 s -= ((t - r) & 256) >> 7; r -= (t & ((t - r) >> 8));
 t  = (v >> (s - 1)) & 0x1;
 // if (r > t) s--;
 s -= ((t - r) & 256) >> 8;
 s = 65 - s;
```
如果在你的CPU上分支指令速度足够快，可以考虑将使用被注释掉的那些if语句，将对应的其它语句注释掉。
2009年11月21日，Juha Järvi将这个发给了我。
***

### Select the bit position (from the most-significant bit) with the given count (rank)

The following 64-bit code selects the position of the rth 1 bit  when counting from the left.  In other words if we start  at the most significant bit and proceed to the right,  counting the number of bits set to 1 until we reach the desired rank, r,  then the position where we stop is returned.  If the rank requested exceeds the count of bits set, then 64 is returned. The code may be modified for 32-bit or counting from the right.

```
  uint64_t v;          // Input value to find position with rank r.
  unsigned int r;      // Input: bit's desired rank [1-64].
  unsigned int s;      // Output: Resulting position of bit with rank r [1-64]
  uint64_t a, b, c, d; // Intermediate temporaries for bit count.
  unsigned int t;      // Bit count temporary.

  // Do a normal parallel bit count for a 64-bit integer,                     
  // but store all intermediate steps.                                        
  // a = (v & 0x5555...) + ((v >> 1) & 0x5555...);
  a =  v - ((v >> 1) & ~0UL/3);
  // b = (a & 0x3333...) + ((a >> 2) & 0x3333...);
  b = (a & ~0UL/5) + ((a >> 2) & ~0UL/5);
  // c = (b & 0x0f0f...) + ((b >> 4) & 0x0f0f...);
  c = (b + (b >> 4)) & ~0UL/0x11;
  // d = (c & 0x00ff...) + ((c >> 8) & 0x00ff...);
  d = (c + (c >> 8)) & ~0UL/0x101;
  t = (d >> 32) + (d >> 48);
  // Now do branchless select!                                                
  s  = 64;
  // if (r > t) {s -= 32; r -= t;}
  s -= ((t - r) & 256) >> 3; r -= (t & ((t - r) >> 8));
  t  = (d >> (s - 16)) & 0xff;
  // if (r > t) {s -= 16; r -= t;}
  s -= ((t - r) & 256) >> 4; r -= (t & ((t - r) >> 8));
  t  = (c >> (s - 8)) & 0xf;
  // if (r > t) {s -= 8; r -= t;}
  s -= ((t - r) & 256) >> 5; r -= (t & ((t - r) >> 8));
  t  = (b >> (s - 4)) & 0x7;
  // if (r > t) {s -= 4; r -= t;}
  s -= ((t - r) & 256) >> 6; r -= (t & ((t - r) >> 8));
  t  = (a >> (s - 2)) & 0x3;
  // if (r > t) {s -= 2; r -= t;}
  s -= ((t - r) & 256) >> 7; r -= (t & ((t - r) >> 8));
  t  = (v >> (s - 1)) & 0x1;
  // if (r > t) s--;
  s -= ((t - r) & 256) >> 8;
  s = 65 - s;
```

If branching is fast on your target CPU, consider uncommenting the  if-statements and commenting the lines that follow them.

Juha Järvi sent this to me on November 21, 2009.

http://graphics.stanford.edu/~seander/bithacks.html