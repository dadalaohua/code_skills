#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
const float error = 1e-5;

float NewtonSqrt(const float num)
{
    if (num < 0)
    {
        return -1;
    }
    else
    {
        float x = num;
        // 如果原值减去近似根的平方大于误差，继续循环
        while (fabs(num - x * x) >= error)
        {
            // 得到下一个近似根
            x = (x + num / x) / 2.0;
        }
        return x;
    }
}

int main(int argc, char* argv[])
{
    float i;
    
    for(i = 0; i < 20; i++)
    {
        printf("%f: %f\n", i, NewtonSqrt(i));
        printf("%f: %f\n", i, sqrt(i));
    }
    
    return 0;
}