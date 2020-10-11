# Count the consecutive zero bits (trailing) on the right by binary search

### Count the consecutive zero bits (trailing) on the right by binary search



```
unsigned int v;     // 32-bit word input to count zero bits on right
unsigned int c;     // c will be the number of zero bits on the right,
                    // so if v is 1101000 (base 2), then c will be 3
// NOTE: if 0 == v, then c = 31.
if (v & 0x1) 
{
  // special case for odd v (assumed to happen half of the time)
  c = 0;
}
else
{
  c = 1;
  if ((v & 0xffff) == 0) 
  {  
    v >>= 16;  
    c += 16;
  }
  if ((v & 0xff) == 0) 
  {  
    v >>= 8;  
    c += 8;
  }
  if ((v & 0xf) == 0) 
  {  
    v >>= 4;
    c += 4;
  }
  if ((v & 0x3) == 0) 
  {  
    v >>= 2;
    c += 2;
  }
  c -= v & 0x1;
}	
```

The code above is similar to the previous method, but it computes the number of trailing zeros by accumulating c in a manner akin to binary search. In the first step, it checks if the bottom 16 bits of v are zeros,  and if so, shifts v right 16 bits and adds 16 to c, which reduces the  number of bits in v to consider by half.  Each of the subsequent  conditional steps likewise halves the number of bits until there is only 1. This method is faster than the last one (by about 33%) because the bodies  of the if statements are executed less often.

Matt Whitlock suggested this on January 25, 2006.  Andrew Shapira shaved a couple operations off on Sept. 5, 2007 (by setting c=1 and unconditionally subtracting at the end).

http://graphics.stanford.edu/~seander/bithacks.html