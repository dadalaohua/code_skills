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
        i = 0x1fbd1df5 + (i >> 1);
        x = *(float*)&i;
        x = 0.5f * x + xhalf / x;
        //x = 0.5f * x + xhalf / x;
        
        return x;
    }
}

int main(int argc, char* argv[])
{
    float i;
    
    for(i = 0; i < 20; i++)
    {
        printf("%f: %f\n", i, MagicSqrt(i));
        printf("%f: %f\n", i, sqrt(i));
    }
    
    return 0;
}