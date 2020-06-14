前言

我们都知道，写完了的C代码是需要编译链接之后才能运行的（也许你不需要手动点击编译，但是IDE可能帮你做了这件事），那么能不能让C代码像执行shell脚本或者Python脚本一样，直接可运行呢？类似于：

$ ./main.c
就可以直接运行了。

看起来虽然没啥用，但是感觉有点小刺激。

小试牛刀

对于文本内容，系统首先会尝试当成shell进行解释执行，这一点还不明白的朋友，建议先阅读《为什么执行命令开头需要./》。

不过话又说回来，.c最终要编译成可执行文件，如果想要它直接执行，那么就得悄悄地在这个过程中做点小动作了。我们试试把编译过程加进去：

#!/usr/bin/gcc  -o main "$0" && ./main
//main.c 公众号编程珠玑
#include<stdio.h>
int main(void)
{
    printf("hello,编程珠玑\n");
    return 0;
}
试一下：

$ ./main.c
./main.c:1:2: error: invalid preprocessing directive #!
 #!/usr/bin/gcc  -o main "$0" && ./main
诶，报错了，看起来像是GCC编译main.c的时候报错了。

仔细一想，这不太正常了吗？很明显第一行就不是C代码的合法内容啊！

再接再厉

怎么办呢？能不能把第一行既能够执行编译，又能够变成合法的C代码内容呢？
这不很简单吗？注释不就是这样的内容吗？

//usr/bin/gcc  -o main "$0" && ./main
//main.c 公众号编程珠玑
#include<stdio.h>
int main(void)
{
    printf("hello,编程珠玑\n");
    return 0;
}
嗯？还真是巧了，对于C代码来说，第一行是注释，对于shell来说，也是一个正常的路径。再试一下：

$ ./main.c
./main.c: line 2: //main.c: No such file or directory
./main.c: line 4: syntax error near unexpected token `('
./main.c: line 4: `int main(void)'
咦？怎么还是报错了？前面说到，这里的内容必须既能被shell识别，又能是合法C代码，显然第二行不符合啊。

投机取巧

很明显，除了第二行，后面的第三行，第四行都不能被当成shell正常执行。那么就果断一点好了，执行完了第一行咱就退出还不行吗？

于是，第一行变成下面这样：

//usr/bin/gcc  -o main "$0" && ./main ;exit
再来执行一下

$ ./main.c
hello,编程珠玑
实际上就达到了下面的效果：

$ gcc -o main main.c && ./main
还能更通用吗？

有人就问了，这里指定了生成文件名，而且如果程序还带了参数怎么办？
但是用//开头已经很取巧了。别忘了，C里面还有终极注释大法：

#if 0
#endif 
而且巧的是，#也是shell脚本的注释符。这就有趣了。

我们改造如下：

#if 0
proName="${0%.*}"  #去掉文件名后缀，作为程序名
gcc -o $proName "$0"
./$proName "$@"   #传入命令行参数
rm $proName
exit
#endif
//main.c 公众号编程珠玑
#include<stdio.h>
int main(void)
{
    printf("hello,编程珠玑\n");
    return 0;
}
现在再来看，是不是符合要求了：

文件名不限定
支持程序传入命令行参数
有人又要问了，如果多文件程序怎么办？

还能怎么办？makefile，cmake bazel等用起来。

总结

好了，秘密也被你知道了，现在一点都不神奇了吧！这里纯属娱乐，仅供学习其中的原理，对于编译链接成可执行程序，构建工具是一个好的选择。