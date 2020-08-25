#include <stdio.h>
#include <string.h>
#include <stdarg.h> 

/************************************************************************/
/*                                                                      */
/************************************************************************/
int sumi(int c, ...)
{  
    va_list argptr;
    va_start(argptr, c); //初始化变元指针  
    int sum = c;
    
    c = va_arg(argptr, int); //作为下一个参数类型的参数类型，返回不定参数  
    //c保存第一个不定参数  
    printf("%d\n", c);  
    while(0 != c) //main函数中最后传入的是0
    {  
        sum = sum + c;  
        c = va_arg(argptr, int);  
    }  
    va_end(argptr);
    
    return sum;  
}

double sum_series(int num, ...)  
{  
    double sum = 0.0, t;
    va_list argptr;
    
    va_start(argptr, num);//初始化变元指针
    
    while (num--)  
    {  
        t = va_arg(argptr, double);  
        sum = sum + t;  
    }  
    va_end(argptr);
    
    return sum;  
} 
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int i;
    double d;
    
    i = sumi(1,2,3,4,5,6,7,8,9,0);
    printf("%d\n", i);  
    
    d = sum_series(4, 1/3.0, 1/4.0, 1/5.0, 1/6.0);  
    printf("%f\n", d);  
    
    return 0;
}