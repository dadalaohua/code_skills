# Count the consecutive zero bits (trailing) on the right in parallel

### Count the consecutive zero bits (trailing) on the right in parallel



```
unsigned int v;      // 32-bit word input to count zero bits on right
unsigned int c = 32; // c will be the number of zero bits on the right
v &= -signed(v);
if (v) c--;
if (v & 0x0000FFFF) c -= 16;
if (v & 0x00FF00FF) c -= 8;
if (v & 0x0F0F0F0F) c -= 4;
if (v & 0x33333333) c -= 2;
if (v & 0x55555555) c -= 1;
```

Here, we are basically doing the same operations as finding the log base 2  in parallel, but we first isolate the lowest 1 bit, and then proceed with c starting at the maximum and decreasing.   The number of operations is at most 3 * lg(N) + 4, roughly, for N bit words.

Bill Burdick suggested an optimization, reducing the time from 4 * lg(N) on  February 4, 2011.

http://graphics.stanford.edu/~seander/bithacks.html