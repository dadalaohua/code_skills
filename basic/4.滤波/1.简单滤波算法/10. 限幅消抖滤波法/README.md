# 限幅消抖滤波法

方法： 
  相当于“限幅滤波法”+“消抖滤波法” 
  先限幅，后消抖。 
优点： 
  继承了“限幅”和“消抖”的优点； 
  改进了“消抖滤波法”中的某些缺陷，避免将干扰值导入系统。 
缺点： 
  对于快速变化的参数不宜。

```c
#define N 12
#define THRESHOLD  10

int value = 55;

int filter(void)
{  
    int count = 0;
    int new_value;
    
    new_value = get_ad();
    
    if ((value - new_value > THRESHOLD) || (new_value - value > THRESHOLD))
        return value;
    
    while (value != new_value)
    {  
        count++;
        if (count >= N)
            return new_value;
        
        //delay();
        
        new_value = get_ad();
    }
    
    return value;
}
```

