# Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)

### Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)



```
unsigned int v; // 32-bit word to find the log base 2 of
unsigned int r = 0; // r will be lg(v)

while (v >>= 1) // unroll for more speed...
{
  r++;
}
```

The log base 2 of an integer is the same as the position of the highest  bit set (or most significant bit set, MSB).  The following log base 2  methods are faster than this one.

http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious