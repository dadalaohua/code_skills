用于动态管理数据内存块
demo例程中，每个内存块为48Byte，共60个
调用data_block_mem_malloc可以申请内存块
比如ptr = data_block_mem_malloc(3);就是申请3个内存块，每个内存块48Byte
使用完后可以调用data_block_mem_free进行释放
申请的内存块地址是连续的，比如申请3个内存块，共3*48Byte的空间都是连续的

使用前可以先调用data_block_mem_init进行初始化，将数据初始化为0
不调用的话，内存中为脏数据

调用data_block_mem_remain获取剩余数据内存块数量

调用data_block_mem_offset(ptr);获取该指针指向的地址分配的数据内存块数量