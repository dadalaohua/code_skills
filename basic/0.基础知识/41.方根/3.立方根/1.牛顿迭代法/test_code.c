#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
const float error = 1e-5;

float NewtonCubeRoot(const float num)
{
    float x = num;
    // 如果原值减去近似根的平方大于误差，继续循环
    while (fabs(num - (x * x * x)) >= error)
    {
        // 得到下一个近似根
        x = (2 * x + num / (x * x)) / 3.0;
    }
    return x;
}

int main(int argc, char* argv[])
{
    float i;
    
    for(i = -20; i < 20; i++)
    {
        printf("%f: %f\n", i, NewtonCubeRoot(i));
        printf("%f: %f\n", i, pow(i, 1/3.0));
    }
    
    return 0;
}