# bsearch, bsearch_s

| 定义于头文件 `<stdlib.h>`                                    |      |          |
| ------------------------------------------------------------ | ---- | -------- |
| void* bsearch( const void *key, const void *ptr, [size_t](http://zh.cppreference.com/w/c/types/size_t) count, [size_t](http://zh.cppreference.com/w/c/types/size_t) size,  int (*comp)(const void*, const void*) ); | (1)  |          |
| void* bsearch_s( const void *key, const void *ptr, rsize_t count, rsize_t size, int (*comp)(const void *, const void *, void *),          void *context ); | (2)  | (C11 起) |
|                                                              |      |          |

1) 在 `ptr` 所指向的数组中寻找等于 `key` 所指向的元素。该数组含 `count` 个大小为 `size` 字节的元素，并且已相对于 `key` 划分，也就是说，所有比较小于关键目标的元素必须出现于所有比较等于的元素之前，而且所有比较等于关键目标的元素要出现于所有比较大于关键目标的元素之前。完全排序的数组满足这些要求。用 `comp` 所指向的函数比较元素。若数组未依照与 `comp` 标准相同的相对于 `*key` 的升序划分，则行为未定义。

2) 同 (1) ，除了传递给 `comp` 附加环境参数 `context` ，并在运行时检测下列错误，并调用当前安装的[制约处理](https://zh.cppreference.com/w/c/error/set_constraint_handler_s)函数：



若数组包含数个 `comp` 指示为与欲查找元素相等的元素，则结果返回的具体元素是未指定的。

### 参数

| key     | -    | 指向要查找的元素的指针                                       |
| ------- | ---- | ------------------------------------------------------------ |
| ptr     | -    | 指向要检验的数组的指针                                       |
| count   | -    | 数组的元素数目                                               |
| size    | -    | 数组每个元素的字节数                                         |
| comp    | -    | 比较函数。若首个参数*小于*第二个，则返回负整数值，若首个参数*大于*第二个，则返回正整数值，若两参数等价，则返回零。 将 `key` 传给首个参数，数组中的元素传给第二个。 比较函数的签名应等价于如下形式： int cmp(const void *a, const void *b);该函数必须不修改传递给它的对象，而且在调用比较相同对象时必须返回一致的结果，无关乎它们在数组中的位置。 |
| context | -    | 附加信息（例如，对照序列），作为第三个参数传递给 `comp`      |

### 返回值

1) 指向与 *key 比较相等的指针，在找不到元素时返回空指针。

2) 同 (1) ，除了在运行时制约违规时也返回空指针。

### 注意

与名称无关， C 和 POSIX 标准都未要求此函数用二分查找实现，也未保证任何复杂度。

与其他检查边界的函数不同， `bsearch_s` 不将零大小数组视作运行时制约违规，而是指出找不到元素（另一个接受零大小数组的函数是 qsort_s ）。

在 `bsearch_s` 之前， `bsearch` 的用户通常用全局变量传递比较函数的附加语环境。

### 示例

运行此代码

```
#include <stdlib.h>
#include <stdio.h>
 
struct data {
    int nr;
    char const *value;
} dat[] = {
    {1, "Foo"}, {2, "Bar"}, {3, "Hello"}, {4, "World"}
};
 
int data_cmp(void const *lhs, void const *rhs) 
{
    struct data const *const l = lhs;
    struct data const *const r = rhs;
 
    if (l->nr < r->nr) return -1;
    else if (l->nr > r->nr) return 1;
    else return 0;
 
    // return (l->nr > r->nr) - (l->nr < r->nr); // 可行的简洁写法
    // return l->nr - r->nr; // 错误的简洁写法（若给出 INT_MIN 就会失败）
}
 
int main(void) 
{
    struct data key = { .nr = 3 };
    struct data const *res = bsearch(&key, dat, sizeof dat / sizeof dat[0],
                                     sizeof dat[0], data_cmp);
    if (res) {
        printf("No %d: %s\n", res->nr, res->value);
    } else {
        printf("No %d not found\n", key.nr);
    }
}
```

输出：

```
No 3: Hello
```

### 引用

- C11 standard (ISO/IEC 9899:2011):

- - 7.22.5.1 The bsearch function (p: 355)

- - K.3.6.3.1 The bsearch_s function (p: 608-609)

- C99 standard (ISO/IEC 9899:1999):

- - 7.20.5.1 The bsearch function (p: 318-319)

- C89/C90 standard (ISO/IEC 9899:1990):

- - 4.10.5.1 The bsearch function
