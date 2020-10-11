# 限幅平均滤波法 

方法： 
  相当于“限幅滤波法”+“递推平均滤波法”； 
  每次采样到的新数据先进行限幅处理； 
  再送入队列进行递推平均滤波处理。 

优点： 
  融合了两种滤波法的优点； 
  对于偶然出现的脉冲性干扰，可消除由于脉冲干扰所引起的采样值偏差。 

缺点： 
  比较浪费RAM。

```c
#define N 12
#define THRESHOLD  10

int value_buf[N];
int value_sn = 0;
int value_average = 0;

int filter(void) 
{  
    int count;
    int sum = 0;
    int value;
    
    value = get_ad();
    
    if ((value - value_buf[value_sn] > THRESHOLD) || (value_buf[value_sn] - value > THRESHOLD))
        return value_average;
    
    value_buf[value_sn++] = value;

    if (value_sn == N)
        value_sn = 0;
    
    for(count = 0; count < N; count++)
        sum += value_buf[count];
    
    value_average = sum/N;
    
    return value_average;
}

void value_buf_init(void)
{
    int count;
    int sum = 0;
    
    for(count = 0; count < N; count++)
        value_buf[count] = get_ad();
    
    for(count = 0; count < N; count++)
        sum += value_buf[count];
    
    value_average = sum/N;
}
```

