# **getopt_long**

getopt_long支持长选项的命令行解析, 所为长选项就是诸如`--help`的形式, 使用该函数, 需要引入`<getopt.h>`下面是函数原型:

```c
#include <getopt.h>

int getopt_long(int argc, 
                char * const argv[],
                const char *optstring,
                const struct option *longopts,
                int *longindex);

int getopt_long_only(int argc,
                    char * const argv[],
                    const char *optstring,
                    const struct option *longopts,
                    int *longindex);
```

其中 **argc** , **argv** , **optstring** 和**getopt**中的含义一样, 下面解释一下**longopts** 和**longindex**

**longopts**  

longopts 指向一个struct option 的数组, 下面是option的定义:

```c
struct option {
    const char *name;
    int         has_arg;
    int        *flag;
    int         val;
};
```

下面是各字段的含义

- **name** - 长选项的名称, 例如 `help`
- **has_arg** - 是否带参数, 0 不带参数, 1 必须带参数, 2 参数可选
- **flag** - 指定长选项如何返回结果, 如果flag为NULL, **getopt_long**() 会返回val. 如果flag不为NULL, **getopt_long**会返回0, 并且将val的值存储到flag中
- **val** - 将要被**getopt_long**返回或者存储到flag指向的变量中的值

下面是**longopts**的一个示例

```c
struct option opts[] = {
       {"version", 0, NULL, 'v'},
       {"name", 1, NULL, 'n'},
       {"help", 0, NULL, 'h'}
   };
```

我们来看`{"version", 0, NULL, 'v'}`, **version** 即为长选项的名称, 即按如下形式`--version`, **0** 表示该选项后面不带参数, **NULL** 表示直接将**v**返回(字符v在ascii码中对应的数值), 即在使用**getopt_long**遍历到该条选项时, **getopt_long** 返回值为字符v对应的ascii码值.

**longindex**  

longindex表示长选项在longopts中的位置, 例如在上面的示例中, **version** 对应的 **longindex** 为0, **name** 对应的 **longindex** 为1, **help**对应的 **longindex** 为2, 该项主要用于调试, 一般设为 NULL 即可.

下面是一个使用示例:

```c
void use_getpot_long(int argc, char *argv[]) {
    const char *optstring = "vn:h";
    int c;
    struct option opts[] = {
        {"version", 0, NULL, 'v'},
        {"name", 1, NULL, 'n'},
        {"help", 0, NULL, 'h'}
    };

    while((c = getopt_long(argc, argv, optstring, opts, NULL)) != -1) {
        switch(c) {
            case 'n':
                printf("username is %s\n", optarg);
                break;
            case 'v':
                printf("version is 0.0.1\n");
                break;
            case 'h':
                printf("this is help\n");
                break;
            case '?':
                printf("unknown option\n");
                break;
            case 0 :
                printf("the return val is 0\n");
                break;
            default:
                printf("------\n");

        }
    }
}
```

然后我们运行程序 `./test --name bob --version --help --haha`, 下面是运行结果:

```shell
username is bob
version is 0.0.1
this is help
./test: unrecognized option '--haha'
unknown option
```

当然我们也可以使用短选项 `./test -n bob -v -h`

下面我们对程序做一下修改, 这一次将 struct option 中的 **flag** 和 **longindex** 设为具体的值

```c
void use_getpot_long2(int argc, char *argv[]) {
    const char *optstring = "vn:h";
    int c;

    int f_v = -1, f_n = -1, f_h = -1, opt_index = -1; 
    struct option opts[] = {
        {"version", 0, &f_v, 'v'},
        {"name", 1, &f_n, 'n'},
        {"help", 0, &f_h, 'h'}
    };

    while((c = getopt_long(argc, argv, optstring, opts, &opt_index)) != -1) {
        switch(c) {
            case 'n':
                printf("username is %s\n", optarg);
                break;
            case 'v':
                printf("version is 0.0.1\n");
                break;
            case 'h':
                printf("this is help\n");
                break;
            case '?':
                printf("unknown option\n");
                break;
            case 0 :
                printf("f_v is %d \n", f_v);
                printf("f_n is %d \n", f_n);
                printf("f_h is %d \n", f_h);
                break;
            default:
                printf("------\n");
        }
        printf("opt_index is %d\n\n", opt_index);
    }
}
```

运行程序: `./test --name zhangjikai --version --help` , 下面是运行结果:

```shell
f_v is -1 
f_n is 110 
f_h is -1 
opt_index is 1

f_v is 118 
f_n is 110 
f_h is -1 
opt_index is 0

f_v is 118 
f_n is 110 
f_h is 104 
opt_index is 2
```

我们可以看到当给 **flag** 指定具体的指针之后, **getopt_long** 会返回0, 因此会去执行case 0, 并且 **val** 的值赋给了 **flag** 指向的变量. 下面我们用短选项执行一下程序 `./test -n bob -v -h`, 下面是运行结果

```shell
username is bob
opt_index is -1

version is 0.0.1
opt_index is -1

this is help
opt_index is -1
```

我们看到使用短选项的时候 **getopt_long** 就相当于 **getopt** , **flag** 和 **longindex**都不起作用了. 

### getopt_long 和 getopt_long_only

下面解释一下 **getopt_long** 和 **getopt_long_only**的区别, 首先用下列选项运行一下 **use_getopt_long**  `./test -name zhangjkai -version -help` , 下面是输出结果:

```shell
username is ame
version is 0.0.1
./test: invalid option -- 'e'
unknown option
./test: invalid option -- 'r'
unknown option
./test: invalid option -- 's'
unknown option
./test: invalid option -- 'i'
unknown option
./test: invalid option -- 'o'
unknown option
username is -help
```

我们看到使用短选项标识符 `-` 指向长选项时, 程序还是会按短选项来处理, 即一个字符一个字符的解析. 下面我们将 **use_getopt_long** 做一下更改, 即将 `getopt_long` 改为 `getopt_long_only` , 如下所示:

```c
void use_getpot_long3(int argc, char *argv[]) {
    const char *optstring = "vn:h";
    int c;
    struct option opts[] = {
        {"version", 0, NULL, 'v'},
        {"name", 1, NULL, 'n'},
        {"help", 0, NULL, 'h'}
    };

    while((c = getopt_long_only(argc, argv, optstring, opts, NULL)) != -1) {
        switch(c) {
            case 'n':
                printf("username is %s\n", optarg);
                break;
            case 'v':
                printf("version is 0.0.1\n");
                break;
            case 'h':
                printf("this is help\n");
                break;
            case '?':
                printf("unknown option\n");
                break;
            case 0 :
                printf("the return val is 0\n");
                break;
            default:
                printf("------\n");

        }
    }
}
```

下面再运行程序 `./test -name bob -version -help` , 下面是运行结果:

```shell
username is bob
version is 0.0.1
this is help
```

即使用 **getopt_long_only** 时, `-` 和 `--`都可以作用于长选项, 而使用 **getopt_long** 时, 只有 `--`可以作用于长选项.