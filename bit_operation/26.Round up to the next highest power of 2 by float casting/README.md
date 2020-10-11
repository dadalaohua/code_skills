# Round up to the next highest power of 2 by float casting

### Round up to the next highest power of 2 by float casting



```
unsigned int const v; // Round this 32-bit value to the next highest power of 2
unsigned int r;       // Put the result here. (So v=3 -> r=4; v=8 -> r=8)

if (v > 1) 
{
  float f = (float)v;
  unsigned int const t = 1U << ((*(unsigned int *)&f >> 23) - 0x7f);
  r = t << (t < v);
}
else 
{
  r = 1;
}
```

The code above uses 8 operations, but works on all v <= (1<<31).

Quick and dirty version, for domain of 1 < v < (1<<25):

```
float f = (float)(v - 1);  
r = 1U << ((*(unsigned int*)(&f) >> 23) - 126);
```

Although the quick and dirty version only uses around 6 operations,  it is roughly three times slower than the  [technique below](http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2)  (which involves 12 operations) when  benchmarked on an Athlon™ XP 2100+ CPU.  Some CPUs will fare better with it, though.

On September 27, 2005 Andi Smithers suggested I include a technique  for casting to floats to find the lg of a number for rounding up to a power of 2.  Similar to the quick and dirty version here,  his version worked with values less than (1<<25), due to mantissa  rounding, but it used one more operation.

http://graphics.stanford.edu/~seander/bithacks.html