# 倒序输出参数



```c
#include <stdio.h>
int main(void)   
{

    printf ( "%4$d  %3$d  %2$d  %1$d ",  1,  2,  3,  4);    
    return 0;
}
```

输出结果：

```
4 3 2 1
```