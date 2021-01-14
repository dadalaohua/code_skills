# 计算奇偶性(普通的方法) 
如果设置了奇数位数，则为1，否则为0
```
unsigned int v;       // word value to compute the parity of
                      // 计算奇偶性的数值
bool parity = false;  // parity will be the parity of v
                      // 变量parity保存v的奇偶性
while (v)
{
  parity = !parity;
  v = v & (v - 1);
}
```
上面这段代码实现使用了类似Brian Kernigan的统计二进制位中1个数的方法。二进制中有多少个1，这个算法就会计算多少次。
***

### Computing parity the naive way
(1 if an odd number of bits set, 0 otherwise) 
```
unsigned int v;       // word value to compute the parity of
bool parity = false;  // parity will be the parity of v

while (v)
{
  parity = !parity;
  v = v & (v - 1);
}
```

The above code uses an approach like Brian Kernigan's bit counting, above.   The time it takes is proportional to the number of bits set.

http://graphics.stanford.edu/~seander/bithacks.html