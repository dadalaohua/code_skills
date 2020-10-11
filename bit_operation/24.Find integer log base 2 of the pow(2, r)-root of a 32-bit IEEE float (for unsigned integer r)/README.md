# Find integer log base 2 of the pow(2, r)-root of a 32-bit IEEE float  (for unsigned integer r)

### Find integer log base 2 of the pow(2, r)-root of a 32-bit IEEE float  (for unsigned integer r)



```
const int r;
const float v; // find int(log2(pow((double) v, 1. / pow(2, r)))), 
               // where isnormal(v) and v > 0
int c;         // 32-bit int c gets the result;

c = *(const int *) &v;  // OR, for portability:  memcpy(&c, &v, sizeof c);
c = ((((c - 0x3f800000) >> r) + 0x3f800000) >> 23) - 127;
```

So, if r is 0, for example, we have c = int(log2((double) v)).   If r is 1, then we have c = int(log2(sqrt((double) v))). If r is 2, then we have c = int(log2(pow((double) v, 1./4))).

On June 11, 2005, Falk Hüffner pointed out that  ISO C99 6.5/7 left the type punning idiom *(int *)& undefined, and he suggested using memcpy. 

http://graphics.stanford.edu/~seander/bithacks.html