# Compute the lexicographically next bit permutation

### Compute the lexicographically next bit permutation

Suppose we have a pattern of N bits set to 1 in an integer and we want the  next permutation of N 1 bits in a lexicographical sense.   For example, if N is 3 and the bit pattern is 00010011, the next patterns  would be 00010101, 00010110, 00011001,00011010, 00011100, 00100011,  and so forth.  The following is a fast way to compute the next permutation.

```
unsigned int v; // current permutation of bits 
unsigned int w; // next permutation of bits

unsigned int t = v | (v - 1); // t gets v's least significant 0 bits set to 1
// Next set to 1 the most significant bit to change, 
// set to 0 the least significant ones, and add the necessary 1 bits.
w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));  
```

The __builtin_ctz(v) GNU C compiler intrinsic for x86 CPUs returns the  number of trailing zeros.  If you are using Microsoft compilers for x86,  the intrinsic is _BitScanForward.  These both emit a bsf instruction, but equivalents may be available for other architectures.  If not, then  consider using one of the methods for counting the consecutive zero bits mentioned earlier.

Here is another version that tends to be slower because of its division operator, but it does not require counting the trailing zeros.

```
unsigned int t = (v | (v - 1)) + 1;  
w = t | ((((t & -t) / (v & -v)) >> 1) - 1);  
```



Thanks to Dario Sneidermanis of Argentina, who provided this on  November 28, 2009.

[ A Belorussian translation](http://webhostingrating.com/libs/bithacks-be) (provided by [Webhostingrating](http://webhostingrating.com/)) is available.

http://graphics.stanford.edu/~seander/bithacks.html