使用动态链接库

gcc -o test_code test_code.c -lfunc -L.
1.当使用-lxxx的时候，连接器试图在默认的链接库路径去寻找libxxx.so
    这里使用lfunc，就会去寻找libfunc.so
2.-L是指定链接器在哪个目录下寻找库文件，点.表示当前目录

测试程序可以编译成功，但运行会出错，错误信息如下
./test_code: error while loading shared libraries: libfunc.so: cannot open shared object file: No such file or directory
错误原因：动态链接库运行时需要被加载
运行时环境在执行test程序的时候发现动态链接了libfunc.so，于是会去固定目录尝试加载libfunc.so，如果加载失败则会输出以上错误信息

解决方法一：将libfunc.so放到固定目录下就可以了，这个固定目录一般是/usr/lib目录

解决方法二：使用环境变量LD_LIBRARY_PATH。操作系统在加载固定目录前，会先去LD_LIBRARY_PATH这个环境变量所指定的目录去寻找，如果没找到再去/usr/lib目录
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/work/code/code_skills/application/1.linux/0.basic/6.制作库/2.动态链接库/2.使用动态链接库
    
ldd 命令
解析使用了哪些动态库

ldd test_code
        linux-gate.so.1 =>  (0xb77a0000)
        libfunc.so => not found
        libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xb75e4000)
        /lib/ld-linux.so.2 (0xb77a1000)
        
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/work/code/code_skills/application/1.linux/0.basic/6.制作库/2.动态链接库/2.使用动态链接库
    
ldd test_code
        linux-gate.so.1 =>  (0xb7710000)
        libfunc.so (0xb770b000)
        libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xb7551000)
        /lib/ld-linux.so.2 (0xb7711000)