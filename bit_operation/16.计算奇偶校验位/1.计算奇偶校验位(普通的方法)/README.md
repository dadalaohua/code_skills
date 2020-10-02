# 计算奇偶校验位(普通的方法) 

计算奇偶校验位(普通的方法) 
```
unsigned int v;       // 要被计算的数
bool parity = false;  // 结果
 
while (v)
{
  parity = !parity;
  v = v & (v - 1);
}
```
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