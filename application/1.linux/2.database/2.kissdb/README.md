# kissdb

https://github.com/adamierymenko/kissdb

(Keep It) Simple Stupid Database

(保持)简单而愚蠢的数据库

KISSDB is about the simplest key/value store you'll ever see, anywhere. It's written in plain vanilla C using only the standard string and FILE I/O functions, and should port to just about anything with a disk or something that acts like one.

KISSDB 是关于你将在任何地方看到的最简单的键/值存储。它是用普通的 C 语言编写的，只使用标准的字符串和 FILE I/O 函数，并且应该移植到几乎任何带有磁盘或类似磁盘的东西。

It stores keys and values of fixed length in a stupid-simple file format based on fixed-size hash tables. If a hash collision occurrs, a new "page" of hash table is appended to the database. The format is append-only. There is no delete. Puts that replace an existing value, however, will not grow the file as they will overwrite the existing entry.

它基于固定大小的哈希表以愚蠢的简单文件格式存储固定长度的键和值。如果发生哈希冲突，则将哈希表的新“页面”附加到数据库中。格式是仅附加的。没有删除。但是，替换现有值的放置不会增大文件，因为它们会覆盖现有条目。

Hash table size is a space/speed trade-off parameter. Larger hash tables will reduce collisions and speed things up a bit, at the expense of memory and disk space. A good size is usually about 1/2 the average number of entries you expect.

哈希表大小是空间/速度权衡参数。较大的哈希表将减少冲突并加快速度，但会占用内存和磁盘空间。一个好的大小通常是您期望的平均条目数的 1/2。

Features:

- Tiny, compiles to ~4k on an x86_64 Linux system
- 很小，在 x86_64 Linux 系统上编译到 ~4k
- Small memory footprint (only caches hash tables)
- 内存占用小（仅缓存哈希表）
- Very space-efficient (on disk) if small hash tables are used
- 如果使用小型哈希表，则非常节省空间（在磁盘上）
- Makes a decent effort to be robust on power loss
- 在电力损耗方面做了很大的努力
- Pretty respectably fast, especially given its simplicity
- 相当快，特别是考虑到它的简单性
- 64-bit, file size limit is 2^64 bytes
- 64 位，文件大小限制为 2^64 字节
- Ports to anything with a C compiler and stdlib/stdio
- 使用 C 编译器和 stdlib/stdio 移植到任何东西
- Public domain
- 公共区域

Limitations:

- Fixed-size keys and values, must recreate and copy to change any init size parameter
- 固定大小的键和值，必须重新创建和复制以更改任何初始大小参数
- Add/update only, no delete
- 仅添加/更新，不删除
- Iteration is supported but key order is undefined
- 支持迭代，但键顺序未定义
- No search for subsets of keys/values
- 不搜索键/值的子集
- No indexes
- 没有索引
- No transactions
- No special recovery features if a database gets corrupted
- 如果数据库损坏，没有特殊的恢复特性
- No built-in thread-safety (guard it with a mutex in MT code)
- 没有内置线程安全（在 MT 代码中使用互斥锁保护它）
- No built-in caching of data (only hash tables are cached for lookup speed)
- 没有内置的数据缓存（仅缓存哈希表以提高查找速度）
- No endian-awareness (currently), so big-endian DBs won't read on little-endian machines
- 没有字节序意识（当前），所以大字节序数据库不会在小字节序机器上读取

Alternative key/value stores and embedded databases:

替代键/值存储和嵌入式数据库：

- [MDB](http://symas.com/mdb/) uses mmap() and is very fast (not quite as tiny/simple/portable)
- MDB 使用 mmap() 并且非常快（不那么小/简单/便携）
- [CDB](http://cr.yp.to/cdb.html) is also minimal and fast, probably the closest thing to this (but has a 4gb size limit)
- CDB 也是最小且快速的，可能是最接近这个的（但有 4gb 的大小限制）
- [Kyoto Cabinet](http://fallabs.com/kyotocabinet/) is very fast, full-featured, and modern (license required for commercial use)
- Kyoto Cabinet非常快速，功能齐全，现代（商业使用需要许可证）
- [SQLite](http://www.sqlite.org/) gives you a complete embedded SQL server (public domain, very mature, much larger)
- SQLite 给你一个完整的嵌入式 SQL 服务器（公共领域，非常成熟，更大）
- Others include GDBM, NDBM, Berkeley DB, etc. Use your Googles. :)
- 其他包括 GDBM、NDBM、Berkeley DB 等。使用你的谷歌。 :)

KISSDB is good if you want space-efficient relatively fast write-once/read-many storage of keys mapped to values. It's not a good choice if you need searches, indexes, delete, structured storage, or widely varying key/value sizes. It's also probably not a good choice if you need a long-lived database for critical data, since it lacks recovery features and is brittle if its internals are modified. It would be better for a cache of data that can be restored or "re-learned," such as keys, Bitcoin transactions, nodes on a peer-to-peer network, log analysis results, rendered web pages, session cookies, auth tokens, etc.

如果你想要映射到值的键的空间效率相对较快的一次写入/多次读取存储，那么 KISSDB 是很好的选择。如果你需要搜索、索引、删除、结构化存储或广泛变化的键/值大小，这不是一个好的选择。如果你需要一个用于关键数据的长寿命数据库，它也可能不是一个好的选择，因为它缺乏恢复功能，并且如果修改其内部结构会很脆弱。可以恢复或“重新学习”的数据缓存会更好，例如密钥、比特币交易、对等网络上的节点、日志分析结果、呈现的网页、会话 cookie、身份验证令牌， 等等。

KISSDB is in the public domain as according to the [Creative Commons Public Domain Dedication](http://creativecommons.org/publicdomain/zero/1.0/). One reason it was written was the poverty of simple key/value databases with wide open licensing. Even old ones like GDBM have GPL, not LGPL, licenses.

根据知识共享公共领域奉献，KISSDB 属于公共领域。编写它的一个原因是简单的键/值数据库缺乏广泛的开放许可。甚至像 GDBM 这样的老版本也有 GPL，而不是 LGPL，许可证。

See comments in kissdb.h for documentation. Makefile can be used to build a test program on systems with gcc.

请参阅kissdb.h文档中的注释。Makefile可以用来在使用gcc的系统上构建一个测试程序。

Author: Adam Ierymenko / ZeroTier Networks LLC
