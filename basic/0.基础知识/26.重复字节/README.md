重复字节

内核中可以查看
include/linux/kernel.h

kernel 5.8

x不能大于0xff

测试用例
0x5f REPEAT_BYTE 0x5f5f5f5f
0xf8 REPEAT_BYTE 0xf8f8f8f8
0x66 REPEAT_BYTE 0x66666666

