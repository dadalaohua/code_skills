# shell

如果你想使用该文件,你的工程中应该支持 printf 这个函数
用法:
在 文件Externfunc.c中
增加一个元素到 functable[] 数组中
  EXPOTRFUNC( 函数别名 , 真正的函数名 , 输入的格式限定符 ,函数简介)
示例:
EXPOTRFUNC(LIST,ExternFunc_list, ,所有能调用的函数列表);
警告: 在输入限定符中 只能使用 ' ' (空格) 对其隔开
在函数别名中不能含有' ' 字符
示例: %d %d 
错误示例 : %d,%d



在shell_cmd.c中添加自定义函数

最后还要在shell.c中的const CALLFUNCTIONTABLE functable[]中添加

