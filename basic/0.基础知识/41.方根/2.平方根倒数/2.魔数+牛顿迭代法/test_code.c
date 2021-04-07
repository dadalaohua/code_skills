#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
float MagicSqrt(float x)
{
    if (x < 0)
    {
        return -1;
    }
    else
    {
        float xhalf = 0.5f * x;
        int i = *(int*)&x;         // evil floating point bit level hacking
        i = 0x5f3759df - (i >> 1);  // what the fuck?
        x = *(float*)&i;
        x = x*(1.5f-(xhalf*x*x));
        //x = x*(1.5f-(xhalf*x*x));
        return x;
    }
}

int main(int argc, char* argv[])
{
    float i;
    
    for(i = 1; i < 20; i++)
    {
        printf("%f: %f\n", i, MagicSqrt(i));
        printf("%f: %f\n", i, 1/sqrt(i));
    }
    
    return 0;
}