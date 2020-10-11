# Count the consecutive zero bits (trailing) on the right by casting to a float

### Count the consecutive zero bits (trailing) on the right by casting to a float



```
unsigned int v;            // find the number of trailing zeros in v
int r;                     // the result goes here
float f = (float)(v & -v); // cast the least significant bit in v to a float
r = (*(uint32_t *)&f >> 23) - 0x7f;
```

Although this only takes about 6 operations, the time to convert an integer to a float can be high on some machines.   The exponent of the 32-bit IEEE floating point  representation is shifted down, and the bias is subtracted to give the position of the least significant 1 bit set in v. If v is zero, then the result is -127. 

http://graphics.stanford.edu/~seander/bithacks.html