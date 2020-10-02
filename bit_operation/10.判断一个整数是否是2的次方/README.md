# 判断一个整数是否是2的次方 

## 判断一个整数是否是2的次方 

```
unsigned int v; //待检测的数
bool f;         // 结果 

f = (v & (v - 1)) == 0;
```
这里要注意，0不能正确识别为2的次方,为了克服这个，可以用下面的方法
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
