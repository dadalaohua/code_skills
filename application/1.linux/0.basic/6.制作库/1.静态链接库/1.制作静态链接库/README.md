制作静态链接库

	gcc func.c -o func.o -c
	ar -rc libfunc.a func.o
    
    使用gcc -c只编译不链接，生成.o文件。然后使用ar工具打包成.a归档文件
    库命不能乱起，一般是lib+库名称，后缀名是.a表示是一个归档文件
    
    发布时需要发布.a文件和.h文件
