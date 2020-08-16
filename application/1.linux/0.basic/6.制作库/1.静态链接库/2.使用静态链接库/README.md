使用静态链接库

gcc -o test_code test_code.c -lfunc -L.
1.当使用-lxxx的时候，连接器试图在默认的链接库路径去寻找libxxx.a
    这里使用lfunc，就会去寻找libfunc.a
2.-L是指定链接器在哪个目录下寻找库文件，点.表示当前目录
