#  Find the log base 2 of an N-bit integer in O(lg(N)) operations

### Find the log base 2 of an N-bit integer in O(lg(N)) operations



```
unsigned int v;  // 32-bit value to find the log2 of 
const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
const unsigned int S[] = {1, 2, 4, 8, 16};
int i;

register unsigned int r = 0; // result of log2(v) will go here
for (i = 4; i >= 0; i--) // unroll for speed...
{
  if (v & b[i])
  {
    v >>= S[i];
    r |= S[i];
  } 
}


// OR (IF YOUR CPU BRANCHES SLOWLY):

unsigned int v;	         // 32-bit value to find the log2 of 
register unsigned int r; // result of log2(v) will go here
register unsigned int shift;

r =     (v > 0xFFFF) << 4; v >>= r;
shift = (v > 0xFF  ) << 3; v >>= shift; r |= shift;
shift = (v > 0xF   ) << 2; v >>= shift; r |= shift;
shift = (v > 0x3   ) << 1; v >>= shift; r |= shift;
                                        r |= (v >> 1);


// OR (IF YOU KNOW v IS A POWER OF 2):

unsigned int v;  // 32-bit value to find the log2 of 
static const unsigned int b[] = {0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 
                                 0xFF00FF00, 0xFFFF0000};
register unsigned int r = (v & b[0]) != 0;
for (i = 4; i > 0; i--) // unroll for speed...
{
  r |= ((v & b[i]) != 0) << i;
}
```

Of course, to extend the code to find the log of a 33- to 64-bit  number, we would append another element, 0xFFFFFFFF00000000, to b, append 32 to S, and loop from 5 to 0.  This method is much slower than the earlier table-lookup version, but if you don't want big table or your architecture is slow to access memory, it's a good choice. The second variation involves slightly more operations, but it may be  faster on machines with high branch costs (e.g. PowerPC).

The second version was sent to me by  [Eric Cole](http://www.balance-software.com/ec/)  on January 7, 2006.  Andrew Shapira subsequently trimmed a few operations off of it and sent me his variation (above) on Sept. 1, 2007. The third variation was suggested to me by  [John Owens](http://www.ece.ucdavis.edu/~jowens/)  on April 24, 2002; it's faster, but  *it is only suitable when the input is known to be a power of 2*. On May 25, 2003, Ken Raeburn suggested improving the general case by  using smaller numbers for b[], which load faster on some architectures (for instance if the word size is 16 bits, then only one load instruction  may be needed).  These values work for the general version, but not for  the special-case version below it, where v is a power of 2; Glenn Slayden  brought this oversight to my attention on December 12, 2003.

http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious