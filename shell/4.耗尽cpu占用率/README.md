# 耗尽cpu占用率

```sh
for i in `seq 1 $(cat /proc/cpuinfo |grep "physical id" |wc -l)`; do dd if=/dev/zero of=/dev/null & done
```

说明:cat /proc/cpuinfo |grep "physical id" | wc -l 可以获得CPU的个数,　我们将其表示为N.

seq 1 N 用来生成１到Ｎ之间的数字

for i in `seq 1 N`; 就是循环执行命令,从１到N dd if=/dev/zero of=/dev/null 

执行dd命令,　输出到/dev/null, 实际上只占用CPU,　没有IO操作.

由于连续执行N个(N是CPU个数)的dd 命令, 且使用率为100%,这时调度器会调度每个dd命令在不同的CPU上处理.

最终就实现所有CPU占用率100%

