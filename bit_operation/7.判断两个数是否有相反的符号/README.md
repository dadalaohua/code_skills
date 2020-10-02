# 判断两个数是否有相反的符号

## 判断两个数是否有相反的符号 
```
int x, y;               // 待检测的两个数

bool f = ((x ^ y) < 0); // true 表示 x和y有相反的符号， false表示x，y有相同的符号。
```

***

### Detect if two integers have opposite signs



```
int x, y;               // input values to compare signs

bool f = ((x ^ y) < 0); // true iff x and y have opposite signs
```

Manfred Weis suggested I add this entry on November 26, 2009.

http://graphics.stanford.edu/~seander/bithacks.html

