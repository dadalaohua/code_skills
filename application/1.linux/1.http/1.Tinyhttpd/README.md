# tiny-httpd

简易http服务器

原版

https://sourceforge.net/projects/tinyhttpd/

注释版

https://github.com/nengm/Tinyhttpd

https://www.cnblogs.com/nengm1988/p/7816618.html

其他注释版

https://github.com/cbsheng/tinyhttpd

https://github.com/EZLippi/Tinyhttpd



使用方式

直接编译make

然后运行./httpd

本地环境下输入127.0.0.1:端口号

其他局域网内输入 ip:端口号

例如192.168.0.10:34567

可以在htdocs目录里添加html和cgi

html必须没有执行权限，否则看不到内容，例如chmod 644 index.html

cgi必须要有执行权限

不支持二进制文件
