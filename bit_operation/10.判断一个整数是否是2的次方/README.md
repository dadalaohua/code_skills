# 判断一个整数是否是2的次方 

```
unsigned int v; // we want to see if v is a power of 2
                // 判断变量v是否是2的次幂
bool f;         // the result goes here
                // 结果保存在这里

f = (v & (v - 1)) == 0;
```
请注意，这里错误地认为0是2的幂。要解决此问题，请使用： 
```
f = v && !(v & (v - 1));
```

***

### Determining if an integer is a power of 2

```
unsigned int v; // we want to see if v is a power of 2
bool f;         // the result goes here 

f = (v & (v - 1)) == 0;
```

Note that 0 is incorrectly considered a power of 2 here.  To remedy this, use:

```
f = v && !(v & (v - 1));
```

http://graphics.stanford.edu/~seander/bithacks.html
