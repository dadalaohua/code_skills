# 计算一个数里位被置1的个数 (比较差的方法) 

计算一个数里位被置1的个数 (比较差的方法) 
```
unsigned int v; // 待检测的数
unsigned int c; // 位被置1的总数
 
for (c = 0; v; v >>= 1)
{
  c += v & 1;
}
```
这个方法需要进行32次循环，效率低。 
***

### Counting bits set (naive way)



```
unsigned int v; // count the number of bits set in v
unsigned int c; // c accumulates the total bits set in v

for (c = 0; v; v >>= 1)
{
  c += v & 1;
}
```

The naive approach requires one iteration per bit, until no more bits are set.  So on a 32-bit word with only the high set, it will go through 32 iterations.

http://graphics.stanford.edu/~seander/bithacks.html