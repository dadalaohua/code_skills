# 判断两个数是否有相反的符号

## 判断两个数是否有相反的符号 
```
int x, y;               // input values to compare signs
                        // 输入的数值放在变量x和y中，用于比较符号
bool f = ((x ^ y) < 0); // true iff x and y have opposite signs
                        // 当且仅当(iff) x和y的符号相反时返回true
```
2009年11月26日，Manfred Weis建议我加入这一条内容。
***

### Detect if two integers have opposite signs



```
int x, y;               // input values to compare signs

bool f = ((x ^ y) < 0); // true iff x and y have opposite signs
```

Manfred Weis suggested I add this entry on November 26, 2009.

http://graphics.stanford.edu/~seander/bithacks.html

