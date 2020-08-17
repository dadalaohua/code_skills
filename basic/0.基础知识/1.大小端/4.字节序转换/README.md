字节序转换

在C/C++写网络程序的时候，往往会遇到字节的网络顺序和主机顺序的问题。这是就可能用到htons(), ntohl(), ntohs()，htons()这4个函数。
网络字节顺序与本地字节顺序之间的转换函数：
 
htonl()--"Host to Network Long"
ntohl()--"Network to Host Long"
htons()--"Host to Network Short"
ntohs()--"Network to Host Short"
 
之所以需要这些函数是因为计算机数据表示存在两种字节顺序：NBO与HBO
 
网络字节顺序NBO（Network Byte Order）：
按从高到低的顺序存储，在网络上使用统一的网络字节顺序，可以避免兼容性问题。
 
主机字节顺序（HBO，Host Byte Order）：
     不同的机器HBO不相同，与CPU设计有关，数据的顺序是由cpu决定的,而与操作系统无关。 
如 Intel   x86结构下,short型数0x1234表示为34   12, int型数0x12345678表示为78   56   34   12   
如IBM   power PC结构下,short型数0x1234表示为12   34, int型数0x12345678表示为12   34   56   78
 
由于这个原因不同体系结构的机器之间无法通信,所以要转换成一种约定的数序,也就是网络字节顺序,其实就是如同power   pc那样的顺序 。在PC开发中有ntohl和htonl函数可以用来进行网络字节和主机字节的转换。