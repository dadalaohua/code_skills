类型检查

内核中可以查看
include/linux/typecheck.h 

typeof是取变量的类型
如果 int x;
typecheck(double,x);
展开之后就是
double __dummy;
int        __dummy2; 
 (void)(&__dummy == &__dummy2); 
& 是取地址；
这样的话，上面那句比较就会出错或编译器给出警告，因为是讲一个double型的指针和一个int型的指针比较，没法编译的，编译器会提示

如果typecheck（int，x）
就都正常编译，然后最后的数据1，赋值给调用者

整个宏定义其实是一个表达式，不是函数，无所谓返回值，这个值是这个表达式的值，复合表达式，取最后一个表达式的值，作为复杂表达式的值。所以这里整个表达式的值就是最后一个表达式的值，也就是1