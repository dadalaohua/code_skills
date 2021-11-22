

```c
#define _GNU_SOURCE
#include <string.h>
char *strcasestr(const char *haystack, const char *needle);
```

strcasestr函数在"子串"与"父串"进行比较的时候，"不区分大小写"

在字符串string中查找strSearch子串.  返回子串strSearch在string中首次出现位置的指针. 如果没有找到子串strSearch, 则返回NULL. 如果子串strSearch为空串, 函数返回string值. 



如果在编程时没有定义**"_GNU_SOURCE"**宏，则编译的时候会有警告信息

```
warning: initialization makes pointer from integer without a cast
```

原因：

```
strcasestr函数并非是标准C库函数，是扩展函数。函数在调用之前未经声明的默认返回int型
```

解决：

```
要在#include所有头文件之前加  #define _GNU_SOURCE   
```

**另一种解决方法：(但是不推荐)**

在定义头文件下方，自己手动添加strcasestr函数的原型声明

```
#include <stdio.h>
... ...
extern char *strcasestr(const char *, const char *);
... ...         // 这种方法也能消除编译时的警告信息
```
