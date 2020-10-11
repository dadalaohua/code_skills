# Find integer log base 2 of a 32-bit IEEE float 

### Find integer log base 2 of a 32-bit IEEE float 



```
const float v; // find int(log2(v)), where v > 0.0 && finite(v) && isnormal(v)
int c;         // 32-bit int c gets the result;

c = *(const int *) &v;  // OR, for portability:  memcpy(&c, &v, sizeof c);
c = (c >> 23) - 127;
```

The above is fast, but IEEE 754-compliant architectures utilize  *subnormal* (also called *denormal*)  floating point numbers.  These have the exponent bits set to zero  (signifying pow(2,-127)),  and the mantissa is not normalized, so it contains leading zeros and thus the log2 must be computed from the mantissa.  To accomodate for subnormal numbers, use the following:

```
const float v;              // find int(log2(v)), where v > 0.0 && finite(v)
int c;                      // 32-bit int c gets the result;
int x = *(const int *) &v;  // OR, for portability:  memcpy(&x, &v, sizeof x);

c = x >> 23;          

if (c)
{
  c -= 127;
}
else
{ // subnormal, so recompute using mantissa: c = intlog2(x) - 149;
  register unsigned int t; // temporary
  // Note that LogTable256 was defined earlier
  if (t = x >> 16)
  {
    c = LogTable256[t] - 133;
  }
  else
  {
    c = (t = x >> 8) ? LogTable256[t] - 141 : LogTable256[x] - 149;
  }
}
```

On June 20, 2004, Sean A. Irvine suggested that I include code to handle subnormal numbers.  On June 11, 2005, Falk Hüffner pointed out that  ISO C99 6.5/7 specified undefined behavior for the common type punning idiom  *(int *)&, though it has worked on 99.9% of C compilers.   He proposed using memcpy for maximum portability or a union with a float and an int for better code generation than memcpy on some compilers.

http://graphics.stanford.edu/~seander/bithacks.html