# 计算一个数里位被置1的个数 (普通方法) 

```
unsigned int v; // count the number of bits set in v
                // 计算变量v的二进制中1的个数
unsigned int c; // c accumulates the total bits set in v
                // 保存计算的结果

for (c = 0; v; v >>= 1)
{
  c += v & 1;
}
```
这个简单算法对于每一位都需要一次操作，直到结束。所以对于32位字长，且只有最高位为1时（即最坏情况），这个算法会操作32次。
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