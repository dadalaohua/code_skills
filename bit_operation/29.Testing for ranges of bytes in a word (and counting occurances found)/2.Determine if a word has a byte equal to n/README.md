# Determine if a word has a byte equal to n

### Determine if a word has a byte equal to n

We may want to know if any byte in a word has a specific value.  To do so, we can XOR the value to test with a word that has been filled with the  byte values in which we're interested.  Because XORing a value with itself results in a zero byte and nonzero otherwise, we can pass the result to  `haszero`.

```
#define hasvalue(x,n) \
(haszero((x) ^ (~0UL/255 * (n))))
```



Stephen M Bennet suggested this on December 13, 2009 after reading the entry for `haszero`.

http://graphics.stanford.edu/~seander/bithacks.html