# Find the integer log base 2 of an integer with an 64-bit IEEE float

### Find the integer log base 2 of an integer with an 64-bit IEEE float



```
int v; // 32-bit integer to find the log base 2 of
int r; // result of log_2(v) goes here
union { unsigned int u[2]; double d; } t; // temp

t.u[__FLOAT_WORD_ORDER==LITTLE_ENDIAN] = 0x43300000;
t.u[__FLOAT_WORD_ORDER!=LITTLE_ENDIAN] = v;
t.d -= 4503599627370496.0;
r = (t.u[__FLOAT_WORD_ORDER==LITTLE_ENDIAN] >> 20) - 0x3FF;
```

The code above loads a 64-bit (IEEE-754 floating-point) double with  a 32-bit integer (with no paddding bits) by storing the integer in the  mantissa while the exponent is set to 252.   From this newly minted double, 252 (expressed as a double) is subtracted, which sets the  resulting exponent to the log base 2 of the input value, v.  All that is  left is shifting the exponent bits into position (20 bits right) and  subtracting the bias, 0x3FF (which is 1023 decimal).  This technique only takes 5 operations, but many CPUs are slow at manipulating doubles,  and the endianess of the architecture must be accommodated.

Eric Cole sent me this on January 15, 2006.  Evan Felix pointed out a typo on April 4, 2006.  Vincent Lefèvre told me on July 9, 2008 to  change the endian check to use the float's endian, which could differ from the integer's endian.

http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious