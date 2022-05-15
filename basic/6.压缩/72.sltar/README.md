# sltar

https://github.com/Gottox/sltar

Minimal implementation of tar.

tar 的最小实现。

打包

将 Makefile 文件打包到 hello.tar 中

./sltar c Makefile >hello.tar

或者

./sltar c Makefile 1>hello.tar



解包

将 hello.tar 解包

./sltar x <hello.tar

或者

./sltar x 0<hello.tar



打印出 hello.tar 包内的文件

./sltar t <hello.tar