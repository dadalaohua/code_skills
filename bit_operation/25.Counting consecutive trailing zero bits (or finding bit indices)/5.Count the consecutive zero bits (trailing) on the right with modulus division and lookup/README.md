# Count the consecutive zero bits (trailing) on the right with modulus division and lookup

### Count the consecutive zero bits (trailing) on the right with modulus division and lookup



```
unsigned int v;  // find the number of trailing zeros in v
int r;           // put the result in r
static const int Mod37BitPosition[] = // map a bit value mod 37 to its position
{
  32, 0, 1, 26, 2, 23, 27, 0, 3, 16, 24, 30, 28, 11, 0, 13, 4,
  7, 17, 0, 25, 22, 31, 15, 29, 10, 12, 6, 0, 21, 14, 9, 5,
  20, 8, 19, 18
};
r = Mod37BitPosition[(-v & v) % 37];
```

The code above finds the number of zeros that are trailing on the right, so binary 0100 would produce 2.  It makes use of the fact that the first 32 bit position values are relatively prime with 37, so performing a modulus  division with 37 gives a unique number from 0 to 36 for each.  These numbers may then be mapped to the number of zeros using a small lookup table.   It uses only 4 operations, however indexing into a table and performing modulus division may make it unsuitable for some situations. I came up with this independently and then searched for a subsequence of  the table values, and found it was invented earlier by Reiser, according to  [Hacker's Delight](http://www.hackersdelight.org/HDcode/ntz.c.txt).

http://graphics.stanford.edu/~seander/bithacks.html