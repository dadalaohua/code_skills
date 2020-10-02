# Sign extending from a variable bit-width

### Sign extending from a variable bit-width

Sometimes we need to extend the sign of a number but we don't know a priori the number of bits, b, in which it is represented.  (Or we could be programming in a language like Java, which lacks bitfields.)  

```
unsigned b; // number of bits representing the number in x
int x;      // sign extend this b-bit number to r
int r;      // resulting sign-extended number
int const m = 1U << (b - 1); // mask can be pre-computed if b is fixed

x = x & ((1U << b) - 1);  // (Skip this if bits in x above position b are already zero.)
r = (x ^ m) - m;
```

The code above requires four operations, but when the bitwidth is a  constant rather than variable, it requires only two fast operations, assuming the upper bits are already zeroes.

A slightly faster but less portable method that doesn't depend on  the bits in x above position b being zero is:

```
int const m = CHAR_BIT * sizeof(x) - b;
r = (x << m) >> m;
```



Sean A. Irvine suggested that I add sign extension methods to this page on June 13, 2004, and he provided `m = (1 << (b - 1)) - 1; r = -(x & ~m) | x;` as a starting point from which I optimized to get  m = 1U << (b - 1); r = -(x & m) | x.   But then on May 11, 2007, Shay Green suggested the version above,  which requires one less operation than mine.  Vipin Sharma suggested I add a step to deal with situations where x had possible ones in bits  other than the b bits we wanted to sign-extend on Oct. 15, 2008. On December 31, 2009 Chris Pirazzi suggested I add the faster version,  which requires two operations for constant bit-widths and three  for variable widths.

http://graphics.stanford.edu/~seander/bithacks.html
