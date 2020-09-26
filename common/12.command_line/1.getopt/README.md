# **getopt**

getopt主要用来处理短命令行选项, 例如`./test -v`中`-v`就是一个短选项. 使用该函数需要引入头文件`<unistd.h>`, 下面是该函数的定义

```c
int getopt(int argc, char * const argv[], const char * optstring);
```

其中 argc 和 argv 是main函数中的传递的参数个数和内容, optstring用来指定可以处理哪些选项, 下面是optstring的一个示例:

```c
"a:bc"
```

该示例表明程序可以接受3个选项: `-a -b -c`, 其中 `a` 后面的 `:`表示该选项后面要跟一个参数, 即如 `-a text`的形式, 选项后面跟的参数会被保存到 optarg 变量中。



下面是一个使用示例:

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int ch;
    while((ch = getopt(argc, argv, "a:b")) != -1) {
        switch(ch) {
            case 'a':
                printf("option a: %s\n", optarg);
                break;
            case 'b':
                printf("option b \n");
                break;
            case '?': // 输入未定义的选项, 都会将该选项的值变为 ?
                printf("unknown option \n");
                break;
            default:
                printf("default \n");
        }
    }
}
```

执行 `./test -a aa -b -c` 输出结果如下:

```shell
option a: aa
option b 
unknown option
```