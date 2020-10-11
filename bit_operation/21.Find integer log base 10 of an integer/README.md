# Find integer log base 10 of an integer

### Find integer log base 10 of an integer



```
unsigned int v; // non-zero 32-bit integer value to compute the log base 10 of 
int r;          // result goes here
int t;          // temporary

static unsigned int const PowersOf10[] = 
    {1, 10, 100, 1000, 10000, 100000,
     1000000, 10000000, 100000000, 1000000000};

t = (IntegerLogBase2(v) + 1) * 1233 >> 12; // (use a lg2 method from above)
r = t - (v < PowersOf10[t]);
```

The integer log base 10 is computed by first using one of the techniques above  for finding the log base 2.  By the relationship  log10(v) = log2(v) / log2(10), we need to multiply it by 1/log2(10), which is approximately 1233/4096, or 1233 followed by a right shift of 12.  Adding one is needed because the IntegerLogBase2 rounds down.  Finally, since the value t is only an  approximation that may be off by one, the exact value is found by  subtracting the result of v < PowersOf10[t].

This method takes 6 more operations than IntegerLogBase2.  It may be sped up (on machines with fast memory access) by modifying the log base 2 table-lookup method above so that the entries hold what is computed for t (that is, pre-add, -mulitply, and -shift). Doing so would require a total of only 9 operations to find the log base 10, assuming 4 tables were used (one for each byte of v).

Eric Cole suggested I add a version of this on January 7, 2006.

http://graphics.stanford.edu/~seander/bithacks.html