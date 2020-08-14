gcc -o test_code test_code.c animal.c
test_code.c: 在函数‘main’中:
test_code.c:19:1: 错误： 毗连“->”和“Animal”不能给出一个有效的预处理标识符
test_code.c:25:1: 错误： 毗连“->”和“Animal”不能给出一个有效的预处理标识符
test_code.c:28:1: 错误： 毗连“->”和“IMoveable”不能给出一个有效的预处理标识符
test_code.c:31:1: 错误： 毗连“->”和“IMoveable”不能给出一个有效的预处理标识符
test_code.c:34:1: 错误： 毗连“->”和“IMoveable”不能给出一个有效的预处理标识符

用gcc编译不成功
animal.c: In function ?.ish_ctor?.
lw_oopc.h:153:52: error: pasting "->" and "Animal" does not give a valid preprocessing token
#define SUPER_PTR(cthis, father) ((father*)(&(cthis->##father))) 

解决方式
#define SUPER_PTR(cthis, father) ((father*)(&(cthis->##father)))
修改宏为：
#define SUPER_PTR(cthis, father) ((father*)(&(cthis->father)))

VC下不用修改可以编译通过；gcc不行，原因不理解；不过去掉##可以，结果也是正确的。 