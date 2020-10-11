# **计算模除 模数是** `1<<s` **时 没有除法**
```c
const unsigned int n;          // numerator
                               // 变量n为分子（被模除的数）
const unsigned int s;
const unsigned int d = 1U << s; // So d will be one of: 1, 2, 4, 8, 16, 32, ...
                                // 那么变量d从小到大依次为:1, 2, 4, 8, 16, 32, ...
unsigned int m;                // m will be n % d
                               // m保存n%d的结果
m = n & (d - 1);
```
这个技巧大多数程序员都会，为了保持完整性，这里还是把这个技巧放在了这里。

***

### Compute modulus division by 1 << s without a division operator



```
const unsigned int n;          // numerator
const unsigned int s;
const unsigned int d = 1U << s; // So d will be one of: 1, 2, 4, 8, 16, 32, ...
unsigned int m;                // m will be n % d
m = n & (d - 1); 
```

Most programmers learn this trick early, but it was included for the  sake of completeness.

http://graphics.stanford.edu/~seander/bithacks.html