# Find the log base 2 of an integer with a lookup table

### Find the log base 2 of an integer with a lookup table



```
static const char LogTable256[256] = 
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
    LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

unsigned int v; // 32-bit word to find the log of
unsigned r;     // r will be lg(v)
register unsigned int t, tt; // temporaries

if (tt = v >> 16)
{
  r = (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
}
else 
{
  r = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
}
```

The lookup table method takes only about 7 operations to find the log of a 32-bit value.  If extended for 64-bit quantities, it would take roughly  9 operations.  Another operation can be trimmed off by using four tables,  with the possible additions incorporated into each.  Using int table  elements may be faster, depending on your architecture.

The code above is tuned to uniformly distributed *output* values.   If your *inputs* are evenly distributed across all 32-bit values,  then consider using the following:

```
if (tt = v >> 24) 
{
  r = 24 + LogTable256[tt];
} 
else if (tt = v >> 16) 
{
  r = 16 + LogTable256[tt];
} 
else if (tt = v >> 8) 
{
  r = 8 + LogTable256[tt];
} 
else 
{
  r = LogTable256[v];
}
```

To initially generate the log table algorithmically:

```
LogTable256[0] = LogTable256[1] = 0;
for (int i = 2; i < 256; i++) 
{
  LogTable256[i] = 1 + LogTable256[i / 2];
}
LogTable256[0] = -1; // if you want log(0) to return -1
```

Behdad Esfahbod and I shaved off a fraction of an operation (on average) on May 18, 2005.  Yet another fraction of an operation was removed on November 14, 2006 by Emanuel Hoogeveen.  The variation that is tuned to evenly  distributed input values was suggested by David A. Butterfield on September 19, 2008.  Venkat Reddy told me on January 5, 2009 that log(0) should return -1 to indicate an error, so I changed the first entry in the table to that.

http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious