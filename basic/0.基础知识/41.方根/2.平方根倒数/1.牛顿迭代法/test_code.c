#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
const float error = 1e-5;

float NewtonInvSqrt(const float num)
{
    if (num > 0)
    {
        float x = 1/num;
        float xhalf = 0.5f * num;
        // 如果原值减去近似根的平方大于误差，继续循环
        while (fabs(1.0f - num * x * x) >= error)
        {
            x = x*(1.5f-(xhalf*x*x));
        }

        return x;
    }
    else
    {
        return -1;
    }
}

int main(int argc, char* argv[])
{
    float i;
    
    for(i = 1; i < 10; i++)
    {
        printf("%f: %f\n", i, NewtonInvSqrt(i));
        printf("%f: %f\n", i, 1/sqrt(i));
    }
    
    return 0;
}