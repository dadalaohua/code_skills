# 限幅滤波算法

方法解析：
根据经验判断，确定两次采样允许的最大偏差值（设定为A），每次检测到新值时判断：
如果本次值与上次值之差<=A，则本次值有效，
如果本次值与上次值只差>A,则本次值无效，放弃本次值，用上次值代替本次值。

优点：
能有效克服因偶然因素引起的脉冲干扰

缺点：

无法抑制那种周期性的干扰，平滑度差

```c
#define THRESHOLD  10

int value = 55;

int filter(void)
{  
    int new_value;
    
    new_value = get_ad();
    if ((new_value - value > THRESHOLD) || (value - new_value > THRESHOLD))
          return value;

    value = new_value;
    
    return value;
}
```