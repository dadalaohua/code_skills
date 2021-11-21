# 为结构体每个成员初始化成0

https://blog.csdn.net/weidaocc/article/details/110929207

Reference C99 Standard 6.7.8.21:

```
If there are fewer initializers in a brace-enclosed list than there are elements or members of an aggregate,

or fewer characters in a string literal used to initialize an array of known size than there are elements in the array,

the remainder of the aggregate shall be initialized implicitly the same as objects that have static storage duration.
```



每个成功员初始为0的4种方法

```c
struct A = {0};
struct A = {};
memset(&A, 0, sizeof(struct ));
A= (struct){ 0 } // c99 中 compound literal
```



其他资料

https://stackoverflow.com/questions/63355760/how-standard-is-the-0-initializer-in-c89
