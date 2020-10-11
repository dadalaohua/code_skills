# Find the log base 2 of an N-bit integer in O(lg(N)) operations with multiply and lookup

### Find the log base 2 of an N-bit integer in O(lg(N)) operations with multiply and lookup



```
uint32_t v; // find the log base 2 of 32-bit v
int r;      // result goes here

static const int MultiplyDeBruijnBitPosition[32] = 
{
  0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
  8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
};

v |= v >> 1; // first round down to one less than a power of 2 
v |= v >> 2;
v |= v >> 4;
v |= v >> 8;
v |= v >> 16;

r = MultiplyDeBruijnBitPosition[(uint32_t)(v * 0x07C4ACDDU) >> 27];
```

The code above computes the log base 2 of a 32-bit integer with a small table lookup and multiply.  It requires only 13 operations, compared to (up to) 20 for the previous method.  The purely table-based  method requires the fewest operations, but this offers a reasonable compromise between table size and speed.  

If you know that v is a power of 2, then you only need the following:

```
static const int MultiplyDeBruijnBitPosition2[32] = 
{
  0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
  31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};
r = MultiplyDeBruijnBitPosition2[(uint32_t)(v * 0x077CB531U) >> 27];
```



Eric Cole devised this January 8, 2006 after reading about the entry below to [round up to a power of 2](http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2) and  the method below for  [computing the number of trailing bits with a multiply and lookup](http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup) using a DeBruijn sequence. On December 10, 2009, Mark Dickinson shaved off a couple operations  by requiring v be rounded up to one less than the next power of 2  rather than the power of 2.

http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious