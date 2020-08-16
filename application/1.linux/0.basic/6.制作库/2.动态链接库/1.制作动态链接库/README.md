制作动态链接库

	gcc func.c -o func.o -c -fPIC
	gcc -o libfunc.so func.o -shared
    
    -fPIC 是位置无关码
    -shared 是按照共享库的方式来链接
    
    发布时需要libxxx.so和.h文件
