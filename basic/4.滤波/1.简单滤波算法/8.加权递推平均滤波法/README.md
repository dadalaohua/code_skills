# 加权递推平均滤波法 

方法解析：

是对递推平均滤波法的改进，即不同时刻的数据加以不同的权

通常是，越接近现时刻的数据，权取得越大，给予新采样值的权系数越大，则灵敏度越高，但信号平滑度越低。

 

优点：

适用于有较大纯滞后时间常数的对象，和采样周期较短的系统

 

缺点:

 对于纯滞后时间常数较小，采样周期较长，变化缓慢的信号，不能迅速反应系统当前所受干扰的严重程度，滤波效果差。

```c
#define N 12

/* coe数组为加权系数表*/ 
int coe[N] = {1,2,3,4,5,6,7,8,9,10,11,12};
int sum_coe = 1+2+3+4+5+6+7+8+9+10+11+12;

int filter(void)
{  
    int count;
    int value_buf[N];
    int sum = 0;
    
    for(count = 0; count < N; count++)
    {  
        value_buf[count] = get_ad();
        //delay();
    }
    
    for (count = 0; count < N; count++)
        sum += value_buf[count]*coe[count];
    
    return (sum/sum_coe);
}
```

