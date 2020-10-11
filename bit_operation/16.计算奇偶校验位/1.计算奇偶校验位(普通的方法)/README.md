# 计算奇偶校验位(普通的方法) 

```
unsigned int v;       // word value to compute the parity of
                      // 需要计算的值保存在变量v中
bool parity = false;  // parity will be the parity of v
                      // 变量parity保存v的奇偶校验位
while (v)
{
  parity = !parity;
  v = v & (v - 1);
}
```
上面这段代码实现使用了类似Brian Kernigan的统计二进制位中1个数的方法。二进制中有多少个1，这个算法就会计算多少次。
***

### Computing parity the naive way

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