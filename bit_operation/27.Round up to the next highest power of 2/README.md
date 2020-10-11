# Round up to the next highest power of 2

### Round up to the next highest power of 2



```
unsigned int v; // compute the next highest power of 2 of 32-bit v

v--;
v |= v >> 1;
v |= v >> 2;
v |= v >> 4;
v |= v >> 8;
v |= v >> 16;
v++;
```

In 12 operations, this code computes the next highest power of 2 for a  32-bit integer. The result may be expressed by the formula 1U << (lg(v - 1) + 1).   Note that in the edge case where v is 0, it returns 0, which isn't a power of 2; you might append the expression v += (v == 0) to remedy this if it matters. It would be faster by 2 operations to use the formula and the  log base 2 method that uses a lookup table,  but in some situations, lookup tables are not suitable, so the above code may be best.  (On a Athlon™ XP 2100+ I've found the above shift-left  and then OR code is as fast as using a single BSR assembly language  instruction, which scans in reverse to find the highest set bit.) It works by copying the highest set bit to all of the lower  bits, and then adding one, which results in carries that set all of the lower bits to 0 and one bit beyond the highest set bit to 1.  If the original number was a power of 2, then the decrement will reduce it to one less, so that we round up to the same original value.

You might alternatively compute the next higher power of 2  in only 8 or 9 operations using a lookup table for  floor(lg(v)) and then evaluating 1<<(1+floor(lg(v)));  Atul Divekar suggested I mention this on September 5, 2010.

Devised by Sean Anderson, Sepember 14, 2001.   Pete Hart  pointed me to  [a  couple newsgroup posts](http://groups.google.com/group/comp.lang.python/browse_thread/thread/c4d3aae0df917df5/6fdae3872f9de79d?lnk=st&q=comp.lang.python+zeddy&rnum=6#6fdae3872f9de79d) by him and William Lewis in February of 1997, where they arrive at the same algorithm.

http://graphics.stanford.edu/~seander/bithacks.html