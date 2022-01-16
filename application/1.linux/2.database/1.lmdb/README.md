# lmdb

lmdb是一款开源的高效快速的内存映射数据库，C语言编写，基于B+树索引，支持MVCC事务处理。它不是一个需要独立运行的数据库管理进程，只要在需要访问lmdb数据库的代码里引用lmdb库，给出数据库所在目录，就能方便地实现读写lmdb数据库。

https://github.com/LMDB/lmdb.git

https://git.openldap.org/openldap/openldap/-/tree/mdb.master/libraries

编译lmdb，生成 liblmdb.a 静态库：

```bash
git clone https://github.com/LMDB/lmdb.git
cd lmdb/libraries/liblmdb
make
```

测试程序的代码逻辑为初始化一个lmdb数据库testdb, 写入一条key-value数据，再从数据库中读出所有的key-value数据，打印输出。

https://www.jianshu.com/p/38c5cb0a64ec

LMDB通过DBI区分不同的数据库实例，支持在一个数据文件中存储多个数据库实例；
LMDB是一个轻量级的开源数据库library，常用在硬件受限的嵌入式环境，不支持SQL语句；
LMDB通过mmap将文件映射到进程的虚拟地址空间，可加速数据库的访问；
LMDB采用B+树算法存储数据，通过游标cursor可方便的访问不同位置的数据；
LMDB的数据存/取都采用c语言中通用的void类型，其类型解析由程序员自行处理，提供更大的灵活性；
https://blog.csdn.net/zhaogang1993/article/details/90612646
