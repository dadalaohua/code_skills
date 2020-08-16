四舍五入整数除法

DIV_ROUND_CLOSEST_ULL的功能和DIV_ROUND_CLOSEST一样
但是被除数为u64类型，除数必须为32bit的数

被除数，除数均要为正数

内核中可以查看
include/linux/kernel.h 
include/asm-generic/div64.h 