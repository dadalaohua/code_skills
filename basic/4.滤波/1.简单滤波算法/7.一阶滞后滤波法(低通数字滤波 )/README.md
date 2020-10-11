# 一阶滞后滤波法(低通数字滤波 )

方法解析：

取a=0-1

本次滤波结果 = (1-a) * 本次采样值 + a * 上次滤波结果

 

优点：

对周期性干扰具有良好的抑制作用，适用于波动频率较高的场合

 

缺点：

相位滞后，灵敏度低，滞后程度取决于a值的大小，不能消除滤波频率高于采样频率的1/2的干扰信号

```c
#define a 50

int value = 55;

/* 假定基数为100，a=0~100 */ 
int filter(void)
{
    int new_value;
    
    new_value = get_ad();
    
    value = (100 - a) * value + a * new_value;
    value /= 100;
    
    return value;
} 
```

