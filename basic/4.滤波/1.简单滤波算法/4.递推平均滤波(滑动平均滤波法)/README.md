# 递推平均滤波（滑动平均滤波法）

方法解析：

把连续取N个采样值看成一个队列，队列的长度固定为N，每次采样到一个新数据放入队尾，并扔掉原来队首的一次数据（先进先出）。

把队列中的N个数据进行算术平均运算，就可获得新的滤波结果。N值的选取：一般12.

 

优点：

对周期性干扰有良好的抑制作用，平滑度高，适应于高频振荡的系统



缺点：

灵敏度低，对偶然出现的脉冲性干扰的抑制作用较差。不易消除由于脉冲干扰所引起打的采样值偏差，不适用于脉冲干扰比较严重的场合

浪费RAM

```c
#define N 12

int value_buf[N];
int value_sn = 0;

int filter(void) 
{  
    int count;
    int sum = 0;
    
    value_buf[value_sn++] = get_ad();
    
    if (value_sn == N)
        value_sn = 0;
    
    for(count = 0; count < N; count++)
        sum += value_buf[count];
    
    return (sum/N);
}

void value_buf_init(void)
{
    int count;
    
    for(count = 0; count < N; count++)
        value_buf[count] = get_ad();
}
```

