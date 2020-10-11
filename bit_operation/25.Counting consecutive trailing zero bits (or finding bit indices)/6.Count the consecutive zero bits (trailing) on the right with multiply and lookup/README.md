# Count the consecutive zero bits (trailing) on the right with multiply and lookup

### Count the consecutive zero bits (trailing) on the right with multiply and lookup



```
unsigned int v;  // find the number of trailing zeros in 32-bit v 
int r;           // result goes here
static const int MultiplyDeBruijnBitPosition[32] = 
{
  0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
  31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};
r = MultiplyDeBruijnBitPosition[((uint32_t)((v & -v) * 0x077CB531U)) >> 27];
```

Converting bit vectors to indices of set bits is an example use for this.   It requires one more operation than the earlier one involving modulus division, but the multiply may be faster.  The expression  (v & -v) extracts the least significant 1 bit from v.  The constant  0x077CB531UL is a de Bruijn sequence, which produces a unique pattern  of bits into the high 5 bits for each possible bit position that it is  multiplied against.  When there are no bits set, it returns 0.   More information can be found by reading the paper [Using de Bruijn Sequences to Index 1 in a Computer Word](http://citeseer.ist.psu.edu/leiserson98using.html) by Charles E. Leiserson, Harald Prokof, and Keith H. Randall.  

On October 8, 2005 [Andrew Shapira](http://onezero.org/)  suggested I add this.  Dustin Spicuzza asked me on April 14, 2009 to  cast the result of the multiply to a 32-bit type so it would work when  compiled with 64-bit ints.

http://graphics.stanford.edu/~seander/bithacks.html