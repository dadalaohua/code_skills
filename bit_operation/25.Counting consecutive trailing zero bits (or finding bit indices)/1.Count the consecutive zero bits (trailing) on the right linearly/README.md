# Count the consecutive zero bits (trailing) on the right linearly

### Count the consecutive zero bits (trailing) on the right linearly



```
unsigned int v;  // input to count trailing zero bits
int c;  // output: c will count v's trailing zero bits,
        // so if v is 1101000 (base 2), then c will be 3
if (v)
{
  v = (v ^ (v - 1)) >> 1;  // Set v's trailing 0s to 1s and zero rest
  for (c = 0; v; c++)
  {
    v >>= 1;
  }
}
else
{
  c = CHAR_BIT * sizeof(v);
}
```

The average number of trailing zero bits in a (uniformly distributed)  random binary number is one, so this O(trailing zeros) solution isn't  that bad compared to the faster methods below.

Jim Cole suggested I add a linear-time method for counting the trailing zeros on August 15, 2007.  On October 22, 2007, Jason Cunningham pointed out that I had neglected to paste the unsigned modifier for v.

http://graphics.stanford.edu/~seander/bithacks.html